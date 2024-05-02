#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <iterator>
#include "UI.h"
using namespace std;

void pause();
string tab = "\t\t\t\t";

Restaurant::Restaurant() noexcept : _order_index(0)
{}

void Restaurant::ShowMenu()
{
	system("cls");
	ifstream fs("source\\menu.txt", ios::in | ios::binary);
	string menu;

	if (!fs) return;
	while (getline(fs, menu))
	{
		cout << "\t\t" << menu << endl;
		Sleep(100);
	}

	fs.close();
}

void Restaurant::LoadOrders()
{
	ifstream in("source\\orders.txt");

	if (!in) return;

	order buff;
	while (!in.eof() and in.peek() != EOF)
	{
		in >> buff.order_num;
		in >> buff.name_waiter;
		in >> buff.price;
		in >> buff.order_time;
		in.get();
		getline(in, buff.filling);
		in >> buff.done;
		in.get();
		list.push_back(buff);
		_order_index++;
	}
	in.close();
}

void Restaurant::LoadMenuData()
{
	ifstream in("source\\menu_data.txt", ios::in);

	if (!in) return;

	while (!in.eof())
	{
		string _title;
		float _price;

		in.get();
		getline(in, _title);
		in >> _price;

		menu_list.insert({ _title, _price });
	}
}

static bool checkOrder(vector<int> orderIndexes, int numOrder) //функция для проверки наличия элемента в списке
{
	return (find(begin(orderIndexes), end(orderIndexes), numOrder) != end(orderIndexes));
}

void Restaurant::DelOrder()
{
	int _numorder;
	cout << endl << tab << "__________________ [ УДАЛЕНИЕ ЗАКАЗА ] ___________________\n" << endl;

	vector<int> availableOrders{};
	cout << endl << tab << "Доступные заказы:" << endl << tab;
	if (list.empty())
	{
		cout << "Пока что заказов нет" << endl;
		pause();
		return;
	}
	else
		for (int i = 0; i < list.size(); i++)
		{
			availableOrders.push_back(list.at(i).order_num);
			cout << list.at(i).order_num + 1 << " ";
		}

	cout << endl << tab << "Введите номер заказа: ";
	cin >> _numorder;

	if (!(checkOrder(availableOrders, _numorder - 1)))
	{
		cout << tab << "Такого заказа не существует. Попробуйте в другой раз.";
		pause();
		system("cls");
		return;
	}
	else
	{
		char change;
		cout << tab << "Заказ №" << _numorder << " удалён." << endl;
		cout << tab << "Сохранить изменения? (это действие нельзя будет отменить)" << endl;
		cout << tab << "      1. Да" << endl;
		cout << tab << "      0. Нет" << endl;
		cout << endl << tab << "____________________________________________________\n";
		change = _getch();

		if (change == '0') return;

		//удаление элемента

		for (int i = 0; i < _order_index; i++)
			if (_numorder == list.at(i).order_num)
				list.erase(list.begin() + i - 1);

		_order_index--;
		_changed = true;
	}
}

vector<string> Restaurant::ChooseDishes()
{
	vector<string> dishes{};
	bool _continue = true;
	do
	{
		system("cls");
		cout << endl << tab << "_________________ [ ВЫБОР БЛЮДА ] __________________\n" << endl;
		PrintMenu();

		cout << endl << tab << "Введите код блюда:\n";
		cout << tab;

		int dish = -1;

		cin >> dish;

		if (dish < 0 or dish > 18)
		{
			cout << tab << "Нет такого блюда." << endl;
			cout << tab << "Нажмите любую клавишу для продолжения" << endl;
			pause();
			continue;
		}

		//поиск блюда по номеру в списке
		string keyDish;
		int counter = 0;
		for (auto& d : menu_list)
			if (counter != dish - 1)
			{
				counter++;
				continue;
			}
			else
			{
				keyDish = d.first;
				break;
			}


		dishes.push_back(keyDish);
		cout << tab << "Это всё? (y/n)" << endl;
		
		do
		{
			const char __continue = _getch();
			if (__continue == 'y')
			{
				_continue = false;
				break;
			}
			else if (__continue == 'n')
				break;

		} while (true);

	} while (_continue);

	return dishes;
}

float Restaurant::CalculatePrice(vector<string> keyDishes)
{
	float _price = 0;
	for (int i = 0; i < keyDishes.size(); i++)
	{
		_price += menu_list[keyDishes.at(i)];
	}
	return _price;
}

void Restaurant::PrintMenu()
{
	int i = 0;
	for (const auto& dish : menu_list)
	{
		i++;
		cout << setw(34) << i << ". " << setw(35) << dish.first << setw(10) << dish.second << "BYN" << endl;
	}
	cout << tab << "____________________________________________________\n\n";
}

void Restaurant::ShowOrders()
{
    cout << endl << tab << "_____________________ [ ЗАКАЗЫ ] ____________________\n" << endl;
	if (list.empty())
	{
		cout << tab<< "Пока что заказов нет" << endl;
		cout << tab << "Нажмите любую клавишу для продолжения..." << endl;
		pause();
		return;
	}
	
	for (int i = 0; i < _order_index; i++)
	{
		cout << tab << "\tЗаказ №" << list.at(i).order_num + 1 << endl;
		cout << tab << "\tИмя официанта: " << list.at(i).name_waiter << endl;
		cout << tab << "\tВремя принятия заказа: " << list.at(i).order_time << endl;

		//вывод содержимого заказа
		cout << tab << "\tСодержание заказа:\n" << tab << '\t' << list.at(i).filling << endl;

		cout << tab << "\tСтоимость: " << list.at(i).price << "BYN" << endl;
		cout << tab << "\tГотовность: " << (list.at(i).done ? "готов" : "не готов") << endl;
		cout << tab << "____________________________________________________\n\n";
	}
	cout << tab << "Нажмите любую клавишу для продолжения..." << endl;
	pause();
}

void Restaurant::AddOrder()
{
	system("cls");
	_changed = true;
	order buff;

	cout << endl << tab << "__________________ [ НОВЫЙ ЗАКАЗ ] _________________" << endl;

	buff.order_num = _order_index; //установка номера заказа

	_time.SetTime();
	buff.order_time = _time.ToString(); // установка времени добавления заказа

	buff.done = false;

	cout << endl << tab << "Введите имя официанта: ";
	cin >> buff.name_waiter;

	//наполнение заказа
	vector<string> _dishes = ChooseDishes();
	for (const auto& dish : _dishes)
		buff.filling += dish + ",";

	//стоимость заказа
	buff.price = CalculatePrice(_dishes);



	cout << endl << tab << "____________________________________________________\n";
	cout << endl << tab << "Новый заказ добавлен.";
	cout << endl << tab << "Нажмите любую клавишу для продолжения..." << endl;
	pause();
	list.push_back(buff);

	_order_index++;
	SaveOrders();
}

void Restaurant::SaveOrders()
{
	int mode = 0;
	mode = _changed ? ios::out : ios::app;

	ofstream out("source\\orders.txt", mode);

	if (!out) return;

	if (_changed)
		for (int i = 0; i < _order_index; i++)
		{
			out << list.at(i).order_num << ' ';
			out << list.at(i).name_waiter << ' ';
			out << list.at(i).price << ' ';
			out << list.at(i).order_time << '\n';
			out << list.at(i).filling << '\n';
			out << list.at(i).done << '\n';
		}

	out.close();
}

void Restaurant::CheckMark()
{
	if (list.empty())
	{
		cout << tab << "Пока что заказов нет" << endl;
		pause();
		return;
	}

	_changed = true;
	int _numorder = 0;
	cout << endl << tab << "__________________ [ РЕДАКТОР ЗАКАЗОВ ] ___________________\n" << endl;
	cout << tab << "Введите номер заказа: ";
	cin >> _numorder;

	if (_numorder < 0)
	{
		cout << "Такого заказа не существует.\nПопробуйте в другой раз.";
		pause();
		system("cls");
		return;
	}

	char change;
	cout << tab << "Готовость заказа №" << _numorder << " изменена на 'готов'." << endl;
	cout << tab << "Сохранить изменения? (это действие нельзя будет отменить)" << endl;
	cout << tab << "      1. Да" << endl;
	cout << tab << "      0. Нет" << endl;
	cout << endl << tab << "____________________________________________________\n";
	change = _getch();

	if (change == '0') return;
	list.at(_numorder - 1).done = true;
}

void Restaurant::ltime::SetTime() noexcept
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	seconds = time.wSecond;
	minutes = time.wMinute;
	hours = time.wHour;
}

string Restaurant::ltime::ToString()
{
	return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
}
