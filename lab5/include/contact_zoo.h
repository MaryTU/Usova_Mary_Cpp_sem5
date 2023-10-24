#include <map>
//Стандартные заголовочные файлы, такие как <vector>, уже включают механизм защиты от множественного включения, поэтому не нужно беспокоиться о двойном включении и создавать собственные include guards для стандартных заголовочных файлов.
#include <vector>
#include <ctime>
#include <iostream>
#include <cmath>

const double CHANCE_TO_PLAY_CAT_WITH_CAT = 0.4;
const double CHANCE_TO_PLAY_DOG_WITH_DOG = 0.5;
const double CHANCE_TO_PLAY_VOMBAT_WITH_VOMBAT = 0.3;
const double CHANCE_TO_PLAY_RAT_WITH_RAT = 0.1;

const short DATE_SHIFT = 6;//что бы зоопарк начинал работать не с 00:00 а с 06:00


enum doing{
    NOTHING,
    SLEEP,
    EAT,
    ANIMAL_PLAY,
    HUMAN_PLAY,
};

enum typeAnimal{
    CAT,
    DOG,
    VOMBAT,
    RAT,
};

class ContactZoo{
    private:
        std::vector<void*> animal_arr;
        std::vector<typeAnimal> animal_type;

    public:
        ContactZoo(std::vector<void*> animal_arr, std::vector<typeAnimal> animal_type);
        ~ContactZoo();
    
    public:
        /**
         * @brief Проверяет животных, и если необходимо кормит их и отправляет отдыхать
         * 
         */
        void zooInspection();
        /**
         * @brief моделирует раоту зоопарка по заданному времени
         * 
         * @param time_life время в часах
         */
        void zooModelibg(int time_life);

    private:
        void seeModeling(std::map<int,int[2]> busy_aniimal, int time_now);

        bool wantPlayWithAnimal(int num_animal);
        bool needEat(int num_animal);
        bool needSleep(int num_animal);
        void eat(int num_animal);
        void eatWithCycle(int num_animal, int time_to_eat);
        void sleep(int num_animal);
        void playWithAnimal(int num_animal);
        void playWithHuman(int num_animal);

        std::string getName(int num_animal);
        int getAge(int num_animal);
        short getSatiety(int num_animal);
        short getFatigue(int num_animal);
        std::string getType(int num_animal);
        

};

ContactZoo::ContactZoo(std::vector<void*> animal_arr, std::vector<typeAnimal> animal_type){
    this->animal_arr = animal_arr;
    this->animal_type = animal_type;
}

ContactZoo::~ContactZoo(){}

void ContactZoo::zooInspection(){
    // перебираем всех животных в зоопарке
    for(int ani = 0; ani < (int)this->animal_arr.size(); ani++){
        // проверка на сытость и усталость
        bool i_wanna_eat = this->needEat(ani);
        if(i_wanna_eat){
            this->eat(ani);
            continue;
        }
        bool i_wanna_sleap = this->needSleep(ani);
        if(i_wanna_sleap){
            this->sleep(ani);
            continue;
        }
    }
}
void ContactZoo::zooModelibg(int time_life/*в часах*/){
    // для случайной генерации действий животных 
    std::srand(std::time(NULL));
    
    // полезые переменные
    int amount_animal = (int)this->animal_arr.size();

    // словарь занятости животных
    std::map<int,int[2]> busy_aniimal; // в значении будет хранится сколько часов еще животное занято, а если свободно то 0, на каждом шаге моделирования будет уменьшаться данное значение, при этом второе значение масива, будет соответсвовать действию enum
    // в самом начале все свободны
    for (int i = 0; i < amount_animal; i++){
        busy_aniimal[i][0] = 0;
        busy_aniimal[i][1] = (int)NOTHING;
    }
    
    // зоопарк работает 16 часов, и тут могут все взаимодействовать с друг дружкой, а потом 8 часов отдых в зоопарке 
    // шаг моделирования в 1 час
    for (int i = 0; i < time_life; i++){ 
        // 16 часов работы зоопарка
        //!!!!!!!!!!!!!
        if(i%24 < 16){
            // перебираем всех животных в зоопарке
            for(int ani = 0; ani < amount_animal; ani++){
                // проверка на сытость и усталость
                bool i_wanna_eat = this->needEat(ani);
                if(i_wanna_eat && busy_aniimal[ani][0] == 0){
                    this->eatWithCycle(ani, ((i%24) + DATE_SHIFT)); // допустим рабочии часы с 6 до 22, тогда сдвиг относительно 0 это 6
                    busy_aniimal[ani][0]++;
                    busy_aniimal[ani][1] = (int)EAT;
                    continue;
                }
                bool i_wanna_sleap = this->needSleep(ani);
                if(i_wanna_sleap && busy_aniimal[ani][0] == 0){
                    this->sleep(ani);
                    busy_aniimal[ani][0]++;
                    busy_aniimal[ani][1] = (int)SLEEP;
                    continue;
                }



                // если животное не занято оно может с какой-то вероятностью, провзаимодействовать с другим животным такого же типа или посетителем а если занято переходим к другому животному
                if(busy_aniimal[ani][0] != 0){
                    continue;
                }
                //Смотрим попадет вероятность того, что животное захочет поиграть с другим животным
                if(wantPlayWithAnimal(ani)){
                    //Проверяем на занятость других животных того же типа
                    for (int ani2 = ani+1; ani2 < amount_animal; ani2++){
                        if(
                            this->animal_type[ani] == this->animal_type[ani2] &&
                            busy_aniimal[ani2][0] == 0
                        ){
                            this->playWithAnimal(ani);
                            this->playWithAnimal(ani2);
                            busy_aniimal[ani][0]++;
                            busy_aniimal[ani][1] = (int)ANIMAL_PLAY;
                            busy_aniimal[ani2][0]++;
                            busy_aniimal[ani2][1] = (int)ANIMAL_PLAY;
                            break;
                        }
                    }
                }

                // опять же если животное не занято есть вероятность поиграть с посетителем
                if(busy_aniimal[ani][0] != 0){
                    continue;
                }
                // вероятность что люди захотят поиграть с этим животным (интенсивность людей и есть вероятность)
                double intensity_people = (double)(rand()%101)/100;
                double chance_activity = (double)(rand()%101)/100;
                if(chance_activity <= intensity_people){
                    playWithHuman(ani);
                    busy_aniimal[ani][0]++;
                    busy_aniimal[ani][1] = (int)HUMAN_PLAY;
                }
                    
                
                
            }
        }
        //8 часов не рабочих часов зоопарка
        else{
            // перебераем всех животных
            for(int ani = 0; ani < amount_animal; ani++){
                // если занято, то ничего делать другого не может
                if(busy_aniimal[ani][0] != 0){
                    continue;
                }
                // в противном случае спать надо ночью
                this->sleep(ani);
                busy_aniimal[ani][0]++;
                busy_aniimal[ani][1] = (int)SLEEP;
            }
        }

        // выводим все что происходит в зоопарке
        this->seeModeling(busy_aniimal,i);
        // как бы час проходит значит и все животные, которые были заняты этот час, его  отработали
        for (int ani = 0; ani < amount_animal; ani++){
            if(busy_aniimal[ani][0] > 0){
                busy_aniimal[ani][0]--;
            }
            if(busy_aniimal[ani][0] == 0){
                busy_aniimal[ani][1] = (int)NOTHING;
            }
        }
        
    }
    
}

void ContactZoo::seeModeling(std::map<int,int[2]> busy_aniimal, int time_now){
    // выводим время
    // не забываем сдвиг на 6 часов
    std::cout<<"time: "<< std::floor((time_now+DATE_SHIFT)/24) << " days, "<< (time_now+DATE_SHIFT)%24 << " hours\n";
    for(int ani = 0; ani < (int)this->animal_arr.size(); ani++){
        std::cout<<"\t"<<this->getType(ani)<< " \""
        <<this->getName(ani) <<" "<<this->getAge(ani)<<"y.o.\" \n\t\tsatienty = "
        <<this->getSatiety(ani)<<"\tfatigue = "<<this->getFatigue(ani)<<"\n\t\t busy: ";
        switch ((doing)busy_aniimal[ani][1])
        {
            case NOTHING:
                std::cout<<"not busy with anything";
                break;
            case SLEEP:
                std::cout<<"sleeping now";
                break;
            case EAT:
                std::cout<<"eating now";
                break;
            case ANIMAL_PLAY:
                std::cout<<"playing in an aviary with a friend animal";
                break;
            case HUMAN_PLAY:
                std::cout<<"playing with a visitor";
                break;
            default:
                break;
        }
        std::cout<<"\n";
    }

}


bool ContactZoo::needEat(int num_animal){
    switch (this->animal_type[num_animal]){
        case CAT:
            return ((Cat*)this->animal_arr[num_animal])->needEat();
        case DOG:
            return ((Dog*)this->animal_arr[num_animal])->needEat();
        case VOMBAT:
            return ((Vombat*)this->animal_arr[num_animal])->needEat();
        case RAT:
            return ((Rat*)this->animal_arr[num_animal])->needEat();
        default:
            return false;
    }
}
bool ContactZoo::needSleep(int num_animal){
    switch (this->animal_type[num_animal]){
        case CAT:
            return ((Cat*)this->animal_arr[num_animal])->needSleep();
        case DOG:
            return ((Dog*)this->animal_arr[num_animal])->needSleep();
        case VOMBAT:
            return ((Vombat*)this->animal_arr[num_animal])->needSleep();
        case RAT:
            return ((Rat*)this->animal_arr[num_animal])->needSleep();
        default:
            return false;
    }
}
bool ContactZoo::wantPlayWithAnimal(int num_animal){
    double rand_num = (double)(rand()%101);
    switch (this->animal_type[num_animal]){
        case CAT:
            return (rand_num/100 < CHANCE_TO_PLAY_CAT_WITH_CAT);
        case DOG:
            return (rand_num/100 < CHANCE_TO_PLAY_DOG_WITH_DOG);
        case VOMBAT:
            return (rand_num/100 < CHANCE_TO_PLAY_VOMBAT_WITH_VOMBAT);
        case RAT:
            return (rand_num/100 < CHANCE_TO_PLAY_RAT_WITH_RAT);
        default:
            return false;
    }
}
void ContactZoo::eat(int num_animal){
    switch (this->animal_type[num_animal]){
        case CAT:
            ((Cat*)this->animal_arr[num_animal])->eat();
            break;
        case DOG:
            ((Dog*)this->animal_arr[num_animal])->eat();
            break;
        case VOMBAT:
            ((Vombat*)this->animal_arr[num_animal])->eat();
            break;
        case RAT:
            ((Rat*)this->animal_arr[num_animal])->eat();
            break;
        default:
            break;
    }
    return;
}
void ContactZoo::eatWithCycle(int num_animal, int time_to_eat){
    switch (this->animal_type[num_animal]){
        case CAT:
            ((Cat*)this->animal_arr[num_animal])->eat(time_to_eat);
            break;
        case DOG:
            ((Dog*)this->animal_arr[num_animal])->eat(time_to_eat);
            break;
        case VOMBAT:
            ((Vombat*)this->animal_arr[num_animal])->eat(time_to_eat);
            break;
        case RAT:
            ((Rat*)this->animal_arr[num_animal])->eat(time_to_eat);
            break;
        default:
            break;
    }
    return;   
}
void ContactZoo::sleep(int num_animal){
    switch (this->animal_type[num_animal]){
        case CAT:
            ((Cat*)this->animal_arr[num_animal])->sleep();
            break;
        case DOG:
            ((Dog*)this->animal_arr[num_animal])->sleep();
            break;
        case VOMBAT:
            ((Vombat*)this->animal_arr[num_animal])->sleep();
            break;
        case RAT:
            ((Rat*)this->animal_arr[num_animal])->sleep();
            break;
        default:
            break;
    }
    return;
}
void ContactZoo::playWithAnimal(int num_animal){
    switch (this->animal_type[num_animal]){
        case CAT:
            ((Cat*)this->animal_arr[num_animal])->playWithAnimal();
            break;
        case DOG:
            ((Dog*)this->animal_arr[num_animal])->playWithAnimal();
            break;
        case VOMBAT:
            ((Vombat*)this->animal_arr[num_animal])->playWithAnimal();
            break;
        case RAT:
            ((Rat*)this->animal_arr[num_animal])->playWithAnimal();
            break;
        default:
            break;
    }
    return;
}
void ContactZoo::playWithHuman(int num_animal){
    switch (this->animal_type[num_animal]){
        case CAT:
            ((Cat*)this->animal_arr[num_animal])->play();
            break;
        case DOG:
            ((Dog*)this->animal_arr[num_animal])->play();
            break;
        case VOMBAT:
            ((Vombat*)this->animal_arr[num_animal])->play();
            break;
        case RAT:
            ((Rat*)this->animal_arr[num_animal])->play();
            break;
        default:
            break;
    }
    return;
}
std::string ContactZoo::getName(int num_animal){
    switch (this->animal_type[num_animal]){
        case CAT:
            return ((Cat*)this->animal_arr[num_animal])->getName();
        case DOG:
            return ((Dog*)this->animal_arr[num_animal])->getName();
        case VOMBAT:
            return ((Vombat*)this->animal_arr[num_animal])->getName();
        case RAT:
            return ((Rat*)this->animal_arr[num_animal])->getName();
        default:
            return "";
    }
}
int ContactZoo::getAge(int num_animal){
    switch (this->animal_type[num_animal]){
        case CAT:
            return ((Cat*)this->animal_arr[num_animal])->getAge();
        case DOG:
            return ((Dog*)this->animal_arr[num_animal])->getAge();
        case VOMBAT:
            return ((Vombat*)this->animal_arr[num_animal])->getAge();
        case RAT:
            return ((Rat*)this->animal_arr[num_animal])->getAge();
        default:
            return 0;
    }
}
short ContactZoo::getSatiety(int num_animal){
    switch (this->animal_type[num_animal]){
        case CAT:
            return ((Cat*)this->animal_arr[num_animal])->getSatiety();
        case DOG:
            return ((Dog*)this->animal_arr[num_animal])->getSatiety();
        case VOMBAT:
            return ((Vombat*)this->animal_arr[num_animal])->getSatiety();
        case RAT:
            return ((Rat*)this->animal_arr[num_animal])->getSatiety();
        default:
            return 0;
    }
}
short ContactZoo::getFatigue(int num_animal){
    switch (this->animal_type[num_animal]){
        case CAT:
            return ((Cat*)this->animal_arr[num_animal])->getFatigue();
        case DOG:
            return ((Dog*)this->animal_arr[num_animal])->getFatigue();
        case VOMBAT:
            return ((Vombat*)this->animal_arr[num_animal])->getFatigue();
        case RAT:
            return ((Rat*)this->animal_arr[num_animal])->getFatigue();
        default:
            return 0;
    }    
}
std::string ContactZoo::getType(int num_animal){
    switch (this->animal_type[num_animal]){
        case CAT:
            return (std::string)"Cat   ";
        case DOG:
            return (std::string)"Dog   ";
        case VOMBAT:
            return (std::string)"Vombat";
        case RAT:
            return (std::string)"Rat   ";
        default:
            return (std::string)"      ";
    }   
}

