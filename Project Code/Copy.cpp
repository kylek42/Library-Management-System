#pragma once
#include "Copy.h"


using namespace std;

Copy::Copy() : Book()
{

}

Copy::Copy(string a) : Book(a)
{
}


//mutators
void Copy::setID(int a) {
	ID = a;
}
void Copy::setBorrower(string b) {
	borrower = b;
}
void Copy::setBorrowDate(int c) {
	borrowDate = c;
}
void Copy::setReserveDate(int d) {
	resDate = d;

}
void Copy::setExpDate(int e) {
	expDate = e;
}

//acessors
int Copy::getID() {
	return ID;
}
string Copy::getBorrower() {
	return borrower;
}

int Copy::getBorrowDate() {
	return borrowDate;
}

int Copy::getReserveDate() {
	return resDate;
}

int Copy::getExpDate() {
	return expDate;
}

void Copy::printCopy(ostream &cout)
{
	cout << "\n" << getISBN() << " " << getID() << " ";
	if (getBorrower().empty()) {
		cout << "noborrower";
	}
	else {
		cout << getBorrower();
	}
	cout << " " << getBorrowDate() << " " << getReserveDate() << " " << getExpDate();
}
