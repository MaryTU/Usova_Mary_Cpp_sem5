#include "basketball_game.h"
#include "../basketball_player/basketball_player.h"

// За каждое действие, активное (передача, бросок) или пассивное (попытка подобрать, попытка перехватить, попытка помешать броску) игрок теряет от 1 до (5 – значение выносливости) очков энергии. Как только энергия игрока падает ниже 50, все его характеристики уменьшаются вдвое и его стоит заменить.
const int MAX_LOSE_ENERG = 5;
const int MIN_LOSE_ENERG = 1;

const int TIRED_ENERG = 50;

// уникальная рандомизация работает с момента создания игроков


// Тот у кого мяч определяет действие
Action BasketballGame::whatWeDo(BasketballPlayer &p){
    // Вероятность совершения действия вычисляется сопоставимо характеристикам игрока:
    // - Вероятность паса =  1,5 * передачи / (1,5 * передачи + 2очк + 3очк)
    // - Вероятность 2очк =  2очк / (1,5 * передачи + 2очк + 3очк)
    // - Вероятность 3очк =  3очк / (1,5 * передачи + 2очк + 3очк)  
    double n_assist = (p.getEnergy()>=TIRED_ENERG)?(1.5*(double)(p.getAssist())):(1.5*(double)(p.getAssist())/2);
    double n_tw = (p.getEnergy()>=TIRED_ENERG)?((double)(p.getTwoPointShot())):((double)(p.getTwoPointShot())/2);
    double n_th = (p.getEnergy()>=TIRED_ENERG)?((double)(p.getThreePointShot())):((double)(p.getThreePointShot())/2);

    double delitel = n_assist + n_tw + n_th; 

    double chance_pass = n_assist/delitel;
    double chance_two_point_shot = n_tw/delitel;
    // double chance_three_point_shot = n_th/delitel; // не обязателен к рассчету так как chance_pass + chance_two_point_shot + chance_three_point_shot = 1

    double chance = ((double)(rand()%101))/100;

    // // В любом из 3х действий тратится энергия
    // int lose_energe = rand()%(MAX_LOSE_ENERG+1-MIN_LOSE_ENERG) + MIN_LOSE_ENERG;
    // int rez_energy = p.getEnergy() - lose_energe;
    // p.setEnergy((rez_energy<0)?(0):(rez_energy));

    if(chance<=chance_pass){ return PASS; }
    else if(chance_pass<chance && chance<=(chance_pass+chance_two_point_shot)){ return TWO_POINT_SHOT; }
    else { return THREE_POINT_SHOT; }
}



// перехват
bool BasketballGame::doSteal(BasketballPlayer &p_steal, BasketballPlayer &p_pass){
    // но игрок опекающий его может перехватить его с вероятностью 15 + (значение перехвата – значение передачи дающего) процентов. Тогда начинает атаковать другая команда.
    
    double ch_steal = (p_steal.getEnergy()>=TIRED_ENERG)?(p_steal.getSteal()):((double)(p_steal.getSteal())/2);
    double ch_pass = (p_pass.getEnergy()>=TIRED_ENERG)?(p_pass.getSteal()):((double)(p_pass.getSteal())/2);

    double chance_steal = 15 + ch_steal - ch_pass;
    
    double chance = (double)(rand()%101);

    // энергия того кто хотел перехватить
    this->loseEnargy(p_steal);
    // энергия того кто пассовал
    this->loseEnargy(p_pass);

    if(chance_steal>=chance){
        return true; // украли мяч
    }
    else{ return false; } // спасовали мяч
}



// Бросо в кольцо
bool BasketballGame::doShot(BasketballPlayer &p_shot, BasketballPlayer &p_block, Action type_shot){
    // В случае любого броска, игрок забивает с вероятностью n + (значение показателя этого броска – значение блокшота опекающего – значение перехвата опекающего) процентов. n для 2очк = 40, для 3очк=30. 
    double n = 0;
    double n_shot = 0;
    if(type_shot == TWO_POINT_SHOT) { 
        n = 40;
        n_shot = (p_shot.getEnergy()>=TIRED_ENERG)?((double)(p_shot.getTwoPointShot())):(((double)(p_shot.getTwoPointShot()))/2); 
    }
    else if(type_shot == THREE_POINT_SHOT) {
        n = 30; 
        n_shot = (p_shot.getEnergy()>=TIRED_ENERG)?((double)(p_shot.getThreePointShot())):(((double)(p_shot.getThreePointShot()))/2); 
    }

    double n_block = (p_block.getEnergy()>=TIRED_ENERG)?((double)(p_block.getBlocks())):(((double)(p_block.getBlocks()))/2);
    double n_steal = (p_block.getEnergy()>=TIRED_ENERG)?((double)(p_block.getSteal())):(((double)(p_block.getSteal()))/2);

    double chance_shot = n + n_shot - n_block - n_steal;
 
    // энергия того кто атаковал
    this->loseEnargy(p_shot);
    // энергия того кто защищал
    this->loseEnargy(p_block);

    double chance = (double)(rand()%101);

    if(chance_shot>=chance){
        return true; // мяч попал в кольцо
    }
    else{ return false; } // не попал
}



// уменьшение энергии из-за действия
void BasketballGame::loseEnargy(BasketballPlayer &p){
    // За каждое действие, активное (передача, бросок) или пассивное (попытка подобрать, попытка перехватить, попытка помешать броску) игрок теряет от 1 до (5 – значение выносливости) очков энергии. Как только энергия игрока падает ниже 50, все его характеристики уменьшаются вдвое и его стоит заменить.
    // Вот тут нужно как то использовать выносливость
    int lose_energe = rand()%(MAX_LOSE_ENERG+1-MIN_LOSE_ENERG) + MIN_LOSE_ENERG;
    int rez_energy = p.getEnergy() - lose_energe;
    p.setEnergy((rez_energy<0)?(0):(rez_energy));
    return;
}



// подбор не попавшего мяча
bool BasketballGame::doRebounds(BasketballPlayer &p_attack,BasketballPlayer &p_defend){
    // Если бросок не забит, из каждой команды случайно выбирается по игроку, которые борются за подбор. Игроку нападение к характеристике подбора прибавляется значение от 1 до 7, а игроку защиты от 1 до 10, подбор забирает игрок с большим суммарным значением и его команда начинает атаковать. 
    double attack_rebound = (rand()%7 + 1) + (p_attack.getEnergy()>=TIRED_ENERG)?((double)(p_attack.getRebound())):(((double)(p_attack.getRebound()))/2);
    double defend_rebound = (rand()%10 + 1) + (p_defend.getEnergy()>=TIRED_ENERG)?((double)(p_defend.getRebound())):(((double)(p_defend.getRebound()))/2);

    this->loseEnargy(p_attack);
    this->loseEnargy(p_defend);

    // если true то аттакающая команда перехватила,
    // если false то защищающая команда перехватила
    if(attack_rebound > defend_rebound) { return true; }
    else if(attack_rebound == defend_rebound) { return (rand()%2==1)?(true):(false); }
    else { return false; }
}



// Попытка замены игрока
bool BasketballGame::attemptDoReplacePlayer(BasketballPlayer &p_tired, std::vector<BasketballPlayer> &work_group, std::vector<bool> &busy_team, BasketballTeam &team){
    // Как только энергия игрока падает ниже 50, все его характеристики уменьшаются вдвое и его стоит заменить. Менять можно только на игрока той же позиции и только если значение энергии игрока на скамейке меньше, чем у игрока на площадке. (видимо наоборот) 
    Position pos = p_tired.getPosition();
    for (int i = 0; i < (int)(busy_team.size()); i++){

        BasketballPlayer sub_p = team.getTeam()[i]; 

        if(busy_team[i] == false && sub_p.getPosition()==pos && sub_p.getEnergy()>TIRED_ENERG/*sub_p.getEnergy()>p_tired.getEnergy()*/){

            // находим на каком месте находится уставший игрок во всей команде
            int num_p = 0;
            for (int j = 0; j < (int)(busy_team.size()); j++){
                if(p_tired.getNumber() == team.getTeam()[j].getNumber()){ num_p = j; break;}
            }
            // находим позицию в раюочей группе
            int num_p2 = 0;
            for (int j = 0; j < (int)(work_group.size()); j++){
                if(p_tired.getNumber() == work_group[j].getNumber()){ num_p2 = j; break;}
            }

            busy_team[num_p] = false; // усаживаем уставшего на скамейку
            team.changePlayer(p_tired, num_p);
            busy_team[i] = true; // выпускаем игрока на поле
            work_group[num_p2] = team.getTeam()[i];
            
            return true; // произошла замена
        }
    }
    return false; // не произошла замена    
}


void BasketballGame::relaxOnBenchOneMinut(BasketballTeam &team, std::vector<bool> &busy_team){
    // При этом за каждую полноценную минут на скамейке игрок восстанавливает 5 очков энергии.
    for (int i = 0; i < (int)(busy_team.size()); i++){
        if(!busy_team[i]){
            int rez_energ = team.getTeam()[i].getEnergy() + 5; 
            if(rez_energ <= MAX_ENERGY) { team.restPlayer(i,rez_energ); }
            else{ team.restPlayer(i,MAX_ENERGY); }
        }
    }
    return;
}