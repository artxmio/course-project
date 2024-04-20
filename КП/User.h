#pragma once
#include <string>
using namespace std;

class User
{
public: 
	User();
	User(string name, bool is_admin);
	string name;
	bool is_admin;
};

