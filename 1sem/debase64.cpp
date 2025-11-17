#include <iostream>
#include <fstream>

bool isBase64(char ch){
    if (ch>='A' && ch<='Z') return true;
    if (ch>='a' && ch<='z') return true;
    if (ch>='0' && ch<='9') return true;
    if (ch=='+') return true;
    if (ch=='/') return true;
    if (ch=='=') return true;
    return false;
}

unsigned char base64Code(char ch){
	if (ch>='A' && ch<='Z') return ch-'A';
	if (ch>='a' && ch<='z') return (ch-'a')+26;
	if (ch>='0' && ch<='9') return (ch-'0')+52;
	if (ch=='+') return 62;
	if (ch=='/') return 63;
	return 64;
}

int base64Decode(char inStr[], int len, char outStr[], int &errno){
	unsigned char b1, b2, b3, b4;
	int inIndex = 0;
	int outIndex = 0;
	int skip = 0;
	for(inIndex = 0; inIndex < len; inIndex+=4){
		b1 = base64Code(inStr[inIndex]);
        b2 = base64Code(inStr[inIndex+1]);
        b3 = base64Code(inStr[inIndex+2]);
        b4 = base64Code(inStr[inIndex+3]);
		if (b3==64) { b3 = 0; b4 = 0; skip = 2;}
		if (b4==64) { b4 = 0; skip = 1;}

		outStr[outIndex++] = (b1 << 2) | (b2 >> 4);
        outStr[outIndex++] = (b2 << 4) | (b3 >> 2);
        outStr[outIndex++] = (b3 << 6) | b4;

		if (skip > 0) break;
	}
	return outIndex - skip;
}

int main(int argc, char* argv[]){
	if (argc != 3){
		std::cout << "Use for decoding:\n";
		std::cout << "\t" << argv[0] << " source destination\n";
		return 1;
	}

	std::ifstream inFile(argv[1]);
	if (!inFile){
		std::cout << "Can not open file '" << argv[1] <<"'\n";
		return 2;
	}

    std::ofstream outFile(argv[2], std::ios_base::binary);
    if (!outFile){
        std::cout << "Can not write to file '" << argv[2] <<"'\n";
		inFile.close();
        return 3;
    }

	char inStr[4];
	char outStr[3];
	int counter = 0;
	int ch;
	while( (ch = inFile.get()) != EOF){
		if (isBase64(ch)){
			inStr[counter++] = ch;
			if (counter==4){
				// Каждые 4 символа BASE64 декодируем
				counter = base64Decode(inStr, 4, outStr);
				outFile.write(outStr, counter);
				counter = 0;
			}
		}
	}
	inFile.close();
	outFile.close();
	std::cout << "File " << argv[1] << " encoded" << std::endl;
	return 0;
}
