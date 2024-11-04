/*
Кодирование BASE64.
Имена входного и выходного файлов задаются в командной строке.
*/

#include <iostream>
#include <fstream>

char base64Char(unsigned char b){
	b &= 0x3F;
	/*
	char base64Alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	return base64Alphabet[b];
	*/
	if (b < 26) return 'A' + b;
	if (b < 52) return 'a' + (b - 26);
	if (b < 62) return '0' + (b - 52);
	if (b == 62) return '+';
	return '/';
}

int base64Encode(char inStr[], int Len, char outStr[]){
	unsigned char a1, a2, a3;
	unsigned char b1, b2, b3, b4;
	int inIndex=0, outIndex=0;
	for(inIndex = 0; inIndex < Len; inIndex+=3){
		a1 = a2 = a3 = 0;
		a1 = inStr[inIndex];
		if (inIndex+1 < Len) a2 = inStr[inIndex+1];
		if (inIndex+2 < Len) a3 = inStr[inIndex+2];

		b1 = a1 >> 2;
		b2 = ( (a1 & 0x3) << 4 ) | (a2 >> 4);
		b3 = ( (a2 & 0xF) << 2 ) | (a3 >> 6);
		b4 = a3 & 0x3F;

		outStr[outIndex++] = base64Char(b1);
		outStr[outIndex++] = base64Char(b2);
		outStr[outIndex++] = (inIndex+1<Len) ? base64Char(b3) : '=';
		outStr[outIndex++] = (inIndex+2<Len) ? base64Char(b4) : '=';
	}
	return outIndex;
}


void help(const char* cmdname) {
	std::cout << "Use for encoding:\n";
	std::cout << "\t " << cmdname << " source_file destination_file" << std::endl;
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		help(argv[0]);
		return 1;
	}

	std::ifstream inFile(argv[1], std::ios_base::binary); // Входной файл может быть любым.
	if (!inFile) {
		std::cout << "Can not open file "<< argv[1] << std::endl;
		return 1;
	}
	std::ofstream outFile(argv[2]);  // На выходе получается текстовый файл.
	if (!outFile) {
		std::cout << "Can not open file "<< argv[2] << std::endl;
		inFile.close();
		return 2;
	}

	const int block_size = 20;   // Читать из входного файла будем блоками
	char inStr[ 3*block_size ];  // Размер блока будет (3*block_size) байт
	char outStr[ 4*block_size ]; // Так как в BASE64 из 3 байт получаем 4 символа из base64,
								 // то на выходе будет блок (4*block_size) байт
	int counter = 0;
	while(inFile.peek()!=EOF){
		inFile.read(inStr, 3*block_size); // Пытаемся прочитать 3*block_size байт
		int s = inFile.gcount();          // Сколько фактически было прочитано байт
		s = base64Encode(inStr, s, outStr);
		outFile.write(outStr, s);
		counter += s;
		if (counter >= 80) {
			outFile << "\n";
			counter = 0;
		}
	}
	inFile.close();
	outFile.close();
	std::cout<< "File " << argv[1] << " encoded - OK" <<std::endl;

	return 0;
}