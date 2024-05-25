#include "Restaurant.h"
using namespace std;

void _getstring(string* str, int max);

void pause();

string tab = "\t\t\t\t"; //отступ

//конструктор устанавливает значение номера заказа в списке в 0
Restaurant::Restaurant() noexcept : _order_index(0)
{}

vector<Restaurant::order> Restaurant::get_list()
{
	return this->list;
}

//вывод меню из файла menu.txt
void Restaurant::ShowMenu()
{
	system("cls");

	int i = 0;
	cout << endl << tab << "______________________ [ МЕНЮ ] _____________________" << endl << endl;

	for (const auto& dish : menu_list)
	{
		i++;
		cout << setw(34) << i << ". " << setw(35) << dish.first << setw(10) << dish.second << " BYN" << endl;
	}
	cout << tab << "_____________________________________________________\n\n";
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

	if (!in) throw " ";

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
	cout << endl << tab << "__________________ [ УДАЛЕНИЕ ЗАКАЗА ] ____________________\n" << endl;
	
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
	cout << endl << tab << "___________________________________________________________\n";

	for (;;)
	{
		_change = _getch();
		if (_change == 'n') return;
		else if (_change == 'y') break;
	}

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
		ShowMenu();

		//блюда выбираются с помощью их кода в списке
		cout << tab << "Введите код блюда:\n";
		cout << tab;

		string dish;
		_getstring(&dish, 4);

		if (dish.empty()) return vector<string>();

		int _dish = 0;

		try
		{
			_dish = stoi(dish);
		}
		catch (const exception& ex)
		{
			cout << tab << "Неверное значение." << endl;
			cout << tab << "Нажмите любую клавишу для продолжения" << endl;
			pause();
			continue;
		}

		//не больше, чем в списке меню
		if (_dish <= 0 or _dish > menu_list.size())
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
			if (counter != _dish - 1)
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
		cout << endl  << tab << "Это всё? (y/n)" << endl;

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

//вывод всех заказов на экран
void Restaurant::ShowOrders()
{
	//прооверка на отсутсвие элементов в списке
	if (list.empty())
	{
		cout << endl << tab << "_____________________ [ ЗАКАЗЫ ] ____________________\n" << endl;
		cout << tab << "Пока что заказов нет" << endl;
		cout << tab << "Нажмите любую клавишу для продолжения..." << endl;
		pause();
		return;
	}

	int i = 0;

	for (;;)
	{
		system("cls");
		cout << endl << "\n\n" << tab << "_____________________ [ ЗАКАЗЫ ] ____________________\n" << endl;

		cout << tab << "\tЗаказ №" << list.at(i).order_num + 1 << endl;
		cout << tab << "\tИмя: " << list.at(i).name_waiter << endl;
		cout << tab << "\tВремя принятия заказа: " << list.at(i).order_time << endl;

		//вывод содержимого заказа
		cout << tab << "\tСодержание заказа:\n";

		cout << tab << '\t';
		string filling = list.at(i).filling;

		//вывод посимвольно, чтобы в нужный момент поставить запятую
		cout << "\n" << tab << "\t   ";
		for (int j = 0; j < filling.size(); j++)
			if (filling[j] == ',') cout << endl << tab << "\t   ";
			else cout << filling[j];

		cout << endl;
		cout << tab << "\tСтоимость: " << list.at(i).price << "BYN" << endl;
		cout << tab << "\tГотовность: " << (list.at(i).done ? "готов" : "не готов") << endl;
		cout << tab << "____________________________________________________\n\n";
		cout << tab << " Стрелочки влево/вправо: предыдущий/следующий заказ\n";
		cout << tab << " esc: выйти\n\n";
		
		//esc
		if (_getch() == 27) return;

		const char _code_key = _getch();

		//считывание стрелочек
		if (_code_key == 75)
			i--;
		else if (_code_key == 77)
			i++;

		//проверка на выход за границы списка
		if (i < 0) i = 0;
		else if (i >= list.size()) i = list.size() - 1;
	}

}

//добавление нового заказа
void Restaurant::AddOrder(User* u)
{
	system("cls");
	system("mode con cols=115 lines=40");
	_changed = true;

	order buff;

	cout << endl << tab << "__________________ [ НОВЫЙ ЗАКАЗ ] _________________" << endl;

	buff.order_num = _order_index; //установка номера заказа

	_time.SetTime();
	buff.order_time = _time.ToString(); // установка времени добавления заказа

	buff.done = false;

	buff.name_waiter = u->_name;

	if (buff.name_waiter.empty())
	{
		system("mode con cols=115 lines=30");
		return;
	}

	//наполнение заказа
	vector<string> _dishes = ChooseDishes();

	if (_dishes.empty())
	{
		system("mode con cols=115 lines=30");
		return;
	}

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
	system("mode con cols=115 lines=30");
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

//сохранение данных о меню
void Restaurant::SaveMenuData()
{
	if (!_changed_menu) return;

	const int mode = ios::out;

	ofstream out("source\\menu_data.txt", mode);

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

	while (true)
	{
		system("cls");

		cout << endl << tab << "__________________ [ РЕДАКТОР ЗАКАЗОВ ] ___________________\n";

		cout << endl << tab << "	Изменить готовность заказов" << endl;
		cout << endl << tab << "	esc: выход" << endl;
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
				if(!list.at(i).done)
				{
					availableOrders.push_back(list.at(i).order_num);
					cout << list.at(i).order_num + 1 << " ";
				}
			}

		if (availableOrders.empty())
		{
			cout << "Пока что заказов нет или они все готовы" << endl;
			pause();
			return;
		}

		cout << endl << tab << "Введите номер заказа: ";

		string numorder;
		_getstring(&numorder, 4);

		if (numorder.empty())
			return;

		int _numorder = 0;

		try
		{
			_numorder = stoi(numorder);
		}
		catch (const exception& e)
		{
			cout << endl << tab << "Неверное значение" << endl;
			pause();
			continue;
		}

		if (!(checkOrder(availableOrders, _numorder - 1)))
		{
			cout << endl << tab << "Такого заказа не существует. Попробуйте в другой раз.";
			pause();
			system("cls");
			return;
		}

		cout << endl << tab << "Готовость заказа №" << _numorder << " изменена на 'готов'." << endl;
		cout << tab << "Сохранить изменения? (это действие нельзя будет отменить)" << endl;
		cout << tab << "      y. Да" << endl;
		cout << tab << "      n. Нет" << endl;
		cout << endl << tab << "___________________________________________________________\n";

		for (;;)
		{
			const char _change = _getch();
			if (_change == 'n') return;
			else if (_change == 'y') break;
		}

		list.at(_numorder - 1).done = true;
		break;
	}
}

//добавить новый пункт меню
void Restaurant::AddNewMenuItem()
{
	_changed_menu = true;

	bool _continue = true;
	do
	{
		system("cls");
		cout << endl << tab << "____________________ [ МЕНЮ ] ___________________" << endl;

		//название блюда
		string dish_title = "";
		cout << endl << tab << "Название блюда: \n";
		cout << tab;

		_getstring(&dish_title, 30);

		if (dish_title.empty()) return;

		//цена
		string price;

		cout << endl << tab << "Цена блюда (например 14.88): \n" << tab;

		_getstring(&price, 30);

		if (price.empty()) return;

		float _price = 0.0;
		try
		{
			_price = stof(price);
		}
		catch (const exception& ex)
		{
			cout << tab << "____________________________________________________\n\n";
			cout << tab << "Неверное значение." << endl;
			cout << tab << "Нажмите любую клавишу для продолжения" << endl;
			pause();
			continue;
		}

		if (_price <= 0)
		{
			cout << tab << "____________________________________________________\n\n";
			cout << tab << "Неверное значение" << endl;
			cout << tab << "Нажмите любую клавишу, чтобы выйти" << endl;
			pause();
			system("cls");
			return;
		}

		//округление до 2 знаков после запятой
		_price = round((_price * 100)) / 100.0;

		cout << tab << "____________________________________________________\n\n";

		cout << tab << "Новый пункт меню добавлен";

		menu_list.insert({ dish_title, _price });
		_continue = false;
	} while (_continue);

}

//удалить пункт меню по названию блюда
void Restaurant::DelMenuItem()
{
	system("mode con cols=115 lines=50");

	cout << endl << tab << "______________________ [ МЕНЮ ] ______________________" << endl;

	if (menu_list.empty())
	{
		cout << "Пока что заказов нет" << endl;
		pause();
		return;
	}

	ShowMenu();

	cout << tab << "Для удаления блюда из списка необходимо ввести\n" << tab << "его название";
	cout << endl << tab << "_____________________________________________________\n";

	//название блюда
	string dish_title = "";
	cout << endl << tab << "Название блюда: \n";
	cout << tab;


	string cing = "";
	cing = cin.get();

	getline(cin, dish_title);

	//если cin.get() съест лишний символ
	if (cing != "\n")
	{
		cing += dish_title;
		dish_title = cing;
		cing = "";
	}

	if (!menu_list.count(dish_title))
	{
		cout << endl << tab << "_____________________________________________________\n";
		cout << tab << "Такого блюда не существует" << endl;
		pause();
		system("mode con cols=115 lines=30");
		return;
	}

	//подтверждение удаления
	cout << endl << tab << "_____________________________________________________\n";

	cout << endl << tab << dish_title << " удалён." << endl;
	cout << tab << "Сохранить изменения? (это действие нельзя будет отменить)" << endl;
	cout << tab << "      y. Да" << endl;
	cout << tab << "      n. Нет" << endl;
	cout << endl << tab << "_____________________________________________________\n";

	for (;;)
	{
		const char _change = _getch();
		if (_change == 'n') return;
		else if (_change == 'y') break;
	}

	menu_list.erase(dish_title);

    system("mode con cols=115 lines=30");
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