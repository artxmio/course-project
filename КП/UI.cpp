#include "UI.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include "User.h"
using namespace std;

void pause();

void UI::Hello()
{
	cout << "____________________________________________________\n";

	cout << "\n\tДОБРО ПОЖАЛОВАТЬ В “TRENDY-БУЛЬБА”!!!" << endl;

	cout << "____________________________________________________\n";

	Sleep(2000);
}

void UI::ByeBye()
{
	system("cls");
	cout << "Спасибо за то, что выбрали наше приложение!:)";
	pause();
}

void UI::MainMenu()
{
	LoadMenuAnimation();

	cout << "---------------- [ ГЛАВНОЕ МЕНЮ ] ------------------" << endl <<endl;
	cout << "\t\t1. Меню заказов" << endl;
	cout << "\t\t2. Меню ресторана" << endl;
	cout << "\t\t3. История ресторана" << endl;
	cout << "\t\t0. Выход" << endl;
	cout << "\n____________________________________________________\n";
}

void UI::OrderMenu()
{
	LoadMenuAnimation();

	cout << "------------------- [ Заказы ] ---------------------" << endl;
	cout << "\n\t\t1. Готовность заказов" << endl;
	cout << "\t\t2. Добавить заказ (admin)" << endl;
	cout << "\t\t3. Удалить заказ (admin)" << endl;
	cout << "\t\t0. Выйти в главное меню" << endl;
	cout << "\n____________________________________________________\n";

}

struct autorization
{
	string _login;
	string _password;
	string _name;
};

User UI::Autorization()
{
	autorization aut;
	start_aut:
	cout << "\n------------------ [ АВТОРИЗАЦИЯ ] -----------------" << endl;
	
	cout << "\n\t\tВведите имя: ";
	cin >> aut._name;

	cout << "\n\t\tВведите логин: ";
	cin >> aut._login;

	cout << "\n\t\tВведите пароль: ";
	cin >> aut._password;
	
	cout << "____________________________________________________\n";
	if (aut._login == "admin" && aut._password == "12345")
	{
		cout << "\nДоступ на правах администратора разрешён." << endl;
		return User(aut._name, true);
	}
	else if (aut._login == "user" && aut._password == "54321")
	{
		cout << "\nДоступ на правах пользователя разрешён." << endl;
		return User(aut._name, false);
	}
	else
	{
		cout << "\nТакого логина или пароля не существует. Попробуйте снова." << endl;
		pause();
		system("cls");
		goto start_aut;
	}
}

void UI::RestaurantHistory()
{
	LoadMenuAnimation();

	string line;

	ifstream in("source\\history.txt");
	if (in.is_open())
		while (getline(in, line))
		{
			cout << line << endl;
			Sleep(100);
		}
	in.close();
}

void UI::LoadMenuAnimation()
{
	system("cls");

	const string load_simb = " - ";

	cout << "____________________________________________________\n";
	cout << "\n\t\t    Загрузка..." << endl;
	cout << "____________________________________________________\n";
	cout << "\n\t  [";
	for (int i = 0; i < 10; i++)
	{
		cout << load_simb;
		Sleep(300);
	}
	cout << "]\n";
	cout << "____________________________________________________\n";
	cout << "\nЗагрузка завершена.\nНажмите любую клавишу для продолжения..." << endl;
	pause();
	system("cls");
}