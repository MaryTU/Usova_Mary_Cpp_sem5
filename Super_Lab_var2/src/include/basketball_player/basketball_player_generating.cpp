#include "basketball_player.h"

#include <ctime>
#include <iostream>

// если ориентированы то от 6 до 10
// если не ориентированы то от 1 до 5
int MIN_EXPERT = 6;
int MAX_EXPERT = 10;
int MIN_NEWBY = 1;
int MAX_NEWBY = 5;


static bool first_random = true;

void BasketballPlayer::generat_player(){

    if(first_random){
        std::srand(std::time(NULL));
        first_random = false;
    }

    // уникальные характеристики
    if(this->position == DEFENDER){
        // - защитники на передачи, перехваты и владение мячом
        this->two_point_shots = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
        this->three_point_shots = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
        this->rebounds = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
        this->assists = rand()%(MAX_EXPERT + 1 - MIN_EXPERT) + MIN_EXPERT;
        this->steals = rand()%(MAX_EXPERT + 1 - MIN_EXPERT) + MIN_EXPERT;
        this->blocks = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
        this->possession = rand()%(MAX_EXPERT + 1 - MIN_EXPERT) + MIN_EXPERT;
    }
    else if(this->position == FORWARD){
        // - форварды на все типы бросков и подборы
        this->two_point_shots = rand()%(MAX_EXPERT + 1 - MIN_EXPERT) + MIN_EXPERT;
        this->three_point_shots = rand()%(MAX_EXPERT + 1 - MIN_EXPERT) + MIN_EXPERT;
        this->rebounds = rand()%(MAX_EXPERT + 1 - MIN_EXPERT) + MIN_EXPERT;
        this->assists = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
        this->steals = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
        this->blocks = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
        this->possession = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
    }
    else if(this->position == CENTER){
        // - центровые больше ориентированы на двухочковые броски, подборы и блокшоты
        this->two_point_shots = rand()%(MAX_EXPERT + 1 - MIN_EXPERT) + MIN_EXPERT;
        this->three_point_shots = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
        this->rebounds = rand()%(MAX_EXPERT + 1 - MIN_EXPERT) + MIN_EXPERT;
        this->assists = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
        this->steals = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
        this->blocks = rand()%(MAX_EXPERT + 1 - MIN_EXPERT) + MIN_EXPERT;
        this->possession = rand()%(MAX_NEWBY + 1 - MIN_NEWBY) + MIN_NEWBY;
    }

    // характеристики для всех
    this->endurance = rand()%(4/*5+1-2*/)+2;
    this->energy = MAX_ENERGY;

    return;
}