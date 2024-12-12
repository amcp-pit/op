#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Use:\n\t"<< argv[0] << " source destination\n";
		return 0;
	}

	std::ifstream inFile;
	std::ofstream outFile;

	inFile.open(argv[1]);
	if (!inFile) {
		std::cout << "Can not open file '" << argv[1] << "'\n";
		return 1;
	}

	outFile.open(argv[2]);
	if (!outFile) {
		std::cout << "Can not open file '" << argv[2] << "'\n";
		return 1;
	}

	int ch;
	int state = 1;
	while ((ch = inFile.get()) != EOF) {
		if (ch == '\\') {
			switch (state) {
			case 2: outFile << "<math>"; state = 3; break;
			case 4: outFile << "</math>"; state = 1; break;
			}
			outFile.put(ch);
			if (EOF != (ch = inFile.get())) {
				outFile.put(ch);
			}
		}
		else if (ch == '$') {
			switch (state) {
			case 1: state = 2; break;
			case 2: outFile << "<math>"; state = 3; break;
			case 3: state = 4; break;
			case 4: outFile << "</math>"; state = 1; break;
			}
		}
		else {
			switch (state) {
			case 2: outFile << "<math>"; state = 3; break;
			case 4: outFile << "</math>"; state = 1; break;
			}
			outFile.put(ch);
		}
	}
	if (state == 3) outFile << "</math>";

	inFile.close();
	outFile.close();
	return 0;
}

