#pragma once
#include "includes_file.h"

using namespace std;

//заказ
struct order
	{
		int order_num;       //номер заказа
		string name_waiter;  //имя официанта
		string order_time;   //время получения заказа
		bool done;           //отметка о выполнении
		string filling;		 //содержание заказа
		float price;		 //стоимость 
	};

class Restaurant
{
private:
	//время заказа
	struct ltime 
	{
		int seconds;
		int minutes;
		int hours;

		void SetTime() noexcept;
		string ToString();
	};
		
	ltime _time;
    int _order_index;
	bool _changed;		//флаг изменения списка заказов
	bool _changed_menu; //флаг изменения меню

	unordered_map<string, float> menu_list;

	vector<order> list;						//список заказов

	vector<string> ChooseDishes();								//выбор блюд 
	float CalculatePrice(vector<string> keyDishes);				//подсчёт стоимости заказа
	bool checkOrder(vector<int> _orderIndexes, int _numOrder);	//проверка наличия заказа по номеру

public:
	Restaurant() noexcept;

	vector<order> get_list();

	void LoadOrders();		 //загрузить информацию о заказах из файла
	void LoadMenuData();     //загрузить данные о меню ресторана

	void ShowOrders();       //вывести список заказов
	void ShowMenu();         //вывести меню

	void AddOrder();         //добавить заказ
	void DelOrder();         //удалить заказ
	void CheckMark();        //отметка о выполнении

	void AddNewMenuItem();   //добавить новый пункт в меню
	void DelMenuItem();      //удалить пункт меню

	void SaveOrders();       //сохранить заказ в файл
	void SaveMenuData();     //сохранить информацию о меню в файл
};
