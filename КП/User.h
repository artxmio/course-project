#pragma once
#include <string>
using namespace std;

class User
{
private:
	bool _is_admin;   //является ли пользователем администратором
	string _login;    //логин пользователя
	string _password; //пароль пользователя
public: 
	User(); //конструктор без параметров
	User(bool is_admin, string login, string pass); //конструктор со всеми параметрами для заполнения полей

	bool is_admin() const noexcept; //функция для получения значения поля is_admin
	void set_admin(bool w); //установка поля is_admin
};