#include "dictpara.h"
std::ostream& operator << (std::ostream& out, const dictPara& X){
	out<< X.get_word()<<": "<<X.get_translate() << std::endl;
	return out;
}

std::ifstream& operator>>(std::ifstream& in, dictPara& X){
	char buf[1024];
	in.getline(buf, 1024);
	char* p=buf;
	while((*p!='\t') && (*p!='\0')){
		++p;
	}
	if(*p){
		*p = '\0';
		++p;
	}
	X = dictPara(buf, p);
	return in;
}
