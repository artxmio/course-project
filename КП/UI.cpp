#include "UI.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
using namespace std;

void pause();

void UI::MainMenu()
{
	cout << "Добро пожаловать в “TrendyБульба”" << endl;
	cout << "\nДля продолжения нажмите любую клавишу...";
	pause();

	system("cls");
	LoadMenuAnimation();
	system("cls");

	cout << "ГЛАВНОЕ МЕНЮ" << endl;
	cout << "1. Меню заказов" << endl;
	cout << "2. История ресторана" << endl;
	cout << "0. Выход" << endl;
}

void UI::OrderMenu()
{
	system("cls");
	LoadMenuAnimation();
	system("cls");

	cout << "МЕНЮ ЗАКАЗОВ" << endl;
	cout << "1. Готовность заказов" << endl;
	cout << "2. Добавить заказ (admin)" << endl;
	cout << "3. Удалить заказ (admin)" << endl;
	cout << "0. Выйти в главное меню" << endl;
}

void UI::АuthenticationMenu()
{
}

void UI::RestaurantHistory()
{
	pause();
	system("cls");
	LoadMenuAnimation();
	system("cls");

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
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const string load_simb = " - ";

	cout << "Загрузка..." << endl;
	cout << "\n[";
	for (int i = 0; i < 10; i++)
	{
		cout << load_simb;
		Sleep(500);
	}
	cout << "]";
	cout << "\n\nЗагрузка завершена. Нажмите любую клавишу для продолжения..." << endl;
	pause();
}
