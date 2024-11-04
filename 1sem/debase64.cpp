/*
Декодирование файла из BASE64.
Имена входного и выходного файлов задаются в командной строке.
*/

#include <iostream>
#include <fstream>

unsigned char base64Code(char ch){
	if (ch>='A' && ch<='Z') return ch-'A';
	if (ch>='a' && ch<='z') return (ch-'a')+26;
	if (ch>='0' && ch<='9') return (ch-'0')+52;
	if (ch=='+') return 62;
	if (ch=='/') return 63;
	return 64;
}

bool isBase64(char ch){
	if (ch>='A' && ch<='Z') return true;
	if (ch>='a' && ch<='z') return true;
	if (ch>='0' && ch<='9') return true;
	if (ch=='+') return true;
	if (ch=='/') return true;
	if (ch=='=') return true;
	return false;
}

int base64Decode(char inStr[], int Len, char outStr[]){
	if (Len%4>0) throw "Wrang data for decoding";

	int inIndex = 0, outIndex = 0; 
	unsigned char b1,b2,b3,b4;
	int s = 0;
	for(inIndex = 0; inIndex < Len; inIndex += 4){
		b1 = base64Code(inStr[inIndex]);
		b2 = base64Code(inStr[inIndex+1]);
		b3 = base64Code(inStr[inIndex+2]);
		b4 = base64Code(inStr[inIndex+3]);
		if (b3==64){ b3 = 0; b4 = 0; s = 2;}
		if (b4==64){ b4 = 0; s = 1;}
		outStr[outIndex++] = (b1<<2) | (b2>>4);
		outStr[outIndex++] = (b2<<4) | (b3>>2);
		outStr[outIndex++] = (b3<<6) | b4;
		if (s > 0) break;
	}
	return outIndex-s;
}


void help(const char* cmdname) {
	std::cout << "Use for decoding:\n";
	std::cout << "\t" << cmdname << " source_file destination_file" << std::endl;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		help(argv[0]);
		return 1;
	}

	std::ifstream inFile(argv[1]);  // На входе текстовый файл.
	if (!inFile) {
		std::cout << "Can not open file "<< argv[1] << std::endl;
		return 1;
	}
	std::ofstream outFile(argv[2], std::ios_base::binary); // На выходе может быть произвольный файл
	if (!outFile) {
		std::cout << "Can not open file "<< argv[2] << std::endl;
		inFile.close();
		return 2;
	}

	// Decode
	char inStr[4], outStr[3];
	int ch;
	int cnt = 0;
	while( (ch=inFile.get()) != EOF ){
		// Во входном потоке могут быть не только символы из BASE64.
		// Например, могут быть символы перевода строки. Их пропускаем.
		if (isBase64(ch)){
			inStr[cnt++] = ch;
			if (cnt==4) {
				// Каждые 4 символа из BASE64 будем преобразовывать в 3 байта.
				cnt = base64Decode(inStr, 4, outStr);
				outFile.write(outStr, cnt);
				cnt=0;
			}
		}
	}

	inFile.close();
	outFile.close();
	std::cout<< "File " << argv[1] << " encoded - OK" <<std::endl;

	return 0;
}