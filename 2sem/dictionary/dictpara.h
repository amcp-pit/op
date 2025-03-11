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
	const stroka& get_word() const { return word_; }
	const stroka& get_translate() const { return translate_; }
	bool operator==(const DictPara& other) const { return word_ == other.word_; }
    bool operator!=(const DictPara& other) const { return word_ != other.word_; }
    bool operator<(const DictPara& other) const { return word_ < other.word_; }
};

#endif
