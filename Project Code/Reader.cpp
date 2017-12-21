#pragma once
#include "Reader.h"

//unfinished because books/copies unimplemented
//overload:
/*void Reader::operator >> (ifstream in, Reader r) {
in >>

}*/


Reader::Reader() : User()
{
	penalties = 0;
	numBorrowedCopies = 0;
	numReservedBooks = 0;
	std::list<Copy> borrowedCopies;
	std::list<string> reservedBooks;
}

Reader::Reader(string s) : User(s)
{
	penalties = 0;
	numBorrowedCopies = 0;
	numReservedBooks = 0;
	std::list<Copy> borrowedCopies;
	std::list<string> reservedBooks;
}

Reader::Reader(string s1, string s2) : User(s1, s2)
{
	penalties = 0;
	numBorrowedCopies = 0;
	numReservedBooks = 0;
	std::list<Copy> borrowedCopies;
	std::list<string> reservedBooks;
}

Reader::Reader(string s1, string s2, int ut) : User(s1, s2, ut) {
	penalties = 0;
	numBorrowedCopies = 0;
	numReservedBooks = 0;
	std::list<Copy> borrowedCopies;
	std::list<string> reservedBooks;
}

int Reader::getReaderType() {
	return getUserType();
}

void Reader::setPenalties(int p) {
	penalties = p;
}

int Reader::getPenalties() {
	return penalties;
}

void Reader::setKeepTime(int a)
{
	keepTime = a;
	return;
}

int Reader::getKeepTime()
{
	return keepTime;
}

void Reader::setMaxCopies(int b)
{
	maxCopies = b;
}

int Reader::getMaxCopies()
{
	return maxCopies;
}

void Reader::setNumBorrowedCopies(int c)
{
	numBorrowedCopies = c;
}

int Reader::getNumBorrowedCopies()
{
	return numBorrowedCopies;
}

void Reader::setNumReservedBooks(int d)
{
	numReservedBooks = d;
}

int Reader::getNumReservedBooks()
{
	return numReservedBooks;
}

void Reader::borrowCopy()
{
}

void Reader::returnCopy(int e)
{
	for (int i = 0; i < numBorrowedCopies; i++) {
		Copy temp = borrowedCopies.front();
		borrowedCopies.pop_front();
		if (e != temp.getID()) {
			borrowedCopies.push_back(temp);
		}
	}
	numBorrowedCopies--;
}

list<Copy> Reader::getListBorrowedCopies()
{
	return borrowedCopies;
}

void Reader::reserveBook(string e)
{
}

void Reader::addToListBC(Copy h) {
	borrowedCopies.push_back(h);
	numBorrowedCopies++;
}

void Reader::cancelReservation(string f)
{
}

void Reader::addToListRB(string g) {
	reservedBooks.push_back(g);
}

list<string> Reader::getListReservedBooks()
{
	return reservedBooks;
}

void Reader::printReader(ostream &cout)
{
	cout << getUserType() << " " << getUsername() << " " << getPassword() << " " << getPenalties() << " " << numBorrowedCopies << " ";
	for (int i = 0; i < numBorrowedCopies; i++) {
		cout << borrowedCopies.front().getISBN() << " " << borrowedCopies.front().getID() << " ";
		borrowedCopies.pop_front();
	}

	cout << numReservedBooks << " ";
	for (int i = 0; i < numReservedBooks; i++) {
		cout << reservedBooks.front() << " ";
		reservedBooks.pop_front();
	}
}

