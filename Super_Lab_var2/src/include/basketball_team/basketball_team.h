#ifndef BASKETBALL_TEAM_H
#define BASKETBALL_TEAM_H

#include "../basketball_player/basketball_player.h"

#include <vector>

class BasketballTeam{
    private:
        std::vector<BasketballPlayer> team;

    public:
        BasketballTeam(){this->generateTeam();}
        ~BasketballTeam(){}
    
    private:
        void generateTeam();

    public:
        std::vector<BasketballPlayer> getTeam(){return this->team;}

    public:
        void changePlayer(BasketballPlayer p, int pos) {this->team[pos] = p;}
        void restPlayer(int num_p, int energ){ this->team[num_p].setEnergy(energ); }
};


#endif