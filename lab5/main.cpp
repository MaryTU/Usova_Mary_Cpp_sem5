#include "include/animals.h"
#include "include/animals/class_cat.h"
#include "include/animals/class_dog.h"
#include "include/animals/class_vombat.h"
#include "include/animals/class_rat.h"
#include "include/contact_zoo.h"
// #include <iostream>
// #include <vector>

int main()
{
    Cat c1("Boris",2);
    Cat c2("Leon", 5);
    Cat c3("Markiz", 8);

    Dog d1("Sharik", 1);
    Dog d2("Bear", 10);

    Vombat v1("Grizha", 2);
    Vombat v2("Leha", 2);

    Rat r1("Jerry", 1);
    Rat r2("Melisa", 2);
    Rat r3("Garry", 3);

    std::vector<void*> a = {&c1,&c2,&c3,&d1,&d2,&v1,&v2,&r1,&r2,&r3};
    std::vector<typeAnimal> b = {CAT,CAT,CAT,DOG,DOG,VOMBAT,VOMBAT,RAT,RAT,RAT};

    ContactZoo cz(a,b);
    cz.zooModelibg(30*24); // месяц в часах


    return 0;
}
