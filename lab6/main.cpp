#include "include/class_target.h"
#include "include/class_weapon.h"
#include "include/class_shooting_range.h"

#include "include/target/AppearDisappearTarget.h"
#include "include/target/MoveForwardBackwardTarget.h"
#include "include/target/MoveRightLeftTarget.h"

#include <vector>
#include <ctime>

int main()
{
    std::srand(std::time(NULL));

    int max_targets = 15;

    int 
        amount_target_1 = rand()%(max_targets) + 1,
        amount_target_2 = rand()%(max_targets) + 1,
        amount_target_3 = rand()%(max_targets) + 1;

    std::vector<AppearDisappearTarget*> targets_1;
    std::vector<MoveForwardBackwardTarget*> targets_2;
    std::vector<MoveRightLeftTarget*> targets_3;

    std::vector<Target*> all_target;

    for (int i = 0; i < amount_target_1; i++){
        targets_1.push_back(new AppearDisappearTarget());
        all_target.push_back(targets_1[i]);
    }
    for (int i = 0; i < amount_target_2; i++){
        targets_2.push_back(new MoveForwardBackwardTarget());
        all_target.push_back(targets_2[i]);
    }
    for (int i = 0; i < amount_target_3; i++){
        targets_3.push_back(new MoveRightLeftTarget());
        all_target.push_back(targets_3[i]);
    }

    // for(auto a:all_target){
    //     a->view_data();
    // }

    Weapon weapon;

    ShootingRange tir(weapon, all_target);
    tir.modelingShootingRange(60);
    
    return 0;
}
