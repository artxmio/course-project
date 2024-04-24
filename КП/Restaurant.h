#pragma once
#include <string>
#include <vector>
using namespace std;

class Restaurant
{
private:
	struct ltime 
	{
		int seconds;
		int minutes;
		int hours;

		void SetTime();
		string ToString();
	};
	struct order
	{
		int order_num; //номер заказа
		string name_waiter; //имя официанта
		ltime order_time; //время получения заказа
		bool done; //отметка о выполнении
		string filling; //содержание заказа
	};

	string menu; //меню ресторана
    int order_index;
	vector<order> list; //список заказов

	void AddOrder();
public:
	Restaurant();
	
	void ShowOrders(); //вывести список заказов
	void ShowMenu(); //вывести меню
	void AddOrderInFile(); //добавить заказ
	void DelOrder(); //удалить заказ
	void CheckMark(); //отметка о выполнении
};
