#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include "Restaurant.h"
#include "UI.h"
#include "User.h"
using namespace std;

void pause()
{
	_getch();
}

int main()
{
	setlocale(LC_ALL, "ru");

	UI userInterface;
	Restaurant restaurant;
	User user;

	user = userInterface.Autorization();
	
	pause();
	system("cls");

	cout << "Добро пожаловать в “TrendyБульба”!!!" << endl;
	Sleep(1000);
	while (true)
	{
		userInterface.MainMenu();

		const char change_main_menu = _getch();

		switch (change_main_menu)
		{
		case '1': //работа с заказами

			userInterface.OrderMenu();
			pause();
			break;

		case '2': //меню ресторана

			restaurant.ShowMenu();
			pause();
			break;

		case '3': //история ресторана

			userInterface.RestaurantHistory();
			pause();
			break;

		case '0':

			break;
		default: break;
		}
	}
}