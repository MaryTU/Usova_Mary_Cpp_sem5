#include "field.h"

#include <vector>

bool Field::shoot(int x, int y){
    // уменьшаем x и y на единичку так как у нас массив с 0, а выбор клетки с 1
    x--; y--;

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

    // Если пусто(true) то промах иначе попадание
    this->playing_feild[y][x] = (feild_free[y][x])?(MISS):(BROKEN);



    // Проверяем все ли корабли сломаны
    // всего клеток с кораблями
    int amount_cell_ships = 0;
    for(auto &ship:this->ships){ amount_cell_ships += ship.size_cell; }

    // количество сломанных клеток
    int amount_broken_cell = 0;
    for(auto &f1:this->playing_feild){
        for(auto &f2:f1){
            if(f2 == BROKEN){ amount_broken_cell++;}
        }
    }

    // если количество сломанных клеток равно общему количеству 
    this->ships_alive = (amount_cell_ships != amount_broken_cell);



    // и возвращаем true если попали и false в противном случае
    return (feild_free[y][x])?(false):(true);

    // // Смотрим есть ли в выбранной клетке корабль
    // bool cell_empty = true;
    // for(auto &ship:this->ships){
    //     if(ship.x_location == x && ship.y_location == y){
    //         cell_empty = false;
    //         break;
    //     }
    // }
    //
    // // Если нет то промах иначе попадание
    // this->playing_feild[y][x] = (cell_empty)?(MISS):(BROKEN);

}

// bool Field::checkingShipsAliveAfterShoot(){
    
// }

bool Field::alreadyShooT(int x, int y){
    // уменьшаем x и y на единичку так как у нас массив с 0, а выбор клетки с 1
    x--; y--;
    // возвращаем true если уже была аттакована клетка false в противном случае
    return (this->playing_feild[y][x] != NOT_ATTAKED)?(true):(false);
}
