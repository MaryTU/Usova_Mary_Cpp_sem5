#include <ctime>
#include <iostream>

class AppearDisappearTarget: public Target{
    private:
        int time_of_appearance; //per sec, время показывания/появления мишени
        int time_of_disappearance; //per sec, время непоказывания/исчезновения мишени
    
        /*
        // для разного порога попаданий
        const double survivability_coefficient = 0.75;
        */
    public:
        AppearDisappearTarget();
        ~AppearDisappearTarget();

        double getChanceHitTarget(int time_from_start); 
        void getDamage(int damage);
        bool isAvailable();

        void view_data();
};

AppearDisappearTarget::AppearDisappearTarget(){
    //std::srand(std::time(NULL));
    this->health_point = rand()%((int)MAX_HEALTH + 1 - (int)MIN_HEALTH) + MIN_HEALTH; 
    this->distance_to_target = rand()%((int)MAX_DISTANCE + 1);
    this->form_factor = (FormFactor)(rand()%AMOUNT_TYPE_FORM);
    this->material = (Material)(rand()%AMOUNT_TYPE_MATERIAL);
    this->size_target = rand()%((int)MAX_AREA + 1) + MIN_AREA;
    this->available = true;

    this->time_of_appearance = rand()%(MAX_TIME + 1 - MIN_TIME) + MIN_TIME;
    this->time_of_disappearance = rand()%(MAX_TIME + 1 - MIN_TIME) + MIN_TIME;

    // изначально мишень есть, но в шансе уменьшается
    if(this->material == BLICK){
        this->hit_chance = 0.5 - 0.5*this->distance_to_target/MAX_DISTANCE + 0.5*this->size_target/MAX_AREA - REDUCING_CHANCE_OF_BLICK;
    }
    else{
        this->hit_chance = 0.5 - 0.5*this->distance_to_target/MAX_DISTANCE + 0.5*this->size_target/MAX_AREA;
    }
    if (this->hit_chance<=0){
        this->hit_chance = 0.1;
    }
}
AppearDisappearTarget::~AppearDisappearTarget(){}

double AppearDisappearTarget::getChanceHitTarget(int time_from_start){
    int left_time = time_from_start % (this->time_of_appearance + this->time_of_disappearance);
    // сначала у нас поднята мишень
    if(left_time <= this->time_of_appearance){
        return this->hit_chance;
    }
    else{
        return 0;
    }
}
void AppearDisappearTarget::getDamage(int damage){
    this->health_point -= damage;
    if (this->health_point <= 0){
        this->available = false;
    }
    return;
}

bool AppearDisappearTarget::isAvailable(){
    return this->available;
}

void AppearDisappearTarget::view_data(){
    std::cout<<"\nAppearDisappearTarget"
        <<"\n\tdistance = "<<this->distance_to_target
        <<"\n\thp = "<<this->health_point
        <<"\n\tsize = "<<this->size_target
        <<"\n\tchance = "<<this->hit_chance
        <<"\n\tmaterial = "<<this->material;
}
