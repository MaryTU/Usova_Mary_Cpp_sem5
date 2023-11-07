#include <string>
#include <map>
#include <ctime>
#include <vector>
#include <iostream>


enum Genres{
    DETECTIVE, 
    ROMANCE, 
    FANTASY, 
    SCIENCE_FICTION,
};
const int AMOUNT_GENRES = 4;

static bool need_random_book = true; // для не повторяющейся случайной генерации для каждого экземпляра
const int MAX_PAGES_IN_BOOK = 1000;
const int MIN_PAGES_IN_BOOK = 25;

const std::vector<short> AGE_RESTRICTION = {0,6,12,18};


class Book{
    private:
        std::string name, author;
        int quantity_of_pages;
        short age_restrictions;
        std::map<int,short> score; // id reader, raiting
        std::vector<Genres> genre;

    public:
        Book(
            std::string name, std::string author,
            int quantity_of_pages, short age_restrictions,
            std::map<int,short> score, std::vector<Genres> genre);
        Book();
        ~Book();

    public:
        /**
         * @brief Показывает всю информацию о книге
         * 
         */
        void viewBookInfo();
        /**
         * @brief Get the Avarage Rate
         * 
         * @return double Rate
         */
        double getAvarageRate();

    public:
        std::vector<Genres> getGenre(){return this->genre;}
        std::string getName(){return this->name;}
        std::string getAuthor(){return this->author;}
        int getQuantityOfPages(){return this->quantity_of_pages;}
        short getAgeRestrictions(){return this->age_restrictions;}
        std::map<int,short> getScore(){return this->score;}

        void setScore(int id_visiter, int rate){this->score[id_visiter] = rate; return;}

};

Book::Book(){
    if(need_random_book) std::srand(std::time(NULL));
    need_random_book = false;

    int amount_name_book = 20;
    std::string name_book[]{
        "The Silent Echo","Echoes of Eternity","Whispers in the Wind",
        "The Secret Garden", "Lost and Found", "The Enchanted Forest", "Under the Moonlight",
        "The Forgotten Dreams", "A Tale of Two Worlds", "Shadows of the Past", "The Midnight Serenade",
        "The Crimson Rose", "The Hidden Path", "Mysteries of the Deep", "The Enigma Chronicles",
        "Hearts in Harmony", "A Symphony of Stars", "The Labyrinth of Time", 
        "The Whispers of Destiny", "Sands of Serenity"
    };
    int amount_name_author = 20;
    std::string name_author[]{
        "John Smith", "Emily Johnson", "Michael Brown", "Jennifer Davis", "David Wilson", "Sarah Lee", "James Anderson", "Jessica Taylor", "Robert Moore", "Olivia White", "William Clark", "Sophia Martinez", "Daniel Turner", "Emma Evans", "Joseph Harris", "Ava Lewis", "Matthew King", "Grace Scott", "Andrew Perez", "Chloe Robinson"
    };

    this->name = name_book[rand()%amount_name_book];
    this->author = name_author[rand()%amount_name_author];
    this->quantity_of_pages = rand()%(MAX_PAGES_IN_BOOK + 1 - MIN_PAGES_IN_BOOK) + MIN_PAGES_IN_BOOK;
    this->age_restrictions = AGE_RESTRICTION[rand()%AGE_RESTRICTION.size()];
    
    std::map<int,short> a;
    this->score = a;

    int amount_g = rand()%AMOUNT_GENRES + 1;
    std::vector<Genres> result_genre;
    for (int i = 0; i < amount_g; i++){
        Genres g = (Genres)(rand()%AMOUNT_GENRES);

        bool we_find = false;
        while (!we_find){
            for(Genres gg: result_genre){
                if (gg == g){
                    g = (Genres)(((int)g + 1)%AMOUNT_GENRES);
                    we_find = false;
                    break;
                }
                we_find = true;
            }  
            if(result_genre.size() == 0) we_find = true;
        }
        result_genre.push_back(g);
    }
    this->genre = result_genre;
}
Book::Book(
    std::string name, std::string author,
    int quantity_of_pages, short age_restrictions,
    std::map<int,short> score, std::vector<Genres> genre
    ){
        if(need_random_book) std::srand(std::time(NULL));
        need_random_book = false;

        this->name = name;
        this->author = author;
        this->quantity_of_pages = quantity_of_pages;
        this->age_restrictions = age_restrictions;
        this->score = score;
        this->genre = genre;
}
Book::~Book(){}


void Book::viewBookInfo(){
    std::cout<<"Book: \""<<this->name<<"\" "<<this->author<<", "<<this->quantity_of_pages<<"pages, \n";
    std::cout<<"\t Age restrictions: "<<this->age_restrictions<<"\n";
    std::cout<<"\t Geners: ";
    for(Genres g: this->genre){
        if(g == DETECTIVE) std::cout<<"detective, ";
        else if(g == ROMANCE) std::cout<<"romance, ";
        else if(g == FANTASY) std::cout<<"fantasy, ";
        else if(g == SCIENCE_FICTION) std::cout<<"science fiction, ";
    }
    std::cout<<"\n";

}
double Book::getAvarageRate(){
    double avarage_rate = 0;
    for(auto rate: this->score) avarage_rate += rate.second;
    avarage_rate /= (double)this->score.size();
    return avarage_rate;
    //std::cout<<avarage_rate<<"\n";
}
