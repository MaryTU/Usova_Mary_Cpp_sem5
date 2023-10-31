#include <vector>
#include <cmath>
#include <iostream>
#include <thread>
#include <chrono>

const double CHANCE_CHANGE_TYPE_SHOOTING = 0.44;

class ShootingRange
{
    private:
        Weapon weapon;
        std::vector<Target*> targets;

    public:
        ShootingRange(Weapon weapon, std::vector<Target*> targets);
        ~ShootingRange();

    public:
        void modelingShootingRange(int time_sec);
};

ShootingRange::ShootingRange(Weapon weapon, std::vector<Target*> targets){
    this->weapon = weapon;
    this->targets = targets;
}
ShootingRange::~ShootingRange(){}

void ShootingRange::modelingShootingRange(int time_sec){
    int all_damageses = 0;
    std::srand(std::time(NULL));

    for (int i = 0; i < time_sec; i++){
        std::cout << i+1 << " second\n";

        // проверка, нужно ли перезарядить магазин
        if(this->weapon.isEmptyMagazin()){
            this->weapon.recharge();
            std::cout<<"\tRecharge\n";
            continue; // перезарядка будет занимать 1 секунду
        }

        // шанс изменить режим стрельбы
        double chance_change_type_shooting = (double)(rand()%(101))/100;
        if(chance_change_type_shooting <= CHANCE_CHANGE_TYPE_SHOOTING){
            this->weapon.changeFiringMode();
            std::cout<<"\tChange mod\n";
        }

        // попытка выстрела
        bool isShoot = false;
        while (!isShoot){
            //случайно выбираем цель
            int num_target = rand()%this->targets.size();

            // проверяем не сломана ли цель
            if(!targets[num_target]->isAvailable()){
                // если сломана переходим к следущей, и так перебираем все, пока не найдем целую
                bool all_element_broken = false;
                for (int j = 0; j < (int)this->targets.size(); j++){
                    num_target = (num_target + 1)%this->targets.size(); 

                    if (targets[num_target]->isAvailable()){
                        all_element_broken = false;
                        break;
                    } 
                    // если целых нет, указываем что все элементы сломаны
                    all_element_broken = true;                  
                } 
                // и если все элементы сломаны, нам больше не по чему стрелять
                if(all_element_broken){
                    isShoot = true;
                    std::cout<<"\tall target broken\n";
                    continue;
                }
                //continue;
            }
            
            // если цель найдена
            isShoot = true;
            double a = this->weapon.getChance(); // считаем шанс попадания оружия
            double b = this->targets[num_target]->getChanceHitTarget(i+1); // считаем шанс попадения в мишень 
            if(a > b){
                int damage = this->weapon.shoot(1);
                this->targets[num_target]->getDamage(damage);
                all_damageses += damage; //для получения среднего урона
                std::cout << "\tTarget num." << num_target << " get damage: " << damage << "\n";
                if (!this->targets[num_target]->isAvailable()){
                    std::cout << "\tTarget num." << num_target << " is broken\n";
                }

            }else{
                std::cout << "\t Lose shoot to target num." << num_target << "\n";
            }
        }
        // делаем задержку, что бы видеть результаты, и что бы рандом был более рандомистый
        std::this_thread::sleep_for(std::chrono::milliseconds(444));
    }

    // считаем не разрушенные мишени
    int live_targets = 0;
    for(auto a:targets){
        if(a->isAvailable()){
            live_targets++;
        }
    }
    std::cout<<"Unresolved targets: "<<live_targets<<"\n";
    std::cout<<"Resolved targets: "<<this->targets.size() - live_targets<<"\n";
    std::cout<<"Avarage damage: "<<all_damageses/time_sec<<"\n";


    return;
    
}

