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

		void SetTime() noexcept;
		string ToString();
	};
	struct order
	{
		int order_num; //номер заказа
		string name_waiter; //имя официанта
		string order_time; //время получения заказа
		bool done; //отметка о выполнении
		string filling; //содержание заказа
		int price; //стоимость 
	};
	ltime _time;
    int _order_index;
	bool _changed;

	vector<order> list; //список заказов
	
public:
	Restaurant() noexcept;

	void LoadOrders(); //загрузить информацию о заказах из файла
	void ShowOrders(); //вывести список заказов
	void ShowMenu(); //вывести меню
	void AddOrder(); //добавить заказ
	void SaveOrders(); //добавить заказ
	void DelOrder(); //удалить заказ
	void CheckMark(); //отметка о выполнении
};
