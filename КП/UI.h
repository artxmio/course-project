#pragma once
#include "User.h"

class UI
{
public:
	void Hello() const;
	void ByeBye() const;
	void MainMenu() const;
	void OrderMenu() const;
	User Autorization() const;
	void RestaurantHistory() const;
	void LoadMenuAnimation() const;
private:
	string tab = "\t\t\t\t";
};