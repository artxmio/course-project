#include <iostream>
#include <fstream>
#include <conio.h>
#include "Restaurant.h"
#include "UI.h"
using namespace std;

void pause()
{
    _getch();
}

int main()
{ 
    setlocale(LC_ALL, "ru");

    UI userInterface;
    Restaurant restaurant;

    userInterface.Autorization();

    pause();
    system("cls");
    while (true)
    {
        cout << "Добро пожаловать в “TrendyБульба”!!!" << endl;
        cout << "\nДля продолжения нажмите любую клавишу...";
        pause();
        while (true)
        {
            userInterface.MainMenu();

            const char change_main_menu = _getch();

            switch (change_main_menu)
            {
            case '1': //работа с заказами

                userInterface.OrderMenu(); 
                pause();
                break;

            case '2': //меню ресторана
                restaurant.ShowMenu();
                pause();
                break; 
            case '3': 

                userInterface.RestaurantHistory(); 
                pause();
                break;

            case '0': 

                break;
            default: break;
        }

        }
    }

}