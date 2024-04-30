#pragma once
#include "User.h"
#include <map>;
using namespace std;

class UI
{
public:
	void Hello() const;
	void ByeBye() const;

	void StartMenu() const;
	void MainMenu() const; 
	void OrderMenu(const User* u) const;

	User Autorization() const;
	void Registration();

	void RestaurantHistory() const;

	void LoadMenuAnimation() const;
	void LoadLogins();
	void SaveLogin(const string* login, const string* pass);
private:
	map<string, string> _logins;

	const string tab = "\t\t\t\t";
	const string n = "\n\n\n\n\n\n\n\n\n";
};