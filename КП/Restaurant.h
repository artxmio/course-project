#pragma once
#include <string>
using namespace std;

struct order
{
	int order_num; //номер заказа
	string name_waiter; //имя официанта
	time_t order_time; //время получения заказа
	bool done; //отметка о выполнении
	string filling; //содержание заказа
};

class Restaurant
{
private:
	string path_orders; 
	string path_menu;
	string menu; //меню ресторана
	order list[100];
	int i = 0; //номер заказа в массиве
public:
	Restaurant();
	void ShowOrders(); //вывести список заказов
	void ShowMenu(); //вывести меню
	void Add(); //добавить заказ
	void Del(); //удалить заказ
	void CheckMark(); //отметка о выполнении
};
