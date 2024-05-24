#include "User.h"

using namespace std;

void pause();

User::User()
{}


User::User(bool is_admin, string login, string pass, string name, bool u) : _is_admin(is_admin), _login(login), _password(pass), _name(name), user_alive(u)
{}

bool User::is_admin() const noexcept
{
	return _is_admin;
}

void User::set_admin(bool w)
{
	this->_is_admin = w;
}

bool User::alive()
{
	return user_alive;
}

void User::PrintInfo() const
{
	cout << "\n\n\n\n\n\n";
	cout << "\t\t\t\t" << "_________________ [ ЛИЧНЫЙ КАБИНЕТ ] _________________" << endl;

	cout << endl << "\t\t\t\t\t\t" << " Логин: " << _login << endl;
	cout << "\t\t\t\t\t\t" << "Пароль: " << _password << endl;
	cout << "\t\t\t\t\t\t" << "   Имя: " << _name << endl;
	cout << endl << "\t\t\t\t" << "____________________________________________________\n";

	cout << endl << "\t\t\t\t" << "Нажмите любую клавишу, чтобы выйти";
}

void User::ShowMyOrders(Restaurant* restaurant)
{
	vector<order> list = restaurant->get_list();

	system("mode con cols=158 lines=50");


	system("cls");

	cout << "\n\n" << '\t' << "____________________________________________________________ [ МОИ ЗАКАЗЫ ] _________________________________________________________________" << endl;
	cout << endl << '\t' << "|  №  | " << "      Время      | " << "                   Содержание заказа                    | " << "      Cтоимость       |" << "           Готовность           | " << endl;

	COORD c;
	int y = 5;
	int x = 36;


	int yy = y;
	for (const auto& item : list)
	{
		if(_name == item.name_waiter)
		{
			cout << '\t' << "|" << setw(4) << item.order_num + 1 << " |" << setw(17) << item.order_time << " |" << endl;


			c.X = x;
			c.Y = yy;

			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleCursorPosition(h, c);

			string filling = item.filling;


			//вывод посимвольно, чтобы в нужный момент поставить запятую
			for (int j = 0; j < filling.size(); j++)
				if (filling[j] == ',')
				{
					++c.Y;
					yy++;
					SetConsoleCursorPosition(h, c);
				}
				else cout << filling[j];

			COORD cc;
			cc.X = 94;
			cc.Y = yy - 1;

			SetConsoleCursorPosition(h, cc);
			cout << item.price;

			cc.X = 117;
			SetConsoleCursorPosition(h, cc);
			cout << (item.done ? "готов" : "не готов");

			cc.X = 0;
			cc.Y = ++yy;

			SetConsoleCursorPosition(h, cc);
		}
	}
	cout << "\n\n" << '\t' << "_____________________________________________________________________________________________________________________________________________" << endl;

	cout << "\t Нажмите любую клавишу, чтобы выйти...";
	pause();

	system("mode con cols=115 lines=30");
}
