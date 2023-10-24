#include <string>
#include <ctime>
#include <vector>

const int CAT_FATIGUE_PER_HOUR_FROM_PEOPLE = 30; //усталость при игре с человеком
const int CAT_FATIGUE_PER_HOUR_FROM_CAT = 10; // усталость при игре с кошкой

const int CAT_HUNGRY_WHILE_PLAY_PER_HOUR = 8; // на сколько сытость падает у кошки в час

const double CAT_PROBABILITY_FEEDING_BY_VISITER = 0.75; // вероятность что посетитель накормит животное
const int CAT_BEING_FED_BY_VISITER = 10; // сколько может восстановить сытости еда от посетителей 


class Cat: public Animals{
    private:
        const int sleep_duration = 16; // 16 часов нужно что бы выспаться со 100 до 0
        std::vector<int> time_eat {0,2,4,6,8,10,12,14,16,18,20,22}; // цикл питания
    
    public:
        Cat(std::string name, int age);
        ~Cat();

    public:
        using Animals::eat;

        // собственным способом взаимодействия, длительностью сна и циклами питания.
        void eat(int time_to_eat);
        void play();
        void playWithAnimal();
        void sleep();

};

Cat::Cat(std::string name, int age){
    this->name = name;
    this->age = age;
}

Cat::~Cat(){}



void Cat::play(){
    // усталость копится 30 в час
    if (this->fatigue < (100 - CAT_FATIGUE_PER_HOUR_FROM_PEOPLE)){
        this->fatigue += CAT_FATIGUE_PER_HOUR_FROM_PEOPLE;
    }
    else{
        this->fatigue = 100;
    }

    // так же уменьшается сытость
    if(this->satiety > CAT_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= CAT_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;
    }

    // но посетители могут покормить с какой-то верочтностью животное разрешенной едой небольшого объема
    std::srand(std::time(NULL));
    double ver_feeding = (double)(rand()%101);
    if((ver_feeding/100) < CAT_PROBABILITY_FEEDING_BY_VISITER){
        if(this->satiety < (100 - CAT_BEING_FED_BY_VISITER)){
            this->satiety += CAT_BEING_FED_BY_VISITER;
        }else{
            this->satiety = 100;
        }
    }
}
void Cat::playWithAnimal(){
    // усталость копится 10 в час
    if (this->fatigue < (100 - CAT_FATIGUE_PER_HOUR_FROM_CAT)){
        this->fatigue += CAT_FATIGUE_PER_HOUR_FROM_CAT;
    }
    else{
        this->fatigue = 100;
    }

    // так же копится голод
    if(this->satiety > CAT_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= CAT_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;
    }
    
}
void Cat::eat(int time_to_eat){
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
void Cat::sleep(){
    // за 1 час усталость снимется 100/sleep_duration
    int relax = (int)(100/this->sleep_duration);
    if(this->fatigue > relax){
        this->fatigue -= relax;
    }else{
        this->fatigue = 0;
    }
    // так же уменьшается сытость
    if(this->satiety > CAT_HUNGRY_WHILE_PLAY_PER_HOUR){
        this->satiety -= CAT_HUNGRY_WHILE_PLAY_PER_HOUR;
    }else{
        this->satiety = 0;
    }
}

