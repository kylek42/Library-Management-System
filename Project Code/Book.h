#pragma once
#include "User.h"

class Book {
private:
	//data members
	string ISBN;
	string title;
	string author;
	string category;
	int nReserved;

public:
	//constructors
	queue<User> reserverList;		//queue contains list of those who reserved the book
	Book();
	Book(string a);
	Book(string a, string b);
	Book(string a, string b, string c);

	//mutators
	void setISBN(string a);
	void setTitle(string b);
	void setAuthor(string c);
	void setCategory(string d);
	void addReserver(User e);
	void setnReserved(int f);

	//accessors
	string getISBN();
	string getTitle();
	string getAuthor();
	string getCategory();
	User getNextReserver();
	int getnReserved();

	void Book::printBook(ostream &cout);
};
