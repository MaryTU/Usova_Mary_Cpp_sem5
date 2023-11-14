#include "include/my_queue.h"

#include <iostream>

int main()
{
    MyQueue<int> md;
    std::cout<<"is empty: "<<md.isEmpty()<<std::endl;
    std::cout<<"Size = "<<md.getSize()<<std::endl;
    std::cout<<"First element = "<<md.getFirst()<<std::endl;

    std::cout<<"\nadd 5"<<std::endl;
    md.pushBack(5);
    std::cout<<"is empty: "<<md.isEmpty()<<std::endl;
    std::cout<<"Size = "<<md.getSize()<<std::endl;
    std::cout<<"First element = "<<md.getFirst()<<std::endl;

    std::cout<<"\nadd 6"<<std::endl;
    md.pushBack(6);
    std::cout<<"is empty: "<<md.isEmpty()<<std::endl;
    std::cout<<"Size = "<<md.getSize()<<std::endl;
    std::cout<<"First element = "<<md.getFirst()<<std::endl;
    
    // std::cout<<"\ndelete first"<<std::endl;
    // md.popFirst();
    // std::cout<<"is empty: "<<md.isEmpty()<<std::endl;
    // std::cout<<"Size = "<<md.getSize()<<std::endl;
    // std::cout<<"First element = "<<md.getFirst()<<std::endl;

    // std::cout<<"\ndelete first"<<std::endl;
    // md.popFirst();
    // std::cout<<"is empty: "<<md.isEmpty()<<std::endl;
    // std::cout<<"Size = "<<md.getSize()<<std::endl;
    // std::cout<<"First element = "<<md.getFirst()<<std::endl;


    //int a[] = {1,2,3,4,5};
    for (auto aa:md){
        std::cout<<aa<<"hey ";
    }
    

    return 0;
}
