// #include <iostream>
// #include <string>
// #include <map>
// #include <ctime>
#include <vector>

#include "include/class_book.h"
#include "include/class_visiter.h"
#include "include/class_library.h"



int main()
{
    //std::srand(std::time(NULL));
    //Visiter v1(18,DETECTIVE,BIG,80);
    // std::map<int,short> aaa;
    // Book b1("Hey","Norman",111,18, aaa, {DETECTIVE,FANTASY});
    // std::vector<Book> my_library;
    // for (int i = 0; i < 15; i++) my_library.push_back(Book());
    // for(Book book:my_library) book.viewBookInfo();
    
    std::vector<Visiter> wormes;
    for (int i = 0; i < 15; i++) wormes.push_back(Visiter());
    for(Visiter v: wormes) v.viewViseter();

    // std::queue<int> a;
    // a.push(1);
    // a.push(2);
    // a.push(3);
    // for (int i = 0; i < (int)a.size(); i++){
    //     std::cout<<a.front()<<"\n";
    //     a.push(a.front());
    //     a.pop();
    // }

    Library l;
    l.modelingLibrary(wormes, 10);
    

    return 0;
}
