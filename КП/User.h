#pragma once
#include <string>
using namespace std;

class User
{
private:
	bool _is_admin;
	string _login;
	string _password;
public: 
	User();
	User(bool is_admin, string login, string pass);

	bool is_admin() const noexcept;
};