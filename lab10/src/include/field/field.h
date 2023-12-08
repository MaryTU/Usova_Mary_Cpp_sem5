#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <exception>

/**
 * @brief Генерирует игровое поле с кораблями размером n на n
 * 
 * @param n размеры поля
 */

// Направления расположения кораблей
enum Direction{
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
};

// Структура корабля
struct Ships{
    int size_cell;
    int x_location;
    int y_location;
    Direction direction;
};

// Состояния клеткок поля
enum Condition{
    BROKEN,
    MISS,
    NOT_ATTAKED,
};

class Field{
    private:
        int n; /// amount ships
        std::vector<Ships> ships;
        std::vector<std::vector<Condition>> playing_feild;
        bool ships_alive;
        
    public:
        Field(){}
        Field(int n){
            this->n = n;
            this->ships_alive = true; 
            std::vector<std::vector<Condition>> playing_feild1(10, std::vector<Condition>(10, NOT_ATTAKED));
            this->playing_feild = playing_feild1;
        }
        ~Field(){}

    public:
        void fieldGeneration();

        void viewFieldWithShips();
        void viewPlayingField();

        bool shoot(int x, int y);
        bool alreadyShooT(int x, int y);

        int getAmountDestroyShips();
        int getAmountShoot();
        int getAmountBroken();
        double getAccurate();

        // Усложненный вариант
        void manualLocation();

    public:
        bool getShipsAlive(){ return this->ships_alive;}
        std::vector<std::vector<Condition>> getPlayingFeid(){ return this->playing_feild; }


};


// Определение собственного класса исключений
class SomethingWrong : public std::exception {
public:
    const char* what() const throw () {
        return "Something wrong with generation";
    }
};


#endif