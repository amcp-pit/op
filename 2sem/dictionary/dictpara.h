#ifndef _DICTPARA_25_
#define _DICTPARA_25

#include "stroka.h"
class DictPara{
	stroka word_;
	stroka translate_;
public:
	DictPara(): word_(""), translate_("") {}
	DictPara(const stroka& word, const stroka& translate) : 
			word_(word), translate_(translate){}
	DictPara(stroka&& word, stroka&& translate) : 
			word_(std::move(word)), translate_(std::move(translate)) {}
	DictPara(DictPara&& other) : word_(std::move(other.word_)),
								 translate_(std::move(other.translate_)) {}

	DictPara& operator=(const DictPara& other){
		// Приходится реализовывать из-за наличия operator=(DictPara&&)
		if (this!=&other){
			word_ = other.word_;
			translate_ = other.translate_;
		}
		return *this;
	}
	
	DictPara& operator=(DictPara&& other){
		if (this!=&other){
			word_ = std::move(other.word_);
			translate_ = std::move(other.translate_);
		}
		return *this;
	}
	const stroka& get_word() const { return word_; }
	const stroka& get_translate() const { return translate_; }
	bool operator==(const DictPara& other) const { return word_ == other.word_; }
    bool operator!=(const DictPara& other) const { return word_ != other.word_; }
    bool operator<(const DictPara& other) const { return word_ < other.word_; }
};

#endif