#include <iostream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

int main(){
	std::multimap<int, string> M;
	M.insert(make_pair(4, "of"));
	M.insert(make_pair(2, "a"));
    M.insert(make_pair(5, "tagged"));
    M.insert(make_pair(1, "this"));
    M.insert(make_pair(6, "strings"));
    M.insert(make_pair(3, "multimap"));
    M.insert(make_pair(1, "is"));

	for(auto pos = M.begin(); pos!=M.end(); ++pos){
		cout << pos->second <<" ";
	}
	cout << endl;

	map<string, float> C;
	C.insert(make_pair("e", 2.71));
	C.insert(make_pair("G", 6.67e-23));
	C["pi"] = 3.1415;
	C["g"] = 9.81;
	C["Null"] = 0;
	for(auto pos = C.begin(); pos!=C.end(); ++pos){
		cout <<"key: " << pos->first
			 <<"\t = " << pos->second <<endl;
	}
	cout << "result = " << C["G"] * 1e24 * C["pi"] / C["g"] << endl;

	multimap<string, string> dict;
	dict.insert(make_pair("car", "coche"));
    dict.insert(make_pair("car", "auto"));
    dict.insert(make_pair("motor", "coche"));
    dict.insert(make_pair("day", "dia"));
    dict.insert(make_pair("day", "fecha"));
    dict.insert(make_pair("date", "fecha"));
    dict.insert(make_pair("student", "estudiante"));
    dict.insert(make_pair("student", "alumino(a)"));
    dict.insert(make_pair("computer", "computador"));
    dict.insert(make_pair("computer", "ordinator"));
    dict.insert(make_pair("study", "estudiar"));
    dict.insert(make_pair("smart", "intelegente"));
    dict.insert(make_pair("clever", "intelegente"));
    dict.insert(make_pair("smart", "elegante"));

	cout.setf(std::ios::left);
	cout << ' ' <<setw(10) << "english" << setw(20) <<"spanish" <<endl;
	cout << setfill('-') << setw(32) << " " << setfill(' ') <<endl;
	for(auto pos= dict.begin(); pos!=dict.end(); ++pos){
		cout << ' ' << setw(10) << pos->first
			 << setw(20) << pos->second << endl;
	}
	cout << endl;

	string what("smart");
	cout << what <<": ";
	for(auto pos= dict.begin(); pos!=dict.end(); ++pos){
		if (pos->first == what){
			cout << pos->second <<"; ";
		}
	}
	cout << endl;

	for(auto pos = dict.lower_bound(what); pos!=dict.upper_bound(what); ++pos){
		cout << pos->second << "; ";
	}
	cout << endl;

	what = "fecha";
	cout << what << ": ";
	for(auto pos=dict.begin(); pos!=dict.end(); ++pos){
		if(pos->second == what){
			cout << pos->first <<"; ";
		}
	}

	cout << endl;

	multimap<string, string> tcid;
	for(auto pos=dict.begin(); pos!=dict.end(); ++pos){
		tcid.insert(make_pair(pos->second, pos->first));
	}

	cout << what <<": ";
    for(auto pos = tcid.lower_bound(what); pos!=tcid.upper_bound(what); ++pos){
        cout << pos->second << "; ";
    }
    cout << endl;

}
