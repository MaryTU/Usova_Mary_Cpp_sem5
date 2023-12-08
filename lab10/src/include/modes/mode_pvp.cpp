#include "modes.h"

#include <iostream>
#include <string>
#include <sstream>

void playPVPGen(Field &p1, Field &p2){
    // // Для отладочки
    // {
    //     std::cout<<"1 Player:\n";
    //     p1.viewFieldWithShips();
        
    //     std::cout<<"\n2 Player:\n";
    //     p2.viewFieldWithShips();
    // }
    
    // переменная которая определяет кто сейчас ходит
    bool move_1p = true;

    // сам процесс игры 
    while(true){
        std::cout<<"\n1 Player:\n";
        p1.viewPlayingField();
        std::cout<<"\n2 Player:\n";
        p2.viewPlayingField();

        // Получаем от пользователя координаты
        int x, y;
        while(true){
            if(move_1p){ std::cout<<"\n1 player's move(in the 1:1 format): "; }
            else{ std::cout<<"\n2 player's move(in the 1:1 format): "; }
            std::string str_x_y = "";
            std::cin >> str_x_y;

            // Парсим строку
            std::istringstream ss(str_x_y);
            char ch; // для хранения символа ':'
            ss >> x >> ch >> y;
            // Проверка что бы не выходить за границы массива
            if(!(x>0 && x < 11 && y>0 && y < 11)){
                std::cout<<"The coordinates are out of bounds, try again\n"; 
                continue;
            }

            // Проверка что точка уже была ранее аттакована
            if(move_1p){
                if(p2.alreadyShooT(x,y)){
                    std::cout<<"You have already attacked that point before, try again\n";
                } else { break; }
            }
            else{
                if(p1.alreadyShooT(x,y)){
                    std::cout<<"You have already attacked that point before, try again\n";
                } else { break; }
            }
        }
        

        bool broken_ship = false;
        // выстрел
        if(move_1p){ broken_ship = p2.shoot(x,y);}
        else{ broken_ship = p1.shoot(x,y); }

        if(broken_ship){
            std::cout<<"hit\n";
        }
        else{
            std::cout<<"miss\n";
            move_1p = !move_1p;
        }


        // Если все корабли у кого-то разрушены игра окончена
        if(!p1.getShipsAlive()){
            std::cout<<"Player 2 win!!!\n";
        }
        if(!p2.getShipsAlive()){
            std::cout<<"Player 1 win!!!\n";
        }

        if(!p1.getShipsAlive() || !p2.getShipsAlive()){
            // Вывод игровых полей с коралями
            std::cout<<"Field player 1:\n";
            p1.viewFieldWithShips();
            std::cout<<"\nField player 2:\n";
            p2.viewFieldWithShips();
             

            // Вывод статистики
            std::cout<<"1 Player broken "<<p2.getAmountDestroyShips()<<" ships\n";
            std::cout<<"1 Player have accurate "<<p2.getAccurate()*100<<"%\n\n";

            std::cout<<"2 Player broken "<<p1.getAmountDestroyShips()<<" ships\n";
            std::cout<<"2 Player have accurate "<<p1.getAccurate()*100<<"%\n\n";

            break;
        }
        
        
    }
}
