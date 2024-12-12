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
	int actions[4][3] = { {1, 7, 4},
		                  {2, 8, 5},
		                  {1, 7, 4},
		                  {3, 9, 6} 
	                    };
	int states[4][3] = {  {1, 0, 0}, 
		                  {2, 2, 2},
		                  {3, 2, 2},
		                  {0, 0, 0}
	                    };
	int state = 0;
	while ((ch = inFile.get()) != EOF) {
		int col;
		if (ch == '$') {
			col = 0;
		}
		else if (ch == '\\') {
			col = 1;
		}
		else {
			col = 2;
		}
		switch (actions[state][col]) {
		case 1: break;
		case 2: outFile << "<math>";  break;
		case 3: outFile << "</math>";  break;
		case 4: outFile.put(ch);  break;
		case 5: outFile << "<math>";  outFile.put(ch); break;
		case 6: outFile << "</math>";  outFile.put(ch); break;
		case 7:
			outFile.put('\\');
			if (EOF != (ch = inFile.get()))
				outFile.put(ch);
			break;
		case 8: outFile << "<math>";
			outFile.put('\\');
			if (EOF != (ch = inFile.get()))
				outFile.put(ch);
			break;
		case 9:
			outFile << "</math>";
			outFile.put('\\');
			if (EOF != (ch = inFile.get()))
				outFile.put(ch);
			break;
		}
		state = states[state][col];
	}


	inFile.close();
	outFile.close();
	return 0;
}

