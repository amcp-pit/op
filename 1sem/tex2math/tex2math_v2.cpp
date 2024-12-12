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
    int state = 1; // 1-text,   2-start_math, 3-math, 4-end_math
    int skip = 0;

    while ((ch = inFile.get()) != EOF) {
        if (skip == 1) {
            outFile.put(ch);
            skip = 0;
            continue;
        }

        if (state == 1) {
            if (ch == '\\') {
                outFile.put(ch);
                skip = 1;
            }
            else if (ch == '$') {
                state = 2;
            }
            else {
                outFile.put(ch);
            }
        }
        else if (state == 2) {
            if (ch == '$') {
                outFile << "<math>";
                state = 3;
            }
            else if (ch == '\\') {
                outFile << "<math>";
                outFile.put(ch);
                skip = 1;
                state = 3;
            }
            else {
                outFile << "<math>";
                outFile.put(ch);
                state = 3;
            }
        }
        else if (state == 3) {
            if (ch == '\\') {
                outFile.put(ch);
                skip = 1;
            }
            else if (ch == '$') {
                state = 4;
            }
            else {
                outFile.put(ch);
            }
        }
        else {
            if (ch == '$') {
                outFile << "</math>";
            }
            else if (ch == '\\') {
                outFile << "</math>";
                outFile.put('\\');
                skip = 1;
            }
            else {
                outFile << "</math>";
                outFile.put(ch);
            }
            state = 1;
        }
    }

    if (state > 1) {
        outFile << "</math>";
    }

	inFile.close();
	outFile.close();
	return 0;
}

