#include "basketball_game.h"
#include "../basketball_team/basketball_team.h"

#include <vector>
#include <iostream>
#include <map>
#include <string>

void BasketballGame::play(){
    // рандом включен еще при создании команд, поэтому тут можно не начинать отсчет рандома

    // переменные для статистики
    std::vector<std::map<std::string,int>> stat_team1;
    std::vector<std::map<std::string,int>> stat_team2;
    // 0 - броски; 1 - забитые двухочковые; 2 - забитые трехочковые; 3 - всего пасов; 4 - удачные пассы; 5 - перехватов мяча; 6 - удачных перехватов мяча; 7 - блокшоты; 8 - удачные блокшоты; 9 - подборы; 10 - удачные подборы  
    std::map<std::string,int> m_p;
    m_p["shot"] = 0; m_p["good two-point shot"] = 0; m_p["good three-point shot"] = 0;
    m_p["pass"] = 0; m_p["good pass"] = 0; 
    m_p["steals"] = 0; m_p["good steals"] = 0;
    m_p["blocks"] = 0; m_p["good blocks"] = 0; 
    m_p["rebounds"] = 0; m_p["good rebounds"] = 0;
    for(int i = 0; i < 12; i++){
        stat_team1.push_back(m_p);
        stat_team2.push_back(m_p);
    }

    // Выбор из команд рабочей группы (игроков на поле) [2 защитника, 2 форварда и центровой]
    std::vector<BasketballPlayer> work_group1;
    std::vector<BasketballPlayer> work_group2;
    std::vector<bool> busy_team1(12, false);
    std::vector<bool> busy_team2(12, false);

    // лямбда функция на заполнение рабочей группы
    auto gen_work_group = [](std::vector<BasketballPlayer> t,std::vector<BasketballPlayer>& work_group1,std::vector<bool>& busy_team1){
        int def=0, fow=0, cen=0; int ii = 0;
        for(auto p:t/*this->team1.getTeam()*/){
            if(def!=2 && p.getPosition() == DEFENDER){
                work_group1.push_back(p);
                busy_team1[ii] = true;
                def++;
            }
            if(fow!=2 && p.getPosition() == FORWARD){
                work_group1.push_back(p);
                busy_team1[ii] = true;
                fow++;
            }
            if(cen!=1 && p.getPosition() == CENTER){
                work_group1.push_back(p);
                busy_team1[ii] = true;
                cen++;
            }

            ii++;
        }
    };
    gen_work_group(this->team1.getTeam(),work_group1,busy_team1);
    gen_work_group(this->team2.getTeam(),work_group2,busy_team2);

    // for(auto p:work_group1){
    //     std::cout<<p.getNumber()<<"\n";
    // }
    // for(auto p:busy_team1){
    //     std::cout<<p<<" ";
    // }

    // Переменная для хранения времени 
    int time_in_sec = 0;

    // Действие [Далее команды по очереди атакуют. В начале атаки, игрок даётся случайному игроку, и он делает с ним одну из трёх вещей – передача, двухочковый бросок, трёхочковый бросок.]

    int first_rand_player = (rand()%10); 

    bool move_team1 = true;
    if(first_rand_player>4){ move_team1 = false; }
    
    int num_pl = (first_rand_player)%5;

    // int i = 0;
    int quarter = 1;
    int old_amount_min = 0;
    while(true){
        // мутки со временем и отдыхом
        if(time_in_sec >= 40*60){
            std::cout<<"Time is up and the game ends with a score:\n\tTeam1\tTeam2\n";
            std::cout<<"\t"<<this->score_team1<<"\t"<<this->score_team2<<"\n";
            break; 
        }
        if(old_amount_min < (time_in_sec/60)){ // это работает только при условие что одно действие не более 59 секунд (у нас от 10 до 24, значит подходит)
            old_amount_min++;
            relaxOnBenchOneMinut(this->team1, busy_team1);
            relaxOnBenchOneMinut(this->team2, busy_team2);
        }
        if(old_amount_min%10 == 0 && old_amount_min!=0 && time_in_sec/60 >= quarter*10){ // Определяем перерывы и отдых в них
            quarter++;
            if(quarter == 2 || quarter == 4){
                std::cout<<"The end of the "<<quarter-1<<" quarter , we announce a break\n";
                for(int nn_p = 0; nn_p<(int)(busy_team1.size());nn_p++){
                    int rez_en = team1.getTeam()[nn_p].getEnergy() + 10;
                    rez_en = (rez_en <= 100)?(rez_en):(100);
                    team1.restPlayer(nn_p,rez_en);

                    int rez_en2 = team2.getTeam()[nn_p].getEnergy() + 10;
                    rez_en2 = (rez_en2 <= 100)?(rez_en2):(100);
                    team2.restPlayer(nn_p,rez_en2);
                }
                std::cout<<"The beginning of the "<< quarter <<" quarter\n";
            }
            else if(quarter == 3){
                std::cout<<"The end of the "<<quarter-1<<" quarter , we announce a break\n";
                for(int nn_p = 0; nn_p<(int)(busy_team1.size());nn_p++){
                    int rez_en = team1.getTeam()[nn_p].getEnergy() + 20;
                    rez_en = (rez_en <= 100)?(rez_en):(100);
                    team1.restPlayer(nn_p,rez_en);

                    int rez_en2 = team2.getTeam()[nn_p].getEnergy() + 20;
                    rez_en2 = (rez_en2 <= 100)?(rez_en2):(100);
                    team2.restPlayer(nn_p,rez_en2);
                }
                std::cout<<"The beginning of the "<< quarter <<" quarter\n";
            }
        }
        // Вывод текущего времяни
        int pereh_time_in_min = time_in_sec/60 - (quarter-1)*10; 
        std::cout<<"\t\t\t\t"<<quarter<<" quarter "
            <<pereh_time_in_min<<":"<<time_in_sec-pereh_time_in_min*60 - (quarter-1)*10*60<<"\n";
        // if(i==50){ break;}
        // i++;

        std::cout<<"- ";
        Action act;
        if(move_team1){ 
            act = this->whatWeDo(work_group1[num_pl]);
            work_group1[num_pl].viewDate(); 
        }
        else{
            act = this->whatWeDo(work_group2[num_pl]); 
            work_group2[num_pl].viewDate(); 
        }
        std::cout<< " from "<<((move_team1)?(1):(2))<<" team, get ball\n- And he want ";

        int num_enemy_pl = rand()%5; // номер противника

        if(act==PASS){
            /////////stat//////////
            if(move_team1){ stat_team1[work_group1[num_pl].getNumber()-1]["pass"]++; }
            else { stat_team2[work_group2[num_pl].getNumber()-1]["pass"]++; }
            ///////////////////////
            std::cout<<"pass ball\n";
            bool rez;
            if(move_team1){ rez = doSteal(work_group2[num_enemy_pl],work_group1[num_pl]); }
            else { rez = doSteal(work_group1[num_enemy_pl],work_group2[num_pl]); }

            if(rez){
                /////////stat//////////
                if(move_team1){ 
                    stat_team2[work_group2[num_enemy_pl].getNumber()-1]["steals"]++;
                    stat_team2[work_group2[num_enemy_pl].getNumber()-1]["good steals"]++; }
                else { 
                    stat_team1[work_group1[num_enemy_pl].getNumber()-1]["steals"]++; 
                    stat_team1[work_group1[num_enemy_pl].getNumber()-1]["good steals"]++; }
                ///////////////////////
                std::cout<<"- But ";
                ((move_team1)?(work_group2[num_enemy_pl].viewDate()):(work_group1[num_enemy_pl].viewDate()));
                std::cout<<" from "<<((move_team1)?(2):(1)) << " team, steal ball\n";

                move_team1 = !move_team1;
                num_pl = num_enemy_pl; // ход переходит к противнику
            }
            else{
                /////////stat//////////
                if(move_team1){ 
                    stat_team2[work_group2[num_enemy_pl].getNumber()-1]["steals"]++; 
                    stat_team1[work_group1[num_pl].getNumber()-1]["good pass"]++; }
                else { 
                    stat_team1[work_group1[num_enemy_pl].getNumber()-1]["steals"]++; 
                    stat_team2[work_group2[num_pl].getNumber()-1]["good pass"]++;}
                ///////////////////////
                int new_num_pl = rand()%5;
                if(new_num_pl == num_pl){ new_num_pl = (new_num_pl+1)%5; }
                num_pl = new_num_pl; // удачный пас сокомаднику

                std::cout<<"- And he made a good pass for ";
                ((move_team1)?(work_group1[new_num_pl].viewDate()):(work_group2[new_num_pl].viewDate()));
                std::cout<<" from "<<((move_team1)?(1):(2)) << " team\n";
            }
        }
        else{
            /////////stat//////////
            if(move_team1){ stat_team1[work_group1[num_pl].getNumber()-1]["shot"]++; }
            else { stat_team2[work_group2[num_pl].getNumber()-1]["shot"]++; }
            ///////////////////////
            if(act == TWO_POINT_SHOT){ std::cout<<"score a two-pointer\n";}
            else { std::cout<<"score a three-pointer\n"; }

            bool rez;
            if(move_team1){ rez = doShot(work_group1[num_pl], work_group2[num_enemy_pl], act); }
            else { rez = doShot(work_group2[num_pl], work_group1[num_enemy_pl], act); }

            if(!rez){ // если false то защитили (не попали в) кольцо 
                /////////stat//////////
                if(move_team1){ 
                    stat_team2[work_group2[num_enemy_pl].getNumber()-1]["blocks"]++;
                    stat_team2[work_group2[num_enemy_pl].getNumber()-1]["good blocks"]++;
                }else {  
                    stat_team1[work_group1[num_enemy_pl].getNumber()-1]["blocks"]++; 
                    stat_team1[work_group1[num_enemy_pl].getNumber()-1]["good blocks"]++; }
                ///////////////////////
                std::cout<<"- But ";
                ((move_team1)?(work_group2[num_enemy_pl].viewDate()):(work_group1[num_enemy_pl].viewDate()));
                std::cout<<" from "<<((move_team1)?(2):(1)) << " team, defended the basketball hoop\n";

                // Далее идет подбор
                int p_att = rand()%5; int p_def = rand()%5;
                bool p_attacked_get_ball; 
                if(move_team1){ p_attacked_get_ball = doRebounds(work_group1[p_att],work_group2[p_def]); }
                else { p_attacked_get_ball = doRebounds(work_group2[p_att],work_group1[p_def]); }
                /////////stat//////////
                if(move_team1){
                    stat_team1[work_group1[p_att].getNumber()-1]["rebounds"]++; 
                    stat_team2[work_group2[p_def].getNumber()-1]["rebounds"]++;
                }else { 
                    stat_team2[work_group2[p_att].getNumber()-1]["rebounds"]++; 
                    stat_team1[work_group1[p_def].getNumber()-1]["rebounds"]++; }
                ///////////////////////


                // тут нужно вывести информацию о подборе
                std::cout<<"- Attaked ";
                ((move_team1)?(work_group1[p_att].viewDate()):(work_group2[p_def].viewDate()));
                std::cout<<" from "<<((move_team1)?(1):(2))<<" team and defended ";
                ((move_team1)?(work_group2[p_att].viewDate()):(work_group1[p_def].viewDate()));
                std::cout<< " from "<<((move_team1)?(2):(1))<<" team are fighting for the ball selection\n";

                if(p_attacked_get_ball){ // если аттакующая сторона перехватиа мяч
                    /////////stat//////////
                    if(move_team1){stat_team1[work_group1[p_att].getNumber()-1]["good rebounds"]++;
                    }else { stat_team2[work_group2[p_att].getNumber()-1]["good rebounds"]++;}
                    ///////////////////////
                    // Если аттакующая команда получила мяч, ведущая команда не изменяется
                    num_pl = p_att;
                    std::cout<<"- The attacking team got the ball\n";
                }
                else{ // если защищающаяся сторона перехватиа мяч
                    /////////stat//////////
                    if(move_team1){stat_team2[work_group2[p_def].getNumber()-1]["good rebounds"]++;
                    }else { stat_team1[work_group1[p_def].getNumber()-1]["good rebounds"]++;}
                    ///////////////////////
                    // Если защищающаяся команда получила мяч, ведущая команда изменяется
                    num_pl = p_def;
                    move_team1 = !move_team1;
                    std::cout<<"- The defending team got the ball\n";
                }
            }
            else{
                /////////stat//////////
                if(move_team1){ 
                    if(act == TWO_POINT_SHOT){stat_team1[work_group1[num_pl].getNumber()-1]["good two-point shot"]++;} 
                    else {stat_team1[work_group1[num_pl].getNumber()-1]["good three-point shot"]++;} 
                    stat_team2[work_group2[num_enemy_pl].getNumber()-1]["blocks"]++;
                }else { 
                    if(act == TWO_POINT_SHOT){stat_team2[work_group2[num_pl].getNumber()-1]["good two-point shot"]++;} 
                    else {stat_team2[work_group2[num_pl].getNumber()-1]["good three-point shot"]++;} 
                    stat_team1[work_group1[num_enemy_pl].getNumber()-1]["blocks"]++; 
                }
                ///////////////////////
                // удачное попадание
                std::cout<<"- And he earned "<<((act == TWO_POINT_SHOT)?(2):(3))<<" points for his team\n";
                
                // Нужно показать счёт и начать заново
                int n_score = (act == TWO_POINT_SHOT)?(2):(3);

                if(move_team1){ this->score_team1 += n_score; }
                else{ this->score_team2 += n_score; }

                std::cout<<"- Now the score of the game:\n\tTeam1\tTeam2\n";
                std::cout<<"\t"<<this->score_team1<<"\t"<<this->score_team2<<"\n";

                // Только в этот момент и в перерыв логично сделать замену во всех командах, если необходимо
                for (int i = 0; i < (int)(work_group1.size()); i++){
                    if(work_group1[i].getEnergy()<50){
                        std::cout<<"- ";
                        work_group1[i].viewDate();

                        bool replace = attemptDoReplacePlayer(work_group1[i],work_group1,busy_team1,this->team1);
                        if(replace){
                            std::cout<<" was replaced by ";
                            work_group1[i].viewDate();
                            std::cout<<"\n";
                        }
                        else{
                            std::cout<<" tired but there's no one to replace him\n";
                        }
                    }
                }
                for (int i = 0; i < (int)(work_group2.size()); i++){
                    if(work_group2[i].getEnergy()<50){
                        std::cout<<"- ";
                        work_group2[i].viewDate();

                        bool replace = attemptDoReplacePlayer(work_group2[i],work_group2,busy_team2,this->team2);
                        if(replace){
                            std::cout<<" was replaced by ";
                            work_group2[i].viewDate();
                            std::cout<<"\n";
                        }
                        else{
                            std::cout<<" tired but there's no one to replace him\n";
                        }
                    }
                }
                

                // Выбираем человека из всех кто заберет мяч в начале хода
                int first_get_player = (rand()%10); 

                move_team1 = true;
                if(first_get_player>4){ move_team1 = false; }
                
                num_pl = (first_rand_player)%5;

            }
        }

        // Каждая атака команды занимает от 10 до 24 секунд.
        int time_attack = rand()%(24+1 - 10) + 10;
        time_in_sec += time_attack;
    }

    std::cout<<"\n\n\t\t\tStatistics\n";
    auto func_print_stat = [](std::vector<std::map<std::string,int>> stat_team1, BasketballTeam team1){
        int gege = 0;
        for(auto e_p:stat_team1){
            std::cout<<gege+1<<". ";
            team1.getTeam()[gege].viewDate();
            std::cout<<std::endl;
            std::cout<<"\t shoot: "<<e_p["shot"]<<"\tgood two-point shot:"<<e_p["good two-point shot"]<<"\tgood three-point shot: "<<e_p["good three-point shot"]<<"\n";
            std::cout<<"\t pass: "<<e_p["pass"]<<"\tgood pass:"<<e_p["good pass"]<<"\n";
            std::cout<<"\t steals: "<<e_p["steals"]<<"\tgood steals:"<<e_p["good steals"]<<"\n";
            std::cout<<"\t blocks: "<<e_p["blocks"]<<"\tgood blocks:"<<e_p["good blocks"]<<"\n";
            std::cout<<"\t rebounds: "<<e_p["rebounds"]<<"\tgood rebounds:"<<e_p["good rebounds"]<<"\n";
            gege++;
        }
    };

    std::cout<<"Team 1:\n";
    func_print_stat(stat_team1,this->team1);
    std::cout<<"Team 2:\n";
    func_print_stat(stat_team2,this->team2);

    return;
}