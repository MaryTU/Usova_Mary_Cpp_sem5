#include <string>
#include <ctime>
#include <vector>

const int VOMBAT_FATIGUE_PER_HOUR_FROM_PEOPLE = 50; //усталость при игре с человеком
const int VOMBAT_FATIGUE_PER_HOUR_FROM_VOMBAT = 20; // усталость при игре с вомбатом

const int VOMBAT_HUNGRY_WHILE_PLAY_PER_HOUR = 5; // на сколько сытость падает у вомбата в час

const double VOMBAT_PROBABILITY_FEEDING_BY_VISITER = 0.9; // вероятность что посетитель накормит животное
const int VOMBAT_BEING_FED_BY_VISITER = 15; // сколько может восстановить сытости еда от посетителей 


class Vombat: public Animals{
    private:
        const int sleep_duration = 10; // 10 часов нужно что бы выспаться с 0 до 100
        std::vector<int> time_eat {6,10,14,18,22}; // цикл питания

    public:
        Vombat(std::string name, int age);
        ~Vombat();

    public:
        using Animals::eat;

        void eat(int time_to_eat);
        void play();
        void playWithAnimal();
        void sleep();


};

Vombat::Vombat(std::string name, int age){
    this->name = name;
    this->age = age;
}

Vombat::~Vombat(){}


void Vombat::play(){
    // усталость копится 30 в час
    if (this->fatigue < (100 - VOMBAT_FATIGUE_PER_HOUR_FROM_PEOPLE)){
        this->fatigue += VOMBAT_FATIGUE_PER_HOUR_FROM_PEOPLE;
    }
    else{
        this->fatigue = 100;
    }

    // так же уменьшается сытость
    if(this->satiety > VOMBAT_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= VOMBAT_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;;
    }

    // но посетители могут покормить с какой-то верочтностью животное разрешенной едой небольшого объема
    std::srand(std::time(NULL));
    double ver_feeding = (double)(rand()%101);
    if((ver_feeding/100) < VOMBAT_PROBABILITY_FEEDING_BY_VISITER){
        if(this->satiety < (100 - VOMBAT_BEING_FED_BY_VISITER)){
            this->satiety += VOMBAT_BEING_FED_BY_VISITER;
        }else{
            this->satiety = 100;
        }
    }
}
void Vombat::playWithAnimal(){
    // усталость копится 10 в час
    if (this->fatigue < (100 - VOMBAT_FATIGUE_PER_HOUR_FROM_VOMBAT)){
        this->fatigue += VOMBAT_FATIGUE_PER_HOUR_FROM_VOMBAT;
    }
    else{
        this->fatigue = 100;
    }

    // так же копится голод
    if(this->satiety > VOMBAT_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= VOMBAT_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;
    }
}
void Vombat::eat(int time_to_eat){
    // если время еды совпадает с циклом, то животное полностью кормится
    for(int a:this->time_eat){
        if (time_to_eat == a){
            this->satiety = 100;
            return;
        }
    }
    // елсли не совпадает с циклом питания, то только 25% от всей сыточти
    if (this->satiety < 75){
        this->satiety += 25;
    }
    else{
        this->fatigue = 100;
    }
    return;
}
void Vombat::sleep(){
    // за 1 час усталость снимется 100/sleep_duration
    int relax = (int)(100/this->sleep_duration);
    if(this->fatigue > relax){
        this->fatigue -= relax;
    }else{
        this->fatigue = 0;
    }

    // так же уменьшается сытость
    if(this->satiety > VOMBAT_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= VOMBAT_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;;
    }
}