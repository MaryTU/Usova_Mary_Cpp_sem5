#ifndef BASKETBALL_GAME_H
#define BASKETBALL_GAME_H

#include "../basketball_team/basketball_team.h"

enum Action{
    TWO_POINT_SHOT,
    THREE_POINT_SHOT,
    PASS,
};

class BasketballGame{
    private:
        BasketballTeam team1;
        BasketballTeam team2;
        int score_team1;
        int score_team2;

    public:
        BasketballGame();
        ~BasketballGame(){}

    public:
        void play();

    private:
        Action whatWeDo(BasketballPlayer &p);
        bool doSteal(BasketballPlayer &p_steal, BasketballPlayer &p_pass);
        bool doShot(BasketballPlayer &p_shot, BasketballPlayer &p_block, Action type_shot);
        bool doRebounds(BasketballPlayer &p_attack,BasketballPlayer &p_defend);
        bool attemptDoReplacePlayer(BasketballPlayer &p_tired, std::vector<BasketballPlayer> &work_group, std::vector<bool> &busy_team, BasketballTeam &team);

    private:
        void loseEnargy(BasketballPlayer &p);
        void relaxOnBenchOneMinut(BasketballTeam &team, std::vector<bool> &busy_team);
        
};

#endif