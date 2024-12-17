#include <iostream>

union bytecod {
	unsigned char ch;
	struct {
		unsigned char a0 : 1;
		unsigned char a1 : 1;
		unsigned char a2 : 1;
		unsigned char a3 : 1;
		unsigned char a4 : 1;
		unsigned char a5 : 1;
		unsigned char a6 : 1;
		unsigned char a7 : 1;
	} byte;
};

std::ostream& operator << (std::ostream& out, const bytecod& b) {
	out << (int)b.byte.a7
		<< (int)b.byte.a6
		<< (int)b.byte.a5
		<< (int)b.byte.a4
		<< (int)b.byte.a3
		<< (int)b.byte.a2
		<< (int)b.byte.a1
		<< (int)b.byte.a0;
	return out;
}

union cod32 {
	int x;
	bytecod b[4];
};

std::ostream& operator<< (std::ostream& out, const cod32& c) {
	out << c.x << ": ";
	for (int i = 3; i >= 0; --i) {
		out << (int)c.b[i].ch << ".";
	}
	std::cout << ": ";
	for (int i = 3; i >=0; --i) {
		out << c.b[i] << ".";
	}
	return out;
}

union codFloat {
	float f;
	cod32 x;
};

std::ostream& operator<< (std::ostream& out, const codFloat& F) {
	out << F.f << ": ";
	for (int i = 3; i >= 0; --i) {
		out << F.x.b[i] << ".";
	}
	return out;
}

union codDouble {
	double d;
	cod32 x[2];
};

std::ostream& operator<< (std::ostream& out, const codDouble& D) {
	out << D.d << ": ";
	for (int i = 3; i >= 0; --i) {
		out << D.x[1].b[i] << ".";
	}
	for (int i = 3; i >= 0; --i) {
		out << D.x[0].b[i] << ".";
	}
	return out;
}

int main() {
	bytecod S;
	for (S.ch = 0; S.ch < 32; ++S.ch) {
		std::cout << (int)S.ch << ": " << S << std::endl;
	}

	cod32 C;
	for (C.x = -1000; C.x < 3000; C.x += 101) {
		std::cout << C << std::endl;
	}

	C.x = -10;
	std::cout << C << std::endl;
	C.x = 10;
	std::cout << C << std::endl;
	C.b[2].byte.a4 = 1;
	std::cout << C << std::endl;

	codFloat F;
	F.f = 0.0;
	std::cout << "F = " << F << std::endl;
	do {
		std::cout << "Input numerator: ";
		int num;
		std::cin >> num;
		std::cout << "Input denumerator: ";
		int denum;
		std::cin >> denum;
		F.f = num / (float)denum;
		std::cout << "F = " << F << std::endl;
	} while (F.f != 0.0);


	codDouble D;
	D.d = 0.0;
	std::cout << "D = " << D << std::endl;
	do {
		std::cout << "Input numerator: ";
		int num;
		std::cin >> num;
		std::cout << "Input denumerator: ";
		int denum;
		std::cin >> denum;
		D.d = num / (double)denum;
		std::cout << "D = " << D << std::endl;
	} while (D.d != 0.0);
}
