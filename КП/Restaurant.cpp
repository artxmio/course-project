#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
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
		cout << menu << endl;
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

void Restaurant::DelOrder()
{
	int _numorder;
	cout << endl << tab << "__________________ [ УДАЛЕНИЕ ЗАКАЗА ] ___________________\n" << endl;
	cout << tab << "Введите номер заказа: ";
	cin >> _numorder;

	if (_numorder < 0)
	{
		cout << tab << "Такого заказа не существует.\nПопробуйте в другой раз.";
		pause();
		system("cls");
		return;
	}

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
		if(_numorder == list.at(i).order_num)
			list.erase(list.begin() + i - 1);
	
	_order_index--;
	_changed = true;
}

void Restaurant::ShowOrders()
{
	cout << endl << tab << "_____________________ [ ЗАКАЗЫ ] ____________________\n" << endl;
	for (int i = 0; i < _order_index; i++)
	{
		cout << tab << "\tЗаказ №" << list.at(i).order_num + 1 << endl;
		cout << tab << "\tИмя официанта: " << list.at(i).name_waiter << endl;
		cout << tab << "\tВремя принятия заказа: " << list.at(i).order_time << endl;
		cout << tab << "\tСодержание заказа: " << list.at(i).filling << endl;
		cout << tab << "\tСтоимость: " << list.at(i).price << endl;
		cout << tab << "\tГотовность: " << (list.at(i).done? "готов": "не готов") << endl;
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

	cout << endl << tab << "Введите содержание заказа: ";
	cin.get();
	getline(cin, buff.filling);
	cout << endl << tab << "Введите стоимость заказа: ";
	cin >> buff.price;

	cout << endl << tab << "____________________________________________________\n";
	cout << endl << tab << "Новый заказ добавлен.";
	cout << endl << tab << "Нажмите любую клавишу для продолжения..." << endl;
	pause();
	list.push_back(buff);

	_order_index++;
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
	_changed = true;
	int _numorder = 0;
	cout << endl << tab << "__________________ [ РЕДАКТОР ЗАКАЗОВ ] ___________________\n" << endl;
	cout << tab << "Введите номер заказа: ";
	cin >> _numorder;

	if (_numorder > size(list) or _numorder < 0)
	{
		cout << "Такого заказа не существует.\nПопробуйте в другой раз.";
		pause();
		system("cls");
		return;
	}

	char change;
	cout << tab << "Готовость заказа №"<< _numorder << " изменена на 'готов'." << endl;
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
