#include <string>
#include <fstream>
#include <iostream>

#include "../lib/nlohmann/json.hpp"

class User{
    private:
        std::string name, surname, patronymic;
        int age;
        std::string login;
        std::string password;

        bool activity; // true - активный, false - не активный
        
    public:
        User(){};
        User(std::string name,std::string surname,std::string patronymic, int age, bool activity);
        ~User(){};

    private:
        void getLogin();

    public:
        // getters
        int getAge(){return this->age;}
        bool getActivity(){return this->activity;}
        std::string getMyLogin(){return this->login;}
        std::string getName(){return this->name;}
        std::string getSurname(){return this->surname;}
        std::string getPatronymic(){return this->patronymic;}

    public:
        friend std::ostream& operator<<(std::ostream& os, const User& obj);
};

User::User(std::string name, std::string surname, std::string patronymic, int age, bool activity){
    this->name = name;
    this->surname = surname;
    this->patronymic = patronymic;
    this->age = age;
    this->activity = activity;

    this->getLogin();
}


void User::getLogin(){
    std::ifstream file_translit("..\\resources\\transliteration.json"); 

    std::string text_translit;

    if (file_translit.is_open()) {
        std::string text((std::istreambuf_iterator<char>(file_translit)), std::istreambuf_iterator<char>());
        text_translit = text;
        //std::cout << text_translit;
        file_translit.close();
    } else {
        std::cout << "\nНе удалось открыть файл\n";
    }

    nlohmann::json arr_translit{nlohmann::json::parse(text_translit)};

    //std::cout<<arr_translit;

    if (arr_translit.is_object()) {} 
    else if (arr_translit.is_array()) { arr_translit = arr_translit[0];}
    else { std::cout << "Unexpected data format\n"; }

    // std::string str = "где? он";
    // for (size_t i = 0; i < str.size(); ) {
    //     size_t len = 1;
    //     unsigned char c = str[i];
    //     if (c >= 0xC0) len = (c >= 0xE0 ? (c >= 0xF0 ? 4 : 3) : 2);
    //     std::cout << "Символ " << str.substr(i, len) << " занимает " << len << " байт(а)\n";
    //     i += len;
    // }
    // Если первый байт меньше 0xC0 (в десятичной системе это 192), то символ занимает 1 байт.
    // Если первый байт больше или равен 0xC0, но меньше 0xE0 (в десятичной системе это 224), то символ занимает 2 байта.
    // Если первый байт больше или равен 0xE0, но меньше 0xF0 (в десятичной системе это 240), то символ занимает 3 байта.
    // Если первый байт больше или равен 0xF0, то символ занимает 4 байта.

    std::string en_surname = "";
    for(size_t surn = 0; surn < this->surname.size(); ){
        size_t len = 1;
        unsigned char c = this->surname[surn];
        if (c >= 0xC0) len = (c >= 0xE0 ? (c >= 0xF0 ? 4 : 3) : 2);
        //std::cout<< len<<" "<< surname.substr(surn, len)<<"\n";

        en_surname = en_surname + arr_translit[this->surname.substr(surn, len)].get<std::string>();

        surn += len;
    }
    unsigned char l1_n = this->name[0];
    std::string liter1_name = this->name.substr(0,((l1_n >= 0xC0) ? ((l1_n>=0xE0)?(l1_n>=0xF0 ? 4 : 3):2) : 1));
    unsigned char li_p = this->patronymic[0]; 
    std::string liter1_patronymic = this->patronymic.substr(0,((li_p >= 0xC0) ? ((li_p>=0xE0)?(li_p>=0xF0 ? 4 : 3):2) : 1));

    this->login = arr_translit[liter1_name].get<std::string>()+"."+arr_translit[liter1_patronymic].get<std::string>()+"."+en_surname;
   
}



std::ostream& operator<<(std::ostream& os, const User& obj){    
    std::string data_class = 
        "\nФамилия: " + obj.surname +
        "\nИмя: " + obj.name +  
        "\nОтчество: " + obj.patronymic + 
        "\nЛогин: " + obj.login;
    os << data_class;

    os << "\nВозраст: " << obj.age << "\n";

    if(obj.activity){os<<"Активен\n";}else{os<<"Не активен\n";};

    return os;
}

