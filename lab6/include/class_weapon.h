#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>

const int MIN_SHOOT_DAMAGE = 100;
const int MAX_SHOOT_DAMAGE = 500;
const std::vector<int> SIZES_OF_WEAPON_STORE = {65, 75, 100};
// одна энная часть магазина одна очередь в секунду
const int ENNAIA = 5;

enum TypeShooting{
    SINGLE_SHOOTING,
    FIRING_BURSTS,
};

class Weapon
{
    private:
        int magazin, max_cartridges_in_magazine;
        TypeShooting type_shooting;

        int damage;
        int rate_of_fire; // выстрелов в секунду

        int empty_magazin = false;
    public:
        Weapon();
        Weapon(int max_cartridges_in_magazine, TypeShooting type_shooting, int damage, int rate_of_fire);
        ~Weapon();

    public:
        double shoot();
        double shoot(int time_shoot); //время в секундах
        void recharge();
        void changeFiringMode();

        double getChance();
        bool isEmptyMagazin();
};


Weapon::Weapon(){
    //std::srand(std::time(NULL));

    this->damage = rand()%(MAX_SHOOT_DAMAGE+1-MIN_SHOOT_DAMAGE) + MIN_SHOOT_DAMAGE;
    this->type_shooting = (TypeShooting)(rand()%2);
    this->max_cartridges_in_magazine = SIZES_OF_WEAPON_STORE[rand()%(SIZES_OF_WEAPON_STORE.size())];
    this->magazin = this->max_cartridges_in_magazine;
    this->rate_of_fire = (int)std::ceil(((double)this->max_cartridges_in_magazine)/ENNAIA);
}
Weapon::Weapon(int max_cartridges_in_magazine, TypeShooting type_shooting, int damage, int rate_of_fire){
    this->max_cartridges_in_magazine = max_cartridges_in_magazine;
    this->type_shooting = type_shooting;
    this->damage = damage;
    this->rate_of_fire = rate_of_fire;
}
Weapon::~Weapon(){}


double Weapon::shoot(){
    if(this->magazin == 0){
        this->empty_magazin = true;
        return 0;
    }
    magazin--;
    if(this->magazin == 0) this->empty_magazin = true;
    return damage;
}
double Weapon::shoot(int time_shoot){
    if(this->type_shooting == SINGLE_SHOOTING){
        return this->shoot();
    }
    else if(this->type_shooting == FIRING_BURSTS){
        int all_damage = 0;
        for (int i = 0; i < time_shoot; i++){
            if(this->magazin < this->rate_of_fire){
                all_damage += this->magazin*damage;
                this->magazin = 0;
                this->empty_magazin = true;
                return all_damage;
            }
            all_damage += this->rate_of_fire*damage;
            this->magazin -= this->rate_of_fire;
        }
        return all_damage;
    }
    return 0;
}

void Weapon::recharge(){
    this->magazin = this->max_cartridges_in_magazine;
    this->empty_magazin = false;
    return;
}
void Weapon::changeFiringMode(){
    if (this->type_shooting == SINGLE_SHOOTING)
        this->type_shooting = FIRING_BURSTS;
    else
        this->type_shooting = SINGLE_SHOOTING;
    return;   
}

double Weapon::getChance(){
    std::srand(std::time(NULL));
    return ((double)(rand()%(101))/100);
}

bool Weapon::isEmptyMagazin(){
    return this->empty_magazin;
}
