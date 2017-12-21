#pragma once
#include "User.h"

class Librarian : public User {
private:

public:
	//constructors
	Librarian();
	Librarian(string s);
	Librarian(string s1, string s2);
	Librarian(string s1, string s2, int ut);

	void printLibrarian(ostream &cout);
};
