#include <string>
#include <ctime>
#include <vector>

const int RAT_FATIGUE_PER_HOUR_FROM_PEOPLE = 16; //усталость при игре с человеком
const int RAT_FATIGUE_PER_HOUR_FROM_RAT = 8; // усталость при игре с мышкой

const int RAT_HUNGRY_WHILE_PLAY_PER_HOUR = 7; // на сколько сытость падает у мышки в час

const double RAT_PROBABILITY_FEEDING_BY_VISITER = 0.2; // вероятность что посетитель накормит животное
const int RAT_BEING_FED_BY_VISITER = 40; // сколько может восстановить сытости еда от посетителей 



class Rat: public Animals{
    private:
        const int sleep_duration = 4; // 4 часов нужно что бы выспаться с 0 до 100
        std::vector<int> time_eat {0,6,12,18}; // цикл питания

    public:
        Rat(std::string name, int age);
        ~Rat();

    public:
        using Animals::eat;

        void eat(int time_to_eat);
        void play();
        void playWithAnimal();
        void sleep();

};

Rat::Rat(std::string name, int age){
    this->name = name;
    this->age = age;
}

Rat::~Rat(){}

void Rat::play(){
    // усталость копится 30 в час
    if (this->fatigue < (100 - RAT_FATIGUE_PER_HOUR_FROM_PEOPLE)){
        this->fatigue += RAT_FATIGUE_PER_HOUR_FROM_PEOPLE;
    }
    else{
        this->fatigue = 100;
    }

    // так же уменьшается сытость
    if(this->satiety > RAT_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= RAT_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;;
    }

    // но посетители могут покормить с какой-то верочтностью животное разрешенной едой небольшого объема
    std::srand(std::time(NULL));
    double ver_feeding = (double)(rand()%101);
    if((ver_feeding/100) < RAT_PROBABILITY_FEEDING_BY_VISITER){
        if(this->satiety < (100 - RAT_BEING_FED_BY_VISITER)){
            this->satiety += RAT_BEING_FED_BY_VISITER;
        }else{
            this->satiety = 100;
        }
    }
}
void Rat::playWithAnimal(){
    // усталость копится 10 в час
    if (this->fatigue < (100 - RAT_FATIGUE_PER_HOUR_FROM_RAT)){
        this->fatigue += RAT_FATIGUE_PER_HOUR_FROM_RAT;
    }
    else{
        this->fatigue = 100;
    }

    // так же копится голод
    if(this->satiety > RAT_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= RAT_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;
    }
}
void Rat::eat(int time_to_eat){
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
void Rat::sleep(){
    // за 1 час усталость снимется 100/sleep_duration
    int relax = (int)(100/this->sleep_duration);
    if(this->fatigue > relax){
        this->fatigue -= relax;
    }else{
        this->fatigue = 0;
    }

    // так же копится голод
    if(this->satiety > RAT_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= RAT_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;
    }
}
