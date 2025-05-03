#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <iterator>

using namespace std;

int main(){
	deque<string> S;
	S.assign(4, string("string"));
	S.push_back("last string");
	S.push_front("first string");

	copy(S.begin(), S.end(), ostream_iterator<string>(cout,"\n"));
	std::cout <<"--------------" << endl;

	S.pop_back();
	S.pop_front();
	for(size_t i=0; i<S.size(); ++i)
		S[i] = "another " + S[i];
	S.resize(8, "new string");
    copy(S.begin(), S.end(), ostream_iterator<string>(cout,"\n"));
    std::cout <<"--------------" << endl;

}
