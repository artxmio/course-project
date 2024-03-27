#pragma once
#include <string>
#include <fstream>
using namespace std;

class Menu
{
protected:
	string functions; //храниться текстовое содеражние меню
	string path_in;
public:
	virtual void show(); //вывести информацию
};