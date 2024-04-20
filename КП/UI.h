#pragma once
#include "User.h"

class UI
{
public:
	void MainMenu();
	void OrderMenu();
	User Autorization();
	void RestaurantHistory();
private:
	void LoadMenuAnimation();
};