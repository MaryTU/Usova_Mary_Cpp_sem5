#ifndef BOT_MOVING_H
#define BOT_MOVING_H

#include "../field/field.h"

#include <vector>

bool bot_move(Field &enemy_field);

// class Bot{
//     private:
//         std::vector<int> moves;
//         Field enemy_field;
//     public:
//         Bot(Field enemy_field){
//             this->enemy_field = enemy_field;
//         }
//         ~Bot(){}

//     public:
//         void bot_move();
// };


#endif