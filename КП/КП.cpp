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
void setsettings() noexcept
{
	srand(static_cast<unsigned int>(time(0)));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = false; // изменяем видимость курсора
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
	SetConsoleTitle(L"Trendy Бульбу by Tёmik");
}

int main()
{
	setsettings();
	UI userInterface;
	Restaurant restaurant;
	User user;

	//загрузка информации
	restaurant.LoadOrders();
	userInterface.LoadLogins();

	userInterface.Hello();


	start:
	userInterface.StartMenu();
	const char change_start_menu = _getch();
	switch (change_start_menu)
	{
	case '1':
		user = userInterface.Autorization();
		break;
	case '2':
		user = userInterface.Registration();
		break;
	default: goto start; break;
	}

	system("cls");

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

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.AddOrder();
					}
					else warning();
					break;

				case '3': //удалить заказ

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.DelOrder();
					}
					else warning();
					break;

				case '4': //тут что-то про отметку о готовности заказа

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.CheckMark();
					}
					else warning();
					break;

				case '0':

					__continue = false;
					break;

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
			restaurant.SaveOrders();
			_continue = false;
			break;
		default: break;
		}
	}
	return 0;
}