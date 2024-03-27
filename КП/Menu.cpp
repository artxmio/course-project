#include "Menu.h"
#include <iostream>

void Menu::show()
{
	ifstream in;
	in.open(path_in);

	if (in.is_open())
	{
		std::cout << "file " << path_in << " is open\n";
		while (getline(in, functions))
			std::cout << functions << endl;
	}
	in.close();
}