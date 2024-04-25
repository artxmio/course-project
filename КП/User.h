#pragma once
#include <string>
using namespace std;

class User
{
public: 
	User();
	User(bool is_admin);

	bool is_admin;
};

