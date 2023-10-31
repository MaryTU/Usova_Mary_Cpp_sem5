#include <ctime>
#include <iostream>

class MoveRightLeftTarget: public Target{
    private:
        int horizontal_speed;

        /*
        // для разного порога попаданий
        const double survivability_coefficient = 0.5;
        */
    public:
        MoveRightLeftTarget();
        ~MoveRightLeftTarget();

        double getChanceHitTarget(int time_from_start); 
        void getDamage(int damage);
        bool isAvailable();

        void view_data();

};

MoveRightLeftTarget::MoveRightLeftTarget(){
    //std::srand(std::time(NULL));
    this->health_point = rand()%((int)MAX_HEALTH + 1 - (int)MIN_HEALTH) + MIN_HEALTH; 
    this->distance_to_target = rand()%((int)MAX_DISTANCE + 1);
    this->form_factor = (FormFactor)(rand()%AMOUNT_TYPE_FORM);
    this->material = (Material)(rand()%AMOUNT_TYPE_MATERIAL);
    this->size_target = rand()%((int)MAX_AREA + 1) + MIN_AREA;
    this->available = true;

    this->horizontal_speed = rand()%((int)MAX_SPEED + 1 - (int)MIN_SPEED) + MIN_SPEED;

    double uniqe_haracteristic = RIGHT_LEFT_MOVING_REDUCING_CHANCE*horizontal_speed/MAX_SPEED;
    if(this->material == BLICK){
        this->hit_chance = 0.5 - 0.5*this->distance_to_target/MAX_DISTANCE + 0.5*this->size_target/MAX_AREA - uniqe_haracteristic - REDUCING_CHANCE_OF_BLICK;
    }
    else{
        this->hit_chance = 0.5 - 0.5*this->distance_to_target/MAX_DISTANCE + 0.5*this->size_target/MAX_AREA - uniqe_haracteristic;
    }
    if (this->hit_chance<=0){
        this->hit_chance = 0.1;
    }
    
}
MoveRightLeftTarget::~MoveRightLeftTarget(){}

double MoveRightLeftTarget::getChanceHitTarget(int time_from_start){
    return this->hit_chance;
}
void MoveRightLeftTarget::getDamage(int damage){
    this->health_point -= damage;
    if (this->health_point <= 0){
        this->available = false;
    }
    return;
}

bool MoveRightLeftTarget::isAvailable(){
    return this->available;
}

void MoveRightLeftTarget::view_data(){
    std::cout<<"\nMoveRightLeftTarget"
        <<"\n\tdistance = "<<this->distance_to_target
        <<"\n\thp = "<<this->health_point
        <<"\n\tsize = "<<this->size_target
        <<"\n\tchance = "<<this->hit_chance
        <<"\n\tmaterial = "<<this->material;
}
