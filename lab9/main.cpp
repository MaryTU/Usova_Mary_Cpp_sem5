#include "include/user.h"

#include <iostream>
#include <fstream>
#include <windows.h> // for change encoding
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <map>
#include <sstream>
#include <tuple>

#include <iomanip>

#include "lib/nlohmann/json.hpp"

/**
 * @brief Генерирует объект пользоователя
 * 
 * @return Объект пользователя
 */
User gen();

/**
 * @brief 
 * 
 * Cпасибо тебе добрый человек
 * https://ru.stackoverflow.com/questions/783946/Конвертировать-в-кодировку-utf8/784038#784038
 * ████████████████████████████▀▀██████████
 * ████████████████████████▀░░░░░░░▀███████
 * ██████████████████████▀░░░░░░░░░░███████
 * ██████████████████████░░░░░░░░░░▄███████
 * █████████████████▀▀▀░░░░░░░░░░▄▄████████
 * ██████████████▀▀░░░░░░░▄▄▄▄▄▄███████████
 * █████████████▀░░░░░░░░░░█████████▀▀▀████
 * ████████████░░░░░░░░░░░░███████▀░░░█████
 * ███████████░░░░░░░░░█░░░░█████░░░░██████
 * ███████████░░░░░░░░███░░░▀████░░▄███████
 * ██████████▀░░░░░░░░████░░░▀█▀░░▄████████
 * ██████████░░░░░░░░░█████░░░░░░▄█████████
 * ██████████░░░░░░░░░██████▄░░░███████████
 * ██████████░░░░░░░░░▀████████████████████
 * ██████████▄░░░░░░░░░▀▀▀█████████████████
 * ███████████▄░░░░░░░░░░░░░░▀▀▀███████████
 * ███████▀▀▀▀▀▀▀░░░░░░░░░░░░░░░░▀█████████
 * █████▀░░░░░░░░░░░░░░░░░░░░░░░░▄█████████
 * ████████████████████████████████████████
 * 
 * @param str 
 * @return std::string 
 */
std::string cp1251_to_utf8(const char *str){
    std::string res;
    int result_u, result_c;
    result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
    if(!result_u ){return 0;}
    wchar_t *ures = new wchar_t[result_u];
    if(!MultiByteToWideChar(1251, 0, str, -1, ures, result_u)){
        delete[] ures;
        return 0;
    }
    result_c = WideCharToMultiByte(65001, 0, ures, -1, 0, 0, 0, 0);
    if(!result_c){
        delete [] ures;
        return 0;
    }
    char *cres = new char[result_c];
    if(!WideCharToMultiByte(65001, 0, ures, -1, cres, result_c, 0, 0)){
        delete[] cres;
        return 0;
    }
    delete[] ures;
    res.append(cres);
    delete[] cres;
    return res;
}

void getUserForAge(std::vector<User> users);

void getMultiUserData(std::vector<User> users);

void multiSort(std::vector<User> users);

void findUser(std::vector<User> users);

int main(){
    SetConsoleCP(65001); // 65001 this is utf8
    SetConsoleOutputCP(65001); // once change forever, while don't change on another encoding
    int n = 0;

    std::cout << "\n Сколько пользователей создать: ";
    std::cin >> n;

    std::vector<User> users(n);
    std::generate_n (users.begin(), n, gen); 
    //std::generate (users.begin(), users.end(), gen); 
    
    while(true){
        std::cout<<"\nЧто делаем?"<<
            "\n 1. Отобразить всех пользователей"<<
            "\n 2. Найти пользователей старше выбранного возраста"<<
            "\n 3. Посмотреть информации об активности и тесках"<<
            "\n 4. Отсортировать пользователей"<<
            "\n 5. Поиск пользователей"
            "\n 6. Выйти из программы"
            "\n\t Введите пункт: ";
        
        int n = 0;
        std::cin>>n;
        
        if(n == 1){ for (auto i : users) { std::cout << i; } }
        else if(n == 2){ getUserForAge(users); }
        else if(n == 3){ getMultiUserData(users); }
        else if(n == 4){ multiSort(users); }
        else if(n == 5){ findUser(users); }
        else if(n == 6){break;}
    }

    //for (auto i : users) { std::cout << i; }
    // getUserForAge(users);
    // getMultiUserData(users);
    // multiSort(users);
    // findUser(users);

    return 0;
}



User gen(){
    static bool hop = true;
    static nlohmann::json arr_fio;

    if(hop){
        std::srand(std::time(NULL));

        std::ifstream file_fio("..\\resources\\SNP.json"); 

        std::string text_fio;

        if (file_fio.is_open()) {
            std::string text((std::istreambuf_iterator<char>(file_fio)), std::istreambuf_iterator<char>());
            text_fio = text;
            file_fio.close();
        } else { std::cout << "\nНе удалось открыть файл\n"; }

        nlohmann::json arr_fio_pereh{nlohmann::json::parse(text_fio)};
        arr_fio = arr_fio_pereh;
        // std::cout<<"\n"<<arr_fio<<"\n";

        if (arr_fio.is_object()) {} 
        else if (arr_fio.is_array()) { arr_fio = arr_fio[0];}
        else { std::cout << "Unexpected data format\n"; }

        hop = false;
        // std::cout<<std::endl<<arr_fio["names"].size()<<std::endl<<std::endl;
    }

    // std::cout<<"\n"<<arr_fio<<"\n";

    std::string new_name = arr_fio["names"][rand()%(arr_fio["names"].size())].get<std::string>();
    std::string new_surname = arr_fio["surnames"][rand()%(arr_fio["surnames"].size())].get<std::string>();
    std::string new_patronymic = arr_fio["patronymic"][rand()%(arr_fio["patronymic"].size())].get<std::string>();

    // if we have age
    int age = rand()%93+8;

    // if we have activity
    bool activity = (rand()%2==0)?(true):(false);

    User user(new_name,new_surname,new_patronymic,age,activity);

    return user;
}

void getUserForAge(std::vector<User> users){
    int min_age = 0; // пороговое значение

    std::cout << "\nВедите минимальный возраст с которого нужно найти людей: ";
    std::cin >> min_age;

    std::vector<User> result; // вектор для хранения результата

    // копирование элементов больше порогового значения
    std::copy_if(users.begin(), users.end(), std::back_inserter(result), [min_age](User x){return x.getAge() >= min_age;});

    // вывод результата
    for(auto i : result) { std::cout << i; }
}

void getMultiUserData(std::vector<User> users){
    // количество активных пользователей
    int amount_activity = std::count_if(users.begin(),users.end(),[](User x){return x.getActivity();});

    // количество неактивных пользователей
    int amount_disactivity = std::count_if(users.begin(),users.end(),[](User x){return (!x.getActivity());});

    // количество однофамильцев
    std::map<std::string, int> counts_sur; // словарь для хранения количества каждого элемента
    for (User num : users) { counts_sur[num.getSurname()]++;}

    // количество полных тесок
    std::map<std::string, int> counts_fio; // словарь для хранения количества каждого элемента
    for (User num : users) {counts_fio[num.getName()+" "+num.getPatronymic()+" "+num.getSurname()]++;}

    // Вывод полученных данных
    std::cout << "\nАктивных пользователей: " << amount_activity << ", Неактивных: "<< amount_disactivity;
    std::cout << "\nОднофамильцы:\n";
    for(auto pair:counts_sur){if(pair.second > 1) std::cout<<pair.first<<":\t"<<pair.second<<"\n";};
    std::cout << "\nПолные тески:\n";
    for(auto pair:counts_fio){if(pair.second > 1) std::cout<<pair.first<<":\t"<<pair.second<<"\n";};

}

void multiSort(std::vector<User> users){
    auto sorted_users = users;
    int (User::*get_f1)() = &User::getAge;
    std::string (User::*get_f2)() = &User::getName;
    std::string (User::*get_f3)() = &User::getSurname;
    std::string (User::*get_f4)() = &User::getPatronymic;
    std::string (User::*get_f5)() = &User::getMyLogin;
    bool (User::*get_f6)() = &User::getActivity;

    int max_field = 3;
    int our_field = 6;

    auto ptr_meth = std::make_tuple(get_f1, get_f2, get_f3,get_f4, get_f5, get_f6);
    std::vector<int> your_choise(our_field, 0);

    for (int i = 0; i < max_field; i++){
        std::cout<<"\nПо какому поле сортируем?"<<
            "\n 1. Возраст"<<
            "\n 2. Имя"<<
            "\n 3. Фамилия"<<
            "\n 4. Отчество"<<
            "\n 5. Логин"<<
            "\n 6. Активность"<<
            "\n 7. Закончить выбор"<<
            "\n\t Введите пункт: ";
        
        int n = 0;
        std::cin>>n;
        
        if(n == (our_field + 1)){ break;}
        
        for (int j = 0; j < our_field; j++){
            if(n == (j+1)){
                your_choise[j] = i+1;
                break;
            }
        }
    }

    max_field = 0;
    for(auto b:your_choise){ if(b != 0){ max_field++;} }

    // true - тогда элементы не меняются; false - элементы меняются
    // что бы итерировать кортеж нужно делать шаблонные функции...
    // std::sort(sorted_users.begin(), sorted_users.end(),  
    //     [&ptr_meth,vec_choise_sort, your_choise,your_choise_index](User &a, User &b){
    //         for(int num = 0; num<6;num++){
    //             if (your_choise[num] && (a.*std::get<your_choise_index[num]>(ptr_meth))() != (b.*std::get<iter>(ptr_meth))())
    //                 return (a.*std::get<iter>(ptr_meth))() < (b.*std::get<iter>(ptr_meth))();
    //         }
    //         return true;
    //     }
    // );
    if(max_field != 0){
        std::sort(sorted_users.begin(), sorted_users.end(),  
            [&ptr_meth,your_choise,max_field,our_field](User a, User b){
                for (int i = 1; i < max_field+1; i++){
                    int j = 0;
                    for (j = 0; j < our_field; j++) { if(i == your_choise[j]) break; }      

                    if (your_choise[0] && j == 0 && (a.*std::get<0>(ptr_meth))() != (b.*std::get<0>(ptr_meth))())
                        return (a.*std::get<0>(ptr_meth))() < (b.*std::get<0>(ptr_meth))();
                    if (your_choise[1] && j == 1 && (a.*std::get<1>(ptr_meth))() != (b.*std::get<1>(ptr_meth))())
                        return (a.*std::get<1>(ptr_meth))() < (b.*std::get<1>(ptr_meth))();
                    if (your_choise[2] && j == 2 && (a.*std::get<2>(ptr_meth))() != (b.*std::get<2>(ptr_meth))())
                        return (a.*std::get<2>(ptr_meth))() < (b.*std::get<2>(ptr_meth))();
                    if (your_choise[3] && j == 3 && (a.*std::get<3>(ptr_meth))() != (b.*std::get<3>(ptr_meth))())
                        return (a.*std::get<3>(ptr_meth))() < (b.*std::get<3>(ptr_meth))();
                    if (your_choise[4] && j == 4 && (a.*std::get<4>(ptr_meth))() != (b.*std::get<4>(ptr_meth))())
                        return (a.*std::get<4>(ptr_meth))() < (b.*std::get<4>(ptr_meth))();
                    if (your_choise[5] && j == 5 && (a.*std::get<5>(ptr_meth))() != (b.*std::get<5>(ptr_meth))())
                        return (a.*std::get<5>(ptr_meth))() < (b.*std::get<5>(ptr_meth))();
                }
                return true;
            }
        );
    }
    

    // std::sort(sorted_users.begin(), sorted_users.end(),  
    //     [&ptr_meth,&your_choise](User a, User b){
    //         if (your_choise[0] && (a.*std::get<0>(ptr_meth))() != (b.*std::get<0>(ptr_meth))())
    //             return (a.*std::get<0>(ptr_meth))() < (b.*std::get<0>(ptr_meth))();
    //         if (your_choise[1] && (a.*std::get<1>(ptr_meth))() != (b.*std::get<1>(ptr_meth))())
    //             return (a.*std::get<1>(ptr_meth))() < (b.*std::get<1>(ptr_meth))();
    //         if (your_choise[2] && (a.*std::get<2>(ptr_meth))() != (b.*std::get<2>(ptr_meth))())
    //             return (a.*std::get<2>(ptr_meth))() < (b.*std::get<2>(ptr_meth))();
    //         if (your_choise[3] && (a.*std::get<3>(ptr_meth))() != (b.*std::get<3>(ptr_meth))())
    //             return (a.*std::get<3>(ptr_meth))() < (b.*std::get<3>(ptr_meth))();
    //         if (your_choise[4] && (a.*std::get<4>(ptr_meth))() != (b.*std::get<4>(ptr_meth))())
    //             return (a.*std::get<4>(ptr_meth))() < (b.*std::get<4>(ptr_meth))();
    //         if (your_choise[5])
    //             return (a.*std::get<5>(ptr_meth))() < (b.*std::get<5>(ptr_meth))();
    //         return true;
    //     }
    // );

    // std::sort(sorted_users.begin(), sorted_users.end(),  
    //     [get_f1,get_f2,get_f3](User a, User b){
    //         if ((a.*get_f1)() != (b.*get_f1)())
    //             return (a.*get_f1)() < (b.*get_f1)();
    //         if ((a.*get_f2)() != (b.*get_f2)())
    //             return (a.*get_f2)() < (b.*get_f2)();
    //         return (a.*get_f3)() < (b.*get_f3)();
    //     }
    // );

    std::cout<<"\nОтсортированныйсписок\n";
    // std::cout<<"Возраст\tИмя\tФамилия\tОтчество\tЛогин\tактивность\n";
    // for(auto i:sorted_users){
    //     std::cout<<
    //         i.getAge()<<"\t"<<
    //         i.getName()<<"\t"<<
    //         i.getSurname()<<"\t"<<
    //         i.getPatronymic()<<"\t"<<
    //         i.getMyLogin()<<"\t"<<
    //         ((i.getActivity())?("Активен"):("Не активен"))<<"\n";
    // }

    std::cout << std::left << std::setw(10) << "Age"
              << std::setw(30) << "Имя"
              << std::left << std::setw(30) << "Фамилия"
              << std::setw(30) << "Отчество"
              << std::setw(20) << "Логин"
              << std::setw(15) << "Астивность" << "\n";

    // Разделитель
    std::cout << std::setfill('-') << std::setw(10+30*3+20+15) << "" << "\n";
    // Восстановление символа заполнения
    std::cout << std::setfill(' ');

    // Данные
    for(auto i:sorted_users){
        std::cout << std::left << std::setw(10) << i.getAge()
              << std::setw(30) << i.getName()
              << std::left << std::setw(30) << i.getSurname()
              << std::setw(30) << i.getPatronymic()
              << std::setw(20) << i.getMyLogin()
              << std::setw(15) << ((i.getActivity())?("Активен"):("Не активен")) << "\n";
    }
}

void findUser(std::vector<User> users){
    // Считывание ФИО
    std::cout<<"Введите ФИО пользователя, которых хотите найти: ";
    std::string str_fio0;

    SetConsoleCP(1251); // 65001 this is utf8
    SetConsoleOutputCP(1251);
    std::cin.ignore();
    std::getline(std::cin, str_fio0);

    SetConsoleCP(65001); // 65001 this is utf8
    SetConsoleOutputCP(65001);
    const char* cstr = str_fio0.c_str();
    std::string str_fio = cp1251_to_utf8(cstr);


    std::istringstream iss(str_fio); // создается поток ввода
    std::string word; 
    std::vector<std::string> word_all_fio; // вектор для хранения слов

    while (iss >> word) { word_all_fio.push_back(word); } // добавление слова в вектор

    // Поиск
    std::vector<std::function<bool(User)>> checks = {
        [word_all_fio](User u){return u.getSurname() == word_all_fio[0];},
        [word_all_fio](User u){return u.getName() == word_all_fio[1];},
        [word_all_fio](User u){return u.getPatronymic() == word_all_fio[2];}
    };

    int iter = 1;
    for(auto l_f:checks){
        std::vector<User> find_FIO;
        auto it = users.begin();

        while (it != users.end()) {
            it = std::find_if(it, users.end(),l_f);
            if (it != users.end()) {
                // std::cout << "\tЗапись найдена: " << *it << std::endl;
                find_FIO.push_back(*it);
                ++it;
            }
        }

        if(find_FIO.empty()){
            std::cout<<"\nНе найдено подходящих записей\n";
            users = find_FIO;
            break;
        } 
        users = find_FIO;
        
        if(iter==(int)word_all_fio.size()){break;}
        iter++;
    }

    for(auto i: users){std::cout<< "\n\tЗапись найдена:"<<i;}

    return;
}


