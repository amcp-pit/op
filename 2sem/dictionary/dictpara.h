#pragma once
#include "stroka.h"

class dictPara{
	stroka word_;
	stroka translate_;
public:
	dictPara(): word_(""), translate_("") {}
	dictPara(const stroka& word, const stroka& translate) 
		: word_(word), translate_(translate) {}
	dictPara(const dictPara& other): word_(other.word_),
								translate_(other.translate_) {}
	dictPara(dictPara&& other): word_(std::move(other.word_)),
								translate_(std::move(other.translate_)) {}

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

	dictPara& operator=(const dictPara& other){
		if (this != &other){
			word_ = other.word_;
			translate_ = other.translate_;
		}
		return *this;
	}

	dictPara& operator=(dictPara&& other){
		if (this != &other){
			word_ = std::move(other.word_);
			translate_ = std::move(other.translate_);
		}
		return *this;
	}
};

#include <iostream>
std::ostream& operator << (std::ostream& out, const dictPara& X);

#include <fstream>
std::ifstream& operator>>(std::ifstream& in, dictPara& X);