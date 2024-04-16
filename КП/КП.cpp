#include <iostream>
#include <fstream>
#include <conio.h>
#include "Restaurant.h"
#include "UI.h"
using namespace std;

void pause(); //_getch другим вызовом

int main()
{ 
    setlocale(LC_ALL, "ru");
    
    cout << "Курсовой проект. Артюшевский Артём. 73ТП. Ресторанный бизнес. Обработка заказов.\n";
    pause();
    

    UI userInterface;

    while (true)
    {
        userInterface.MainMenu();

        const char change_main_menu = _getch();

        switch (change_main_menu)
        {
        case '1': 

            userInterface.OrderMenu(); 
            break;

        case '2': 

            userInterface.RestaurantHistory(); 
            break;

        case '0': 

            break;
        default: break;
        }
    }

}

void pause()
{
    _getch();
}