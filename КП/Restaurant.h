#pragma once
#include <string>
#include <vector>
#include <unordered_map>
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
		float price; //стоимость 
	};
	ltime _time;
    int _order_index;
	bool _changed;

	unordered_map<string, float> menu_list;
	vector<order> list; //список заказов
	
public:
	Restaurant() noexcept;

	void LoadOrders(); //загрузить информацию о заказах из файла
	void LoadMenuData(); //загрузить данные о меню ресторана

	void ShowOrders(); //вывести список заказов
	void ShowMenu(); //вывести меню

	void AddOrder(); //добавить заказ
	void SaveOrders(); //добавить заказ
	void ChooseDishes(); //выбор блюд 
	void PrintMenu(); //вывод блюд
	void DelOrder(); //удалить заказ
	void CheckMark(); //отметка о выполнении
};
