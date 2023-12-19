#ifndef BASKETBALL_PLAYER_H
#define BASKETBALL_PLAYER_H

#include <iostream>

enum Position{
    DEFENDER,
    FORWARD,
    CENTER,
};

const int MAX_ENERGY = 100;

class BasketballPlayer{
    private:
        Position position; //(defender / forward / center)
        int number; 
        int two_point_shots; // (1-10)
        int three_point_shots; //(1-10)
        int rebounds; //(1-10) подборы
        int assists; //(1-10) передачи
        int steals; //(1-10) перехваты
        int blocks; //(1-10) блокшоты
        int possession; //(1-10) ведение мячом
        int endurance; //(2-5) выносливость
        int energy; //(when generating 100)
    public:
        BasketballPlayer(){}
        BasketballPlayer(Position position, int num);
        ~BasketballPlayer(){}

    private:
        void generat_player();

    public:
        // getters
        int getTwoPointShot(){return this->two_point_shots; }
        int getThreePointShot(){return this->three_point_shots; }
        int getRebound(){return this->rebounds; }
        int getAssist(){return this->assists; }
        int getSteal(){return this->steals; }
        int getBlocks(){return this->blocks; }
        int getPossession(){return this->possession; }
        int getEndurance(){return this->endurance; }
        int getEnergy(){return this->energy; }
        int getNumber(){return this->number; }
        Position getPosition(){return this->position; }
    
    public:
        void setEnergy(int energy){this->energy = energy;}
    
    public:
        void viewDate(){
            if(this->position==FORWARD){std::cout<<"Forward";}else if(this->position==CENTER){std::cout<<"Center";}else{std::cout<<"Defender";}
            std::cout<<" player "<<this->getNumber()<<"(energ:"<<this->energy<<")";
        }
};

#endif