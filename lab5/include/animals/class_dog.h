#include <ctime>
#include <string>
#include <vector>

const int DOG_FATIGUE_PER_HOUR_FROM_PEOPLE = 10; //усталость при игре с человеком
const int DOG_FATIGUE_PER_HOUR_FROM_DOG = 5; // усталость при игре с животным

const int DOG_HUNGRY_WHILE_PLAY_PER_HOUR = 9; // на сколько сытость падает у собаки в час

const double DOG_PROBABILITY_FEEDING_BY_VISITER = 0.4; // вероятность что посетитель накормит животное
const int DOG_BEING_FED_BY_VISITER = 10; // сколько может восстановить сытости еда от посетителей 


class Dog: public Animals{
    private:
        const int sleep_duration = 8; // 8 часов нужно что бы выспаться с 0 до 100
        std::vector<int> time_eat {6, 9, 15, 21}; // цикл питания

    public:
        Dog(std::string name, int age);
        ~Dog();

    public:
        using Animals::eat;

        void eat(int time_to_eat);
        void play();
        void playWithAnimal();
        void sleep();

};

Dog::Dog(std::string name, int age){
    this->name = name;
    this->age = age;
}

Dog::~Dog(){}


void Dog::play(){
    // усталость копится 10 в час
    if (this->fatigue < (100 - DOG_FATIGUE_PER_HOUR_FROM_PEOPLE)){
        this->fatigue += DOG_FATIGUE_PER_HOUR_FROM_PEOPLE;
    }
    else{
        this->fatigue = 100;
    }

    // так же уменьшается сытость
    if(this->satiety > DOG_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= DOG_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;;
    }

    // но посетители могут покормить с какой-то верочтностью животное разрешенной едой небольшого объема
    std::srand(std::time(NULL));
    double ver_feeding = (double)(rand()%101);
    if((ver_feeding/100) < DOG_PROBABILITY_FEEDING_BY_VISITER){
        if(this->satiety < (100 - DOG_BEING_FED_BY_VISITER)){
            this->satiety += DOG_BEING_FED_BY_VISITER;
        }else{
            this->satiety = 100;
        }
    }
}
void Dog::playWithAnimal(){
    // усталость копится 5 в час
    if (this->fatigue < (100 - DOG_FATIGUE_PER_HOUR_FROM_DOG)){
        this->fatigue += DOG_FATIGUE_PER_HOUR_FROM_DOG;
    }
    else{
        this->fatigue = 100;
    }

    // так же копится голод
    if(this->satiety > DOG_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= DOG_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;
    }
}
void Dog::eat(int time_to_eat){
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
void Dog::sleep(){
    // за 1 час усталость снимется 100/sleep_duration
    int relax = (int)(100/this->sleep_duration);
    if(this->fatigue > relax){
        this->fatigue -= relax;
    }else{
        this->fatigue = 0;
    }

    // так же уменьшается сытость
    if(this->satiety > DOG_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= DOG_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;;
    }
}