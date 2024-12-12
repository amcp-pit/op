#include "mydatabase.h"
#include <fstream>

int addRecord(DataBase& DB, const student& X) {
	Node* tmp = new Node;
	tmp->data = X;
	tmp->next = nullptr;
	tmp->prev = nullptr;

	if (DB.begin != nullptr) {
		DB.end->next = tmp;
		tmp->prev = DB.end;
		DB.end = tmp;
	} else {
		DB.begin = DB.end = tmp;
	}
	++DB.count;
	return DB.count;
}

void deleteDB(DataBase& DB) {
	Node* current;
	while (DB.begin) {
		current = DB.begin;
		DB.begin = DB.begin->next;
		delete current;
	}
	DB.end = nullptr;
	DB.count = 0;
}

void printDB(const DataBase& DB) {
	Node* current = DB.begin;
	while(current) {
		std::cout << current->data << std::endl;
		current = current->next;
	}
}

void saveDB(const DataBase& DB, const char filename[]) {
	std::ofstream outFile(filename, std::ios_base::binary);
	if (!outFile.is_open()) {
		std::cout << "Can not open file '" << filename << "'\n";
		return;
	}
	outFile.write( (const char*)&(DB.count), sizeof(DB.count));
	Node* current = DB.begin;
	while (current) {
		outFile.write((const char*)&(current->data), sizeof(student));
		current = current->next;
	}
	outFile.close();
}

void openDB(DataBase& DB, const char filename[]) {
	std::ifstream inFile(filename, std::ios_base::binary);
	if (!inFile.is_open()) {
		std::cout << "Can not open file '" << filename << "'\n";
		return;
	}
	
	deleteDB(DB);

	int count;
	inFile.read( (char *)&count, sizeof(count));

	student tmp;
	while (inFile.peek() != EOF) {
		inFile.read((char*)&tmp, sizeof(student));
		addRecord(DB, tmp);
	}
	inFile.close();
}

void exportDB(const DataBase& DB, const char filename[]) {
	std::ofstream outFile(filename);
	if (!outFile.is_open()) {
		std::cout << "Can not open file '" << filename << "'\n";
		return;
	}
	
	Node* current = DB.begin;
	while (current) {
		outFile << current->data << std::endl;
		current = current->next;
	}

	outFile.close();
}

Node* findRecord(const DataBase& DB, int what) {
	Node* current = DB.begin;
	while (current) {
		if (current->data.number == what) {
			return current;
		}
		current = current->next;
	}

	return nullptr;
}

void updateRecord(DataBase& DB, Node * index, const student& X) {
	if (index) {
		index->data = X;
	}
}

student getRecord(DataBase& DB, Node* index) {
	student tmp;
	if (index) {
		tmp = index->data;
	}
	return tmp;
}

void deleteRecord(DataBase& DB, Node* index) {
	if (index) {
		std::cout << "Are you sure? (Y/N)";
		char ch[128];
		std::cin.get(ch, 128);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (ch[0] == 'Y' || ch[0] == 'y') {
			
			if (index->prev)
				index->prev->next = index->next;
			else
				DB.begin = index->next;

			if (index->next)
				index->next->prev = index->prev;
			else
				DB.end = index->prev;

			delete index;
			--DB.count;
		}
	}
}

void sort(DataBase& DB, bool (*comparator)(const student&, const student&)){
	if (DB.begin == DB.end) return; 
	bool isSorted = false;
	do{
		// Split
		DataBase tmp[2];
		unsigned char p = 0; // Номер текущего списка (списка в который добавляем)
		tmp[p].begin = tmp[p].end = DB.begin;
		DB.begin = DB.begin->next;
		tmp[!p].begin = tmp[!p].end = nullptr;
		
		while(DB.begin != nullptr){
			if (comparator(DB.begin->data, tmp[p].end->data))
				p = !p;

			if (tmp[p].begin)
				tmp[p].end->next = DB.begin;
			else
				tmp[p].begin = DB.begin;

			tmp[p].end = DB.begin;
			DB.begin = DB.begin->next;
		}
		if (tmp[p].end) tmp[p].end->next = nullptr;
		if (tmp[!p].end) tmp[!p].end->next = nullptr;

		// Merge
		if(tmp[!p].begin){ // Значит два списка
			p = comparator( tmp[0].begin->data, tmp[1].begin->data) ? 0 : 1;
			DB.begin = DB.end = tmp[p].begin;
			tmp[p].begin = tmp[p].begin->next;
			while(tmp[p].begin) {
				bool s1 = comparator(tmp[p].begin->data, DB.end->data);
				bool s2 = comparator(tmp[!p].begin->data, DB.end->data);
				if (s1==s2)
					p = comparator( tmp[0].begin->data, tmp[1].begin->data) ? 0 : 1;
				else{
					if (s1)
						p = !p; // p = 1 - p;
				}

				DB.end->next = tmp[p].begin;
				DB.end = DB.end->next;
				tmp[p].begin = tmp[p].begin->next;
			}
			DB.end->next = tmp[!p].begin;
			DB.end = tmp[!p].end;

		} else {
			// Получился только один список, т. е. всё упорядочено
			DB.begin = tmp[p].begin;
			DB.end = tmp[p].end;
			isSorted = true;
		}
	} while(!isSorted);

	// Восстановление поля prev для записей
	Node * current = DB.begin;
	DB.begin->prev = nullptr;
	while (current->next){
		current->next->prev = current;
		current = current->next;
	}
}
