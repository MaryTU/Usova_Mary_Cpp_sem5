#include "basketball_game.h"
#include "../basketball_team/basketball_team.h"

BasketballGame::BasketballGame(){
    BasketballTeam t1;
    BasketballTeam t2;
    this->team1 = t1;
    this->team2 = t2;
    this->score_team1 = 0;
    this->score_team2 = 0;
}