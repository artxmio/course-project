#include "Restaurant.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <iterator>
#include "UI.h"
using namespace std;

void pause();
string tab = "\t\t\t\t"; //отступ

//конструктор устанавливает значение номера заказа в списке в 0
Restaurant::Restaurant() noexcept : _order_index(0)
{}

//вывод меню из файла menu.txt
void Restaurant::ShowMenu()
{
	system("cls");

	ifstream fs("source\\menu.txt", ios::in | ios::binary);
	string menu;

	if (!fs) return;

	while (getline(fs, menu))
	{
		cout << "\t\t" << menu << endl;
		Sleep(100);
	}

	fs.close();
}

//загрузка заказов из файла orders.txt
void Restaurant::LoadOrders()
{
	ifstream in("source\\orders.txt");

	if (!in) return;

	order buff; //буфферная переменная для чтения заказа по одному

	while (!in.eof() and in.peek() != EOF) //проверка на пустой файл
	{
		in >> buff.order_num;
		in >> buff.name_waiter;
		in >> buff.price;
		in >> buff.order_time;
		in.get();
		getline(in, buff.filling);
		in >> buff.done;
		in.get();

		list.push_back(buff); //добавление заказа в список

		_order_index++;		  //увеличение индекса на 1
	}

	in.close();
}

//сохранение названий блюд и цен в словарь (ключ:название, значение:цена)
void Restaurant::LoadMenuData()
{
	ifstream in("source\\menu_data.txt", ios::in);

	if (!in) return;

	while (!in.eof())
	{
		string _title;
		float _price;

		in.get();
		getline(in, _title);
		in >> _price;

		menu_list.insert({ _title, _price }); //добавление пары в словарь
	}
}

//проверка на наличие заказа в списке по его номеру (order.numorder)
bool Restaurant::checkOrder(vector<int> _orderIndexes, int _numOrder)
{
	//возвращается булевое значение: если заказ есть в списке - true, в противном случае - false
	return (find(begin(_orderIndexes), end(_orderIndexes), _numOrder) != end(_orderIndexes));
}

//функция удаления заказа
void Restaurant::DelOrder()
{
	cout << endl << tab << "__________________ [ УДАЛЕНИЕ ЗАКАЗА ] ___________________\n" << endl;

	//вывод доступных (имеющихся в списке) заказов на удаление

	//если список пуст, дальше нет смысла идти (return)
	if (list.empty())
	{
		cout << "Пока что заказов нет" << endl;
		pause();
		return;
	}

	//подтверждение удаления
	char _change;
	cout << tab << "Последний заказ удалён." << endl;
	cout << tab << "Сохранить изменения? (это действие нельзя будет отменить)" << endl;
	cout << tab << "      y. Да" << endl;
	cout << tab << "      n. Нет" << endl;
	cout << endl << tab << "____________________________________________________\n";
	_change = _getch();

	if (_change == 'n') return;

	//удаление элемента

	list.erase(list.end() - 1);

	_order_index--;  //уменьшение индекса
	_changed = true; //метка о изменении списка
}

//выбор блюд (компонент функции AddOrder())
vector<string> Restaurant::ChooseDishes()
{
	//выбранные блюда
	vector<string> dishes{};

	bool _continue = true;
	do
	{
		system("cls");
		cout << endl << tab << "_________________ [ ВЫБОР БЛЮДА ] __________________\n" << endl;

		//вывод меню
		PrintMenu();

		//блюда выбираются с помощью их кода в списке
		cout << endl << tab << "Введите код блюда:\n";
		cout << tab;

		int dish = -1;

		cin >> dish;

		//не больше, чем в списке меню
		if (dish <= 0 or dish > menu_list.size())
		{
			cout << tab << "Нет такого блюда." << endl;
			cout << tab << "Нажмите любую клавишу для продолжения" << endl;
			pause();
			continue;
		}

		//поиск блюда по номеру в списке
		string keyDish;
		int counter = 0;
		for (auto& d : menu_list)
			if (counter != dish - 1)
			{
				counter++;
				continue;
			}
			else
			{
				keyDish = d.first;
				break;
			}

		dishes.push_back(keyDish);
		cout << tab << "Это всё? (y/n)" << endl;

		do
		{
			const char __continue = _getch();
			if (__continue == 'y')
			{
				_continue = false;
				break;
			}
			else if (__continue == 'n')
				break;

		} while (true);

	} while (_continue);

	//возвращается вектор с блюдами
	return dishes;
}

//подсчёт цены заказа по выбранным блюдам
float Restaurant::CalculatePrice(vector<string> keyDishes)
{
	float _price = 0;
	for (int i = 0; i < keyDishes.size(); i++)
	{
		_price += menu_list[keyDishes.at(i)];
	}
	return _price;
}

//вывод меню на экран
void Restaurant::PrintMenu()
{
	int i = 0;
	for (const auto& dish : menu_list)
	{
		i++;
		cout << setw(34) << i << ". " << setw(35) << dish.first << setw(10) << dish.second << " BYN" << endl;
	}
	cout << tab << "____________________________________________________\n\n";
}

//вывод всех заказов на экран
void Restaurant::ShowOrders()
{
	cout << endl << tab << "_____________________ [ ЗАКАЗЫ ] ____________________\n" << endl;
	//проверка на отсутсвие элементов в списке
	if (list.empty())
	{
		cout << tab << "Пока что заказов нет" << endl;
		cout << tab << "Нажмите любую клавишу для продолжения..." << endl;
		pause();
		return;
	}

	for (int i = 0; i < _order_index; i++)
	{
		cout << tab << "\tЗаказ №" << list.at(i).order_num + 1 << endl;
		cout << tab << "\tИмя официанта: " << list.at(i).name_waiter << endl;
		cout << tab << "\tВремя принятия заказа: " << list.at(i).order_time << endl;

		//вывод содержимого заказа
		cout << tab << "\tСодержание заказа:\n" << tab << '\t';

		string filling = list.at(i).filling;
		for (int i = 0; i < filling.size(); i++)
			if (filling[i] == ',') cout << endl << tab << '\t';
			else cout << filling[i];

		cout << endl;
		cout << tab << "\tСтоимость: " << list.at(i).price << "BYN" << endl;
		cout << tab << "\tГотовность: " << (list.at(i).done ? "готов" : "не готов") << endl;
		cout << tab << "____________________________________________________\n\n";
	}
	cout << tab << "Нажмите любую клавишу для продолжения..." << endl;
	pause();
}

//добавление нового заказа
void Restaurant::AddOrder()
{
	system("cls");

	_changed = true;

	order buff;

	cout << endl << tab << "__________________ [ НОВЫЙ ЗАКАЗ ] _________________" << endl;

	buff.order_num = _order_index; //установка номера заказа

	_time.SetTime();
	buff.order_time = _time.ToString(); // установка времени добавления заказа

	buff.done = false;

	cout << endl << tab << "Введите имя официанта: ";
	cin >> buff.name_waiter;

	//наполнение заказа
	vector<string> _dishes = ChooseDishes();
	for (const auto& dish : _dishes)
		buff.filling += dish + ",";

	//стоимость заказа
	buff.price = CalculatePrice(_dishes);

	cout << endl << tab << "____________________________________________________\n";
	cout << endl << tab << "Новый заказ добавлен.";
	cout << endl << tab << "Нажмите любую клавишу для продолжения..." << endl;
	pause();
	list.push_back(buff);

	_order_index++;
	SaveOrders();
}

//сохранение данных о заказе в файл
void Restaurant::SaveOrders()
{
	if (!_changed) return;

	const int mode = ios::out;

	ofstream out("source\\orders.txt", mode);

	if (!out) return;

	for (int i = 0; i < _order_index; i++)
	{
		out << list.at(i).order_num << ' ';
		out << list.at(i).name_waiter << ' ';
		out << list.at(i).price << ' ';
		out << list.at(i).order_time << '\n';
		out << list.at(i).filling << '\n';
		out << list.at(i).done << '\n';
	}

	out.close();
}

void Restaurant::SaveMenuData()
{
	if (!_changed_menu) return;

	const int mode = ios::out;

	ofstream out("source\\orders.txt", mode);

	if (!out) return;

	for (auto& item : menu_list)
	{
		out << endl << item.first;
		out << endl << item.second;
	}

	out.close();
}

//изменение готовности заказа
void Restaurant::CheckMark()
{
	if (list.empty())
	{
		cout << tab << "Пока что заказов нет" << endl;
		pause();
		return;
	}

	_changed = true;
	int _numorder = 0;
	cout << endl << tab << "__________________ [ РЕДАКТОР ЗАКАЗОВ ] ___________________\n";

	cout << endl << tab << "	Изменить готовность заказов" << endl;
	cout << endl << tab << "___________________________________________________________\n";


	vector<int> availableOrders{};
	cout << endl << tab << "Доступные заказы:" << endl << tab;
	if (list.empty())
	{
		cout << "Пока что заказов нет" << endl;
		pause();
		return;
	}
	else
		for (int i = 0; i < list.size(); i++)
		{
			availableOrders.push_back(list.at(i).order_num);
			cout << list.at(i).order_num + 1 << " ";
		}

	cout << endl << tab << "Введите номер заказа: ";
	cin >> _numorder;

	if (!(checkOrder(availableOrders, _numorder - 1)))
	{
		cout << tab << "Такого заказа не существует. Попробуйте в другой раз.";
		pause();
		system("cls");
		return;
	}

	char change;
	cout << tab << "Готовость заказа №" << _numorder << " изменена на 'готов'." << endl;
	cout << tab << "Сохранить изменения? (это действие нельзя будет отменить)" << endl;
	cout << tab << "      y. Да" << endl;
	cout << tab << "      n. Нет" << endl;
	cout << endl << tab << "____________________________________________________\n";
	change = _getch();

	if (change == 'n') return;
	list.at(_numorder - 1).done = true;
}

//установка времени оформления заказа
void Restaurant::ltime::SetTime() noexcept
{
	SYSTEMTIME time;
	GetLocalTime(&time);

	seconds = time.wSecond;
	minutes = time.wMinute;
	hours = time.wHour;
}

//перевод времени в строку
string Restaurant::ltime::ToString()
{
	return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
}