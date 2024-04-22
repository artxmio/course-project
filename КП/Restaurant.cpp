#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <Windows.h>
using namespace std;

Restaurant::Restaurant()
{
	srand(static_cast<unsigned int>(time(0)));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	system("mode con cols=52 lines=50");
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
}

void Restaurant::DelOrder()
{
}

void Restaurant::CheckMark()
{
}
