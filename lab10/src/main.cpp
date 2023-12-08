#include <iostream>
#include <exception>

#include "include/field/field.h"
#include "include/bot/bot.h"
#include "include/modes/modes.h"

void genTwoPlayer(Field &p1, Field &p2, bool gen_first);


static bool norm_num;


int main()
{
    return 0;

    // Предоставляем выбор играть против человека, или против робота
    std::cout<<"1 play with human\n2 play with robot\nYour choise: ";
    int choise_rezhim = 0;
    std::cin>>choise_rezhim;

    // Предоставляет выбор самому задать поле или сгенерировать автоматически
    std::cout<<"1 generate field\n2 create field\nYour choise: ";
    int choise_rezhim2 = 0;
    std::cin>>choise_rezhim2;

    norm_num = false;
    while(!norm_num){ 


        // считываем количество кораблей
        std::cout<<"Enter the number of ships(min 10): ";
        int n = 0;
        std::cin >> n;

        // проверка на то что бы кораблей было не меньше 10
        if(n >= 10){ norm_num = true; }
        else{std::cout<<"invalid arguments try again\n";continue;}
             
        // Создаем два поля/два игрока
        Field p1(n);
        Field p2(n);

        if(choise_rezhim2 == 1){ genTwoPlayer(p1,p2,true); }
        else if(choise_rezhim2 == 2){ genTwoPlayer(p1,p2,false); }
        
        if(!norm_num) continue;
        
        if(choise_rezhim == 1){ playPVPGen(p1,p2);}
        else if(choise_rezhim == 2){ playWithRobot(p1,p2); }


        // p1.fieldGeneration();

        // p1.viewFieldWithShips();
        


        // p1.viewPlayingField();

        // for (int i = 0; i < 40; i++){
        //     bot_move(p1);

        //     p1.viewPlayingField();
        // }
        

        //p1.manualLocation();

        //playPVPGen(p1,p2);
    }

    return 0;
}



void genTwoPlayer(Field &p1, Field &p2, bool gen_first){
    bool bad_generate = true; 
    int amount_generate = 0;
    // цикл пока не сгенерируются поля
    while(bad_generate){
        try {
            bad_generate = false;
            amount_generate++;
            // Если за 100 попыток не удалось сгенерировать поле
            if(amount_generate>100){
                std::cout<<"Field generation error, try changing the number of ships\n";
                norm_num = false;
                break;
            }

            // Генерируем 2 поля с кораблями
            if(gen_first){p1.fieldGeneration();}
            else{p1.manualLocation();}
            //p1.fieldGeneration();
            p2.fieldGeneration();
        
        } catch(const SomethingWrong& e) {
            //std::cerr << "Exeption: " << e.what() << '\n';
            // если не удалось сгенерировать поле
            bad_generate = true;
            continue;
        } catch(const std::invalid_argument& e) {
            // проверка что бы кораблей не было слишком много
            std::cerr << "Exeption: " << e.what() << '\n';
            std::cout<< "Try again\n";
            norm_num = false;
            return;
        }
    } 
}

