#include "include/my_queue.h"

#include <iostream>
#include <ctime>

int main()
{
    std::srand(std::time(NULL));

    int n = rand()%50 + 10; 

    MyQueue<int> queue_int;

    std::cout<<"is empty: "<<queue_int.isEmpty()<<"\n";
    //std::cout<<"First element = "<<queue_int.getFirst()<<"\t";

    for (int i = 0; i < n; i++){
        int rand_value = rand();

        std::cout<<"\nadd "<<rand_value<<std::endl;
        queue_int.pushBack(rand_value);

        std::cout<<"is empty: "<<queue_int.isEmpty()<<"\t";
        std::cout<<"Size = "<<queue_int.getSize()<<"\t";

        if(queue_int.getSize()){
            std::cout<<"First element = "<<queue_int.getFirst()<<"\t";
            if(rand()%2){
                std::cout<<"delete first element\t";
                queue_int.popFirst();
            }
        }
        
        std::cout<<std::endl<<"all element queue: ";
        for (auto q1:queue_int){
            std::cout<<q1<<", ";
        }

        std::cout<<"\n";
    }



    MyQueue<char> queue_char;
    char en_symb[] = {"qwertyuiopasdfghjklzxcvbnm"};
    std::cout<<"is empty: "<<queue_char.isEmpty()<<"\n";
    for (int i = 0; i < n; i++){
        int rand_value = rand()%26;

        std::cout<<"\nadd "<<rand_value<<std::endl;
        queue_char.pushBack(en_symb[rand_value]);

        std::cout<<"is empty: "<<queue_char.isEmpty()<<"\t";
        std::cout<<"Size = "<<queue_char.getSize()<<"\t";

        if(queue_char.getSize()){
            std::cout<<"First element = "<<queue_char.getFirst()<<"\t";
            if(rand()%2){
                std::cout<<"delete first element\t";
                queue_char.popFirst();
            }
        }
        
        std::cout<<std::endl<<"all element queue: ";
        for (auto q1:queue_char){
            std::cout<<q1<<", ";
        }

        std::cout<<"\n";
    }

    // std::cout<<std::endl<<"all element queue: ";
    // for (auto q1:queue_int){
    //     std::cout<<q1<<", ";
    // }

    return 0;
}
