#include <iostream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

void print_dictionary(const multimap<string, string> & dict, const char *from, const char *to) {
    cout.setf(std::ios::left);
    cout << ' '  << setw(20) << from << setw(20) << to << '\n';
    cout << setfill('-') << setw(42) << " " << setfill(' ') << '\n';
    for(auto pos = dict.begin(); pos != dict.end(); ++pos){
        cout << ' ' << setw(20) << pos->first
             << setw(20) << pos->second << '\n';
    }
    cout << '\n' << endl;
}

int main(){
	// English-Spanish dictionary
	multimap<string, string> en2es;
	en2es.insert(make_pair("car", "coche"));
    en2es.insert(make_pair("car", "auto"));
    en2es.insert(make_pair("motor", "coche"));
    en2es.insert(make_pair("day", "dia"));
    en2es.insert(make_pair("day", "fecha"));
    en2es.insert(make_pair("date", "fecha"));
    en2es.insert(make_pair("student", "estudiante"));
    en2es.insert(make_pair("student", "alumino(a)"));
    en2es.insert(make_pair("computer", "computador"));
    en2es.insert(make_pair("computer", "ordinator"));
    en2es.insert(make_pair("study", "estudiar"));
    en2es.insert(make_pair("smart", "intelegente"));
    en2es.insert(make_pair("clever", "intelegente"));
    en2es.insert(make_pair("smart", "elegante"));
    en2es.insert(make_pair("perhaps", "quizas"));
    en2es.insert(make_pair("perhaps", "tal vez"));

	print_dictionary(en2es, "english", "spanish");


	// Search for English-to-Spanish translations
	cout << "\n-- Search for English-to-Spanish translations\n";
	string what("student");
	cout << what << ": ";
	for(auto pos = en2es.begin(); pos != en2es.end(); ++pos){
		if (pos->first == what){
			cout << pos->second << "; ";
		}
	}
	cout << endl;

    cout << what << ": ";
	for(auto pos = en2es.lower_bound(what); pos != en2es.upper_bound(what); ++pos){
		cout << pos->second << "; ";
	}
	cout << '\n' << endl;


	// Search for Spanish-to-English translations
	cout << "\n-- Search for Spanish-to-English translations\n";
	what = "fecha";
	cout << what << ": ";
	for(auto pos = en2es.begin(); pos != en2es.end(); ++pos){
		if(pos->second == what){
			cout << pos->first <<"; ";
		}
	}

	cout << endl;


	// Reverse dictionary
	multimap<string, string> es2en;
	for(auto pos = en2es.begin(); pos != en2es.end(); ++pos){
		es2en.insert(make_pair(pos->second, pos->first));
	}

    print_dictionary(es2en, "spanish", "english");


    // Search for Spanish-to-English translations
    cout << "\n-- Search for Spanish-to-English translations\n";
	cout << what <<": ";
    for(auto pos = es2en.lower_bound(what); pos!=es2en.upper_bound(what); ++pos){
        cout << pos->second << "; ";
    }
    cout << '\n' << endl;

    multimap<string, string> en2de;
    en2de.insert(make_pair("car", "Wagen"));
    en2de.insert(make_pair("car", "Auto"));
    en2de.insert(make_pair("motor", "Motor"));
    en2de.insert(make_pair("day", "Tag"));
    en2de.insert(make_pair("date", "Datum"));
    en2de.insert(make_pair("student", "Studierende"));
    en2de.insert(make_pair("student", "Student(in)"));
    en2de.insert(make_pair("computer", "Computure"));
    en2de.insert(make_pair("computer", "Rechener"));
    en2de.insert(make_pair("study", "studieren"));
    en2de.insert(make_pair("smart", "schlau"));
    en2de.insert(make_pair("clever", "clever"));
    en2de.insert(make_pair("smart", "intelligent"));
    en2de.insert(make_pair("perhaps", "vielleicht"));

    print_dictionary(en2de, "english", "german");

	multimap<string, string> es2de;
	for(auto espos = es2en.begin(); espos != es2en.end(); ++espos){
		for(auto depos = en2de.lower_bound(espos->second); depos!=en2de.upper_bound(espos->second); ++depos){
			es2de.insert(make_pair(espos->first, depos->second));
    	}
	}
	print_dictionary(es2de, "spanish", "german");

	do {
		cout << "> ";
		getline(cin, what);
		for(auto pos = es2de.lower_bound(what); pos!=es2de.upper_bound(what); ++pos){
        	cout << pos->second << "; ";
    	}
		cout << endl;
	} while (what.length()>0);

	return 0;
}

