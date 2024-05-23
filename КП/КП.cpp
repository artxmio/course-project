#include "includes_file.h"
#ifndef _INCLUDES_FILE_H
#define _INCLUDES_FILE_H
#endif

using namespace std;

void pause() noexcept
{
	_getch();
}

//установка настроек консоли
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
	UI userInterface;       //интерфейс программы
	Restaurant restaurant;  //объект с функциями программы
	User user;				//пользователь программы

	//ошибка доступа к функциям
	error e("У вас нет прав администратора.\n\t\t\t\tВойдите и попробуйте снова");

	//загрузка информации
	restaurant.LoadOrders();    //загрузка информации о заказах
	restaurant.LoadMenuData();  //загрузка блюд из меню
	userInterface.LoadLogins(); //загрузка информации о пользователях

	userInterface.Hello();      //приветственное меню
	userInterface.LoadMenuAnimation();

	//этап входа пользователя
	bool _continue = true;
	do
	{
		/*
			Во все функции вывода меню приложения вшит
			возврат значения нажатой клавиши
		*/
		const char change_start_menu = userInterface.StartMenu();;

		switch (change_start_menu)
		{
			//авторизация
		case 1:

			user = userInterface.Autorization();
			/*
				Если авторизация будет отменена клавишей esc, то в
				пользователе установится свойство user_alive = false;
			*/
			if (!user.alive()) break;

			//при успешной авторизации этап завершается
			_continue = false;

			break;

			//регистрация
		case 2:
			userInterface.LoadMenuAnimation();
			userInterface.Registration();
			break;

			//выход
		case 27:
			exit(0);

		default: break;
		}
	} while (_continue);

	system("cls");

	//основной этап программы
	_continue = true;

	userInterface.LoadMenuAnimation();

	while (_continue)
	{
		const char _change_main = userInterface.MainMenu(&user);

		switch (_change_main)
		{
		//работа с заказами ресторана
		case 1:
		{
			//очистка буфера консоли
			fflush(stdin);

			//работа с заказами до нажатия кнопки выхода
			bool __continue = true;
			userInterface.LoadMenuAnimation();
			while (__continue)
			{
				const char _change_orders = userInterface.OrderMenu(&user);

				switch (_change_orders)
				{
					//показать все заказы
				case 1:

					userInterface.LoadMenuAnimation();
					restaurant.ShowOrders();

					break;
					//добавить заказ
				case 2:

					userInterface.LoadMenuAnimation();
					restaurant.AddOrder();

					break;

					//удалить заказ
				case 3:

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

					//тут что-то про отметку о готовности заказа
				case 4:

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

					//выход на клавишу esc
				case 27:

					userInterface.LoadMenuAnimation();
					__continue = false;
					break;

				default:  break;
				}
			}
			break;
		}
		//работа с меню ресторана
		case 2:
		{
			bool __continue = true;
			userInterface.LoadMenuAnimation();

			while (__continue)
			{
				const char _change_menu = userInterface.RMenuMenu(&user);

				switch (_change_menu)
				{
					//вывод меню ресторана
				case 1:

					userInterface.LoadMenuAnimation();
					restaurant.ShowMenu();
					pause();

					break;

					//добавление нового пункта меню
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

					//удаление пункта меню по названию
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

					//выход на прошлое меню при нажатии esc
				case 27:

					userInterface.LoadMenuAnimation();
					__continue = false;
					break;

				default:
					break;
				}
			}
			break;
		}
		//мой профиль
		case 3:
		{
			bool __continue = true;
			userInterface.LoadMenuAnimation();

			while (__continue)
			{
				const char _change_user = userInterface.UserProfile(&user);

				switch (_change_user)
				{
					//личная информация
				case 1:

					break;

					//мои заказы
				case 2:

					break;

					//выход на главное меню
				case 27:

					__continue = false;
					break;

				default:
					break;
				}
			}
			break;
		}

		//вход под администратором
		case 4:

			if (!user.is_admin())
				userInterface.SingInAdmin(&user);
			else
				userInterface.ExitAdmin(&user);

			break;

			//информация о разработчике
		case 5:

			userInterface.About();
			pause();
			break;

			//выход на клавишу esc
		case 27:

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