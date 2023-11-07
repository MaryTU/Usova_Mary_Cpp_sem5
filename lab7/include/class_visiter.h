#include <vector>
#include <ctime>
#include <iostream>
#include <cmath>

// перечесление(enum) Genres находится в файле class_book.h 

enum VolumePreferences{
    BIG,
    MEDIUM,
    SMALL,
    ANY,
};
const int AMOUT_VOLUME_PREFERENCES = 4;

static bool need_random_visiter = true;
const int MAX_AGE = 100;
const int MIN_AGE = 5;
const int MAX_READ_SPEED = 150;
const int MIN_READ_SPEED = 20;

class Visiter{
    private:
        int age;
        Genres favorite_genres;
        VolumePreferences volume_preferences; 
        int reading_speed; // стр в час

    public:
        Visiter();
        Visiter(int age, Genres favorite_genres, VolumePreferences volume_preferences, int reading_speed);
        ~Visiter();
    
    public:
        /**
         * @brief Генерирует какие предпочтения в книгах сейчас у посетителя
         * 
         */
        void nowIWant();
        /**
         * @brief Отображает все данные о посетителе
         * 
         */
        void viewViseter();
        /**
         * @brief Считает сколько времени посетитель читает книгу
         * 
         * @param pages_book - сколько страниц в книге
         * @return время чтениях в минутах
         */
        int readBook(int pages_book); // время чтения книги возвращаем в минутах

    public:
        int getAge(){return this->age;}
        Genres getFavoriteGenres(){return this->favorite_genres;}
        VolumePreferences getVolumePreferences(){return this->volume_preferences;} 


};

Visiter::Visiter(){
    if(need_random_visiter) std::srand(time(NULL));
    need_random_visiter = false;

    this->age = rand()%(MAX_AGE + 1 - MIN_AGE) + MIN_AGE;
    this->volume_preferences = (VolumePreferences)(rand()%AMOUT_VOLUME_PREFERENCES);
    this->reading_speed = rand()%(MAX_READ_SPEED + 1 - MIN_READ_SPEED) + MIN_READ_SPEED;
    this->favorite_genres = (Genres)(rand()%AMOUNT_GENRES);

    
}
Visiter::Visiter(int age, Genres favorite_genres, VolumePreferences volume_preferences, int reading_speed){
    if(need_random_visiter) std::srand(time(NULL));
    need_random_visiter = false;

    this-> age =  age;
    this-> favorite_genres = favorite_genres;
    this-> volume_preferences = volume_preferences; 
    this->reading_speed = reading_speed;
}
Visiter::~Visiter(){}


void Visiter::nowIWant(){
    this->volume_preferences = (VolumePreferences)(rand()%AMOUT_VOLUME_PREFERENCES);
    this->favorite_genres = (Genres)(rand()%AMOUNT_GENRES);
}

void Visiter::viewViseter(){
    std::cout<<"Visiter: Age = "<<this->age<<", speed reading = "<<this->reading_speed
        <<"\n\t favorit ganre: ";
    if(this->favorite_genres == DETECTIVE) std::cout<<"DETECTIVE";
    else if(this->favorite_genres == ROMANCE) std::cout<<"ROMANCE";
    else if(this->favorite_genres == FANTASY) std::cout<<"FANTASY";
    else if(this->favorite_genres == SCIENCE_FICTION) std::cout<<"SCIENCE FICTION";
    else std::cout<<"wtf";
    
    std::cout<<", VolumePreferences: ";
    if(this->volume_preferences == BIG) std::cout<<"BIG";
    else if(this->volume_preferences == MEDIUM) std::cout<<"MEDIUM";
    else if(this->volume_preferences == SMALL) std::cout<<"SMALL";
    else if(this->volume_preferences == ANY) std::cout<<"ANY";
    else std::cout<<"wtf";

    std::cout<<std::endl;
    
}

int Visiter::readBook(int pages_book){
    return (int)std::round((double)pages_book*60/(double)(this->reading_speed));
}

