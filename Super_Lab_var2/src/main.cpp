#include "include/basketball_player/basketball_player.h"
#include "include/basketball_team/basketball_team.h"
#include "include/basketball_game/basketball_game.h"

#include <iostream>
#include <vector>


int main(){

    BasketballGame bg;
    bg.play();

    // BasketballTeam t1;
    // std::vector<BasketballPlayer> for_t1 = t1.getTeam();

    // for(auto f:for_t1){
    //     std::cout<<"Num "<<f.getNumber()<<"\n";
    //     std::cout<<"Position "<<f.getPosition()<<"\n";
    //     std::cout<<"2point "<<f.getTwoPointShot()<<"\n";
    //     std::cout<<"Having ball "<<f.getPossession()<<"\n\n";
    // }
    
    return 0;
}
