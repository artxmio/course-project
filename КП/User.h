#pragma once
#include "includes_file.h"
using namespace std;

class User
{
private:

	//инфомация о пользователе
	string _login;    //логин пользователя
	string _password; //пароль пользователя
	string _name;     //имя пользователя
	//флаги 

	bool _is_admin;   //является ли пользователем администратором
	bool user_alive;  //флаг успешной авторизации
public: 
	User();															//конструктор без параметров
	User(bool is_admin, string login, string pass, string name, bool u = false); //конструктор со всеми параметрами для заполнения полей

	bool is_admin() const noexcept; //получение значения поля is_admin
	void set_admin(bool w);			//установка поля is_admin
	bool alive();					//получение значения поля user_alive


};