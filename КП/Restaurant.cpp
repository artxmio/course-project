#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <Windows.h>
using namespace std;

Restaurant::Restaurant(): order_index(0)
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

void Restaurant::ShowOrders()
{}

void Restaurant::AddOrder()
{
	order buff;
	buff.order_num = order_index; //установка номера заказа

	buff.order_time.SetTime(); // установка времени добавления заказа

	buff.done = false;

	cout << "Введите имя официанта: ";
	cin >> buff.name_waiter;

	cout << "Введите содержание заказа\n" << "(для подтвреждения нажмите enter): ";
	cin >> buff.filling;	

	list.push_back(buff);
}

void Restaurant::AddOrderInFile()
{
	system("cls");

	AddOrder();

	ofstream out("source\\orders.txt", ios::app);
	
	if (!out) return;

	out << list.at(order_index).order_num + 1 << '\n';
	out << list.at(order_index).name_waiter << '\n';
	out << list.at(order_index).order_time.ToString() << '\n';
	out << list.at(order_index).filling << '\n';
	out << list.at(order_index).done << '\n';
	order_index++;
}

void Restaurant::DelOrder()
{
}

void Restaurant::CheckMark()
{
}

void Restaurant::ltime::SetTime()
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
