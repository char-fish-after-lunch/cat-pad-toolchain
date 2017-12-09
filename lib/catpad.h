#ifndef CATPAD_H
#define CATPAD_H

#include<vector>
#include<string>
#include<map>
#include<algorithm>

typedef unsigned short WORD;


inline bool is_identifier(const std::string& token){
	return token[0] < '0' || token[0] > '9'; // not a number
}

inline std::string gen_upper(const std::string& s){
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(), std::ptr_fun<int, int>(std::toupper));
	return res;
}


inline bool look_up_label(const std::map<std::string, WORD>& labels, const std::string& l, WORD& res){
	if(labels.find(l) != labels.end()){
		res = labels.at(l);
		return true;
	}
	return false;
}



extern WORD parse_immediate(const std::string& s);
extern WORD parse_register(const std::string& s);
extern WORD parse_address(const std::string& s, const std::map<std::string, WORD>& labels, WORD c_addr);

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


