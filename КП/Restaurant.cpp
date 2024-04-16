#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
using namespace std;
Restaurant::Restaurant()
{
	srand(static_cast<unsigned int>(time(0)));
	path_orders = "source\\orders.txt";
	path_menu = "source\\menu.txt";
}

void Restaurant::ShowOrders() //ПЕРЕДЕЛАЙ, заказы должны сохраняться в массив
{	

}

void Restaurant::ShowMenu()
{
	ifstream in;
	in.open(path_menu);

	if (in.is_open())
	{
		cout << "file " << path_menu << " is open\n";
		while (getline(in, menu))
			cout << menu << endl;
	}
	in.close();
}

void Restaurant::Add() //ДОДЕЛАЙ
{

}