#include "mydatabase.h"

struct Node {
	student data;
	Node* prev;
	Node* next;
};

struct Index {
	Node* current;
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

Index* findRecord(const Database* DB, int what){
    Node* current = DB->begin;
    while(current){
        if (current->data.number == what)
            break;
        current = current->next;
    }
	Index * tmp = new Index;
	tmp->current = current;
	return tmp;
}

bool eodb(Index * index){
	return index->current == nullptr;
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

void updateRecord(Database* DB, Index *index, const student &x){
	if (index->current){
		index->current->data = x;
	}
}

student getRecord(const Database* DB, Index *index){
	student tmp{};
	if (index->current) tmp = index->current->data;
	return tmp;
}

void deleteRecord(Database* DB, Index* index){
	Node * current = index->current;
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
	if (DB->begin == DB->end) {
		return;
	}
	bool isSorted = false;
	do{
		// Split
		Database tmp[2];
		tmp[0].begin = tmp[0].end = nullptr;
        tmp[1].begin = tmp[1].end = nullptr;

		unsigned char p = 0; // Номер текущего списка (того, куда добавляем)
		tmp[p].begin = tmp[p].end = DB->begin;
		DB->begin = DB->begin->next;

		while(DB->begin != nullptr){
			// Выбираем куда добавлять
			if (comparator(DB->begin->data, tmp[p].end->data)){
				p = !p; // p = 1 - p;
			}

			if (tmp[p].begin)
				tmp[p].end->next = DB->begin;
			else
				tmp[p].begin = DB->begin;

			tmp[p].end = DB->begin;
			DB->begin = DB->begin->next;
		}
		if (tmp[0].end) tmp[0].end->next = nullptr;
		if (tmp[1].end) tmp[1].end->next = nullptr;

		// Merge
		if (tmp[!p].begin) {
			// Значит два списка получилось
			p = comparator(tmp[0].begin->data, tmp[1].begin->data) ? 0 : 1;
			DB->begin = DB->end = tmp[p].begin;
			tmp[p].begin = tmp[p].begin->next;
			while(tmp[p].begin){
				bool sp = comparator(tmp[p].begin->data, DB->end->data);
				bool snotp = comparator(tmp[!p].begin->data, DB->end->data);
				if (sp == snotp){
					 p = comparator(tmp[0].begin->data, tmp[1].begin->data) ? 0 : 1;
				} else {
					if (sp) p = !p;
				}
				DB->end->next = tmp[p].begin;
				DB->end = DB->end->next;
				tmp[p].begin = tmp[p].begin->next;
			}
			DB->end->next = tmp[!p].begin;
			DB->end = tmp[!p].end;

		} else {
			DB->begin = tmp[p].begin;
			DB->end = tmp[p].end;
			isSorted = true;
		}
	} while(!isSorted);

	// Восстановить двухсвязность для списка
	Node* current = DB->begin;
	DB->begin->prev = nullptr;
	while(current->next){
		current->next->prev = current;
		current = current->next;
	}
}
