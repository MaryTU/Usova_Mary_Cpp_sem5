#include "basketball_player.h"

BasketballPlayer::BasketballPlayer(Position position, int num){
    this->position = position;
    this->number = num;
    this->generat_player();
}