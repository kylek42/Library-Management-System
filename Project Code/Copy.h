#pragma once
#include "Book.h"


class Copy : public Book {
private:
	int ID;
	string borrower;
	int borrowDate;
	int resDate;
	int expDate;

public:
	//constructors
	Copy();
	Copy(string a);

	//mutators
	void setID(int a);
	void setBorrower(string b);
	void setBorrowDate(int c);
	void setReserveDate(int d);
	void setExpDate(int e);

	//acessors
	int getID();
	string getBorrower();
	int getBorrowDate();
	int getReserveDate();
	int getExpDate();


	void printCopy(ostream &cout);
};

