#pragma once
#include "Reader.h"
#include "Librarian.h"



class FileOp {
private:

public:

	vector<Reader> readers;
	vector<Librarian> librs;
	vector<Book> books;
	vector<Copy> copies;

	string currentUser;
	int in_date;
	int date_sum;

	void read();
	void write();
	void readReaders(ifstream &rd);
	void readLibrarians(ifstream &rL);
	void readBooks(ifstream &rb);
	void readCopies(ifstream &rc);
	void writeReaders(ofstream &rd);
	void writeLibrarians(ofstream &rL);
	void writeBooks(ofstream &rb);
	void writeCopies(ofstream &rc);

	void removeCopy(int id);
};

