#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <iostream>
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
		if(line_tokens[0].back() == ':')
			labels[line_tokens[0].substr(0, line_tokens[0].length() - 1)] = address;
		else{
			token_list.push_back(line_tokens);
			++ address;
		}
	}
	int line_n = token_list.size();

	FILE* out_s;
	
	if(out_type == BIN)
		out_s = fopen(out, "wb");

	for(int i = 0; i < line_n; i ++){
		WORD inst = Instruction(token_list[i], labels, i).getCode();
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

	if(out_type == BIN)
		fclose(out_s);

	return 0;
}

