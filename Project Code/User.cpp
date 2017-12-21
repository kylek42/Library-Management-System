#pragma once
#include "User.h"


using namespace std;

User::User()
{
	setUsernameNew();
	setPasswordNew();
}

User::User(string s) {
	setUsername(s);
	setPasswordNew();
}

User::User(string s1, string s2) {
	setUsername(s1);
	setPassword(s2);
}

User::User(string s1, string s2, int i3) {
	setUsername(s1);
	setUsername(s2);
	setUserType(i3);
}

void User::setUsernameNew()
{
	cout << "\nPlease enter a username for the new user: ";
	cin >> username;
}

void User::setUsername(string s)
{
	username = s;
}

void User::setUsernameChange()
{
	cout << "\nPlease enter a new username: ";
	cin >> username;
}

void User::setPasswordNew()
{
	cout << "\nPlease enter a password for new user " << username << ": ";
	string temp1, temp2;
	cin >> temp1;
	cout << "\nPlease reenter the password: ";
	cin >> temp2;
	if (temp1 == temp2) {
		password = temp1;
		return;
	}
	else {
		cout << "\nPasswords did not match...";
		setPasswordNew();
		return;
	}
}

void User::setPasswordChange()
{
	cout << "\nPlease enter a new password for user " << username << ": ";
	string temp1, temp2;
	cin >> temp1;
	cout << "\nPlease reenter the password: ";
	cin >> temp2;
	if (temp1 == temp2) {
		password = temp1;
		return;
	}
	else {
		cout << "\nPasswords did not match...";
		setPasswordChange();
		return;
	}
}
void User::setPassword(string s)
{
	password = s;
}

void User::setUserType(int ut) {
	userType = ut;
}

string User::getUsername()
{
	return username;
}

string User::getPassword()
{
	return password;
}

int User::getUserType() {
	return userType;
}

