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
	_getch();
}

static void setsettings() noexcept
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));
	system("mode con cols=115 lines=30");

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = false; // изменяем видимость курсора
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
	SetConsoleTitle(L"Trendy Бульба by Tёmik");

	HWND consoleWindow = GetConsoleWindow();
	SetWindowLongPtr(consoleWindow, GWL_STYLE, GetWindowLongPtr(consoleWindow, GWL_STYLE) & ~WS_THICKFRAME);
	SetWindowLongPtr(consoleWindow, GWL_STYLE, GetWindowLongPtr(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX);
	SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

int main()
{
	//установка настроек консоли
	setsettings();

	//основные объекты
	UI userInterface;
	Restaurant restaurant;
	User user;

	//загрузка информации
	restaurant.LoadOrders();
	restaurant.LoadMenuData();
	userInterface.LoadLogins();

	userInterface.Hello();

	//авторизация/регистрация пользователя
start:
	userInterface.StartMenu();
	const char change_start_menu = _getch();
	switch (change_start_menu)
	{
	case '1':
		user = userInterface.Autorization();
		break;
	case '2':
		userInterface.Registration();
		goto start;
		break;
	case '0':
		exit(0);
	default: goto start; break;
	}

	system("cls");

	//основная часть программы
	bool _continue = true;
	while (_continue)
	{
		userInterface.MainMenu(&user);

		switch (_getch())
		{
			//работа с заказами
		case '1':
		{
			fflush(stdin);
			bool __continue = true;
			while (__continue)
			{
				userInterface.OrderMenu(&user);

				switch (_getch())
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
					break;

				case '3': //удалить заказ

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.DelOrder();
					}
					break;

				case '4': //тут что-то про отметку о готовности заказа

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.CheckMark();
					}
					break;

				case 27: //ждё нажатие клавиши 'esc'

					__continue = false;
					break;

				default: break;
				}
			}
			break;
		}
		case '2': //меню ресторана
		{
			bool __continue = true;

			while (__continue)
			{
				userInterface.RMenuMenu(&user);

				switch (_getch())
				{
				case '1':

					userInterface.LoadMenuAnimation();
					restaurant.ShowMenu();
					pause();

					break;
				case '2':

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.AddNewMenuItem();
					}

					break;
				case '3':

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.DelMenuItem();
					}

					break;
				case 27: //ждё нажатие клавиши 'esc'

					__continue = false;
					break;

				default:
					break;
				}
			}
			break;
		}
		case '3': //история ресторана

			userInterface.RestaurantHistory();
			pause();
			break;

		case '4': //вход под администратором

			if (!user.is_admin())
				userInterface.SingInAdmin(&user);
			else
				userInterface.ExitAdmin(&user);

			break;

		case 27: //также ждёт нажатия 'esc'

			userInterface.ByeBye();
			restaurant.SaveOrders();
			restaurant.SaveMenuData();
			_continue = false;
			break;

		default: break;
		}
	}
	return 0;
}