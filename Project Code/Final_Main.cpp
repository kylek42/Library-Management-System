#include "DisplayOption.h"

/*note
clock begins when user logs in,
clock stops when user logs out,
located in displayoption-switchoption
*/
using namespace std;



bool authenticate(FileOp &a);

void main() {
	/*
	int a;
	clock_t start = clock();
	for (int i = 0; i < 3; i++) {
	cout << "\n";
	cin >> a;
	clock_t cur = clock();
	cout << "\n" << int(cur - start) / CLOCKS_PER_SEC;
	}
	*/

	FileOp files;
	files.read();
	bool login;


	//HEADER
	cout << "\n--------------------------------------------------------------------------" << endl;
	cout << "			Welcome to Our Library!" << endl;
	cout << "	Please see the ReadMe.txt and Books.dat for instructions!" << endl;
	cout << "--------------------------------------------------------------------------" << endl;

	do {
		login = authenticate(files);
		if (login) {
			int term = 1;
			cout << "\n\n\nEnter 1 to return to login screen, 0 to terminate: ";
			cin >> term;
			if (term == 0) {
				login = false;
				exit(1);
			}
		}
	} while (login);
	system("pause");
	return;
}


bool authenticate(FileOp &files) {
	int utype, locate, loginAttempts(0);
	bool nameExists, passMatch;
	string userAttempts, passAttempts;
	do {
		utype = 5;
		nameExists = false;
		passMatch = false;
		cout << "\n\nPlease enter login credentials:\nUsername: ";
		cin >> userAttempts;
		for (int i = 0; i < files.readers.size(); i++) {
			if (files.readers[i].getUsername() == userAttempts) {
				nameExists = true;
				files.currentUser = userAttempts;
				utype = files.readers[i].getUserType();
				locate = i;
			}
		}
		for (int i = 0; i < files.librs.size(); i++) {
			if (files.librs[i].getUsername() == userAttempts) {
				nameExists = true;
				files.currentUser = userAttempts;
				utype = 2;
				locate = i;
			}
		}
		if (!nameExists) {
			cout << "\nUser does not exist, try again...";
			continue;
		}
		files.currentUser = userAttempts;
		cout << "Please enter your password: ";
		//masks password for windows OS
		char c;
		while ((c = _getch()) != '\r') {
			if (c == '\b') {
				cout << '\b';
				cout << " ";
				cout << '\b';
				passAttempts = passAttempts.substr(0, passAttempts.length() - 1);
			}
			else {
				cout << '*';
				passAttempts += c;
			}
		}
		if (utype < 2) {
			if (files.readers[locate].getPassword() == passAttempts) {
				DisplayOption display;
				display.setUserType(0);
				cout << "\n\nWelcome, " << userAttempts << "\n" << endl;
				display.switchOptions(files);
				files.write();
				return true;
			}
			else {
				loginAttempts++;
				cout << "\nIncorrect Password...";
			}
		}
		else if (utype == 2) {
			if (files.librs[locate].getPassword() == passAttempts) {
				DisplayOption display;
				display.setUserType(1);
				cout << "\n\nWelcome, " << userAttempts << "\n" << endl;
				display.switchOptions(files);
				files.write();
				return true;
			}
			else {
				loginAttempts++;
				cout << "\nIncorrect Password...";
			}
		}
	} while (loginAttempts<3);
	if (loginAttempts == 3) {
		cout << "\nLogin attempts exceeded.";
		return false;
		exit(1);
		//terminates
	}
	return false;
}