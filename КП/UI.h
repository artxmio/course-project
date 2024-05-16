#pragma once
#include "User.h"
#include <map>;
using namespace std;

class UI
{
public:
	void Hello() const;  //экран при запуске программы
	void ByeBye() const; //экран при закрытии программы

	void StartMenu() const;
	void MainMenu(User* u);
	void OrderMenu(const User* u);

	User Autorization() const;
	void Registration();
	void SingInAdmin(User* u); //вход как админ

	void RestaurantHistory() const; //экран с историей ресторана

	void LoadMenuAnimation() const; //анимация загрузки (смысл в уменьшении "скорости перехода между окнами")
	void AdminModeMessage(); //сообщение о том, что сейчас вы находитесь под учётной записью администратора
	void LoadLogins(); //загрузка логинов и паролей из файла logins.txt
	void SaveLogin(const string* login, const string* pass); //сохранение логинов и паролей в файл logins.txt
private:
	map<string, string> _logins; 

	const string tab = "\t\t\t\t";         //отступ по горизонтали
	const string n = "\n\n\n\n\n\n\n\n\n"; //отступ по вертикали
};