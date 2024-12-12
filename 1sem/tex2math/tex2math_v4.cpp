#include <iostream>
#include <fstream>

std::ifstream inFile;
std::ofstream outFile;

void (*state)(int);
void text(int);
void math(int);
void math_start(int);
void math_stop(int);


int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Use:\n\t" << argv[0] << " source destination\n";
		return 0;
	}

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
	state = text;
	while ((ch = inFile.get()) != EOF) {
		state(ch);
	}

	inFile.close();
	outFile.close();
	return 0;
}

void text(int ch) {
	switch (ch) {
	case '\\':
		outFile.put(ch);
		if ((ch = inFile.get()) != EOF) {
			outFile.put(ch);
		}
		break;
	case '$': state = math_start; break;
	default: outFile.put(ch);
	}
}

void math_start(int ch) {
	outFile << "<math>";
	switch (ch) {
	case '\\':
		outFile.put(ch);
		if ((ch = inFile.get()) != EOF) {
			outFile.put(ch);
		}
		break;
	case '$': break;
	default: outFile.put(ch);
	}
	state = math;
}

void math(int ch) {
	switch (ch) {
	case '\\':
		outFile.put(ch);
		if ((ch = inFile.get()) != EOF) {
			outFile.put(ch);
		}
		break;
	case '$': state = math_stop; break;
	default: outFile.put(ch);
	}
}

void math_stop(int ch) {
	outFile << "</math>";
	switch (ch) {
	case '\\':
		outFile.put(ch);
		if ((ch = inFile.get()) != EOF) {
			outFile.put(ch);
		}
		break;
	case '$': break;
	default: outFile.put(ch);
	}
	state = text;
}
