#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include "catpad.h"

using namespace std;

enum OutputType {
	BIN,
	TXTBIN,
	TXTHEX
};

static map<string, WORD> labels;

const char HEX_MAP[17] = "0123456789ABCDEF";

static void printInstruction(WORD inst, OutputType out_type, FILE* out_s){
    switch(out_type){
        case BIN:
            fwrite(&inst, sizeof(WORD), 1, out_s);
            break;
        case TXTBIN:
            for(int j = 15; j >= 0; j --)
                cout << ((inst >> j) & 1);
            cout << endl;
            break;
        case TXTHEX:
            for(int j = 12; j >= 0; j -= 4)
                cout << HEX_MAP[(inst >> j) & 15];
            cout << endl;
            break;
    }
}

int main(int argc, char** argv){
	OutputType out_type = BIN;
	bool error = false;
	char* out;
	if(argc > 1){
		if(strcmp(argv[1], "-tb") == 0)
			out_type = TXTBIN;
		else if(strcmp(argv[1], "-th") == 0)
			out_type = TXTHEX;
		else if(strcmp(argv[1], "-b") == 0){
			if(argc < 3)
				error = true;
			else
				out = argv[2];
		} else
			error = true;
	} else{
		error = true;
	}
	if(error){
		cout << "Usage: catass [-tb|-th|-b output_file]" << endl;
		return 1;
	}

	string line;
	vector<vector<string> > token_list;
	WORD address = 0;
	while(getline(cin, line)){
		vector<string> line_tokens;
		int len = line.length();
		for(int i = 0; i < len; ){
			if(line[i] == ' ' || line[i] == '\t' || line[i] == '\r' || line[i] == '\n')
				++ i;
			else if(line[i] == ';')
				break;
			else {
				string token;
				do{
					token += line[i];
					++ i;
				} while(i < len && line[i] != ' ' && line[i] != '\t' && line[i] != '\r' && line[i] != '\n');
				line_tokens.push_back(token);
			}
		}
		len = line_tokens.size();
		if(len == 0)
			continue;
        if(line_tokens[0] == ".word"){
            address += len - 1;
            token_list.push_back(line_tokens);
        } else if(line_tokens[0] == ".pad"){
            address += parse_immediate(line_tokens[1]);
            token_list.push_back(line_tokens);
        } else if(line_tokens[0] == ".ascii"){
            address += len - 2;
            for(int i = 1; i < len; i ++)
                address += line_tokens[i].length();
            token_list.push_back(line_tokens);
        } else if(line_tokens[0].back() == ':')
			labels[line_tokens[0].substr(0, line_tokens[0].length() - 1)] = address;
        else if(gen_upper(line_tokens[0]) == "LLI"){
            token_list.push_back(line_tokens);
            address += 4;
        } else{
			token_list.push_back(line_tokens);
			++ address;
		}
	}
	int line_n = token_list.size();

	FILE* out_s;
	
	if(out_type == BIN)
		out_s = fopen(out, "wb");

    address = 0;
    for(vector<string> line_tokens : token_list){
        int len = line_tokens.size();
        if(line_tokens[0] == ".word"){
            // put the words into this instruction position
            for(int j = 1; j < len; j ++){
                printInstruction(parse_immediate(line_tokens[j]), out_type, out_s);
                ++ address;
            }
        } else if(line_tokens[0] == ".pad"){
            unsigned short pad_cnt = parse_immediate(line_tokens[1]);
            for(int j = 0; j < pad_cnt; j ++)
                printInstruction(0, out_type, out_s);
            address += pad_cnt;
        } else if(line_tokens[0] == ".ascii"){
            for(int j = 1; j < len; j ++){
                if(j > 1){
                    printInstruction((unsigned short)' ', out_type, out_s);
                    ++ address;
                }
                for(char k : line_tokens[j]){
                    printInstruction((unsigned short)k, out_type, out_s);
                    ++ address;
                }
            }            
        } else if(gen_upper(line_tokens[0]) == "LLI"){
            char sn[20];
            WORD imme = parse_address(line_tokens[2], labels, address);
            sprintf(sn, "%u", (imme) >> 8);
            printInstruction(Instruction(vector<string>({"LI", line_tokens[1], sn}), labels, address).getCode(),
                    out_type, out_s);
            printInstruction(Instruction(vector<string>({"SLL", line_tokens[1], line_tokens[1], "0x0000"}), labels, address).getCode(),
                        out_type, out_s);
            sprintf(sn, "%u", imme & 0b11111111);
            printInstruction(Instruction(vector<string>({"LI", "R6", sn}), labels, address).getCode(),
                    out_type, out_s);
            printInstruction(Instruction(vector<string>({"ADDU", line_tokens[1], "R6", line_tokens[1]}), labels, address).getCode(),
                    out_type, out_s);
            address += 4;
        } else{
            printInstruction(Instruction(line_tokens, labels, address).getCode(),\
                out_type, out_s);
            ++ address;
        }
	}

	if(out_type == BIN)
		fclose(out_s);

	return 0;
}

