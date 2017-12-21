#pragma once
#include "FileStorage.h"
#include <sstream>

vector<Reader> readers;
vector<Librarian> librs;
vector<Book> books;
vector<Copy> copies;

string currentUser;
int in_date, date_sum;

//opens 4 data files, calls methods to read data
void FileOp::read()
{
	ifstream readerdata, librariandata, bookdata, copydata;
	cout << "\nOpening data files...\n";
	readerdata.open("reader.dat"); librariandata.open("librarian.dat");
	bookdata.open("book.dat"); copydata.open("copy.dat");
	//output error and close if files can't be opened
	if (readerdata.fail() || librariandata.fail() || bookdata.fail() || copydata.fail())
	{
		cerr << "\nError opening input files\n";
		system("pause");
		exit(1);
	}
	else {
		cout << "\nReading data files...\n";
		readReaders(readerdata);	readLibrarians(librariandata);
		readBooks(bookdata);		readCopies(copydata);

		//closes data in streams
		readerdata.close();			librariandata.close();
		bookdata.close();			copydata.close();

	}
}

//opens 4 data files, calls methods to write
void FileOp::write() {
	ofstream readerdata, librariandata, bookdata, copydata;
	cout << "\nOpening data files...\n";
	readerdata.open("reader.dat");	librariandata.open("librarian.dat");
	bookdata.open("book.dat");		copydata.open("copy.dat");
	//output error and close if files can't be opened
	if (readerdata.fail() || librariandata.fail() || bookdata.fail() || copydata.fail())
	{
		cerr << "\nError opening input files\n";
		system("pause");
		exit(1);
	}
	else {
		cout << "Updating data files...\n";
		writeReaders(readerdata);	writeLibrarians(librariandata);
		writeBooks(bookdata);		writeCopies(copydata);
		//closes data in streams
		readerdata.close();		librariandata.close();
		bookdata.close();		copydata.close();
	}
}

//reads data, stores in readers vector
void FileOp::readReaders(ifstream &readerdata) {
	cout << "\nLoading Student/Teacher data...";
	//reads number of readers from data file
	int ndata;
	readerdata >> ndata;
	int userType, keepTime, penalties;
	int copiesBorrowed, booksReserved;
	//reads readers data file, stores in vector
	while (ndata > 0) {
		string name, pass;
		readerdata >> userType;
		readerdata >> name;
		readerdata >> pass;
		readerdata >> penalties;
		readerdata >> copiesBorrowed;
		readerdata >> booksReserved;
		Reader temp = Reader(name, pass);
		//following loops require edits
		for (int j = 0; j < copiesBorrowed; j++) {
			string isbn;
			int id;
			readerdata >> isbn;
			readerdata >> id;
			Copy temp5 = Copy(isbn);
			temp5.setBorrower(name);
			temp5.setID(id);
			temp.addToListBC(temp5);
		}
		for (int k = 0; k < booksReserved; k++) {
			string isbn;
			readerdata >> isbn;
			temp.addToListRB(isbn);
		}
		//if teacher, else student
		if (userType == 1) {
			temp.setUserType(1);
			keepTime = 50;
			temp.setMaxCopies(10 - copiesBorrowed - (2 * penalties));		//arbitrary number of maximum copies minus penalties
		}
		else {
			temp.setUserType(0);
			keepTime = 30;
			temp.setMaxCopies(5 - copiesBorrowed - (2 * penalties));
		}
		temp.setPenalties(penalties);
		temp.setNumBorrowedCopies(copiesBorrowed);
		temp.setNumReservedBooks(booksReserved);

		readers.push_back(temp);
		ndata--;
	}
	return;
}

//reads data, stores in librs vector
void FileOp::readLibrarians(ifstream &librariandata) {
	cout << "\nLoading Librarian Data..";
	//reads number of librarians from data file
	//date needs to be stored between accesses
	//I just threw it in here
	int ndata;
	librariandata >> ndata;
	librariandata >> in_date;
	librariandata >> date_sum;
	while (ndata > 0) {
		string name, pass;
		librariandata >> name;
		librariandata >> pass;
		Librarian temp = Librarian(name, pass);
		temp.setUserType(2);
		librs.push_back(temp);
		ndata--;
	}
	return;
}

//reads data, stores in books vector
void FileOp::readBooks(ifstream &bookdata) {
	//reads number of books from data file
	int ndata;
	bookdata >> ndata;
	cout << "\nLoading Book data...";
	bookdata.ignore();
	while (ndata > 0) {
		int nRes = 0;
		string isbn, title, author, cat, reserver;
		getline(bookdata, isbn);
		getline(bookdata, title);
		getline(bookdata, author);
		getline(bookdata, cat);

		string line;
		getline(bookdata, line);
		std::istringstream abc(line);
		abc >> nRes >> std::ws;

		Book temp = Book(isbn, title, author);
		temp.setCategory(cat);
		vector <int> place(0);
		for (int i = 0; i < nRes; i++) {
			getline(bookdata, reserver);
			for (int j = 0; j < readers.size(); j++) {
				if (reserver == readers[j].getUsername()) {
					place.push_back(j);
				}
			}
		}
		for (int h = 0; h < place.size(); h++) {
			temp.addReserver(readers[place[h]]);
		}
		temp.setnReserved(nRes);
		books.push_back(temp);

		ndata--;
	}

	return;
}

//reads data, stores in copies vector..needs more values
void FileOp::readCopies(ifstream &copydata) {
	cout << "\nLoading Copy data...";
	//reads number of copies from data file
	int ndata;
	copydata >> ndata;
	while (ndata > 0) {
		string bname, isbn;
		int id, borrowdate, reservedate, expdate;
		copydata >> isbn;
		copydata >> id;
		copydata >> bname;
		copydata >> borrowdate;
		copydata >> reservedate;
		copydata >> expdate;
		Copy temp = Copy(isbn);
		temp.setID(id);
		temp.setBorrowDate(borrowdate);
		temp.setReserveDate(reservedate);
		temp.setExpDate(expdate);
		for (int i = 0; i < books.size(); i++) {
			if (books[i].getISBN() == isbn) {
				temp.setTitle(books[i].getTitle());
				temp.setAuthor(books[i].getAuthor());
				temp.setCategory(books[i].getCategory());
			}
		}

		if (bname != "noborrower") {
			temp.setBorrower(bname);
			for (int i = 0; i < readers.size(); i++) {
				if (bname == readers[i].getUsername()) {
					readers[i].addToListBC(temp);
				}
			}
		}
		else {
			temp.setBorrower("noborrower");
		}
		copies.push_back(temp);
		ndata--;
	}
	return;
}

//reads data from readers vector, writes to data files
void FileOp::writeReaders(ofstream &readerdata) {
	cout << "\nWriting reader data...";
	//reads number of readers from vector
	int ndata = readers.size();
	readerdata << ndata << endl;

	for (int i = 0; i < ndata; i++) {
		readers[i].printReader(readerdata);
		readerdata << "\n";
	}
	return;
}

//reads data from librarians vectors writes to data files
void FileOp::writeLibrarians(ofstream &librariandata) {
	cout << "\nWriting librarian data...";
	//reads number of librarians from vector
	int ndata = librs.size();
	librariandata << ndata << " " << in_date << " " << date_sum << endl;
	for (int i = 0; i < ndata; i++) {
		librs[i].printLibrarian(librariandata);
		librariandata << "\n";
	}
	return;

}

//reads data from books vector, writes to data files
void FileOp::writeBooks(ofstream &bookdata) {
	cout << "\nWriting book data...";
	//reads number of books from vector
	int ndata = books.size();
	bookdata << ndata;
	bookdata.clear();
	bookdata << "\n";
	for (int i = 0; i < ndata; i++) {
		books[i].printBook(bookdata);
	}
	return;

}

//reads data from copies vectors, writes to data files
void FileOp::writeCopies(ofstream &copydata) {
	cout << "\nWriting copy data...";
	//reads number of copies from vector
	int ndata = copies.size();
	copydata << ndata;

	for (int i = 0; i < ndata; i++) {
		copies[i].printCopy(copydata);
	}
	return;
}



void FileOp::removeCopy(int id) {
	string isbn;
	int place = copies.size() - 1;
	bool multCopies = false;
	bool found = false;
	int a = copies.size();
	for (int i = 0; i < a; i++) {
		if (copies[i].getID() == id) {
			isbn = copies[i].getISBN();
			found = true;
			a--;
		}
		if (found) {
			copies[i] = copies[i + 1];
		}

	}
	copies.erase(copies.begin() + copies.size() - 1);
	for (int i = 0; i < copies.size(); i++) {
		if (copies[i].getISBN() == isbn) {
			multCopies = true;
		}
	}
	found = false;
	if (!multCopies) {
		a = books.size();
		for (int i = 0; i < a; i++) {
			if (books[i].getISBN() == isbn) {
				found = true;
				a--;
			}
			if (found) {
				books[i] = books[i + 1];
			}
		}
	}
	books.erase(books.begin() + books.size() - 1);
}