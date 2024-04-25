#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <Windows.h>
#include "UI.h"
using namespace std;

string tab = "\t\t";
void pause();

Restaurant::Restaurant() noexcept : order_index(0)
{
	srand(static_cast<unsigned int>(time(0)));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	system("mode con cols=82 lines=30");
}

void Restaurant::ShowMenu()
{
	system("cls");
	ifstream fs("source\\menu.txt", ios::in | ios::binary);

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
		in >> buff.order_time;
		in.get();
		getline(in, buff.filling);
		in >> buff.done;
		in.get();
		list.push_back(buff);
		order_index++;
	}
	in.close();
}

void Restaurant::ShowOrders()
{
	cout << endl << tab << "_____________________ [ ЗАКАЗЫ ] ___________________\n" << endl;
	for (int i = 0; i < order_index; i++)
	{
		cout << tab << "\tЗаказ №" << list.at(i).order_num + 1 << endl;
		cout << tab << "\tИмя официанта: " << list.at(i).name_waiter << endl;
		cout << tab << "\tВремя принятия заказа: " << list.at(i).order_time << endl;
		cout << tab << "\tСодержание заказа: " << list.at(i).filling << endl;
		cout << tab << "\tГотовность: " << list.at(i).done << endl;
		cout << tab << "____________________________________________________\n\n";
	}
	pause();
}

void Restaurant::AddOrder()
{
	system("cls");

	order buff;

	cout << endl << tab << "__________________ [ НОВЫЙ ЗАКАЗ ] _________________" << endl;

	buff.order_num = order_index; //установка номера заказа

	_time.SetTime();
	buff.order_time = _time.ToString(); // установка времени добавления заказа

	buff.done = false;

	cout << endl << tab << "Введите имя официанта: ";
	cin >> buff.name_waiter;

	cout << endl << tab << "Введите содержание заказа: ";
	cin.get();
	getline(cin, buff.filling);

	cout << endl << tab << "Новый заказ добавлен.";
	Sleep(2000);
	list.push_back(buff);

	AddOrderInFile();
}

void Restaurant::AddOrderInFile()
{
	ofstream out("source\\orders.txt", ios::app);

	if (!out) return;

	out << list.at(order_index).order_num << ' ';
	out << list.at(order_index).name_waiter << ' ';
	out << list.at(order_index).order_time << '\n';
	out << list.at(order_index).filling << '\n';
	out << list.at(order_index).done << '\n';

	out.close();
	order_index++;
}

void Restaurant::CheckMark()
{
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
