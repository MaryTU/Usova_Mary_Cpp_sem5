#include <cmath>
#include "include/character.h"


using namespace std;

/**
 * @brief Создание гильдии из случайных наемников, так что бы в гильдии были наемники всех типов, при этом был хотя бы один мечник танк, хотя бы один мечник наносящий значительный урон, маги и стрелки средних и дальних дистанций.
 * 
 * @return Guild 
 */
Guild createGuild();

/**
 * @brief Создание пользователем команды из представленных героев
 * 
 * @param Гильдия с персонажами
 * @return команду выбраннцю пользователем из приведенной гильдии
 */
Guild getTeam(Guild my_guild);

/**
 * @brief Получение от пользователя целое численное значение
 * 
 * @param phrase Фраза показывающая что нужно ввести.
 * @return Введённое с клавиатуры целое численное значение.
 */
int getConstInputInt(char* phrase);

int main()
{
    srand(time(NULL));
    

    Guild my_guild = createGuild();
    my_guild.seeAllMercenaryInGuild();

    Guild my_groupe = getTeam(my_guild);

    char phrase_for_money[] = "Money: ";
    int money = getConstInputInt(phrase_for_money);
    cout<<"\n\nThe best team in guild for "<<money<<" coin\n";
    
    Guild best_team = my_guild.findBestTeam(money);
    best_team.seeAllMercenaryInGuild();
    
    int mcp = 0,stro = 0, durb = 0;
    for (int i = 0; i < (int)best_team.getAllMercenary().size(); i++){
        mcp+=best_team.getAllMercenary()[i].getCost();
        stro+=best_team.getAllMercenary()[i].getStrength();
        durb+=best_team.getAllMercenary()[i].getDurability();
    }
    cout<< "\nwhole cost = "<<mcp;
    cout<< "\nwhole strength = "<<stro;
    cout<< "\nwhole durability = "<<durb;
    return 0;
}



Guild createGuild(){
    
    //bool all_t_ch[]{false,false,false};
    bool avarage_shoot = false;
    bool avarage_mag = false;
    bool far_shoot = false;
    bool far_mag = false;
    bool tank = false;
    bool significant_sword = false;
    
    vector<Mercenary> many_mercenary;
 
    while(
            !(
                avarage_mag &
                avarage_shoot &
                far_mag &
                far_shoot &
                tank &
                significant_sword
            )
        ){

        void* a;
        TypeCharacter rand_type = (TypeCharacter)(rand()%3);
        switch (rand_type)
        {
        case SWORDMAN:
            a = new Swordsman;

            if( ((Swordsman*)a)->durability>=SWORDMAN_TANK_DURABILITY )
                tank = true;
            if( ((Swordsman*)a)->strength>=SWORDMAN_SIGNIFICANT_DAMAGE )
                significant_sword = true;

            break;
        case MAGICIAN:
            a = new Magician;

            if( ((Magician*)a)->distance>=LOWER_BOUND_FAR_DISTANSE)
                far_mag = true;
            if( 
                ((Magician*)a)->distance >= LOWER_BOUND_AVARAGE_DISTANSE &&
                ((Magician*)a)->distance <= HIGHT_BOUND_AVARAGE_DISTANSE
                )
                avarage_mag = true;

            break;
        case SHOOTER:
            a = new Shooter;

            if( ((Shooter*)a)->distance>=LOWER_BOUND_FAR_DISTANSE)
                far_shoot = true;
            if( 
                ((Shooter*)a)->distance >= LOWER_BOUND_AVARAGE_DISTANSE &&
                ((Shooter*)a)->distance <= HIGHT_BOUND_AVARAGE_DISTANSE
                )
                avarage_shoot = true;

            break;
        default:
            break;
        }

        many_mercenary.push_back(Mercenary(a, rand_type));
    }
    
    
    Guild g(many_mercenary);
    return g;
}

int getConstInputInt(char* phrase){
    //тут бы проверку на ввод int
    int received_input;
    cout << phrase;
    cin >> received_input;
    if (cin.fail())
    {
        // user didn't input a number
        cin.clear(); // reset failbit - используется для сброса флага failbit 
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
        // next, request user reinput
    }
    
    return received_input;
}

Guild getTeam(Guild my_guild){ 
    
    Guild my_team;
    vector<int> proverka;
    int arr_n = 0;

    char phrase[] = "Select the characters that you like by entering a number (enter zero if you have finished selecting characters for the team): ";

    int num = getConstInputInt(phrase);
    bool gege = false;
    while(num != 0){    
        if(num > (int)my_guild.getAllMercenary().size()){
            gege = true;
        }else{
            for (int i = 0; i < arr_n; i++){
                if (num == proverka[i]){
                    gege = true;
                    break;
                }            
            }
        }    
        
        
        if(gege){
            cout<<"\n!!!Have you already chosen this character or does such a character not exist!!!\n\n";
            gege = false;
        }else{
            arr_n++;
            proverka.push_back(num);
            my_team.addNewMercenary(my_guild.getAllMercenary()[num-1]);
        }

        cout<<"Youre team:\n";
        my_team.seeAllMercenaryInGuild();

        num = getConstInputInt(phrase);
    }//while(num != 0);
    
    return my_team;
}

