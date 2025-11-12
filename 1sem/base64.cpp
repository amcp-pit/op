#include <iostream>
#include <fstream>

char base64Char(unsigned char b){
	b &= 0x3F;

	char alphabetBase64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	return alphabetBase64[b];
/*
	if ( b < 26 ) return 'A' + b;
	if ( b < 52 ) return 'a' + (b - 26);
	if ( b < 62 ) return '0' + (b - 52);
	if ( b == 62) return '+';
	return '/';
*/
}

int base64Encode(char inStr[], int len, char outStr[]){
	unsigned char a1, a2, a3;
	unsigned char b1, b2, b3, b4;
	int inIndex = 0;
	int outIndex = 0;
	for(inIndex = 0; inIndex < len; inIndex+=3){
		a1 = a2 = a3 = 0;
		a1 = inStr[inIndex];
		if (inIndex+1 < len) a2 = inStr[inIndex+1];
		if (inIndex+2 < len) a3 = inStr[inIndex+2];

		b1 = a1 >> 2;
		b2 = ( (a1 & 0x3) << 4 ) | (a2 >> 4);
        b3 = ( (a2 & 0xF) << 2 ) | (a3 >> 6);
		b4 = a3 & 0x3F;

		outStr[outIndex++] = base64Char(b1);
        outStr[outIndex++] = base64Char(b2);
        outStr[outIndex++] = (inIndex+1 < len) ? base64Char(b3) : '=';
        outStr[outIndex++] = (inIndex+2 < len) ? base64Char(b4) : '=';
	}
	return outIndex;
}

int main(int argc, char* argv[]){
	if (argc != 3){
		std::cout << "Use for encoding:\n";
		std::cout << "\t" << argv[0] << " source destination\n";
		return 1;
	}

	std::ifstream inFile(argv[1], std::ios_base::binary);
	if (!inFile){
		std::cout << "Can not open file '" << argv[1] <<"'\n";
		return 2;
	}

    std::ofstream outFile(argv[2]);
    if (!outFile){
        std::cout << "Can not write to file '" << argv[2] <<"'\n";
		inFile.close();
        return 3;
    }

	const int block_size = 20;
	char inStr[3 * block_size];
	char outStr[4 * block_size];
	int counter = 0;

	while(inFile.peek() != EOF){
		inFile.read(inStr, sizeof(inStr));
		int s = static_cast<int>(inFile.gcount());
		s = base64Encode(inStr, s, outStr);
		outFile.write(outStr, s);
		counter += s;
		if (counter >= 80){
			outFile.put('\n');
			counter = 0;
		}
	}
	inFile.close();
	outFile.close();
	std::cout << "File " << argv[1] << " encoded" << std::endl;
	return 0;
}
