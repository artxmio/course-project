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
	cout << tab << "____________________________________________________\n" << endl;

	cout << tab << "\tДОБРО ПОЖАЛОВАТЬ В “TRENDY-БУЛЬБА”!!!" << endl;

	cout << tab << "____________________________________________________\n";

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

	cout << tab << "_________________ [ ГЛАВНОЕ МЕНЮ ] _________________" << endl <<endl;
	cout << tab << "\t\t1. Меню заказов" << endl;
	cout << tab << "\t\t2. Меню ресторана" << endl;
	cout << tab << "\t\t3. История ресторана" << endl;
	cout << tab << "\t\t0. Выход" << endl;
	cout << endl << tab << "____________________________________________________\n";
}

void UI::OrderMenu()
{
	LoadMenuAnimation();

	cout << tab << "____________________ [ Заказы ] ____________________" << endl;
	cout << endl << tab << "\t\t1. Показать все заказы заказов" << endl;
	cout << tab << "\t\t2. Добавить заказ (admin)" << endl;
	cout << tab << "\t\t3. Удалить заказ (admin)" << endl;
	cout << tab << "\t\t0. Выйти в главное меню" << endl;
	cout << endl << tab << "____________________________________________________\n";

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
	cout << endl <<tab << "__________________ [ АВТОРИЗАЦИЯ ] _________________" << endl;
	
	cout << endl << tab << "\t\tВведите имя: ";
	cin >> aut._name;

	cout << endl << tab << "\t\tВведите логин: ";
	cin >> aut._login;

	cout << endl << tab << "\t\tВведите пароль: ";
	cin >> aut._password;
	
	cout << tab << "____________________________________________________\n";
	if (aut._login == "admin" && aut._password == "12345")
	{
		cout << endl << tab << "Доступ на правах администратора разрешён." << endl;
		Sleep(2000);
		return User(aut._name, true);
	}
	else if (aut._login == "user" && aut._password == "54321")
	{
		cout << endl << tab << "Доступ на правах пользователя разрешён." << endl;
		Sleep(2000);
		return User(aut._name, false);
	}
	else
	{
		cout << endl << tab << "Такого логина или пароля не существует. Попробуйте снова." << endl;
		Sleep(2000);
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

	cout << tab << "____________________________________________________\n";
	cout << endl << tab << tab << "    Загрузка..." << endl;
	cout << tab << "____________________________________________________\n";
	cout << endl << tab << "\t  [";
	for (int i = 0; i < 10; i++)
	{
		cout << load_simb;
		Sleep(200);
	}
	cout << "]\n";
	cout << tab << "____________________________________________________\n";
	cout << endl << tab << "Загрузка завершена. Нажмите любую клавишу для продолжения..." << endl;
	pause();
	system("cls");
}