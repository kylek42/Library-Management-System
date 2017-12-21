#pragma once
#include "Book.h"

using namespace std;

Book::Book()
{

	cout << "\nEnter ISBN: ";
	cin >> ISBN;
	cout << "\nEnter title: ";
	cin.ignore();
	getline(cin, title);
	cout << "\nEnter author: ";
	getline(cin, author);
	cout << "\nEnter category: ";
	cin >> category;
}

Book::Book(string a)
{
	ISBN = a;
}

Book::Book(string a, string b)
{
	ISBN = a;
	title = b;
}

Book::Book(string a, string b, string c)
{
	ISBN = a;
	title = b;
	author = c;
}

//mutators
void Book::setISBN(string a) {
	ISBN = a;
	return;
}
void Book::setTitle(string b) {
	title = b;
	return;
}
void Book::setAuthor(string c) {
	author = c;
	return;
}
void Book::setCategory(string d) {
	category = d;
	return;
}
void Book::addReserver(User e) {
	reserverList.push(e);
}
void Book::setnReserved(int e) {
	nReserved = e;
	return;
}



//accessors
string Book::getISBN() {
	return ISBN;
}
string Book::getTitle() {
	return title;
}
string Book::getAuthor() {
	return author;
}
string Book::getCategory() {
	return category;
}
User Book::getNextReserver() {
	User temp = User(" ", " ");
	if (!reserverList.empty()) {
		User temp = reserverList.front();
		reserverList.pop();
	}
	return temp;
}
int Book::getnReserved() {
	return nReserved;
}

void Book::printBook(ostream &bookstream) {
	bookstream << getISBN() << "\n" << getTitle() << "\n" << getAuthor() << "\n" << getCategory() << "\n" << getnReserved() << "\n";
	queue<User> temp1, temp2;
	User temp = User("avoid", "default constructor");
	for (int i = 0; i < nReserved; i++) {
		temp = reserverList.front();
		temp1.push(temp);
		reserverList.pop();
	}
	for (int i = 0; i < nReserved; i++) {
		reserverList.push(temp1.front());
		bookstream << temp1.front().getUsername();
		bookstream << "\n";

		temp1.pop();
	}


	/*
	for (int i = 0; i < nReserved; i++) {
	bookstream << reserverList.front().getUsername() << " ";
	reserverList.pop();
	bookstream << "\n";
	}
	*/
	return;
}