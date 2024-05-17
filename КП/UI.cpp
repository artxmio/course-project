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
	cout << tab << "Данные сохранены." << endl;
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

void UI::MainMenu(User* u)
{
	LoadMenuAnimation();

	if (u->is_admin())
		AdminModeMessage();

	cout << n;

	cout << tab << "_________________ [ ГЛАВНОЕ МЕНЮ ] _________________" << endl << endl;

	cout << tab << "\t\t1. Заказы" << endl;
	cout << tab << "\t\t2. Меню" << endl;
	cout << tab << "\t\t3. История ресторана" << endl;

	if (!u->is_admin())
		cout << tab << "\t\t4. Режим администратора" << endl;
	else
		cout << tab << "\t\t4. Выйти из режима администратора" << endl;

	cout << tab << "\t\tesc. Выход" << endl;
	cout << endl << tab << "____________________________________________________\n";
}

void UI::OrderMenu(const  User* u)
{
	LoadMenuAnimation();

	if (u->is_admin())
		AdminModeMessage();

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

void UI::RMenuMenu(const User* u)
{
	LoadMenuAnimation();

	if (u->is_admin())
		AdminModeMessage();

	cout << n;

	cout << tab << "________________ [ МЕНЮ РЕСТОРАНА ] ________________" << endl << endl;

	cout << tab << "\t\t1. Меню ресторана" << endl;

	if (u->is_admin())
	{
		cout << tab << "\t\t2. Добавить пункт меню" << endl;
		cout << tab << "\t\t3. Удалить пункт меню" << endl;
	}

	cout << tab << "\t\tesc. Выход" << endl;
	cout << endl << tab << "____________________________________________________\n";
}

User UI::Autorization() const
{
	system("cls");
	LoadMenuAnimation();

	//для хранения текущий логина и пароля
	string _login;
	string _password;

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
	*/
	cout << tab << "____________________________________________________\n\n";

	//проверка данных на наличие в базе данных 
	if (_logins.count(_login) and _logins.at(_login) == _password)
	{
		cout << tab << "Доступ разрешён";
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
		cout << "\n\n";
		string _login;
		cout << endl << tab << "__________________ [ РЕГИСТРАЦИЯ ] _________________" << endl;

		//справочная информация
		cout << endl << tab << "Правила регистрации:" << endl;
		cout << endl << tab << " 1. Логин(пароль) должен быть не менее 5(8) символов";
		cout << endl << tab << " 2. Логин не должен содержать симовлы - ";
		cout << endl << tab << "	!@#$%^&*()-\"\'№;%:?<>/\\" << endl;
		cout << tab << "____________________________________________________\n";

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
			error e = Validation(_login, _password);
			if (e.is)
			{
				cout << endl << tab << e.message << endl;

				cout << tab << "____________________________________________________\n";
				cout << endl << tab << "Нажмите любую клавишу для продолжения" << endl;
				pause();
				break;
			}


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

error UI::Validation(string _login, string _password)
{
	error e;

	//проверка логина на длину
	if (_login.size() < 5)
	{
		e.is = true;
		e.message = "Длина логина должна быть больше или равна 5 символам";
		return e;
	}
	//проверка логина на запрещенные символы
	for (const char item : _login)
	{
		size_t pos = e.invalid_symbols.find(item);
		if (pos != string::npos)
		{
			e.is = true;
			e.message = "Логин не должен содержать запрещенные символы";
			return e;
		}
	}

	//проверка пароля на длину
	if (_password.size() < 8)
	{
		e.is = true;
		e.message = "Длина пароля должна быть больше или равна 8 символам";
		return e;
	}

	return e;
}

void UI::SingInAdmin(User* u)
{
	system("cls");
	LoadMenuAnimation();

	//код администратора
	constexpr int ADMIN = 112233;

	//получаем код от пользователя
	bool _continue = true;
	do
	{
		system("cls");
		cout << "\n\n\n\n\n\n\n";
		cout << endl << tab << "__________________ [ АВТОРИЗАЦИЯ ] _________________" << endl;

		cout << endl << tab << "\tЧтобы получить права администратора,\n"
			<< tab << "\tнеобходимо ввести код администратора" << endl;
		cout << tab << "____________________________________________________\n";

		cout << endl << tab << "\tКод: ";
		int _your_code = 0;
		cin >> _your_code;

		if (_your_code == ADMIN)
		{
			cout << endl << tab << "\tДоступ на правах администратора разрешён\n";
			u->set_admin(true);
			return;
		}
		else
		{
			cout << tab << "____________________________________________________\n";
			cout << endl << tab << "\tНеверный код\n";
		}

		//можно попробовать ещё раз ввести код
		cout << tab << "____________________________________________________\n";
		cout << tab << "\n\tПопробовать ещё? (y/n)\n";

		do
		{
			const char __continue = _getch();
			if (__continue == 'n')
			{
				_continue = false;
				break;
			}
			else if (__continue == 'y')
				break;

		} while (true);
	} while (_continue);


	cout << tab << "____________________________________________________\n";
	cout << endl << tab << "Нажмите любую клавишу для продолжения" << endl;
	pause();
	system("cls");
}

void UI::ExitAdmin(User* u)
{
	system("cls");
	cout << n;
	cout << endl << tab << "___________________ [ ВЫХОД ] __________________" << endl;

	cout << endl << tab << "\tТочно желаете выйти? (y/n)\n";

	bool _continue = true;
	do
	{
		const char __continue = _getch();
		if (__continue == 'n')
		{
			_continue = false;
			break;
		}
		else if (__continue == 'y') //если да, то убираем права админа
		{
			_continue = false;

			u->set_admin(false);

			break;
		}

	} while (_continue);

	cout << tab << "____________________________________________________\n";
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
		Sleep(50);
	}
	cout << "]\n";
	cout << tab << "____________________________________________________\n";
	cout << endl << tab << "Загрузка завершена." << endl;
	Sleep(1000);
	system("cls");
}

void UI::AdminModeMessage() const
{
	cout << "[admin mode]";
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