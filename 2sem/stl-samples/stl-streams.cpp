#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <bitset>

void hexMultiplicationTable(std::streambuf *buffer, int num){
	std::ostream hexout(buffer);

	hexout << std::hex << std:: showbase;
	hexout.setf(std::ios_base::left);
	for(int i= 1; i<=num; ++i){
		for(int j=1; j<=num; ++j){
			hexout << std::setw(4) << i * j << ' ';
		}
		hexout << std::endl;
	}

}

int main() {
	int num = 10;
	std::cout << "Print " << num << " lines hexademal\n";
	hexMultiplicationTable(std::cout.rdbuf(), num);

	std::ofstream outFile("hexresult.txt");
	if (outFile){
	    hexMultiplicationTable(outFile.rdbuf(), num);
		outFile.close();
	}

	std::ostringstream os;
	hexMultiplicationTable(os.rdbuf(), num);
	std::cout << "Result on os: \n" << os.str() << std::endl;

	std::ostringstream s;
	int x = 15;
	s << "dec: "<< x << std::hex << std::showbase << " hex: " << x << std::endl;
	std::cout <<"s = " << s.str() << std::endl;

	s << "float: " << 4.67 << std::endl;
    std::cout <<"s = " << s.str() << std::endl;

	std::bitset<15> b(5678);
	s << "bitset: " << b << std::endl;
    std::cout <<"s = " << s.str() << std::endl;

	s.seekp(0);
	s << "oct: " << std::oct << x;
    std::cout <<"s = " << s.str() << std::endl;

}
