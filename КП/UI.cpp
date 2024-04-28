#include "UI.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <map>;
#include <utility>
#include "User.h"
using namespace std;

void pause();

void UI::Hello() const
{
	cout << tab << "____________________________________________________\n" << endl;

	cout << tab << "\tДОБРО ПОЖАЛОВАТЬ В “TRENDY-БУЛЬБА”!!!" << endl;

	cout << tab << "____________________________________________________\n";

	Sleep(2000);
}

void UI::ByeBye() const
{
	system("cls");
	cout << endl << tab << "__________________ [ Прощай ] ___________________\n" << endl;
	cout << tab << "Спасибо за то, что выбрали наше приложение!:)" << endl;
	cout << tab << "Данные сохранены в файле orders.txt:)";
	pause();
}

void UI::StartMenu() const
{
	LoadMenuAnimation();

	cout << tab << "_______________ [ ДОБРО ПОЖАЛОВАТЬ ] _______________" << endl << endl;
	cout << tab << "\t\t1. Войти" << endl;
	cout << tab << "\t\t2. Зарегистрироваться" << endl;
	cout << tab << "\t\t0. Выход" << endl;
	cout << endl << tab << "____________________________________________________\n";
}

void UI::MainMenu() const
{
	LoadMenuAnimation();

	cout << tab << "_________________ [ ГЛАВНОЕ МЕНЮ ] _________________" << endl <<endl;
	cout << tab << "\t\t1. Заказы" << endl;
	cout << tab << "\t\t2. Меню ресторана" << endl;
	cout << tab << "\t\t3. История ресторана" << endl;
	cout << tab << "\t\t0. Выход" << endl;
	cout << endl << tab << "____________________________________________________\n";
}

void UI::OrderMenu() const
{
	LoadMenuAnimation();

	cout << tab << "____________________ [ Заказы ] ____________________" << endl;
	cout << endl << tab << "\t\t1. Показать все заказы" << endl;
	cout << tab << "\t\t2. Добавить заказ (admin)" << endl;
	cout << tab << "\t\t3. Удалить заказ (admin)" << endl;
	cout << tab << "\t\t4. Изменить готовность заказа (admin)" << endl;
	cout << tab << "\t\t0. Выйти в главное меню" << endl;
	cout << endl << tab << "____________________________________________________\n";

}

User UI::Autorization() const
{
	system("cls");
	string _login;
	string _password;
	start_aut:
	cout << endl <<tab << "__________________ [ АВТОРИЗАЦИЯ ] _________________" << endl;

	cout << endl << tab << "\t\tВведите логин: ";
	cin >> _login;

	cout << endl << tab << "\t\tВведите пароль: ";
	cin >> _password;
	
	int _admin_code = 0;
	cout << endl << tab << "\t\tВведите код администратора?\n"
		<< tab << "(если его нет, оставьте строку пустой): ";
	cin >> _admin_code;

	cout << tab << "____________________________________________________\n";

	if (_logins.count(_login) > 0 and _logins.at(_login) == _password and _admin_code == 1488)
	{
		cout << tab << "Доступ на правах администратора разрешён";
		return User(true, _login, _password);
	}
	else if (_logins.count(_login) and _logins.at(_login) == _password)
	{
		cout << tab << "Доступ на правах администратора разрешён";
		return User(true, _login, _password);
	}
	else
	{
		cout << "Неверный логин или пароль.";
		pause();
		system("cls");
		goto start_aut;
	}
}

User UI::Registration()
{
	system("cls");
	string _login;
	cout << endl << tab << "__________________ [ РЕГИСТРАЦИЯ ] _________________" << endl;
	cout << endl << tab << "\t\tВведите логин: ";
	cin >> _login;

	string _password;
	cout << endl << tab << "\t\tВведите пароль: ";
	cin >> _password;

	cout << tab << "____________________________________________________\n";

	_logins.insert({_login, _password});
	SaveLogin(&_login, &_password);
	return Autorization();
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
}

void UI::LoadMenuAnimation() const
{
	system("cls");

	const string load_simb = " - ";

	cout << tab << "____________________________________________________\n";
	cout << endl << "\t\t\t\t\t\t    Загрузка..." << endl;
	cout << tab << "____________________________________________________\n";
	cout << endl << tab << "\t  [";
	for (int i = 0; i < 10; i++)
	{
		cout << load_simb;
		Sleep(200);
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
		
		_logins.insert({_login, _pass});
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