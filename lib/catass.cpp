#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "catpad.h"

using namespace std;

enum OutputType {
	BIN,
	TXTBIN,
	TXTDEC,
	TXTHEX
};

static map<string, WORD> labels;

int main(int argc, char** argv){
	OutputType out_type = BIN;
	if(argc > 1){
		if(strcmp(argv[1], "-tb") == 0)
			out_type = TXTBIN;
		else if(strcmp(argv[1], "-td") == 0)
			out_type = TXTDEC;
		else if(strcmp(argv[1], "-th") == 0)
			out_type = TXTHEX;
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
	for(int i = 0; i < line_n; i ++){
		WORD inst = Instruction(token_list[i], labels, i).getCode();
		for(int j = 15; j >= 0; j --)
			cout << ((inst >> j) & 1);
		cout << endl;
	}

	return 0;
}

