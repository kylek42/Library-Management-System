#pragma once
#include "Copy.h"


class Reader : public User {
private:
	int readerType;					//identifies student(0) vs teacher(1) for reading data files
	int keepTime;					//length of time copy can be kept(specific to subclass)
	int maxCopies;					//max # copies allowed to keep(specific to subclass)
	int numBorrowedCopies;			//# copies borrowed
	int numReservedBooks;			//# books reserved
	int penalties;					//# penalties from overdue copies



public:
	list<Copy> borrowedCopies;		//list of copies borrowed
	list<string> reservedBooks;		//list of reserved books
									//void operator>> (ifstream& in, FileOp& fs);
	Reader();
	Reader(string s);
	Reader(string s1, string s2);
	Reader(string s1, string s2, int ut);
	void setPenalties(int p);
	int getPenalties();
	void setKeepTime(int a);
	int getKeepTime();
	void setMaxCopies(int b);
	int getMaxCopies();
	void setNumBorrowedCopies(int c);
	int getNumBorrowedCopies();
	void setNumReservedBooks(int d);
	int getNumReservedBooks();
	int getReaderType();

	void borrowCopy();
	void returnCopy(int e);
	void addToListBC(Copy g);
	list<Copy> getListBorrowedCopies();

	void reserveBook(string f);
	void cancelReservation(string g);
	void addToListRB(string h);
	list<string> getListReservedBooks();

	void printReader(ostream &cout);
};
