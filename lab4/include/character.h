#include <iostream>
#include <vector>
#include <string>



//различие между магом и стрелком в стойкости и силе, маг сильнее но менее вынослив, стрелок наоборот
const int MIN_POWER_MAGICIAN = 200;
const int MAX_POWER_MAGICIAN = 500;
const int MIN_DURABILITY_MAGICIAN = 25;
const int MAX_DURABILITY_MAGICIAN = 100;
const int MIN_DISTANCE_MAGICIAN = 10;
const int MAX_DISTANCE_MAGICIAN = 40;


const int MIN_POWER_SHOOTER = 50;
const int MAX_POWER_SHOOTER = 300;
const int MIN_DURABILITY_SHOOTER = 50;
const int MAX_DURABILITY_SHOOTER = 250;
const int MIN_DISTANCE_SHOOTER = 10;
const int MAX_DISTANCE_SHOOTER = 40;


const int MIN_POWER_SWORDSMAN = 100;
const int MAX_POWER_SWORDSMAN = 350;
const int MIN_DURABILITY_SWORDSMAN = 100;
const int MAX_DURABILITY_SWORDSMAN = 400;
const int MIN_DISTANCE_SWORDSMAN = 1;
const int MAX_DISTANCE_SWORDSMAN = 5;

// Получается дистанция 21-30 - средняя дистанция, 31-40 - дальних дистанций
// мечник танк от 300 стойкости
// мечник наносящий значительный урон от 250
const int LOWER_BOUND_AVARAGE_DISTANSE = 10;
const int HIGHT_BOUND_AVARAGE_DISTANSE = 25;
const int LOWER_BOUND_FAR_DISTANSE = 26;

const int SWORDMAN_TANK_DURABILITY = 300;
const int SWORDMAN_SIGNIFICANT_DAMAGE = 250;



class Character{
    public:
        int strength, durability, distance, cost;
    protected:
        /**
         * @brief Расчёт цены персонажа относительно его характеристик
         * 
         * @return Цена персонажа
         */
        int getPrice();
};


class Swordsman: public Character{
    public:
        /**
         * @brief Construct a new Swordsman object
         * 
         */
        Swordsman();
};
class Magician: public Character{
    public:
        /**
         * @brief Construct a new Magician object
         * 
         */
        Magician();
};
class Shooter: public Character{
    public:
        /**
         * @brief Construct a new Shooter object
         * 
         */
        Shooter();
};






enum TypeCharacter{
    SWORDMAN,
    MAGICIAN,
    SHOOTER,
    UNDEF,
};

class Mercenary{
    public:
        void* weapon;
        TypeCharacter who_i_am;
        /**
         * @brief Construct a new Mercenary object
         * 
         * @param weapon пустой указатель на тип персонажа
         * @param who_i_am тип персонажа
         */
        Mercenary(void* weapon, TypeCharacter who_i_am);
        /**
         * @brief Construct a new Mercenary object
         * 
         */
        Mercenary();

        /**
         * @brief Get the Cost object
         * 
         * @return Cost
         */
        int getCost();
        /**
         * @brief Get the Strength object
         * 
         * @return Strength
         */
        int getStrength();
        /**
         * @brief Get the Durability object
         * 
         * @return Durability 
         */
        int getDurability();
        /**
         * @brief Get the Distance object
         * 
         * @return Distance
         */
        int getDistance();
};





class Guild{
    private:
        std::vector<Mercenary> our_company;

    public:
        /**
         * @brief Construct a new Guild object
         * 
         * @param our_company группа наёмников
         */
        Guild(std::vector <Mercenary> our_company){
            this->our_company = our_company;
        }
        /**
         * @brief Construct a new Guild object
         * 
         */
        Guild(){}

        // что бы доставть приватные значения
        /**
         * @brief Get the All Mercenary object
         * 
         * @return std::vector<Mercenary> get our_company from object
         */
        std::vector<Mercenary> getAllMercenary(){
            return this->our_company;
        }
        /**
         * @brief Добавляет нового наёмника в гильдию 
         * 
         * @param mer новый наёмник
         */
        void addNewMercenary(Mercenary mer){
            this->our_company.push_back(mer);
        }
        /**
         * @brief Показывает таблицу всех наёмников гильдии
         * 
         */
        void seeAllMercenaryInGuild();
        /**
         * @brief Находит лучшую команду при заданной цене и проверяет, возможно ли создать такую команду 
         * 
         * @param money деньги
         * @return лучшую команду типа Guild
         */
        Guild findBestTeam(int money);

    private:
        /**
         * @brief Рекурсивно подбирает лучшую команду
         * 
         * @param strongest_team пустое значение в котором будет происходить подбор лучшей команды
         * @param strongest_team_num номера героев из гильдии которые используются в команде 
         * @param remains_cash оставшиеся деньги на подбор персонажей
         * @param best_team значение где будет хранится лучшая команда
         * @param max_strenght максимальная сила команд (изначально 0)
         * @param schetchik_for_speed для уменьшение вычислений (изначально 0)
         * @return std::vector<Mercenary> Лучшая команда
         */
        std::vector<Mercenary> bruteForceTeam(
            std::vector<Mercenary> strongest_team, 
            std::vector<int> strongest_team_num, 
            int remains_cash,
            std::vector<Mercenary>& best_team,
            int& max_strenght,
            int schetchik_for_speed = 0
        )
        {
            if(remains_cash > 0){
                bool can_li_add = true;
                for (int i = schetchik_for_speed; i < (int)this->our_company.size(); i++){
                    bool pereh = false;
                    for (int j = 0; j < (int)strongest_team.size(); j++){
                        if(
                            strongest_team_num[j] == i ||
                            remains_cash <= this->our_company[i].getCost()
                        ){
                            pereh = true;
                            break;
                        }
                    }
                    
                    if(pereh) continue;
                    
                    if(can_li_add){
                        strongest_team.push_back(this->our_company[i]);
                        strongest_team_num.push_back(i);
                    } 
                    can_li_add = false;
                    

                    
                    strongest_team[strongest_team.size()-1] = this->our_company[i];
                    strongest_team_num[strongest_team.size()-1] = i;                    

                    int remains_cash2 = remains_cash - strongest_team[strongest_team.size()-1].getCost();
                    strongest_team = bruteForceTeam(strongest_team,strongest_team_num,remains_cash2,best_team, max_strenght,i+1); 
                    
                    // std::cout<<"size = "<<strongest_team_num.size()<<"\n";                  
                    // for (int gege = 0; gege < (int)strongest_team_num.size(); gege++)
                    // {
                    //     std::cout<<strongest_team_num[gege]<<" ";
                    // }
                    // std::cout<<"\n";
                    
                    //if(cond exercice)
                    // записываем в лучшее решение 

                    // ТРЕБОВАНИЯ К ИДЕАЛЬНОЙ TEAM:
                    // максимальная сила
                    // средняя и близкая дистанция обязательно (желательно дальняя но не обязательно)
                    // стойкость как минимум половина от силы
                    bool 
                        avarage_dist = false,
                        near_dist = false,
                        half_is_durability = false,
                        strenghtstly = false,
                        min_size_groupe = false;

                    int 
                        sum_durability = 0,
                        sum_strenght = 0;
                    for (int co = 0; co < (int)strongest_team.size(); co++){
                        sum_durability += strongest_team[co].getDurability();
                        sum_strenght += strongest_team[co].getStrength();

                        int dist_co = strongest_team[co].getDistance();
                        if(dist_co < LOWER_BOUND_AVARAGE_DISTANSE)
                            near_dist = true;
                        if(
                            dist_co >= LOWER_BOUND_AVARAGE_DISTANSE &&
                            dist_co <= HIGHT_BOUND_AVARAGE_DISTANSE
                        ) avarage_dist = true;
                    }
                    if(sum_strenght <= sum_durability*2) half_is_durability = true;
                    if(sum_strenght > max_strenght) strenghtstly = true;
                    if((int)strongest_team.size() >=5) min_size_groupe = true;

                    if(
                        half_is_durability && 
                        near_dist && 
                        avarage_dist && 
                        strenghtstly &&
                        min_size_groupe
                    ){
                        best_team = strongest_team;// тогда записываем в лучшую комманду
                        max_strenght = sum_strenght; //обновляем максимальную силу
                    }
                    // else{
                    //     std::cout<<"\nteam is not finded\n";  
                    // }
                    
                }    
                if(!can_li_add) strongest_team.pop_back();
                return strongest_team;
            }
            else{
                return strongest_team;
            }
        }  

};

int Character::getPrice(){
    return strength*2 + durability + distance*5;
}

Swordsman::Swordsman(){
    this->strength = rand()%(MAX_POWER_SWORDSMAN - MIN_POWER_SWORDSMAN) + MIN_POWER_SWORDSMAN;
    this->durability = rand()%(MAX_DURABILITY_SWORDSMAN - MIN_DURABILITY_SWORDSMAN) + MIN_DURABILITY_SWORDSMAN;
    this->distance = rand()%(MAX_DISTANCE_SWORDSMAN - MIN_DISTANCE_SWORDSMAN) + MIN_DISTANCE_SWORDSMAN;
    this->cost = getPrice();
}
Magician::Magician(){
    this->strength = rand()%(MAX_POWER_MAGICIAN - MIN_POWER_MAGICIAN) + MIN_POWER_MAGICIAN;
    this->durability = rand()%(MAX_DURABILITY_MAGICIAN - MIN_DURABILITY_MAGICIAN) + MIN_DURABILITY_MAGICIAN;
    this->distance = rand()%(MAX_DISTANCE_MAGICIAN - MIN_DISTANCE_MAGICIAN) + MIN_DISTANCE_MAGICIAN;
    this->cost = getPrice();
}
Shooter::Shooter(){
    this->strength = rand()%(MAX_POWER_SHOOTER - MIN_POWER_SHOOTER) + MIN_POWER_SHOOTER;
    this->durability = rand()%(MAX_DURABILITY_SHOOTER - MIN_DURABILITY_SHOOTER) + MIN_DURABILITY_SHOOTER;
    this->distance = rand()%(MAX_DISTANCE_SHOOTER - MIN_DISTANCE_SHOOTER) + MIN_DISTANCE_SHOOTER;
    this->cost = getPrice();
}

Mercenary::Mercenary(void* weapon, TypeCharacter who_i_am){
    this->weapon = weapon;
    this->who_i_am = who_i_am;
}
Mercenary::Mercenary(){
    weapon = nullptr;
    who_i_am = UNDEF;
}
int Mercenary::getCost(){
    switch (this->who_i_am){
        case SWORDMAN:
            return ((Swordsman*)this->weapon)->cost;
        case MAGICIAN:
            return ((Magician*)this->weapon)->cost;
        case SHOOTER:
            return ((Shooter*)this->weapon)->cost;
        default:
        return UNDEF;
            break;
    }
}
int Mercenary::getStrength(){
    switch (this->who_i_am){
        case SWORDMAN:
            return ((Swordsman*)this->weapon)->strength;
        case MAGICIAN:
            return ((Magician*)this->weapon)->strength;
        case SHOOTER:
            return ((Shooter*)this->weapon)->strength;
        default:
            return UNDEF;
            break;
    }
}
int Mercenary::getDurability(){
    switch (this->who_i_am){
        case SWORDMAN:
            return ((Swordsman*)this->weapon)->durability;
        case MAGICIAN:
            return ((Magician*)this->weapon)->durability;
        case SHOOTER:
            return ((Shooter*)this->weapon)->durability;
        default:
            return UNDEF;
            break;
    }
}
int Mercenary::getDistance(){
    switch (this->who_i_am){
        case SWORDMAN:
            return ((Swordsman*)this->weapon)->distance;
        case MAGICIAN:
            return ((Magician*)this->weapon)->distance;
        case SHOOTER:
            return ((Shooter*)this->weapon)->distance;
        default:
            return UNDEF;
            break;
    }
}

void Guild::seeAllMercenaryInGuild(){
    int arr_n = (int)this->our_company.size();

    std::string arr_type[arr_n];
    int arr_cost[arr_n];
    int arr_distance[arr_n];
    int arr_durability[arr_n];
    int arr_strength[arr_n];
    int num_r = 4;

    for (int i = 0; i < arr_n; i++){
        switch(this->our_company[i].who_i_am){
            case SWORDMAN:
                arr_type[i] = "swordman:";
                arr_cost[i] = ((Swordsman*)(this->our_company[i].weapon))->cost;
                arr_distance[i] = ((Swordsman*)(this->our_company[i].weapon))->distance; 
                arr_durability[i] = ((Swordsman*)(this->our_company[i].weapon))->durability; 
                arr_strength[i] = ((Swordsman*)(this->our_company[i].weapon))->strength; 

                break;

            case MAGICIAN:
                arr_type[i] = "magician:";
                arr_cost[i] = ((Magician*)(this->our_company[i].weapon))->cost;
                arr_distance[i] = ((Magician*)(this->our_company[i].weapon))->distance; 
                arr_durability[i] = ((Magician*)(this->our_company[i].weapon))->durability; 
                arr_strength[i] = ((Magician*)(this->our_company[i].weapon))->strength; 
                break;

            case SHOOTER:
                arr_type[i] = "shooter: ";
                arr_cost[i] = ((Shooter*)(this->our_company[i].weapon))->cost;
                arr_distance[i] = ((Shooter*)(this->our_company[i].weapon))->distance; 
                arr_durability[i] = ((Shooter*)(this->our_company[i].weapon))->durability; 
                arr_strength[i] = ((Shooter*)(this->our_company[i].weapon))->strength; 
                break;
            
            default:
                break;
        }
    }

    //std::cout<<"\n\n"<<this->count_mercenary<<"\n\n";
    for (int j = 0; j < arr_n; j +=num_r){
        if((arr_n-j)/4<1) num_r = arr_n%num_r;

        std::cout<<"\n";
        for (int i = 0; i < num_r; i++)
            std::cout<<i+j+1<<". "<<arr_type[i+j]<<"\t\t\t";
        std::cout<<"\n";
        for (int i = 0; i < num_r; i++)
            std::cout<<"cost = "<<arr_cost[i+j]<<"\t\t\t";
        std::cout<<"\n";
        for (int i = 0; i < num_r; i++)
            std::cout<<"distance = "<<arr_distance[i+j]<<"\t\t\t";
        std::cout<<"\n";
        for (int i = 0; i < num_r; i++)
            std::cout<<"durability = "<<arr_durability[i+j]<<" \t\t";
        std::cout<<"\n";
        for (int i = 0; i < num_r; i++)
            std::cout<<"strength = "<<arr_strength[i+j]<<"\t\t\t";
        std::cout<<"\n\n";
    }
    
}

Guild Guild::findBestTeam(int money){
    // сначала проверяем возможно ли собрать на такие деньги команду
    int min_amount_character = 5; // минимальный размер команды          
    std::vector<int> team_min_price(min_amount_character); //вектор для проверки минимальной цены

    for (int i = 0; i < min_amount_character; i++){ //заполняем первыми героями гильдии
        team_min_price[i] = this->our_company[i].getCost();
    }

    for (int i = min_amount_character; i < (int)this->our_company.size(); i++){ // проверяем остальных героев
        int price_character = this->our_company[i].getCost();

        int max_in_arr = team_min_price[0];
        int num_max_in_arr = 0;
        for (int j = 1; j < min_amount_character; j++){ // находим самую дорогую из дешевок
            if(max_in_arr<team_min_price[j]){
                max_in_arr = team_min_price[j];
                num_max_in_arr = j;
            }
        }
        
        if(price_character<max_in_arr){ // если более дешевый героем пихаем его вместо кого то в вектор
            team_min_price[num_max_in_arr] = price_character;
        }
    }
    
    int min_price_possible = 0;
    for (int i = 0; i < min_amount_character; i++){ // смотрем цену минимальное количество самых дешевых персонажей 
        min_price_possible += team_min_price[i];
    }
    
    // сравниваем поученную минимальную цену с теми деньгами что у нас есть 
    if(min_price_possible > money){ // если не хватает остальная часть кода бессмыслена, поэтому возвращаем пустой объект
        std::cout<<"\n\nIt is impossible to hire heroes for this price";
        Guild null_guild;
        return null_guild;
    } 

    

    // а тут собствено пошла жара по подбору лучшей кооманды 
    // 
    // ТРЕБОВАНИЯ К ИДЕАЛЬНОЙ TEAM:
    // max сила
    // не менее 5 челов
    // средняя и близкая дистанция обязательно (желательно дальняя но не обязательно)
    // стойкость как минимум половина от силы
    // 
    // /*
    // 1. Сначала находим команду с максимальной силой по данной цене
    //     самый простой способ перебором всех комбинаций
    //     - но в данном случае так же нужно отталкиваться от цены (количество человек)
    //     - перебором по каждому герою при этом если цена позваляет 
    //         а. если одиного героя в комнде представить как ячейку, то меняем значение в каждой ячейке как при счёте начиная справа
    //         б. если цены хватает, так же добавляем по одному человека, если опять хватает денег ещё одного
    //             (опять же все возможные комбинации "хвоста")
    //         в. можно создать рейтинг самых сильных команд, что бы потом изменять ... (но это бред излишний)
    // 2. Проверяем стойкость
    // 3. Если стойкости не хватает, 
    //     ищем героев из неиспользованных с 
    //     - минимальной разницей в силе 
    //     - максимальной разностью в стойкости
    //     - укладывающихся в цену
    // 4. Проверяем ближников и средней дистанции
    // 
    // или
    // ииииили
    // ииииииилииииии
    // ОПТИМИЗЭЙШЕН дискретных значений
    // max(sum(strenght))
    // all_cost <= money
    // sum(strenght) <= sum(durability)*2 
    // amount_people >= 5
    // amount_near_distance >= 1
    // amount_medium_distance >= 1
    // 
    // или
    // Просто перебором, где проверяем для каждого все условия, а когда получаем луччшее значение записываем его 
    //
    /*
    std::vector<Mercenary> strongest_team(min_amount_character);
    std::vector<int> strongest_team_num(min_amount_character);
    int max_strength = 0;
    
    for (int i = 0; i < min_amount_character; i++){ //заполняем первыми героями гильдии
        strongest_team[i] = this->our_company[i];
        strongest_team_num[i] = i;
    }

    int sum_price = 0;

    for (int i = 0; i < strongest_team.size(); i++){ // Считаем цену команды
        sum_price += strongest_team[i].getCost();
    }
    */
    std::vector<Mercenary> strongest_team;
    std::vector<int> strongest_team_num;
    int max_strength = 0;
    std::vector<Mercenary> best_team ;
    bruteForceTeam(strongest_team,strongest_team_num,money,best_team,max_strength);
    // Guild best_t(strongest_team,strongest_team.size());
    Guild best_t(best_team);
    
    return best_t;
    
}  
