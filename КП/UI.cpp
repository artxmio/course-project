#include "UI.h"

#define ESC 27
#define UP 72
#define DOWN 80
#define ENTER 13

using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void pause();

//улучшенный cin
void _getstring(string* str, int max)
{
	while (true)
	{
		const char ch = _getch();
		if (ch == 27)
		{
			*str = "";
			return;
		}
		else if (ch == 8)
		{
			if (!str->empty())
			{
				cout << "\b \b"; // Удаление последнего символа из консоли
				str->pop_back();
			}
		}
		else if (ch == 13) {// Проверка на Enter
			break;  // Завершение ввода при нажатии клавиши Enter
		}
		else {
			if (size(*str) < max)
			{
				*str += ch;  // Добавление символа 
				cout << ch;  // Вывод символа
			}
		}
	}
}

char UI::change_options(const string* opt, int size, string title, bool admin = false)
{
	int active = 0;
	for (;;)
	{
		if (admin)
			AdminModeMessage();
		cout << n;
		cout << tab << title << endl << endl;
		for (char i = 0; i < size; i++)
		{
			//текущая указана стрелочкой
			if (i == active) cout << tab << "\t" << "->\t" << opt[i] << endl;
			else cout << tab << "\t\t" << opt[i] << endl;
		}
		cout << endl << tab << "____________________________________________________\n";

		char c = _getch();
		if (c == -32) c = _getch();
		switch (c)
		{
		case ESC:
			return 27;
		case UP:
			if (active > 0)
				--(active);
			break;
		case DOWN:
			if (active < size - 1)
				++(active);
			break;
		case ENTER:
			return (active == size - 1) ? 27 : active + 1;
			break;
		default: break;
		}
		system("cls");
	}
}

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

char UI::StartMenu()
{
	const string options[]
	{
		"- Войти                -",
		"- Зарегистрироваться   -",
		"- Выйти                -"
	};

	system("cls");

	for (;;)
		return change_options(options, size(options), "_______________ [ ДОБРО ПОЖАЛОВАТЬ ] _______________");
}

char UI::MainMenu(User* u)
{
	const string options[]
	{
		"- Работа с заказами    -",
		"- Работа с меню        -",
		"- История ресторана    -",
		"- Режим администратора -",
		"- О программе          -",
		"- Выйти                -"
	};

	system("cls");

	return change_options(options, size(options), "_________________ [ ГЛАВНОЕ МЕНЮ ] _________________", u->is_admin());

}

char UI::OrderMenu(const  User* u)
{
	const string options[]
	{
		"- Показать все заказы        -",
		"- Добавить заказ             -",
		"- Удалить последний заказ    -",
		"- Изменить готовность заказа -",
		"- Выйти                      -"
	};

	system("cls");

	return change_options(options, size(options), "____________________ [ ЗАКАЗЫ ] ____________________", u->is_admin());

}

char UI::RMenuMenu(const User* u)
{

	const string options[]
	{
		"- Меню ресторана      -",
		"- Добавить пункт меню -",
		"- Удалить пункт меню  -",
		"- Выйти               -"
	};

	system("cls");

	return change_options(options, size(options), "________________ [ МЕНЮ РЕСТОРАНА ] ________________", u->is_admin());

}

void UI::About() const
{
	LoadMenuAnimation();

	ifstream in("source\\about.txt");

	if (!in) return;

	string about;

	while (getline(in, about))
		cout << about << endl;
}

User UI::Autorization()
{
	system("cls");
	LoadMenuAnimation();

	//для хранения текущий логина и пароля
	string _login;
	string _password;

start_aut:
	//получение данных от пользователя
	cout << "\n\n\n\n\n";
	cout << endl << tab << "__________________ [ АВТОРИЗАЦИЯ ] _________________" << endl;
	cout << endl << tab << "                     esc. Выход" << endl;
	cout << tab << "____________________________________________________\n\n";


	cout << tab << "Введите логин: ";
	_getstring(&_login, 16);

	if (_login.empty()) return User(false, "", "");

	cout << endl << tab << "Введите пароль: ";
	_getstring(&_password, 16);

	if (_password.empty()) return User(false, "", "");

	/*
		Все пользователи по дефолту являются обычными пользователями
	*/
	cout << endl << tab << "____________________________________________________\n\n";

	//проверка данных на наличие в базе данных 
	if (_logins.count(_login) and _logins.at(_login) == _password)
	{
		cout << tab << "Доступ разрешён";
		cout << endl << tab << "Нажмите любую клавишу для продолжения" << endl;
		pause();
		return User(false, _login, _password, true);
	}
	else //авторизация заново
	{
		cout << tab << "Неверный логин или пароль.";
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

		cout << endl << tab << "__________________ [ РЕГИСТРАЦИЯ ] _________________" << endl;

		//справочная информация
		cout << endl << tab << "Правила регистрации:" << endl;
		cout << endl << tab << " 1. Логин: не менее 5 и не более 16 символов";
		cout << endl << tab << " 1. Пароль: не менее 8 и не более 20 символов";
		cout << endl << tab << " 2. Логин не должен содержать симовлы - ";
		cout << endl << tab << "	!@#$%^&*()-\"\'№;%:?<>/\\" << endl;
		cout << tab << " esc/enter(оставьте пустую строку). Выйти" << endl;
		cout << tab << "____________________________________________________\n";

		//Получение нового логина и пароля
		string _login;
		cout << endl << tab << "\t\tВведите логин: ";
		_getstring(&_login, 16);

		if (_login.empty()) return;

		string _password;
		cout << endl << tab << "\t\tВведите пароль: ";
		_getstring(&_password, 16);

		if (_password.empty()) return;

		cout << endl << tab << "____________________________________________________\n";

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
	const string ADMIN = "112233";

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
		string _your_code = "";
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
		cout << endl << tab << "\tПопробовать ещё ? (y / n)\n";

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
	system("mode con cols=115 lines=50");

	string line;

	ifstream in("source\\history.txt");

	if (in.is_open())
		while (getline(in, line))
		{
			cout << line << endl;
			Sleep(100);
		}

	in.close();
	cout << endl << "\t\t\tНажмите любую клавишу для выхода" << endl;
	pause();

	system("mode con cols=115 lines=30");
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

	if (!out) return;

	out << *login << ' ';
	out << *pass << '\n';

	out.close();
}