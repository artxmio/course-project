#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include "Restaurant.h"
#include "UI.h"
#include "User.h"
using namespace std;

void pause() noexcept
{
	const char c = _getch();
}
static void warning()
{
	cout << "\n\t\tОшибка. У вас нет прав администратора." << endl;
	Sleep(1500);
}

int main()
{
	setlocale(LC_ALL, "ru");

	UI userInterface;
	Restaurant restaurant;
	User user;

	restaurant.LoadOrders();

	user = userInterface.Autorization();
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
				case '1': //показать все заказы

					userInterface.LoadMenuAnimation();
					restaurant.ShowOrders();
					break;

				case '2': //добавить заказ

					if (user.is_admin)
					{
						userInterface.LoadMenuAnimation();
						restaurant.AddOrder();
					}
					else warning();
					break;

				case '3': //удалить заказ

					if (user.is_admin)
					{
						userInterface.LoadMenuAnimation();
					}
					else warning();
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
	return 0;
}