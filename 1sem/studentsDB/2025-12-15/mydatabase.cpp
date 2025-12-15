#include "mydatabase.h"

struct Node {
	student data;
	Node* prev;
	Node* next;
};

struct Database {
	int count;
	Node* begin;
	Node* end;
};

Database* createDB(){
	Database * DB = new Database;
	DB->count = 0; // (*DB).count = 0;
	DB->begin = nullptr;
	DB->end = nullptr;
	return DB;
}

void deleteDB(Database* & DB){
	if (DB != nullptr)
		destructor(DB);
	delete DB;
	DB = nullptr;
}

void destructor(Database* DB){
	Node *current;
	while(DB->begin){
		current = DB->begin;
		DB->begin = DB->begin->next;
		delete current;
	}
	DB->end = nullptr;
	DB->count = 0;
}

int addRecord(Database* DB, const student& x){
	Node* tmp = new Node;
	tmp->data = x;
	tmp->next = nullptr;
	tmp->prev = nullptr;

	if (DB->begin != nullptr) {
		DB->end->next = tmp;
		tmp->prev = DB->end;
		DB->end = tmp;
	} else {
		// Список пустой
		DB->begin = DB->end = tmp;
	}
	++DB->count;
	return DB->count;
}

void printDB(const Database*  DB) {
	Node* current = DB->begin;
	while(current){
		std::cout << current->data <<std::endl;
		current = current->next;
	}
}

bool saveDB(const Database* DB, const char filename[]){
	std::ofstream outFile(filename, std::ios_base::binary);
	if (!outFile) return false;
	outFile.write((const char *)&(DB->count), sizeof(DB->count));

    Node* current = DB->begin;
    while(current){
	  	outFile.write( (const char *)&(current->data), sizeof(current->data));
    	current = current->next;
    }


	outFile.close();
	return true;
}

bool openDB(Database* DB, const char filename[]){

	std::ifstream inFile(filename, std::ios_base::binary);
	if (!inFile) return false;
	int count ;
	inFile.read((char *)&count, sizeof(count));
	destructor(DB);
	student tmp;
	// while (count-- > 0) {
	while(inFile.peek() != EOF){ 
		inFile.read( (char *)&tmp, sizeof(tmp));
		addRecord(DB, tmp);
	}
	inFile.close();

	return true;
}

bool exportDB(const Database* DB, const char filename[]){
	std::ofstream outFile(filename);
	if (!outFile) return false;

    Node* current = DB->begin;
    while(current){
        outFile << current->data << std::endl;
        current = current->next;
    }

	outFile.close();
	return true;
}

int findRecord(const Database* DB, int what){
	// TODO: Надо избавиться от индекса, так как он идеалогически чужд спискам
	int index = 0;

    Node* current = DB->begin;
    while(current){
		if (current->data.number == what)
			return index;
		++index;
        current = current->next;
    }

	return -1;
}

Node* getNode(const Database* DB, int index){
	if (index >= 0 && index < DB->count){
        Node* current = DB->begin;
        while(current && index > 0){
            --index;
            current = current->next;
        }
		return current;
	}
	return nullptr;
}

void updateRecord(Database* DB, int index, const student &x){
	Node* current = getNode(DB, index);
	if (current){
		current->data = x;
	}
}

student getRecord(const Database* DB, int index){
	student tmp{};
	Node* current = getNode(DB, index);
	if (current) tmp = current->data;
	return tmp;
}

void deleteRecord(Database* DB, int index){
	Node* current = getNode(DB, index);
	if (current==nullptr) return;

	if (current->prev){
		current->prev->next = current->next;
	} else {
		DB->begin = current->next;
	}

	if (current->next){
		current->next->prev = current->prev;
	} else {
		DB->end = current->prev;
	}

	delete current;
	--DB->count;
}

void sort(Database* DB, bool (*comparator) (const student&, const student&)){

	// TODO: сортировка естественное слияние

}
