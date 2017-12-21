#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <list>
#include <vector>
#include <ctime>

using namespace std;

class User {
private:
	//data members
	string username = string();
	string password = string();
	int userType;
public:
	//constructors
	User();
	User(string s);
	User(string s1, string s2);
	User(string s1, string s2, int i3);
	//mutators
	void setPassword(string s);
	void setPasswordNew();
	void setPasswordChange();
	void setUsernameNew();
	void setUsername(string s);
	void setUsernameChange();
	void setUserType(int ut);
	//accessors
	string getUsername();
	string getPassword();
	int getUserType();
};
