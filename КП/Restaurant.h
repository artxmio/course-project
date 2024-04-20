#pragma once
#include <string>
using namespace std;

class Restaurant
{
private:
	struct order
	{
		int order_num = 0; //номер заказа
		string name_waiter = "non"; //имя официанта
		time_t order_time = 0.0; //время получения заказа
		bool done = false; //отметка о выполнении
		string filling = "non"; //содержание заказа
	};

	string menu; //меню ресторана
	order list[100];
public:
	Restaurant();
	void ShowOrders(); //вывести список заказов
	void ShowMenu(); //вывести меню
	void AddOrder(); //добавить заказ
	void DelOrder(); //удалить заказ
	void CheckMark(); //отметка о выполнении
};
