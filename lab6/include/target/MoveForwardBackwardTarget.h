#include <ctime>
#include <cmath>
#include <iostream>

class MoveForwardBackwardTarget: public Target{
    private:
        int speed_of_approach_distance;

        /*
        // для разного порога попаданий
        const double survivability_coefficient = 0.85;
        */
    public:
        MoveForwardBackwardTarget();
        ~MoveForwardBackwardTarget();

        double getChanceHitTarget(int time_from_start); 
        void getDamage(int damage);
        bool isAvailable();

        void view_data();

};

MoveForwardBackwardTarget::MoveForwardBackwardTarget(){
    //std::srand(std::time(NULL));
    this->health_point = rand()%((int)MAX_HEALTH + 1 - (int)MIN_HEALTH) + MIN_HEALTH; 
    this->distance_to_target = rand()%((int)MAX_DISTANCE + 1);
    this->form_factor = (FormFactor)(rand()%AMOUNT_TYPE_FORM);
    this->material = (Material)(rand()%AMOUNT_TYPE_MATERIAL);
    this->size_target = rand()%((int)MAX_AREA + 1) + MIN_AREA;
    this->available = true;

    this->speed_of_approach_distance = rand()%((int)MAX_SPEED + 1 - (int)MIN_SPEED) + MIN_SPEED;

    // изначально дистанция такая как прописано, но в получении шанса попадания изменится
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
MoveForwardBackwardTarget::~MoveForwardBackwardTarget(){}

double MoveForwardBackwardTarget::getChanceHitTarget(int time_from_start){
    int all_distance = time_from_start*this->speed_of_approach_distance;
    int distance_now;
    if(((int)std::floor(this->distance_to_target/all_distance))%2 == 0){
        distance_now = this->distance_to_target % all_distance;
    }
    else{
        distance_now = this->distance_to_target - (this->distance_to_target % all_distance);
    }
    this->hit_chance = 0.5 - 0.5*distance_now/MAX_DISTANCE + 0.5*this->size_target/MAX_AREA;
    if (this->hit_chance<=0){
        this->hit_chance = 0.1;
    }
    return this->hit_chance;
}
void MoveForwardBackwardTarget::getDamage(int damage){
    this->health_point -= damage;
    if (this->health_point <= 0){
        this->available = false;
    }
    return;
}

bool MoveForwardBackwardTarget::isAvailable(){
    return this->available;
}

void MoveForwardBackwardTarget::view_data(){
    std::cout<<"\nMoveForwardBackwardTarget"
        <<"\n\tdistance = "<<this->distance_to_target
        <<"\n\thp = "<<this->health_point
        <<"\n\tsize = "<<this->size_target
        <<"\n\tchance = "<<this->hit_chance
        <<"\n\tmaterial = "<<this->material;
}

