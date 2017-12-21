#pragma once
#include "Librarian.h"

Librarian::Librarian() : User()
{
}

Librarian::Librarian(string s) : User(s)
{
}

Librarian::Librarian(string s1, string s2) : User(s1, s2)
{
}

Librarian::Librarian(string s1, string s2, int ut) : User(s1, s2, ut) {};

void Librarian::printLibrarian(ostream &cout) {
	cout << getUsername() << " " << getPassword();

}