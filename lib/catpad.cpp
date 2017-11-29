#include "catpad.h"

using namespace std;

inline bool look_up_label(const map<string, WORD>& labels, const string& l, WORD& res){
	if(labels.find(l) != labels.end()){
		res = labels[l];
		return true;
	}
	return false;
}

inline bool is_identifier(const string& token){
	return token[0] < '0' || token[0] > '9'; // not a number
}

Instruction::Instruction(const vector<string>& tokens, const map<string, WORD>& labels, WORD address){
	
}

vector<string> Instruction::getTokens(const map<string, WORD>& labels, WORD address){
	switch(code >> 11){
		
	}
}


