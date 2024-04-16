#pragma once

class UI
{
public:
	void MainMenu();
	void OrderMenu();
	void АuthenticationMenu();
	void RestaurantHistory();
private:
	bool isadmin; //true - пользователь является админом.

	void LoadMenuAnimation();
};

