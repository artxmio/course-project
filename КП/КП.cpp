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

	userInterface.Hello();

	bool _continue = true;
	while (_continue)
	{
		userInterface.MainMenu();

		const char change_main_menu = _getch();

		switch (change_main_menu)
		{
		case '1': //работа с заказами
		{
			fflush(stdin);
			bool __continue = true;
			while (__continue)
			{
				userInterface.OrderMenu();


				const char change_order_menu = _getch();

				switch (change_order_menu)
				{
				case '1': //добавить заказ
					restaurant.AddOrderInFile();
					pause();
					break;
				case '2':

					restaurant.AddOrderInFile();
					break;

				case '3':

					restaurant.DelOrder();
					break;

				case '0': __continue = false; break;
				default: break;
				}
			}

			break;
		}


		case '2': //меню ресторана

			restaurant.ShowMenu();
			pause();
			break;

		case '3': //история ресторана

			userInterface.RestaurantHistory();
			pause();
			break;

		case '0':
			userInterface.ByeBye();
			_continue = false;
			break;
		default: break;
		}
	}
}