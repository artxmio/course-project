#pragma once
#include "includes_file.h"
using namespace std;

class User;

class error
{
	friend class UI;
private:
	const string invalid_symbols = "!@#$%^&*()-\"\'№;%:?<>/\\";
public:
	string message;
	bool is;

	error() noexcept : message(""), is(false)
	{}
	error(string message) : message(message), is(true)
	{}
};

class UI
{
private:
	map<string, string> _logins;		   //хранения логина и пароля

	const string tab = "\t\t\t\t";         //отступ по горизонтали
	const string n = "\n\n\n\n\n\n\n\n\n"; //отступ по вертикали

	//функция необходимая для считывания клавиши при выборе опций меню
	char change_options(const string* opt, int size, string title, bool admin);
public:
	void Hello() const;				//экран при запуске программы
	void ByeBye() const;			//экран при закрытии программы

	char StartMenu();				//начальное мню
	char MainMenu(User* u);			//главное меню
	char OrderMenu(const User* u);  //меню при выборе пункта "Работа с заказами"
	char RMenuMenu(const User* u);  //меню при выборе пункта "Работа с меню"

	void About() const;				//информация о программе

	User Autorization();								//авторизация
	void Registration();								//регистрация
	error Validation(string _login, string password);	//проверка логина и пароля

	void SingInAdmin(User* u);			//вход как админ
	void ExitAdmin(User* u);			//выход из admin mode

	void RestaurantHistory() const;		//экран с историей ресторана

	void LoadMenuAnimation() const;		//анимация загрузки (смысл в уменьшении "скорости перехода между окнами")
	void AdminModeMessage() const;		//сообщение о том, что сейчас вы находитесь под учётной записью администратора

	void LoadLogins();					//загрузка логинов и паролей из файла logins.txt
	void SaveLogin(const string* login, const string* pass); //сохранение логинов и паролей в файл logins.txt
};