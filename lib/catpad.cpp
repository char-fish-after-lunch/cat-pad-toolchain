#include "catpad.h"

using namespace std;

const WORD INSTR_H_ADDIU = 0b01001;
const WORD INSTR_H_ADDIU3 = 0b01000;
const WORD INSTR_H_B = 0b00010;
const WORD INSTR_H_BEQZ = 0b00100;
const WORD INSTR_H_BNEZ = 0b00101;
const WORD INSTR_H_LI = 0b01101;
const WORD INSTR_H_LW = 0b10011;
const WORD INSTR_H_LW_SP = 0b10010;
const WORD INSTR_H_NOP = 0b00001;
const WORD INSTR_H_SW = 0b11011;
const WORD INSTR_H_SW_SP = 0b11010;
const WORD INSTR_H_INT = 0b11111;
const WORD INSTR_H_ERET = 0b00011;

const WORD INSTR_H_GROUP1 = 0b11101;
const WORD INSTR_H_GROUP2 = 0b01100;
const WORD INSTR_H_GROUP3 = 0b11100;
const WORD INSTR_H_GROUP4 = 0b11110;
const WORD INSTR_H_GROUP5 = 0b00110;


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

static WORD parse_register(const string& s){
	WORD n = 0;
	int len = s.length();
	for(int i = 1; i < len; i ++)
		n = n * 10 + (s[i] - '0');
	return n;
}

static WORD parse_immediate(const string& s){
	int len = s.length();
	int t = 0; // decimal
	if(len > 2){
		if(s[0] == '0' && s[1] == 'x')
			t = 1; // hexadecimal
		else if(s[0] == '0' && s[1] == 'b')
			t = 2; // binary
	}
	
	WORD n = 0;
	if(t == 0){
		for(int i = 0; i < len; i ++)
			n = n * 10 + (s[i] - '0');
	} else if(t == 1){
		for(int i = 2; i < len; i ++){
			if(s[i] >= '0' && s[i] <= '9')
				n = n * 16 + (s[i] - '0');
			else
				n = n * 16 + (s[i] - 'a' + 10);
		}
	} else if(t == 2){
		for(int i = 2; i < len; i ++)
			n = (n << 1) | (s[i] - '0');
	}
	return n;
}

static WORD parse_address(const string& s, const map<string, WORD>& labels, WORD c_addr){
	WORD res;
	if(is_identifier(s)){
		look_up_labels(labels, s, res);
		res -= c_addr + 1;
	} else
		res = parse_immediate(s);

	return res;
}

Instruction::Instruction(const vector<string>& tokens, const map<string, WORD>& labels, WORD address){
	inst_code = 0;

	const string& rec = tokens[0];
	if(rec == "ADDIU"){
		inst_code |= INSTR_H_ADDIU << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_immediate(tokens[2]) & 0b11111111);
	} else if(rec == "ADDIU3"){
		inst_code |= INSTR_H_ADDIU3 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= (parse_immediate(tokens[3]) & 0b1111);
	} else if(rec == "B"){
		inst_code |= INSTR_H_B << 11;
		inst_code |= (parse_address(tokens[1]) & ((1 << 11) - 1));
	} else if(rec == "BEQZ"){
		inst_code |= INSTR_H_BEQZ << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_address(tokens[2]) & 0b11111111);
	} else if(rec == "BNEZ"){
		inst_code |= INSTR_H_BNEZ << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_address(tokens[2]) & 0b11111111);
	} else if(rec == "LI"){
		inst_code |= INSTR_H_LI << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_immediate(tokens[2]) & 0b11111111);
	} else if(rec == "LW"){
		inst_code |= INSTR_H_LW << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= (parse_immediate(tokens[3]) & 0b11111);
	} else if(rec == "LW_SP"){
		inst_code |= INSTR_H_LW_SP << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_immediate(tokens[2]) & 0b11111111);
	} else if(rec == "NOP"){
		inst_code |= INSTR_H_NOP << 11;
	} else if(rec == "SW"){
		inst_code |= INSTR_H_SW << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= (parse_immediate(tokens[3]) & 0b11111);
	} else if(rec == "SW_SP"){
		inst_code |= INSTR_H_SW_SP << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_immediate(tokens[2]) & 0b11111111);
	} else if(rec == "INT"){
		inst_code |= INSTR_H_INT << 11;
		inst_code |= parse_immedate(tokens[1]) & 0b1111;
	} else if(rec == "ERET"){
		inst_code |= INSTR_H_ERET << 11;
	} else if(rec == "AND"){
		inst_code |= INSTR_H_GROUP1 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= 0b01100;
	} else if(rec == "CMP"){
		inst_code |= INSTR_H_GROUP1 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= 0b01010;
	} else if(rec == "JR"){
		inst_code |= INSTR_H_GROUP1 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
	} else if(rec == "MFPC"){
		inst_code |= INSTR_H_GROUP1 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= 0b010 << 5;
	} else if(rec == "OR"){
		inst_code |= INSTR_H_GROUP1 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= 0b01101;
	} else if(rec == "SLLV"){
		inst_code |= INSTR_H_GROUP1 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= 0b00100;
	} else if(rec == "SLTU"){
		inst_code |= INSTR_H_GROUP1 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= 0b00011;
	} else if(rec == "SRLV"){
		inst_code |= INSTR_H_GROUP1 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= 0b00110;
	} else if(rec == "BTEQZ"){
		inst_code |= INSTR_H_GROUP2 << 11;
		inst_code |= 0b000 << 8;
		inst_code |= (parse_address(tokens[1]) & 0b11111111);
	} else if(rec == "ADDSP"){
		inst_code |= INSTR_H_GROUP2 << 11;
		inst_code |= 0b011 << 8;
		inst_code |= (parse_immediate(tokens[1]) & 0b11111111);
	} else if(rec == "BTNEZ"){
		inst_code |= INSTR_H_GROUP2 << 11;
		inst_code |= 0b001 << 8;
		inst_code |= (parse_address(tokens[1]) & 0b11111111);
	} else if(rec == "ADDU"){
		inst_code |= INSTR_H_GROUP3 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= (parse_register(tokens[3]) & 7) << 2;
		inst_code |= 0b01;
	} else if(rec == "SUBU"){
		inst_code |= INSTR_H_GROUP3 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= (parse_register(tokens[3]) & 7) << 2;
		inst_code |= 0b11;
	} else if(rec == "MFIH"){
		inst_code |= INSTR_H_GROUP4 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
	} else if(rec == "MTIH"){
		inst_code |= INSTR_H_GROUP4 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= 0b00000001;
	} else if(rec == "MFCS"){
		inst_code |= INSTR_H_GROUP4 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= 0b11111111;
	} else if(rec == "MFEPC"){
		inst_code |= INSTR_H_GROUP4 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= 0b11111110;
	} else if(rec == "MTEPC"){
		inst_code |= INSTR_H_GROUP4 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= 0b11111100;
	} else if(rec == "SLL"){
		inst_code |= INSTR_H_GROUP5 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= (parse_immediate(tokens[2]) & 7) << 2;
	} else if(rec == "SRL"){
		inst_code |= INSTR_H_GROUP5 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= (parse_immediate(tokens[2]) & 7) << 2;
		inst_code |= 0b10;
	} else if(rec == "SRA"){
		inst_code |= INSTR_H_GROUP5 << 11;
		inst_code |= (parse_register(tokens[1]) & 7) << 8;
		inst_code |= (parse_register(tokens[2]) & 7) << 5;
		inst_code |= (parse_immediate(tokens[2]) & 7) << 2;
		inst_code |= 0b11;
	}
}

vector<string> Instruction::getTokens(const map<string, WORD>& labels, WORD address){
	return vector<string>();
}


