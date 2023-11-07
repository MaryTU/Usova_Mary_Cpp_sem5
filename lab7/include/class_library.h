#include <vector>
#include <queue>
#include <algorithm>
#include <string>

static bool need_random_library = true;
const int MAX_AMOUNT_BOOK = 30;
const int MIN_AMOUNT_BOOK = 5;

const int MIN_PAGES_IN_BIG_BOOK = 500;
const int MAX_PAGES_IN_SMALL_BOOK = 100;

const int MAX_VISITER_PER_DAY = 5;
const int MIN_VISITER_PER_DAY = 1;

const int MAX_RATE = 10;
const int MIN_RATE = 1;

enum Actions{
    GET_BOOK,
    RETURN_BOOK,
};

class Library{
    private:
        std::vector<Book> catalog;
        std::vector<bool> book_is_free;
    public:
        Library();
        ~Library();

    public:
        /**
         * @brief Подбор подходящей книги из каталога, в зависимости от потребностей посетителя
         * 
         * @param visiter экземпляр посетителя
         * @param id_visiter уникальный идентификатор посетителя
         * @return номер книги в коллекции
         */
        int findSuitableBook(Visiter visiter, int id_visiter);
        /**
         * @brief Моделирование работы библиотеки
         * 
         * @param visiters Массив посетителей
         * @param time_work время моделирования в днях
         */
        void modelingLibrary(std::vector<Visiter> visiters, int time_work); // время в днях
        
};

Library::Library(){
    if(need_random_library) std::srand(std::time(NULL));
    need_random_library = false;

    //std::vector<Book> my_library;
    int amount_book = rand()%(MAX_AMOUNT_BOOK + 1 - MIN_AMOUNT_BOOK) + MIN_AMOUNT_BOOK;
    for (int i = 0; i < amount_book; i++){
        this->catalog.push_back(Book());
        this->book_is_free.push_back(true);
    }
    for(Book book:this->catalog) book.viewBookInfo();
}
Library::~Library(){}


int Library::findSuitableBook(Visiter visiter, int id_visiter){
    int iter = -1;
    for(Book book: this->catalog){
        iter++;
        if(!this->book_is_free[iter]) continue;

        // возрастное ограничение
        if(visiter.getAge() < book.getAgeRestrictions()) continue;

        // предпочтение по жанрам
        bool genre = false;
        for(Genres g:book.getGenre()) genre = genre || (visiter.getFavoriteGenres() == g); 
        if(!genre) continue;

        // предпочтение по объему
        if(visiter.getVolumePreferences() == BIG){
            if(book.getQuantityOfPages() <= 500) continue;
        }
        else if(visiter.getVolumePreferences() == MEDIUM){
            if(book.getQuantityOfPages() > 500 || book.getQuantityOfPages() < 100) continue;
        }
        else if(visiter.getVolumePreferences() == SMALL){
            if(book.getQuantityOfPages() >= 100) continue;
        }

        // и проверяем не читал ли посетитель эту книгу раньше
        auto rate_list = book.getScore();
        if(!rate_list.empty()){
            bool already_readed = false;
            for(auto a:rate_list){
                if(a.first == id_visiter){
                    already_readed = true; 
                    break;
                }
            }
            if (already_readed) continue;
        }
        
        // если дошел до этого места, книга подходит (возвращаем номер книги)
        return iter;
    }

    // если не нашли подходящей книги возвращаем -1
    return -1;
}

void Library::modelingLibrary(std::vector<Visiter> visiters,int time_work){
    // вектора для выполения последовательно действий
    std::vector<int> visiter_who_do_action;
    std::vector<Actions> actions;
    std::vector<int> time_action;
    std::vector<int> num_book_for_action; // у этого вектора размер будет меньше, так как его элементы соответсвуют только action = RETURN_BOOK

    // переменные для получения статистики моделирования
    std::vector<int> amount_bring_book; // количиство взятия каждой книги (оказалось эта переменная не очень нужна, вообще не нужна)
    for(int i = 0; i < (int)this->catalog.size(); i++) amount_bring_book.push_back(0);
    std::vector<int> avg_time_read_book; // сумма времени чтения книги и нужно будет поделить на количество взятий
    for(int i = 0; i < (int)this->catalog.size(); i++) avg_time_read_book.push_back(0);
    // количество взятие по автору можно вывести из предыдущих переменных

    

    for (int o = 0; o < time_work; o++){
        // генерируем число посетителей библиотеки
        int visiter_per_day = rand()%(MAX_VISITER_PER_DAY + 1 - MIN_VISITER_PER_DAY) + MIN_VISITER_PER_DAY;

        // проверка на то если у нас все люди задействованы, но и прийти не могут, следовательно это нужно учесть
        //std::cout<<"v per day: "<< visiter_per_day<<"\nwho action: "<<(int)visiter_who_do_action.size();
        if((int)visiters.size() < (int)visiter_who_do_action.size() + visiter_per_day){
            visiter_per_day = (int)visiters.size() - (int)visiter_who_do_action.size();
        }
        //std::cout<<"\nbefore v per day: "<<visiter_per_day<<"\n";

        //генерируем какие из людей придут и во сколько
        std::map<int,int> all_visiter_one_day;
        for (int i = 0; i < visiter_per_day; i++){
            int num_visiter = rand()%((int)visiters.size()); 

            // //если контейнер пуст сразу генерируем значение (не сразу так как нужно проверить на )
            // if((int)all_visiter_one_day.size() == 0){
            //     all_visiter_one_day[num_visiter] = (rand()%24)*60 + rand()%60 + o*24*60; // время в минутах
            //     continue;
            // }

            // если контейнер не пуст проверяем, что бы сгенерированный пользователь не повторялся
            bool contin_find = true;
            while(contin_find){
                if((int)all_visiter_one_day.size() == 0){
                    contin_find = false;
                }
                for(auto a_v:all_visiter_one_day){
                    if(a_v.first == num_visiter){
                        num_visiter = (num_visiter + 1)%((int)visiters.size());
                        contin_find = true;
                        break;
                    }
                    contin_find = false;
                }
                for(auto be: visiter_who_do_action){
                    if(be == num_visiter){
                        num_visiter = (num_visiter + 1)%((int)visiters.size());
                        contin_find = true;
                    }
                }
            }
            

            all_visiter_one_day[num_visiter] = (rand()%24)*60 + rand()%60 + o*24*60; // время в минутах от начала моднлирования
        }


        std::vector<int> for_sort_time;
        for(auto a:all_visiter_one_day) for_sort_time.push_back(a.second);
        std::sort(for_sort_time.begin(), for_sort_time.end()); // получаем время в порядке возрастания
        // for(auto b:for_sort_time) std::cout<<b<<" ";
        int iter = 0;
        // получаем массивы действий посетителей этого дня
        for(auto a:all_visiter_one_day){
            all_visiter_one_day[a.first] = for_sort_time[iter]; // точно ли тут будет просто push_back?, кажется что нет

            for (int t = 0; t < (int)time_action.size(); t++){
                // вставляем значение либо в середину либо в начало
                if(time_action[t] > all_visiter_one_day[a.first]){// ошибка что a уже определена а мы ее меняем и потом работаем с измененной, а получилось работаем не с измененной поэтому не a.second а all_visiter_one_day[a.first] 
                    visiter_who_do_action.insert(visiter_who_do_action.begin() + t, a.first);
                    actions.insert(actions.begin() + t, GET_BOOK);
                    time_action.insert(time_action.begin() + t, all_visiter_one_day[a.first]);
                    break;
                }// вставляем значение в конец, если соблюдено условие
                else if(time_action.back() <= all_visiter_one_day[a.first]){
                    visiter_who_do_action.push_back(a.first);
                    actions.push_back(GET_BOOK);
                    time_action.push_back(all_visiter_one_day[a.first]);
                    break;
                }
            }

            if((int)time_action.size() == 0){
                visiter_who_do_action.push_back(a.first);
                actions.push_back(GET_BOOK);
                time_action.push_back(all_visiter_one_day[a.first]);
            }
            
            iter++;
        }
        // for(auto a:all_visiter_one_day){
        //     std::cout<<"people: "<< a.first<<", time:"<<a.second<<"("<<a.second/60<<":"<<a.second%60<<")\n";
        // }

        // std::cout<<"before"<<std::endl;
        // for(auto b:actions)
        // std::cout<<b<<" ";
        // std::cout<<std::endl;
        // for(auto b:visiter_who_do_action)
        // std::cout<<b<<" ";
        // std::cout<<std::endl;
        // for(auto b:time_action)
        // std::cout<<b<<" ";
        // std::cout<<std::endl;


        // смотрим взависимости от action какая книга подходит пользователю
        for(auto a:all_visiter_one_day){
            // проверяем первое action это возврат книги или нет (повторяем пока первое действие возврат)
            while(actions[0] == RETURN_BOOK){
                // выводим информацию о возврате
                int time_in_days = time_action[0]/(24*60);
                int time_in_hour = (time_action[0] - time_in_days*24*60)/60;
                std::cout<<"At "<< time_in_days <<"d. "<<time_in_hour<<":"<<time_action[0]%60
                    <<"\n\tvisiter "<<visiter_who_do_action[0]<<" returned the book:"
                    <<"\n\t Book: \""<<this->catalog[num_book_for_action[0]].getName()<<"\" "
                    <<this->catalog[num_book_for_action[0]].getAuthor()<<", "
                    <<this->catalog[num_book_for_action[0]].getQuantityOfPages()<<"pages\n";

                // пользователь ставит оценку произведению
                int rate_for_this_book = rand()%(MAX_RATE + 1 - MIN_RATE) + MIN_RATE;
                this->catalog[num_book_for_action[0]].setScore(visiter_who_do_action[0],rate_for_this_book);
                std::cout<<"\t and gave a rating of "<<rate_for_this_book<<"/10\n";
                this->book_is_free[num_book_for_action[0]] = true;

                // так как мы обработали возврат книги очищаем временные массивы от 1 значения (возврата)
                visiter_who_do_action.erase(visiter_who_do_action.begin());
                actions.erase(actions.begin());
                time_action.erase(time_action.begin());
                num_book_for_action.erase(num_book_for_action.begin()); 

            }



            // генерируем желание посетителя
            visiters[a.first].nowIWant();
            // далее идет подбор книги для посетителя
            int num_book = this->findSuitableBook(visiters[a.first],a.first);


            // если не удалось найти книгу на вкус посетителя (получили -1), то:
            if(num_book == -1){
                int time_in_days = a.second/(24*60);
                int time_in_hour = (a.second - time_in_days*24*60)/60;
                std::cout<<"At "<< time_in_days <<"d. "<<time_in_hour<<":"<<a.second%60
                    <<"\n\tvisiter "<<a.first<<" couldn't find a book suitable for him"
                    <<" (age = "<<visiters[a.first].getAge()<<", genre is ";

                Genres f_g = visiters[a.first].getFavoriteGenres();
                if(f_g == DETECTIVE) std::cout<<"detective";
                else if(f_g == ROMANCE) std::cout<<"romance";
                else if(f_g == FANTASY) std::cout<<"fantasy";
                else if(f_g == SCIENCE_FICTION) std::cout<<"science fiction";

                std::cout<<", volume preferences is ";
                VolumePreferences v_p = visiters[a.first].getVolumePreferences();
                if(v_p == BIG) std::cout<<"BIG";
                else if(v_p == MEDIUM) std::cout<<"MEDIUM";
                else if(v_p == SMALL) std::cout<<"SMALL";
                else if(v_p == ANY) std::cout<<"ANY";

                std::cout<<")\n";
                // если не подошла книга отправляем посетителя куда подальше (удаляем его из очереди)
                for (int t = 0; t < (int)visiter_who_do_action.size(); t++){
                    if(visiter_who_do_action[t] == a.first && actions[t] == GET_BOOK){//time_action[t] == a.second){
                    visiter_who_do_action.erase(visiter_who_do_action.begin() + t);
                    time_action.erase(time_action.begin() + t);
                    actions.erase(actions.begin() + t);
                    break;
                }
            }
                continue;
            }//else{
            // если книга подошла, блокируем ее для чтения 
            this->book_is_free[num_book] = false;
            // и отмечаем что эту книгу взяли
            amount_bring_book[num_book]++;
            // выводим информацию, какую именно книгу взял пользователь и когда
            int time_in_days1 = a.second/(24*60);
            int time_in_hour1 = (a.second - time_in_days1*24*60)/60;
            std::cout<<"At "<< time_in_days1 <<"d. "<<time_in_hour1<<":"<<a.second%60
                <<"\n\tvisiter "<<a.first<<" took the book:"//;
                <<"(age="<<visiters[a.first].getAge()<<", ";
                
                Genres f_g = visiters[a.first].getFavoriteGenres();
                if(f_g == DETECTIVE) std::cout<<"detective";
                else if(f_g == ROMANCE) std::cout<<"romance";
                else if(f_g == FANTASY) std::cout<<"fantasy";
                else if(f_g == SCIENCE_FICTION) std::cout<<"science fiction";

                std::cout<<", volume preferences is ";
                VolumePreferences v_p = visiters[a.first].getVolumePreferences();
                if(v_p == BIG) std::cout<<"BIG";
                else if(v_p == MEDIUM) std::cout<<"MEDIUM";
                else if(v_p == SMALL) std::cout<<"SMALL";
                else if(v_p == ANY) std::cout<<"ANY";
                std::cout <<")";
            std::cout<<"\n\t Book: \""<<this->catalog[num_book].getName()<<"\" "
                <<this->catalog[num_book].getAuthor()<<", "
                <<this->catalog[num_book].getQuantityOfPages()<<"pages\n";


            // расчитываем время, когда пользователь закончит читать эту книгу
            int time_ending_reading = visiters[a.first].readBook(this->catalog[num_book].getQuantityOfPages()) + a.second;// + o*24*60;
            // и за одно отмечаем сколько времени потратили на чтение данной книги
            avg_time_read_book[num_book] = avg_time_read_book[num_book] + visiters[a.first].readBook(this->catalog[num_book].getQuantityOfPages()); // в минутах
            // взависимости от полученного времени вставляем в определенное место массивов данные
            // найдем позицию на которую стоит поставить это значение и добавим в общие массивы очереди
            for (int t = 0; t < (int)time_action.size(); t++){
                // вставляем значение либо в середину либо в начало
                if(time_action[t]>time_ending_reading){
                    //расчет куда вставить книгу
                    std::vector<int> time_return; // массив времени возвращений
                    for(int gg = 0; gg < (int)actions.size();gg++){
                        if(actions[gg] == RETURN_BOOK) time_return.push_back(time_action[gg]);
                    }
                    for(int gg = 0; gg < (int)time_return.size(); gg++){
                        if(time_return[gg]>time_ending_reading){
                            num_book_for_action.insert(num_book_for_action.begin() + gg, num_book);
                            break;
                        }
                        else if(time_return.back()<time_ending_reading){
                            num_book_for_action.push_back(num_book);
                            break;
                        }
                    }
                    if((int)time_return.size() == 0){
                        num_book_for_action.push_back(num_book);
                    }
                    // вставка остальных параметров
                    visiter_who_do_action.insert(visiter_who_do_action.begin() + t, a.first);
                    actions.insert(actions.begin() + t, RETURN_BOOK);
                    time_action.insert(time_action.begin() + t, time_ending_reading);
                    break;
                }// вставляем значение в конец, если соблюдено условие
                else if(time_action.back()<time_ending_reading){
                    visiter_who_do_action.push_back(a.first);
                    actions.push_back(RETURN_BOOK);
                    time_action.push_back(time_ending_reading);
                    num_book_for_action.push_back(num_book);
                    break;
                }
            }


            // а так же нужно убрать из очереди действие взятия книги 
            for (int t = 0; t < (int)visiter_who_do_action.size(); t++){
                if(visiter_who_do_action[t] == a.first && actions[t] == GET_BOOK){//time_action[t] == a.second){
                    visiter_who_do_action.erase(visiter_who_do_action.begin() + t);
                    time_action.erase(time_action.begin() + t);
                    actions.erase(actions.begin() + t);
                    break;
                }
            }
            //}
            // std::cout<<"after"<<std::endl;
            // for(auto b:actions)
            // std::cout<<b<<" ";
            // std::cout<<std::endl;
            // for(auto b:visiter_who_do_action)
            // std::cout<<b<<" ";
            // std::cout<<std::endl;
            // for(auto b:time_action)
            // std::cout<<b<<" ";
            // std::cout<<std::endl;

        }

    }

    std::cout<<"MODELING IS END, WAIT WHEN ALL VISITERES RETURN BOOK\n";

    // когда закончилось время моделирования возвращаются все книги
    while(actions[0] == RETURN_BOOK && (int)actions.size() != 0){
        // выводим информацию о возврате
        int time_in_days = time_action[0]/(24*60);
        int time_in_hour = (time_action[0] - time_in_days*24*60)/60;
        std::cout<<"At "<< time_in_days <<"d. "<<time_in_hour<<":"<<time_action[0]%60
            <<"\n\tvisiter "<<visiter_who_do_action[0]<<" returned the book:"
            <<"\n\t Book: \""<<this->catalog[num_book_for_action[0]].getName()<<"\" "
            <<this->catalog[num_book_for_action[0]].getAuthor()<<", "
            <<this->catalog[num_book_for_action[0]].getQuantityOfPages()<<"pages\n";

        // пользователь ставит оценку произведению
        int rate_for_this_book = rand()%(MAX_RATE + 1 - MIN_RATE) + MIN_RATE;
        this->catalog[num_book_for_action[0]].setScore(visiter_who_do_action[0],rate_for_this_book);
        std::cout<<"\t and gave a rating of "<<rate_for_this_book<<"/10\n";
        this->book_is_free[num_book_for_action[0]] = true;

        // так как мы обработали возврат книги очищаем временные массивы от 1 значения (возврата)
        visiter_who_do_action.erase(visiter_who_do_action.begin());
        actions.erase(actions.begin());
        time_action.erase(time_action.begin());
        num_book_for_action.erase(num_book_for_action.begin()); 

    }

    // std::cout<<"after"<<std::endl;
    // for(auto b:actions)
    // std::cout<<b<<" ";
    // std::cout<<std::endl;
    // for(auto b:visiter_who_do_action)
    // std::cout<<b<<" ";
    // std::cout<<std::endl;
    // for(auto b:time_action)
    // std::cout<<b<<" ";
    // std::cout<<std::endl;


    // теперь выводим отзывы на книги 
    std::cout<<"\n\nAVARAGE RAITING BOOKS, AMOUNT BRINGS, AVARAGE READING TIME:\n";
    int itern = -1;
    for(auto gege: this->catalog){
        //gege.viewBookInfo();
        itern++;
        std::cout<<"\""<<gege.getName()<<"\", "<<gege.getAuthor()<<"\t rate = "<<gege.getAvarageRate()<<"\n";
        std::cout<<"\t bring "<<(int)gege.getScore().size()<<" times\n";
        std::cout<<"\t avarage time reading: ";
        if(avg_time_read_book[itern] == 0) std::cout << "undef\n";
        else std::cout << (int)avg_time_read_book[itern]/((int)gege.getScore().size())<< " min\n";
    }

    // теперь авторы:
    std::cout<<"\n\nAMOUNT BRING BOOK FOR AUTHOR:\n";
    std::vector<std::string> names_author;
    std::vector<int> amount_bring_book_author;
    for(auto gege: this->catalog){
        bool we_already_have_author = false;
        for(auto a: names_author){
            if(a == gege.getAuthor()) we_already_have_author = true;
        }
        if(!we_already_have_author){
            names_author.push_back(gege.getAuthor());
        }
    }
    for(auto aaaa: names_author) amount_bring_book_author.push_back(0);
    for(int i1 = 0; i1 < (int)names_author.size(); i1++){
        for(int i2 = 0; i2 < (int)this->catalog.size(); i2++){
            if(this->catalog[i2].getAuthor() == names_author[i1]) amount_bring_book_author[i1] += (int)this->catalog[i2].getScore().size();
        }
    }
    for(int i1 = 0; i1 < (int)names_author.size(); i1++){
        std::cout << "Autor: " << names_author[i1] << "\t bring " << amount_bring_book_author[i1] << " books\n";
    }

    // std::cout<<"\n\nAVARAGE RAITING BOOKS:\n";
    // int itern = -1;
    // for(auto gege: this->catalog){
    //     itern++;
    //     std::cout<<"\""<<gege.getName()<<"\", "<<gege.getAuthor()<<"\n";
    //     std::cout<<"\t bring "<<amount_bring_book[itern]<<" times\n";
    // }
    
}

