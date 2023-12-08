#include "bot.h"

#include <iostream>
#include <ctime>

static bool randodom = true;

static std::vector<int> bot_moves;
static int bot_good_shoot = -1;

bool bot_move(Field &enemy_field){
    // enemy_field.viewFieldWithShips();
    // Делаем что бы сколько функция не была вызвана были разные случайные значения
    if(randodom){
        std::srand(std::time(NULL));
        randodom = false;
    }

    // Если прошлое попадание не было удачным
    if(bot_good_shoot == -1){
        // Получаем случайную позицию
        int position = (rand()*rand())%100;

        // Проверяем не использовали ли мы эту позицию ранее 
        if((int)(bot_moves.size()) != 0){
            for(int qu = 0; qu < (int)(bot_moves.size()); qu++){
                if(bot_moves[qu]==position){
                    position = (position + 1)%100;
                    qu = -1;
                }
            }
        }

        // Записываем во все ходы наш новый ход, что бы в будущем не повторять его
        bot_moves.push_back(position);

        // достаем из позиции координаты цели
        int x = position%10;
        int y = (position - x)/10;

        enemy_field.shoot(x+1,y+1);

        // Проверяем, если мы попали, то запоминаем позицию
        if(enemy_field.getPlayingFeid()[y][x] == BROKEN){
            // std::cout<<"!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n!\n";
            bot_good_shoot = position;
            return true;
        }
        return false;
    }
    else {
        // Возможно стоило сделать указание на то уничтожан ли корабль или нет, но такого в тз нет
        int x = bot_good_shoot%10;
        int y = (bot_good_shoot - x)/10;

        int position = bot_good_shoot;

        // Проверяем не было ли попадний что точно определят направление корабля
        int itii = -1;
        for (int i = 0; i < (int)(bot_moves.size()); i++){
            if(position == bot_moves[i]){itii = i;break;}
        }

        Direction dire;
        bool have_dire = false;
        if(itii + 1 < (int)(bot_moves.size())){
            for (int i = itii+1; i < (int)(bot_moves.size()); i++){
                int x_n = bot_moves[i]%10;
                int y_n = (bot_moves[i] - x_n)/10;
                if(enemy_field.getPlayingFeid()[y_n][x_n] == BROKEN){
                    // если у нас есть сломааная вторая часть корабля нужно понять какое направление
                    switch (bot_moves[i]-position){
                        case 1:
                            dire = RIGHT;// right
                            break;
                        case -1:
                            dire = LEFT;// left
                            break;
                        case 10:
                            dire = BOTTOM;// bottom
                            break;
                        case -10:
                            dire = TOP;// top
                            break;
                        default: 
                            break;
                    }
                    have_dire = true;
                    position = bot_moves[i];
                    //continue;
                }
                int some_x, some_y;
                if(have_dire){
                    if (dire == TOP){
                        some_x = x_n;
                        some_y = y_n-1;
                    }
                    else if(dire == BOTTOM){
                        some_x = x_n;
                        some_y = y_n+1;
                    }else if(dire == RIGHT){
                        some_x = x_n+1;
                        some_y = y_n;
                    }else if(dire == LEFT){
                        some_x = x_n-1;
                        some_y = y_n;
                    }
                    
                }
                if( 
                    have_dire && 
                    (enemy_field.getPlayingFeid()[y_n][x_n] == MISS ||
                    enemy_field.getPlayingFeid()[some_y][some_x] == MISS) &&
                    (bot_moves[i]-position == -1 || bot_moves[i]-position == 1 ||
                    bot_moves[i]-position == -10 || bot_moves[i]-position == 10)
                    ){
                    if(dire == LEFT){dire = RIGHT;}
                    else if(dire == RIGHT){dire = LEFT;}
                    else if(dire == TOP){dire = BOTTOM;}
                    else if(dire == BOTTOM){dire = TOP;}
                    position = bot_good_shoot;
                }
            }
        }
        
        



        
        // выбираем 1 из 4 соседних клеток от удачного попадания
        int position2;
        bool finding_empty_space = false;
        int rand_num;
        // если мы не вычислили направление идем через случай
        if(!have_dire){
            position2 = bot_good_shoot;
            rand_num = rand()%4;
            for(int b = 0; b<4; b++){
                if(rand_num == 0){//rigth
                    if((x+1) < 10){
                        if(enemy_field.getPlayingFeid()[y][x+1] == NOT_ATTAKED){
                            finding_empty_space = true;
                            position2 = position2 + 1;
                            x++; break;
                        }
                    }
                }
                else if(rand_num == 1){//left
                    if((x+1) >= 0){
                        if(enemy_field.getPlayingFeid()[y][x-1] == NOT_ATTAKED){
                            finding_empty_space = true;
                            position2 = position2 - 1;
                            x--; break;
                        }
                    }
                    
                }
                else if(rand_num == 2){//top
                    if((y-1) >= 0){
                        if(enemy_field.getPlayingFeid()[y-1][x] == NOT_ATTAKED){
                            finding_empty_space = true;
                            position2 = position2 - 10;     
                            y--; break;
                        }
                    }
                    
                }
                else if(rand_num == 3){//bottom
                    if((y+1) < 10){
                        if(enemy_field.getPlayingFeid()[y+1][x] == NOT_ATTAKED){
                            finding_empty_space = true;
                            position2 = position2 + 10;
                            y++; break;
                        }
                    }
                }
                rand_num = (rand_num+1)%4;
            } 
            
        }
        else{ // иначе идем через направление
            position2 = position;
            x = position2%10;
            y = (position2 - x)/10;
            if(dire == RIGHT){//rigth
                if((x+1) < 10){
                    if(enemy_field.getPlayingFeid()[y][x+1] == NOT_ATTAKED ){
                        finding_empty_space = true;
                        position2 = position2 + 1;
                        x++;
                    }
                }
                
            }
            else if(dire == LEFT){//left
                if((x+1) >= 0){
                    if(enemy_field.getPlayingFeid()[y][x-1] == NOT_ATTAKED){
                        finding_empty_space = true;
                        position2 = position2 - 1;
                        x--;
                    }
                } 
            }
            else if(dire == TOP){//top
                if((y-1) >= 0){
                    if(enemy_field.getPlayingFeid()[y-1][x] == NOT_ATTAKED ){
                        finding_empty_space = true;
                        position2 = position2 - 10;     
                        y--;
                    }
                }
                
            }
            else if(dire == BOTTOM){//bottom
                if((y+1) < 10){
                    if(enemy_field.getPlayingFeid()[y+1][x] == NOT_ATTAKED ){
                        finding_empty_space = true;
                        position2 = position2 + 10;
                        y++;
                    }
                }
                
            }
        }

        // Если мы нашли место для выстрела то стреляем
        if(finding_empty_space){
            bot_moves.push_back(position2);
            enemy_field.shoot(x+1,y+1);
            if(enemy_field.getPlayingFeid()[y][x] == BROKEN){
                return true;
            }
            return false;
        }else{
            bot_good_shoot = -1;
            bot_move(enemy_field); // что бы все таки выполнился ход 
        }
        

    }
    
    return false;
}

// void Bot::bot_move(){
//     this->enemy_field.viewFieldWithShips();
//     // Делаем что бы сколько функция не была вызвана были разные случайные значения
//     if(randodom){
//         std::srand(std::time(NULL));
//         randodom = false;
//     }

//     // Получаем случайную позицию
//     int position = rand()%100;

//     // Проверяем не использовали ли мы эту позицию ранее 
//     for(int qu = 0; qu < (int)(this->moves.size()); qu++){
//         if(this->moves[qu]==position){
//             position = (position + 1)%100;
//             qu = 0;
//         }
//     }

//     // Записываем во все ходы наш новый ход, что бы в будущем не повторять его
//     this->moves.push_back(position);

//     // достаем из позиции координаты цели
//     int x = position%10;
//     int y = (position - x)/10;



//     return;
// }