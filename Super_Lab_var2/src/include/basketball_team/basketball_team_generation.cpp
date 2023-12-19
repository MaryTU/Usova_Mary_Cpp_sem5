#include "basketball_team.h"
#include "../basketball_player/basketball_player.h"

#include <ctime>
#include <iostream>

const int MIN_COUNT_DEFENDER = 4;
const int MIN_COUNT_FORWARD = 4;
const int MIN_COUNT_CENTER = 2;
const int MAX_SIZE_TEAM = 12;

// static bool team_first_rand = true;

void BasketballTeam::generateTeam(){

    // if(team_first_rand){
    //     std::srand(std::time(NULL));
    //     team_first_rand = false;
    // }

    // Реализовать класс команда, который хранит в себе 12 игроков. В составе каждой команды должно быть хотя бы 4 защитника, 4 форварда и 2 центровых.

    // защитники
    for (int i = 1; i <= MIN_COUNT_DEFENDER; i++){
        BasketballPlayer b(DEFENDER,i);
        this->team.push_back(b);
    }
    int counter = MIN_COUNT_DEFENDER;

    // форварды
    for (int i = counter+1; i <= counter+MIN_COUNT_FORWARD; i++){
        BasketballPlayer b(FORWARD,i);
        this->team.push_back(b);
    }
    counter += MIN_COUNT_FORWARD;
    
    // центровые
    for (int i = counter+1; i <= counter+MIN_COUNT_CENTER; i++){
        BasketballPlayer b(CENTER,i);
        this->team.push_back(b);
    }
    counter +=MIN_COUNT_CENTER;

    // любые
    for (int i = counter; i <= MAX_SIZE_TEAM; i++){
        Position p = (Position)(rand()%3); // рандом уже 100% отработает при создании предыдущих игроков
        BasketballPlayer b(p,i);
        this->team.push_back(b);
    }
    
    return;
}