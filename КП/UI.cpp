#include "UI.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <map>;
#include "User.h"
using namespace std;

void pause();

void UI::Hello() const
{
	cout << n;

	cout << tab << "____________________________________________________\n" << endl;
	cout << tab << "\tДОБРО ПОЖАЛОВАТЬ В “TRENDY-БУЛЬБА”!!!" << endl;
	cout << tab << "____________________________________________________\n";

	Sleep(2000);
}

void UI::ByeBye() const
{
	system("cls");
	cout << n;
	cout << endl << tab << "___________________ [ Прощай ] _____________________\n" << endl;
	cout << tab << "Спасибо за то, что выбрали наше приложение!:)" << endl;
	cout << tab << "Данные сохранены в файле orders.txt:)" << endl;
	cout << endl << tab << "____________________________________________________\n";
	pause();
}

void UI::StartMenu() const
{
	LoadMenuAnimation();
	cout << n;

	cout << tab << "_______________ [ ДОБРО ПОЖАЛОВАТЬ ] _______________" << endl << endl;
	cout << tab << "\t\t1. Войти" << endl;
	cout << tab << "\t\t2. Зарегистрироваться" << endl;
	cout << tab << "\t\t0. Выход" << endl;
	cout << endl << tab << "____________________________________________________\n";
}

void UI::MainMenu() const
{
	LoadMenuAnimation();
	cout << n;

	cout << tab << "_________________ [ ГЛАВНОЕ МЕНЮ ] _________________" << endl << endl;
	cout << tab << "\t\t1. Заказы" << endl;
	cout << tab << "\t\t2. Меню ресторана" << endl;
	cout << tab << "\t\t3. История ресторана" << endl;
	cout << tab << "\t\tesc. Выход" << endl;
	cout << endl << tab << "____________________________________________________\n";
}

void UI::OrderMenu(const  User* u) const
{
	LoadMenuAnimation();
	cout << n;

	cout << tab << "____________________ [ Заказы ] ____________________" << endl;
	cout << endl << tab << "\t\t1. Показать все заказы" << endl;

	//только админовские опции
	if (u->is_admin())
	{
		cout << tab << "\t\t2. Добавить заказ" << endl;
		cout << tab << "\t\t3. Удалить заказ" << endl;
		cout << tab << "\t\t4. Изменить готовность заказа" << endl;
	}

	cout << tab << "\t\tesc. Выйти в главное меню" << endl;
	cout << endl << tab << "____________________________________________________\n";
}

User UI::Autorization() const
{
	system("cls");
	LoadMenuAnimation();

	//для хранения текущий логина и пароля
	string _login;
	string _password;
	int _sys_admin_code_ = 123;

start_aut:
	//получение данных от пользователя
	cout << n;
	cout << endl << tab << "__________________ [ АВТОРИЗАЦИЯ ] _________________" << endl;

	cout << endl << tab << "\t\tВведите логин: ";
	cin >> _login;

	cout << endl << tab << "\t\tВведите пароль: ";
	cin >> _password;

	/*
		Все пользователи по дефолту являются обычными пользователями
		Чтобы у пользователя был доступ к правам администратора, нужен код администратора
	*/

	//получение кода администратора
	cout << endl << tab << "\t\tУ вас есть код администратора? (y/n)\n";

	int _admin_code = 0;
	bool _continue = true;
	//если кода нет, то скипаем этот участок и начинаем проверку данных
	do
	{
		switch (_getch())
		{
		case 'y':
			cout << endl << tab << "\t\tКод администратора: ";
			cin >> _admin_code;
			_continue = false;
			break;
		case 'n':
			_continue = false;
			break;
		default: break;
		}
	} while (_continue);

	cout << tab << "____________________________________________________\n\n";

	//проверка данных на наличие в базе данных и кода администратора
	if (_logins.count(_login) > 0 and _logins.at(_login) == _password and _admin_code == _sys_admin_code_)
	{
		cout << tab << "Доступ на правах администратора разрешён";
		cout << endl << tab << "Нажмите любую клавишу для продолжения" << endl;
		pause();
		return User(true, _login, _password);
	}
	else if (_logins.count(_login) and _logins.at(_login) == _password) //нет кода администратора или он неверный
	{
		cout << tab << "Доступ на правах пользователя разрешён";
		cout << endl << tab << "Нажмите любую клавишу для продолжения" << endl;
		pause();
		return User(false, _login, _password);
	}
	else //авторизация заново
	{
		cout << endl << tab << "Неверный логин или пароль.";
		cout << endl << tab << "Нажмите любую клавишу для продолжения" << endl;
		pause();
		system("cls");
		goto start_aut;
	}
}

void UI::Registration()
{
	do
	{
		system("cls");
		cout << n;
		string _login;
		cout << endl << tab << "__________________ [ РЕГИСТРАЦИЯ ] _________________" << endl;

		//Получение нового логина и пароля
		cout << endl << tab << "\t\tВведите логин: ";
		cin >> _login;

		string _password;
		cout << endl << tab << "\t\tВведите пароль: ";
		cin >> _password;

		cout << tab << "____________________________________________________\n";

		//проверка на существование такого логина
		if (_logins.count(_login))
		{
			cout << endl << tab << "Такой логин уже существует.";
			cout << endl << tab << "Нажмите любую клавишу для продолжения" << endl;
			pause();
		}
		else //вывод информации о пользователе
		{
			cout << endl << tab << "Вы успешно зарегистрировались." << endl;
			cout << endl << tab << "Ваш логин: " << _login << endl;
			cout << endl << tab << "Ваш пароль: " << _password << endl;

			cout << tab << "____________________________________________________\n";

			cout << endl << tab << "Нажмите любую клавишу для продолжения" << endl;
			pause();

			_logins.insert({ _login, _password });
			SaveLogin(&_login, &_password);
			break;
		}
	} while (true);
}

void UI::RestaurantHistory() const
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
	cout << endl << tab << "Нажмите любую клавишу для выхода" << endl;
}

void UI::LoadMenuAnimation() const
{
	system("cls");

	const string load_simb = " - ";

	cout << n;
	cout << tab << "____________________________________________________\n";
	cout << endl << "\t\t\t\t\t\t    Загрузка..." << endl;
	cout << tab << "____________________________________________________\n";
	cout << endl << tab << "\t  [";
	for (int i = 0; i < 10; i++)
	{
		cout << load_simb;
		Sleep(100);
	}
	cout << "]\n";
	cout << tab << "____________________________________________________\n";
	cout << endl << tab << "Загрузка завершена." << endl;
	Sleep(1000);
	system("cls");
}

void UI::LoadLogins()
{
	ifstream in("source\\logins.txt");

	string _login;
	string _pass;

	while (!in.eof() and in.peek() != EOF)
	{
		in >> _login;
		in >> _pass;

		_logins.insert({ _login, _pass });
	}
	in.close();
}

void UI::SaveLogin(const string* login, const string* pass)
{
	ofstream out("source\\logins.txt", ios::app);

	out << *login << ' ';
	out << *pass << '\n';

	out.close();
}