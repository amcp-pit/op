#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>

using namespace std;

int main(){

	vector<string> sentence;
	sentence.reserve(15);
	sentence.push_back("Hello");
	sentence.push_back("how");
	sentence.push_back("are");
	sentence.push_back("you");
	sentence.push_back("?");
	
	for(vector<string>::iterator pos=sentence.begin(); pos!=sentence.end(); ++pos){
		cout << *pos <<' ';
	}
	cout << endl;

	for(vector<string>::reverse_iterator pos=sentence.rbegin(); pos!=sentence.rend(); ++pos){
		cout << *pos <<' ';
	}
	cout << endl;

	copy(sentence.begin(), sentence.end(), ostream_iterator<string>(cout," "));
	cout << endl;
	copy(sentence.rbegin(), sentence.rend(), ostream_iterator<string>(cout," "));
	cout << endl;

	cout<< "max_size(): "<< sentence.max_size()<<endl;
	cout<< "size(): "<< sentence.size()<<endl;
	cout<< "capacity(): "<< sentence.capacity()<<endl;

	swap(sentence[1], sentence[3]);
	sentence.insert( find(sentence.begin(), sentence.end(), "?") , "always");
	sentence.back() = "!";

	copy(sentence.begin(), sentence.end(), ostream_iterator<string>(cout," "));
	cout << endl;

	deque<string> S;
	S.assign(3, string("string"));
	S.push_back("last string");
	S.push_front("first string");

	copy(S.begin(), S.end(), ostream_iterator<string>(cout,"\n"));
	cout << endl;

	S.pop_back();
	S.pop_front();
	for(int i=1; i<S.size(); ++i){
		S[i] = "another " + S[i];
	}
	S.resize(8, "new string");
	cout<<"----------------------------------"<<endl;
	copy(S.begin(), S.end(), ostream_iterator<string>(cout,"\n"));
	cout << endl;

	return 0;
}
