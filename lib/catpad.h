#ifndef CATPAD_H
#define CATPAD_H

#include<vector>
#include<string>
#include<map>

typedef unsigned short WORD;


extern WORD parse_immediate(const std::string& s);

class Instruction{
	private:
		WORD inst_code;
	public:
		Instruction(WORD code) : inst_code(code) {}
		Instruction(const std::vector<std::string>& tokens,
				const std::map<std::string, WORD>& labels, WORD address);
		WORD getCode() const{
			return inst_code;
		}
		std::vector<std::string> getTokens(const std::map<std::string, WORD>& labels, WORD address);
};

#endif


