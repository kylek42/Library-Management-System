#pragma once
#include "FileStorage.h"
#include <conio.h>

using namespace std;

class DisplayOption {
private:
	int userType;
	int userNumber;
	int option, choice;

public:
	DisplayOption();
	DisplayOption(int x);
	void displayReaderOptions(FileOp &files);
	void displayLibrarianOptions(FileOp &files);
	void switchOptions(FileOp &files);

	void setUserType(int a);
	int getUserType();

	//reader mostly
	void searchBooks(FileOp &files);
	void sortPrint(FileOp &files, vector<Book> foundBooks, string searchTerm);
	void borrowBook(FileOp &files);
	void returnBook(FileOp &files);
	void reserveBook(FileOp &files);
	void cancelReservation(FileOp &files);
	void changePassword(FileOp &files);

	//librarian mostly
	void addBook(FileOp &files);
	void deleteBook(FileOp &files);
	void searchUsers(FileOp &files);
	void addUser(FileOp &files);
	void deleteUser(FileOp &files);
	void displayInfo(FileOp &files, int t);


};