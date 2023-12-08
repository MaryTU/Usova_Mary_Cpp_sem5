#include "field.h"

#include <iostream>
#include <vector>

void Field::viewFieldWithShips(){

    // это как бы поле 10 на 10 заполненое true (ячейки свободны)
    std::vector<std::vector<bool>> feild_free(10, std::vector<bool>(10, true));

    for (auto &ship : this->ships){
        // Отмечаем на поле что уже нет места
        for(int am = 0; am< ship.size_cell; am++){
            if(ship.direction == RIGHT){ feild_free[ship.y_location][ship.x_location+am] = false; }
            else if(ship.direction == LEFT){ feild_free[ship.y_location][ship.x_location-am] = false; }
            else if(ship.direction == TOP){ feild_free[ship.y_location-am][ship.x_location] = false; }
            else if(ship.direction == BOTTOM){ feild_free[ship.y_location+am][ship.x_location] = false;}
        }   
    }

    // // Cмотрим на итоговое поле в виде ноликов и единиц
    // for(auto &f1:feild_free){
    //     for(auto f2:f1){
    //         std::cout<<((f2)?(1):(0))<<" ";
    //     }
    //     std::cout<<"\n";
    // }

    char symb[] = "ABCDEFGHIJ";
    for(char s:symb){ std::cout<<"  "<<s<<" ";}
    std::cout<<std::endl;

    int gg = 1;

    for(auto f1:feild_free){
        for(int i = 0; i < (10*4+1); i++){std::cout<<"-";}
        std::cout<<std::endl;

        for(auto f2:f1){
            char ch;
            if(f2 == 0){ ch = 'O'; }
            else { ch = ' '; }
            std::cout<<"| "<<ch<<" ";
        }
        std::cout<<"| "<<gg++<<"\n";
    }
    for(int i = 0; i < (10*4+1); i++){std::cout<<"-";}
    std::cout<<std::endl;

    return;
}


void Field::viewPlayingField(){
    char symb[] = "ABCDEFGHIJ";
    for(char s:symb){ std::cout<<"  "<<s<<" ";}
    std::cout<<std::endl;

    int gg = 1;

    for(auto &f1:this->playing_feild){
        for(int i = 0; i < (10*4+1); i++){std::cout<<"-";}
        std::cout<<std::endl;

        for(auto &f2:f1){
            char ch;
            if(f2 == NOT_ATTAKED){ ch = ' '; }
            else if(f2 == MISS){ ch = '*'; }
            else if(f2 == BROKEN){ ch = 'X'; }
            std::cout<<"| "<<ch<<" ";
        }
        std::cout<<"| "<<gg++<<"\n";
    }
    for(int i = 0; i < (10*4+1); i++){std::cout<<"-";}
    std::cout<<std::endl;

    return;
}

