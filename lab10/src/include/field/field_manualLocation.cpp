#include "field.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <exception>
#include <sstream>

void Field::manualLocation(){
    /// Рассчёт количество корабликов каждого типа
    // 0 - 1 клеточные корабли, 1 - 2 клеточные корабли, 2..., 3...
    std::vector<int> cell(4);

    //for (int i = 0; i<(int)cell.size();i++){ cell[i] = round(((double)(this->n))*(i+1)*0.1); }
    cell[0] = round(((double)(this->n))*0.4);
    cell[1] = round(((double)(this->n))*0.3);
    cell[2] = round(((double)(this->n))*0.2);
    cell[3] = round(((double)(this->n))*0.1);

    int sum_ships = std::accumulate(cell.begin(),cell.end(),0); 

    while (sum_ships != this->n){
        if(sum_ships > this->n){cell[0]--;}
        if(sum_ships < this->n){cell[0]++;}
        sum_ships = std::accumulate(cell.begin(),cell.end(),0);
    }



    /// Проверка поместятся ли все кораблики на поле
    const int MAX_CELL_BUSY = 50; // (10/2)*10; для поля 10 на 10 с учетом если один корабль занимает + 1 клетку
    int sum_busy_cell = 0;
    for (int i = 0; i < (int)cell.size(); i++){
        sum_busy_cell += cell[i]*(i+1) + cell[i];
    }

    // если не помещается бросаем исключение
    if(sum_busy_cell > MAX_CELL_BUSY){
        throw std::invalid_argument("Such a number of boats will not fit on the field");
        return;
    }



    /// Вручную расставляем кораблики
    std::vector<std::vector<bool>> feild_free(10, std::vector<bool>(10, true));

    std::vector<Ships> ships;
    this->ships = ships;

    // Отобразим в первый раз поле, что бы пользователь понимал что есть поле
    this->viewFieldWithShips();

    // Цикл что бы пройти по каждому типу кораблей
    for(int c = (int)cell.size() - 1; c >= 0; c--){
        // Цикл что бы поставить нужное количество кораблей каждого типа
        for(int i=0; i<cell[c]; i++){ 


            // Переменные для получения от пользователя координат
            int x, y;
            Direction direct;

            while(true){
                std::cout<<"\nChoose a location for the " << c+1 << "-cell ship";
                std::cout<<"\nEnter the coordinates where you want to put the ship in the 1:1:R (R - right, L-left, T-top, B-bottom) format: ";
                std::string str_x_y_direction = "";
                std::cin >> str_x_y_direction;
                // Вообще желательно тут сделать возможность всё отменить и заново начать расставлять

                // Парсим строку
                std::istringstream ss(str_x_y_direction);
                char ch; // для хранения символа ':'
                ss >> x >> ch >> y >> ch >> ch; // считываем x и y
                // считываем направление
                if(ch == 'L'){direct = LEFT;}
                else if(ch == 'R'){direct = RIGHT;}
                else if(ch == 'T'){direct = TOP;}
                else if(ch == 'B'){direct = BOTTOM;}

                // Проверка что бы не выходить за границы массива
                if(!(x>0 && x < 11 && y>0 && y < 11)){
                    std::cout<<"The coordinates are out of bounds, try again\n"; 
                    continue;
                }

                // Уменьшаем x и y что бы было от 0 а не от 1
                x--;y--;

                // Проверка что края корабля не выходят за пределы поля
                // проверяем не заняты ли эти клетки
                bool not_board = true;
                // Проверяем направления 
                for (int d = 0; d < c + 1; d++){
                    bool is_free = true;
                    // проверяем не превышаем ли границы
                    if(direct == RIGHT){ if((x+d) >= 10){ is_free = false; } }
                    else if(direct == LEFT){ if((x-d) < 0){ is_free = false; } }
                    else if(direct == TOP){ if((y-d) < 0){ is_free = false; } }
                    else if(direct == BOTTOM){ if((y+d) >= 10){ is_free = false; } }
                    not_board = not_board && is_free; 
                }

                // у нас получается true если не пересекаются края в противном случае:
                if(!not_board){
                    std::cout<<"The coordinates are out of bounds, try again\n"; 
                    continue;
                }

                bool is_free = true;
                // Проверка что корабль не пересекается с другими кораблями 
                for (int d = 0; d < c + 1; d++){
                    // лямбда функция для проверки окружающих клеток
                    auto around_free = [&feild_free](int x1, int y1){
                        bool result = true;
                        if(
                            feild_free[y1][x1] &&
                            ((y1+1)==10 || feild_free[y1+1][x1]) && 
                            ((y1-1)==-1 || feild_free[y1-1][x1]) && 
                            ((x1+1)==10 || feild_free[y1][x1+1]) && 
                            ((x1-1)==-1 || feild_free[y1][x1-1]) && 
                            ((y1+1)==10 || (x1+1)==10 || feild_free[y1+1][x1+1]) && 
                            ((y1+1)==10 || (x1-1)==-1 || feild_free[y1+1][x1-1]) && 
                            ((y1-1)==-1 || (x1+1)==10 || feild_free[y1-1][x1+1]) && 
                            ((y1-1)==-1 || (x1-1)==-1 || feild_free[y1-1][x1-1])  
                            ){
                            return true;
                        }
                        return false;
                    };

                    // проверяем каждую клетку
                    for(int am = 0; am< c+1; am++){
                        if(direct == RIGHT){ is_free = is_free && around_free(x+am,y); }
                        else if(direct == LEFT){ is_free = is_free && around_free(x-am,y); }
                        else if(direct == TOP){ is_free = is_free && around_free(x,y-am); }
                        else if(direct == BOTTOM){ is_free = is_free && around_free(x,y+am);}
                    }
                }   

                // Если всё свободно для каждой клетки корабя должно быть true, иначе:
                if(is_free){
                    break;
                }else{
                    std::cout<<"The ship intersects with other objects, try again\n"; 
                    continue;
                }  
            }

            // Если мы дошли до этого момента, значит место свободно, тогда создадим экземпляр корабля
            Ships ship;
            ship.direction = direct;
            ship.x_location = x;
            ship.y_location = y;
            ship.size_cell = c + 1;
            // Отмечаем на поле, что уже нет места
            for(int am = 0; am< ship.size_cell; am++){
                if(direct == RIGHT){ feild_free[y][x+am] = false; }
                else if(direct == LEFT){ feild_free[y][x-am] = false; }
                else if(direct == TOP){ feild_free[y-am][x] = false; }
                else if(direct == BOTTOM){ feild_free[y+am][x] = false;}
            }
            // И добавим ко всем кораблям в классе
            this->ships.push_back(ship);

            // И конечно отобразим что получилось и заново
            this->viewFieldWithShips();
        }
    }
}