#pragma once
#include "stroka.h"

class dictPara{
	stroka word_;
	stroka translate_;
public:
	dictPara(): word_(""), translate_("") {}
	dictPara(const stroka& word, const stroka& translate) 
		: word_(word), translate_(translate) {}
	const stroka& get_word() const {return word_;}
	const stroka& get_translate() const {return translate_;}
	bool operator==(const dictPara &right) const{
		return word_==right.word_;
	}
	bool operator!=(const dictPara &right) const{
		return word_!=right.word_;
	}
	bool operator<(const dictPara &right) const{
		return word_<right.word_;
	}
};

#include <iostream>
std::ostream& operator << (std::ostream& out, const dictPara& X);

#include <fstream>
std::ifstream& operator>>(std::ifstream& in, dictPara& X);