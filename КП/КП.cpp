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

	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
}

int main()
{
	//установка настроек консоли
	setsettings();

	//основные объекты
	UI userInterface;
	Restaurant restaurant;
	User user;
	error e("У вас нет прав администратора.\n\t\t\t\tВойдите и попробуйте снова");

	//загрузка информации
	restaurant.LoadOrders();
	restaurant.LoadMenuData();
	userInterface.LoadLogins();

	userInterface.Hello();
	userInterface.LoadMenuAnimation();

	//авторизация/регистрация пользователя
	bool _continue = true;
	do
	{
		const char change_start_menu = userInterface.StartMenu();;
		switch (change_start_menu)
		{
		case 1:
			user = userInterface.Autorization();

			if (!user.alive()) break;
			_continue = false;
			break;
		case 2:
			userInterface.LoadMenuAnimation();
			userInterface.Registration();
			break;
		case 27:
			exit(0);
		default: break;
		}
	} while (_continue);

	system("cls");

	//основная часть программы
	_continue = true;
	userInterface.LoadMenuAnimation();
	while (_continue)
	{
		const char _change_main = userInterface.MainMenu(&user);

		switch (_change_main)
		{
			//работа с заказами
		case 1:
		{
			fflush(stdin);
			bool __continue = true;
			userInterface.LoadMenuAnimation();
			while (__continue)
			{
				const char _change_orders = userInterface.OrderMenu(&user);

				switch (_change_orders)
				{
				case 1: //показать все заказы

					userInterface.LoadMenuAnimation();
					restaurant.ShowOrders();

					break;

				case 2: //добавить заказ

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.AddOrder();
					}
					else
					{
						cout << "\t\t\t\t" << e.message;
						pause();
					}

					break;

				case 3: //удалить заказ

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.DelOrder();
					}
					else
					{
						cout << "\t\t\t\t" << e.message;
						pause();
					}

					break;

				case 4: //тут что-то про отметку о готовности заказа

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.CheckMark();
					}
					else 
					{
						cout << "\t\t\t\t" << e.message;
						pause();
					}

					break;

				case 27: //ждё нажатие клавиши 'esc'

					userInterface.LoadMenuAnimation();
					__continue = false;
					break;

				default:  break;
				}
			}
			break;
		}
		case 2: //меню ресторана
		{
			bool __continue = true;
			userInterface.LoadMenuAnimation();

			while (__continue)
			{
				const char _change_menu = userInterface.RMenuMenu(&user);

				switch (_change_menu)
				{
				case 1:

					userInterface.LoadMenuAnimation();
					restaurant.ShowMenu();
					pause();

					break;
				case 2:

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.AddNewMenuItem();
					}
					else
					{
						cout << "\t\t\t\t" << e.message;
						pause();
					}

					break;
				case 3:

					if (user.is_admin())
					{
						userInterface.LoadMenuAnimation();
						restaurant.DelMenuItem();
					}
					else
					{
						cout << "\t\t\t\t" << e.message;
						pause();
					}

					break;
				case 27: //ждё нажатие клавиши 'esc'

					userInterface.LoadMenuAnimation();
					__continue = false;
					break;

				default:
					break;
				}
			}
			break;
		}
		case 3: //история ресторана

			userInterface.RestaurantHistory();
			break;

		case 4: //вход под администратором

			if (!user.is_admin())
				userInterface.SingInAdmin(&user);
			else
				userInterface.ExitAdmin(&user);

			break;

		case 5: //история ресторана

			userInterface.About();
			pause();
			break;

		case 27: //также ждёт нажатия 'esc'

			userInterface.LoadMenuAnimation();
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