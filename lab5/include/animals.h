#include <iostream>
#include <string>
#include <vector>


class Animals{
    protected:    
        std::string name;
        int age;
        short satiety = 100, fatigue = 0;
        
    public:
        /**
         * @brief Construct a new Animals object
         * 
         */
        Animals();
        /**
         * @brief Destroy the Animals object
         * 
         */
        ~Animals();

    public:
        /**
         * @brief animal play
         * 
         */
        void play();
        /**
         * @brief animal sleep
         * 
         */
        void sleep();
        /**
         * @brief animal eat
         * 
         */
        void eat();
        /**
         * @brief need animal eat
         * 
         * @return true yes it need
         * @return false no it doesn't
         */
        bool needEat();
        /**
         * @brief animal need sleeo or not
         * 
         * @return true yes it need
         * @return false no it didn't
         */
        bool needSleep();

        /**
         * @brief Get the Name object
         * 
         * @return std::string name
         */
        std::string getName();
        /**
         * @brief Get the Age object
         * 
         * @return int age
         */
        int getAge();
        /**
         * @brief Get the Satiety object
         * 
         * @return short satiety
         */
        short getSatiety();
        /**
         * @brief Get the Fatigue object
         * 
         * @return short Fatigue
         */
        short getFatigue();
};


Animals::Animals(){}

Animals::~Animals(){}

void Animals::play(){}
void Animals::sleep(){}
void Animals::eat(){ // наследуется всеми животными без изменений
    this->satiety = 100;
    return;
}
bool Animals::needEat(){ // наследуется всеми животными без изменений
    return (this->satiety < 50);
}
bool Animals::needSleep(){ // наследуется всеми животными без изменений
     return (this->fatigue > 80);
}

std::string Animals::getName(){
    return this->name;
}
int Animals::getAge(){
    return this->age;
}
short Animals::getSatiety(){
    return this->satiety;
}
short Animals::getFatigue(){
    return this->fatigue;
}