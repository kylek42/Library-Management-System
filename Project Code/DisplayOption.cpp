#include "DisplayOption.h"

clock_t start, cur;
int ini_date, date_s;

//takes in the userNumber to get users information
DisplayOption::DisplayOption() {}
DisplayOption::DisplayOption(int x) {
	userNumber = x;
}

//used for displaying librarian options vs reader options
void DisplayOption::setUserType(int a) {
	userType = a;
	//0 = reader
	//1 = librarian
}
int DisplayOption::getUserType() {
	return userType;
}

//search for books by ISBN, Title, Author, Category
void DisplayOption::searchBooks(FileOp &files)
{
	cout << "\n\nSearch Books\n" << endl;
	cout << "1 -- by ISBN" << endl;
	cout << "2 -- by Title" << endl;
	cout << "3 -- by Author" << endl;
	cout << "4 -- by Category" << endl;
	cout << "5 -- exit Search" << endl;
	cin >> choice;
	string searchTerm;
	bool found = false;
	vector <Book> foundBooks;
	switch (choice) {
	case 1:
		cout << "\nEnter ISBN: ";
		cin >> searchTerm;
		cout << "\n";
		for (int i = 0; i < files.books.size(); i++) {
			if (searchTerm == files.books[i].getISBN()) {
				found = true;
				cout << "\n";
				cout << "\nISBN: " << files.books[i].getISBN();
				cout << "\nTitle: " << files.books[i].getTitle();
				cout << "\nAuthor: " << files.books[i].getAuthor();
				cout << "\nCategory: " << files.books[i].getCategory();
				cout << "\nCopy IDs: ";
				for (int j = 0; j < files.copies.size(); j++) {
					if (searchTerm == files.copies[j].getISBN()) {
						cout << files.copies[j].getID() << ", ";
					}
				}
				cout << "\n";
			}
		}
		break;

	case 2:
		cout << "\nEnter Title: ";
		cin.ignore();
		getline(cin, searchTerm);
		cout << "\n";
		for (int i = 0; i < files.books.size(); i++) {
			if (searchTerm == files.books[i].getTitle()) {
				found = true;
				cout << "\n";
				cout << "\nISBN: " << files.books[i].getISBN();
				cout << "\nTitle: " << files.books[i].getTitle();
				cout << "\nAuthor: " << files.books[i].getAuthor();
				cout << "\nCategory: " << files.books[i].getCategory();
				cout << "\nCopy IDs: ";
				for (int j = 0; j < files.copies.size(); j++) {
					if (files.books[i].getTitle() == files.copies[j].getTitle()) {
						cout << files.copies[j].getID() << ", ";
					}
				}
				cout << "\n";
			}
		}
		break;
	case 3:
		cout << "\nEnter Author: ";
		cin.ignore();
		getline(cin, searchTerm);
		cout << "\n";
		for (int i = 0; i < files.books.size(); i++) {
			if (searchTerm == files.books[i].getAuthor()) {
				foundBooks.push_back(files.books[i]);
				found = true;
			}
		}
		sortPrint(files, foundBooks, searchTerm);

		break;
	case 4:
		cout << "\nEnter Category(Action, Romance, Comedy): ";
		cin >> searchTerm;
		cout << "\n";
		for (int i = 0; i < files.books.size(); i++) {
			if (searchTerm == files.books[i].getCategory()) {
				found = true;
				foundBooks.push_back(files.books[i]);
			}
		}
		sortPrint(files, foundBooks, searchTerm);
		break;
	case 5:
		cout << "\nExiting Search... ";
		break;
	default:
		//loop the function till option is chosen
		cout << "\nInvalid choice" << endl;
		cin.ignore();
		searchBooks(files);
		break;
	}
	if (!found) {
		cout << "\nNo books found...";
	}
	switchOptions(files);
}

//sorts and prints vector of books found in search
void DisplayOption::sortPrint(FileOp &files, vector<Book> foundBooks, string searchTerm) {
	int m;
	for (int i = 0; i < foundBooks.size() - 1; i++) {
		for (int j = i + 1; j < foundBooks.size(); j++) {
			if (foundBooks[i].getnReserved() < foundBooks[j].getnReserved()) {
				Book temp = foundBooks[j];
				foundBooks[j] = foundBooks[i];
				foundBooks[i] = temp;
			}
		}
	}
	for (int i = 0; i < foundBooks.size(); i++) {
		cout << "\n";
		cout << "\nISBN: " << foundBooks[i].getISBN();
		cout << "\nTitle: " << foundBooks[i].getTitle();
		cout << "\nAuthor: " << foundBooks[i].getAuthor();
		cout << "\nCategory: " << foundBooks[i].getCategory();
		cout << "\nCopy IDs: ";
		for (int j = 0; j < files.copies.size(); j++) {
			if (foundBooks[i].getISBN() == files.copies[j].getISBN()) {
				cout << files.copies[j].getID() << ", ";
			}
		}
		cout << "\n";
	}

}

//creates a new copy based on librarian specifications
//assigned a random ID
void DisplayOption::addBook(FileOp &files)
{
	srand(time(NULL));
	Copy newBook = Copy();
	cout << "\nISBN: " << newBook.getISBN();
	cout << "\nTitle: " << newBook.getTitle();
	cout << "\nAuthor: " << newBook.getAuthor();
	cout << "\nCategory: " << newBook.getCategory();
	newBook.setID(rand());
	bool exists = false;

	for (int i = 0; i < files.books.size(); i++) {
		if (newBook.getISBN() == files.books[i].getISBN()) {
			exists = true;
		}
	}
	if (exists) {
		files.copies.push_back(newBook);
	}
	else {
		files.copies.push_back(newBook);
		Book newBook1 = Book(newBook.getISBN());
		newBook1.setTitle(newBook.getTitle());
		newBook1.setAuthor(newBook.getAuthor());
		newBook1.setCategory(newBook.getCategory());

		files.books.push_back(newBook1);
	}
}

//deletes copy from library, removes book obj if last copy
//removes the book from all readers reservation lists as per 3.5.3
void DisplayOption::deleteBook(FileOp &files)
{
	int id;
	string er;
	bool multCopies = false;
	cout << "\nEnter the ID of copy to be deleted: ";
	cin >> id;
	for (int i = 0; i < files.copies.size(); i++) {
		if (id == files.copies[i].getID()) {
			if (files.copies[i].getBorrower() != "noborrower") {
				cout << "\nCopy is currently lent to " << files.copies[i].getBorrower() << " and cannot be deleted...";
			}
			else {
				er = files.copies[i].getISBN();
				for (int j = 0; j < files.readers.size(); j++) {
					for (int k = 0; k < files.readers[j].reservedBooks.size(); k++) {
						string temp = files.readers[j].reservedBooks.front();
						files.readers[j].reservedBooks.pop_front();
						files.readers[j].reservedBooks.push_back(temp);
						if (er != temp) {
							files.readers[j].reservedBooks.push_back(temp);
						}
					}
				}
				files.removeCopy(id);
			}
		}
	}
}

//displays usernames/passwords & borrowed copy info
void DisplayOption::searchUsers(FileOp &files)
{
	string uname;
	cout << "\nEnter a username to search for: ";
	cin >> uname;
	for (int i = 0; i < files.librs.size(); i++) {
		if (uname == files.librs[i].getUsername()) {
			cout << "\n" << uname;
			cout << "\n" << files.librs[i].getPassword();
		}
	}
	for (int i = 0; i < files.readers.size(); i++) {
		if (uname == files.readers[i].getUsername()) {
			cout << "\nUsername: " << uname;
			cout << "\nPassword: " << files.readers[i].getPassword();
			if (files.readers[i].getReaderType() == 0) {
				cout << "\nReader is a student.";
			}
			else {
				cout << "\nReader is a teacher.";
			}
			for (int j = 0; j < files.readers[i].getNumBorrowedCopies(); j++) {
				Copy temp = files.readers[i].borrowedCopies.front();
				files.readers[i].borrowedCopies.pop_front();
				files.readers[i].borrowedCopies.push_back(temp);
				cout << "\nCopy of '" << temp.getTitle() << "' borrowed, ID #" << temp.getID();
			}
		}
	}
}

//adds user to database
void DisplayOption::addUser(FileOp &files)
{
	string newUser, newPass;
	int ut;
	bool cont = false;
	cout << "\nEnter new user type (0 = student), (1 = teacher), (2 = Librarian): ";
	cin >> ut;
	do {
		cout << "\nEnter new username: ";
		cin >> newUser;
		if (ut < 2) {
			for (int i = 0; i < files.readers.size(); i++) {
				if (newUser == files.readers[i].getUsername()) {
					cont = true;
				}
			}
		}
		if (ut == 2) {
			for (int i = 0; i < files.librs.size(); i++) {
				if (newUser == files.librs[i].getUsername()) {
					cont = true;
				}
			}
		}
		if (cont) {
			"\nUsername exists already, try again.";
		}
	} while (cont);
	cout << "\nEnter password for new user " << newUser;
	cin >> newPass;
	if (ut < 2) {
		Reader temp = Reader(newUser, newPass, ut);
		files.readers.push_back(temp);
	}
	else {
		Librarian temp = Librarian(newUser, newPass, ut);
		files.librs.push_back(temp);
	}
}

//deletes user from reader vector
void DisplayOption::deleteUser(FileOp &files)
{
	string bye;
	bool found = false;
	int r = files.readers.size();
	cout << "\nEnter username to be deleted: ";
	cin >> bye;
	for (int i = 0; i < r; i++) {
		if (files.readers[i].getUsername() == bye) {
			found = true;
			if (files.readers[i].getNumBorrowedCopies() == 0) {
				for (int j = 0; j < files.readers[i].reservedBooks.size(); j++) {
					string rBooks = files.readers[i].reservedBooks.front();
					files.readers[i].reservedBooks.pop_front();
					for (int k = 0; k < files.books.size(); k++) {
						if (rBooks == files.books[k].getISBN())
						{
							for (int g = 0; g < files.books[k].reserverList.size(); g++) {
								User temp = files.books[k].reserverList.front();
								files.books[k].reserverList.pop();
								if (temp.getUsername() != bye) {
									files.books[k].reserverList.push(temp);
								}

							}
						}
					}
				}
			}
			if (found && i <r - 2) {
				files.readers[i] = files.readers[i + 1];
			}
		}
	}
	files.readers.erase(files.readers.begin() + files.readers.size() - 1);
}

//prints username, password for users
//prints reader type and list of borrowed copies for readers
void DisplayOption::displayInfo(FileOp &files, int t)
{
	if (t == 2) {
		cout << "\nUsername: " << files.currentUser;
		for (int i = 0; i < files.librs.size(); i++) {
			if (files.currentUser == files.librs[i].getUsername()) {
				cout << "\nPassword: " << files.librs[i].getPassword();
			}
		}
	}
	else {
		cout << "\nUsername: " << files.currentUser;
		for (int i = 0; i < files.readers.size(); i++) {
			if (files.currentUser == files.readers[i].getUsername()) {
				cout << "\nPassword: " << files.readers[i].getPassword();
				if (files.readers[i].getReaderType() == 0) {
					cout << "\nStudent Reader.";
				}
				else {
					cout << "\nTeacher.";
				}
				for (int j = 0; j < files.readers[i].getNumBorrowedCopies(); j++) {
					Copy temp = files.readers[i].borrowedCopies.front();
					files.readers[i].borrowedCopies.pop_front();
					files.readers[i].borrowedCopies.push_back(temp);
					cout << "\nCopy of '" << temp.getTitle() << "' borrowed, ID #" << temp.getID();
				}
			}
		}
	}
}


//borrows a copy, affecting necessary structures
void DisplayOption::borrowBook(FileOp &files)
{
	int cID;
	cout << "\nPlease enter the copy id to borrow: ";
	cin >> cID;
	//keeps track if a copy can be borrowed
	bool cB = true;
	int usern = 0;
	for (int i = 0; i < files.readers.size(); i++) {
		if (files.readers[i].getUsername() == files.currentUser) {
			list <Copy> temp = files.readers[i].borrowedCopies;
			for (int j = 0; j < files.readers[i].borrowedCopies.size(); j++) {
				Copy temp1 = temp.front();
				cur = clock();
				if (cID == temp1.getID()) {
					if (temp1.getExpDate() < (date_s + int(cur - start) / (5 * CLOCKS_PER_SEC))) {
						cB = false;
						cout << "\nusername: " << files.readers[i].getUsername();

						cout << "\nCopy can't be borrowed while copies are overdue...";
					}
				}


			}
			if (files.readers[i].getNumBorrowedCopies() == files.readers[i].getMaxCopies()) {
				cB = false;
				cout << "\nMaximum number of copies currently withdrawn...";
			}
			for (int k = 0; k < files.copies.size(); k++) {
				if (cID == files.copies[k].getID()) {
					if (files.copies[k].getBorrower() != "noborrower") {
						cB = false;
						cout << "\nCopy is currently withdrawn and cannot be borrowed...";
					}
					else {
						if ((files.copies[k].getNextReserver().getUsername() == files.readers[i].getUsername()) || (files.copies[k].getNextReserver().getUsername() == " ")) {
							if (cB) {

								//implements bonus in 3.4.2
								if (files.copies[k].getnReserved() > 5) {
									cur = clock();
									files.copies[k].setBorrower(files.currentUser);
									files.copies[k].setBorrowDate((date_s + int(cur - start) / (5 * CLOCKS_PER_SEC)));
									//when list of reservers are long, teachers may borrow for 30 days
									if (files.readers[i].getUserType() == 1) {
										cur = clock();
										files.copies[k].setExpDate((date_s + int(cur - start) / (5 * CLOCKS_PER_SEC)) + 30);
									}
									//students may borrow only 20 days
									else {
										cur = clock();
										files.copies[k].setExpDate((date_s + int(cur - start) / (5 * CLOCKS_PER_SEC)) + 20);
									}
									files.readers[i].addToListBC(files.copies[k]);
								}
								else {
									cur = clock();
									files.copies[k].setBorrower(files.currentUser);
									files.copies[k].setBorrowDate((date_s + int(cur - start) / (5 * CLOCKS_PER_SEC)));
									//when list of reservers are long, teachers may borrow for 30 days
									if (files.readers[i].getUserType() == 1) {
										cur = clock();
										files.copies[k].setExpDate((date_s + int(cur - start) / (5 * CLOCKS_PER_SEC)) + 50);
									}
									//students may borrow only 20 days
									else {
										cur = clock();
										files.copies[k].setExpDate((date_s + int(cur - start) / (5 * CLOCKS_PER_SEC)) + 30);
									}
									files.readers[i].addToListBC(files.copies[k]);

								}
							}
						}
					}
				}
			}
		}
	}
}


void DisplayOption::returnBook(FileOp &files)
{
	int cID;
	cout << "\nEnter the id of the copy to be returned: ";
	cin >> cID;
	for (int j = 0; j < files.readers.size(); j++) {
		if (files.currentUser == files.readers[j].getUsername()) {
			for (int i = 0; i < files.readers[j].getNumBorrowedCopies(); i++) {
				Copy temp = files.readers[j].borrowedCopies.front();
				files.readers[j].borrowedCopies.pop_front();
				if (temp.getID() == cID) {
					cur = clock();
					if (temp.getExpDate() < (date_s + int(cur - start) / (5 * CLOCKS_PER_SEC))) {
						files.readers[j].setPenalties(files.readers[j].getPenalties() + 1);
						if (files.readers[j].getPenalties() > 2) {
							files.readers[j].setMaxCopies(files.readers[j].getMaxCopies() - 1);
						}
					}
					for (int g = 0; g < files.copies.size(); g++) {
						if (cID == files.copies[g].getID()) {
							files.copies[g].setBorrower("noborrower");
						}
					}
				}
				else {
					files.readers[j].borrowedCopies.push_back(temp);
				}

			}
		}
	}
}

//have not implemented last bullet of 3.4.4
void DisplayOption::reserveBook(FileOp &files)
{
	string risbn;
	bool canR = true;
	cout << "\nEnter the ISBN of the book: ";
	cin >> risbn;
	for (int i = 0; i < files.books.size(); i++) {
		if (files.books[i].getISBN() == risbn) {
			for (int j = 0; j < files.readers.size(); j++) {
				if (files.currentUser == files.readers[j].getUsername()) {
					for (int k = 0; k < files.readers[j].getNumBorrowedCopies(); k++) {
						Copy temp = files.readers[j].borrowedCopies.front();
						files.readers[j].borrowedCopies.pop_front();
						cur = clock();
						if (temp.getExpDate() < date_s + int(cur - start) / (5 * CLOCKS_PER_SEC)) {
							canR = false;
						}
						files.readers[j].borrowedCopies.push_back(temp);
					}
					if (canR) {
						for (int f = 0; f < files.copies.size(); f++) {
							if (files.copies[f].getISBN() == risbn) {
								files.copies[f].reserverList.push(files.readers[j]);
							}
						}
					}
				}
			}
		}
	}
}


void DisplayOption::cancelReservation(FileOp &files)
{
	string risbn;
	cout << "\nEnter the ISBN: ";
	cin >> risbn;
	for (int i = 0; i < files.readers.size(); i++) {
		if (files.readers[i].getUsername() == files.currentUser) {
			for (int j = 0; j < files.books.size(); j++) {
				if (files.books[j].getISBN() == risbn) {
					for (int k = 0; k < files.books[j].reserverList.size(); k++) {
						User temp = files.books[j].reserverList.front();
						files.books[j].reserverList.pop();
						if (temp.getUsername() != files.currentUser) {
							files.books[j].reserverList.push(temp);
						}
					}
				}
			}
		}
		for (int h = 0; h < files.readers[i].reservedBooks.size(); h++) {
			string temporary = files.readers[i].reservedBooks.front();
			files.readers[i].reservedBooks.pop_front();
			if (temporary != risbn) {
				files.readers[i].reservedBooks.push_back(temporary);

			}
			else {
				files.readers[i].setNumReservedBooks(files.readers[i].getNumReservedBooks() - 1);
			}

		}
	}
}

void DisplayOption::changePassword(FileOp &files) {
	if (userType == 0) {
		for (int i = 0; i < files.readers.size(); i++) {
			if (files.currentUser == files.readers[i].getUsername()) {
				files.readers[i].setPasswordChange();
			}
		}
	}
	else {
		for (int i = 0; i < files.librs.size(); i++) {
			if (files.currentUser == files.librs[i].getUsername()) {
				files.librs[i].setPasswordChange();
			}
		}
	}

}


void DisplayOption::switchOptions(FileOp &files) {
	start = clock();
	ini_date = files.in_date;
	date_s = files.date_sum;
	if (userType == 0) {
		displayReaderOptions(files);
		cur = clock();
		date_s += ini_date + int(cur - start) / (5 * CLOCKS_PER_SEC);
		files.date_sum = date_s;
	}
	else {
		displayLibrarianOptions(files);
		cur = clock();
		date_s += ini_date + int(cur - start) / (5 * CLOCKS_PER_SEC);
		files.date_sum = date_s;
	}

}

//displays the options for the reader
void DisplayOption::displayReaderOptions(FileOp &files) {
	cout << "\n";
	cout << "1 -- Search Books" << endl;
	cout << "2 -- Borrow Books" << endl;
	cout << "3 -- Return Books" << endl;
	cout << "4 -- Reserve Books" << endl;
	cout << "5 -- Cancel Reservation" << endl;
	cout << "6 -- My Information" << endl;
	cout << "7 -- Change Password" << endl;
	cout << "0 -- Log Out" << endl;
	cin >> option;
	//takes input from user to decide what program to run
	switch (option) {

	case 1:
		searchBooks(files);
		break;
	case 2:
		borrowBook(files);
		break;
	case 3:
		returnBook(files);
		break;
	case 4:
		reserveBook(files);
		break;
	case 5:
		cancelReservation(files);
	case 6:
		displayInfo(files, 1);
		break;
	case 7:
		changePassword(files);
		break;
	case 0:
		break;
	default:
		//loop the function till option is chosen
		cout << "\nInvalid choice" << endl;
		displayReaderOptions(files);
		break;
	}
}

//displays the options for librarians
void DisplayOption::displayLibrarianOptions(FileOp &files) {
	cout << "\n";
	cout << "1 -- Search Books" << endl;
	cout << "2 -- Add Books" << endl;
	cout << "3 -- Delete Books" << endl;
	cout << "4 -- Search Users" << endl;
	cout << "5 -- Add Users" << endl;
	cout << "6 -- Delete Users" << endl;
	cout << "7 -- My Information" << endl;
	cout << "8 -- Change Password" << endl;
	cout << "0 -- Log Out" << endl;

	cin >> choice;
	//takes input from user to decide what program to run
	switch (choice) {
	case 1:
		searchBooks(files);
		break;
	case 2:
		addBook(files);
		break;
	case 3:
		deleteBook(files);
		break;
	case 4:
		searchUsers(files);
		break;
	case 5:
		addUser(files);
		break;
	case 6:
		deleteUser(files);
		break;
	case 7:
		displayInfo(files, 2);
		break;
	case 8:
		changePassword(files);
		break;
	case 0:
		break;
	default:
		//loop the function till option is chosen
		cout << "\nInvalid choice" << endl;
		displayLibrarianOptions(files);
		break;
	}
}