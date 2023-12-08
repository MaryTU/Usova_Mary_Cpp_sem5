#include "field.h"

#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <numeric>
#include <exception>


// Реализовать генерацию заполнения игрового поля кораблями по введенному пользователем N не менее 10 (от N должно зависеть количество кораблей разного типа: одно клеточные(40%), дву клеточные(30%), трех клеточные(20%), четырех клеточные(10%)).

// Правила заполнения поля:
// - Корабли не могут примыкать друг к другу, минимальное расстояние между ними 1 клетка.
// - Корабли не могут изгибаться.
// - Корабль не может выходить за границы поля.

static bool randomchik = true;

void Field::fieldGeneration(){

    if(randomchik){
        std::srand(std::time(NULL));
        randomchik = false;
    }

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
    


    /// Расставляем кораблики по полю
    // это как бы поле 10 на 10 заполненое true (ячейки свободны)
    std::vector<std::vector<bool>> feild_free(10, std::vector<bool>(10, true));

    std::vector<Ships> ships;

    // начинаем с 4х клеточных кораблей
    for(int c = (int)cell.size() - 1; c >= 0; c--){
        // сколько n-клеточных столько и выполняем цикл
        for(int i=0; i<cell[c]; i++){
            // создаём экземпляр структуры кораблика
            Ships ship;
            
            // генерируем положение кораблика
            int location_ship = rand()%100; // так как у нас поле 10 на 10 то клеток 100

            // объявляем направление и координаты
            Direction direction;
            int x, y;

            // если пройдемся по всем клеткам и не найдем нужного положения то нужно возвращатся на шаг назад
            bool perfect_ship = false;
            for (int gege = 0; gege < 100; gege++){
                // расчитываем его координаты
                x = location_ship%10;
                y = (location_ship - x)/10;

                // и генерируем направление
                direction = (Direction)(rand()%4);
               
                // проверяем не заняты ли эти клетки
                bool is_free = true;
                // Проверяем направления 
                for (int d = 0; d < 4; d++){
                    is_free = true;
                    // проверяем не превышаем ли границы
                    if(direction == RIGHT){ if((x+c+1) >= 10){ is_free = false; } }
                    else if(direction == LEFT){ if((x-c-1) < 0){ is_free = false; } }
                    else if(direction == TOP){ if((y-c-1) < 0){ is_free = false; } }
                    else if(direction == BOTTOM){ if((y+c+1) >= 10){ is_free = false; } }

                    // если пересекаем границы меняем направление
                    if(!is_free){
                        direction = (Direction)(((int)direction + 1)%4);
                        continue;
                    }

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
                        if(direction == RIGHT){ is_free = is_free && around_free(x+am,y); }
                        else if(direction == LEFT){ is_free = is_free && around_free(x-am,y); }
                        else if(direction == TOP){ is_free = is_free && around_free(x,y-am); }
                        else if(direction == BOTTOM){ is_free = is_free && around_free(x,y+am);}
                    }

                    // если все хорошо выходим, иначе меняем направление
                    if(is_free){break;}
                    else {direction = (Direction)(((int)direction + 1)%4);}
                }

                // если мы нашли местоположение то это идеальный кораблик
                if(is_free){
                    perfect_ship = true;
                    break;
                }else{
                    // если никакое направление не подходит сдвигаемся на клетку
                    location_ship = (location_ship+1)%100;
                    continue;
                }
            } 

            if(perfect_ship){
                // Добавляем кораблик
                ship.size_cell = c + 1;
                ship.x_location = x;
                ship.y_location = y;
                ship.direction = direction;
                ships.push_back(ship);

                // Отмечаем на поле что уже нет места
                for(int am = 0; am< ship.size_cell; am++){
                    if(direction == RIGHT){ feild_free[y][x+am] = false; }
                    else if(direction == LEFT){ feild_free[y][x-am] = false; }
                    else if(direction == TOP){ feild_free[y-am][x] = false; }
                    else if(direction == BOTTOM){ feild_free[y+am][x] = false;}
                }

            }else{
                throw SomethingWrong();
                return;
            }
        }
    }

    // // Для отладки смотрим на итоговое поле 
    // for(auto &f1:feild_free){
    //     for(auto f2:f1){
    //         std::cout<<((f2)?(1):(0))<<" ";
    //     }
    //     std::cout<<"\n";
    // }

    this->ships = ships;

    return;
}