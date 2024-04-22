#pragma once
#include "User.h"

class UI
{
public:
	void Hello();
	void ByeBye();
	void MainMenu();
	void OrderMenu();
	User Autorization();
	void RestaurantHistory();
private:
	void LoadMenuAnimation();
};