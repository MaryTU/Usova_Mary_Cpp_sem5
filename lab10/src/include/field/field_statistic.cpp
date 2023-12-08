#include "field.h"


int Field::getAmountDestroyShips(){
    int amount_destroy_ships = 0;

    for(auto &ship:this->ships){
        bool full_broken = true;
        for (int i = 0; i < ship.size_cell; i++){
            bool pereh = false;

            if(ship.direction == RIGHT){ 
                pereh = (this->playing_feild[ship.y_location][ship.x_location+i] == BROKEN);
            }
            else if(ship.direction == LEFT){
                pereh = (this->playing_feild[ship.y_location][ship.x_location-i] == BROKEN);
            }
            else if(ship.direction == TOP){
                pereh = (this->playing_feild[ship.y_location-i][ship.x_location] == BROKEN);
            }
            else if(ship.direction == BOTTOM){
                pereh = (this->playing_feild[ship.y_location+i][ship.x_location] == BROKEN);
            }

            full_broken = full_broken && pereh;
        }
        
        if(full_broken){
            amount_destroy_ships++;
        }
    }

    return amount_destroy_ships;
}


int Field::getAmountShoot(){
    int amount_shoot = 0;

    for(auto &f1:this->playing_feild){
        for(auto &f2:f1){
            if(f2 != NOT_ATTAKED){ amount_shoot++; }
        }
    }

    return amount_shoot;
}


int Field::getAmountBroken(){
    int amount_broken = 0;

    for(auto &f1:this->playing_feild){
        for(auto &f2:f1){
            if(f2 == BROKEN){ amount_broken++; }
        }
    }

    return amount_broken;
}

double Field::getAccurate(){
    int am_br = this->getAmountBroken();
    int am_sh = this->getAmountShoot();
    double accurate = ((double)am_br)/((double)am_sh);
    return accurate;
}

