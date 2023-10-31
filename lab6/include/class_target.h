/*
    Как расчитывем видимость
    1) если расстояние 5км шанс попадания 0%, если расстояние 0 шанс попадания 100%
    2) если размер 5м2 то шанс попадания 100%, если 0 то шанс 0%
    3) если материал бликующий шанс попадания, меньше чем если матовый
        как итог
        1) чем ближе и больше цель, тем легче попасть
            10м2 площадь и 0км дистанция 100% шанс
            0м2 площадь и 5км дистанция 0% шанс
            влияние 50% размера и 50% дистанции
                вычисляем 
                ((100-(distance/(max_distance/100)))/100)/2 = вероятность попадания от 0 до 0.5 в зависимости от дистанции 
                         |                   |
                         |            this 1 degree
                  это сколько процентов от максимума
                (100 - (100*distance)/max_distance)/200 = 0.5 - 0.5*distance/max_distance

                ((area/(max_area/100)/100)/2 = вероятность попадания от 0 до 0.5 взависимости от площади
                ((100*area)/max_area)/200 = 0.5*area/max_area
        2) материал влияет независимо от остальных параметров  
            допустим блик влияет на вероятность уменьшая ее на 10%
        3) следовательно суммарно шанс:
            0.5 - 0.5*distance/max_distance + 0.5*area/max_area - 0.1(если блик есть)
            если значение шанса меньше или равно нулю, то пусть шанс будет 1% (0.01)  
        
    Как расчитываем шанс попадания
    1) видимость
    2) уникальные характеристики для каждого класса
*/
const double MAX_DISTANCE = 2000; // в метрах
const double MAX_AREA = 10; // в метрах квадратных
const double MIN_AREA = 0.0001; // 1 см^2 
const double REDUCING_CHANCE_OF_BLICK = 0.1; // 10%

// движущееся цели уменьшают шанс на 20%, если максимальная скорость и 0% если нет скорости
// (rand()%((int)MAX_SPEED + 1 - (int)MIN_SPEED)/(MAX_SPEED/20))/100 -> (20*rand()%((int)MAX_SPEED + 1 - (int)MIN_SPEED)/MAX_SPEED )/100 = 0.2*rand()%((int)MAX_SPEED + 1 - (int)MIN_SPEED)/MAX_SPEED 
const double RIGHT_LEFT_MOVING_REDUCING_CHANCE = 0.15; 
// движущиеся вперед назад изменяется дистанция и их шанс на попадание (а также вперед назад)
const double MAX_SPEED = 10; // м/с
const double MIN_SPEED = 1; // м/с
// а при появляющейся исчезающей мишени то 100% то 0% в зависимости от времени
const int MAX_TIME = 20; // с
const int MIN_TIME = 2; // с


const double MAX_HEALTH = 2500;
const double MIN_HEALTH = 1000;

const int AMOUNT_TYPE_FORM = 5;
const int AMOUNT_TYPE_MATERIAL = 2;

enum FormFactor{
    CIRCLE,
    SCUARE,
    TRIANGLE,
    ELLIPSE,
    RANDOM_FIGURE, // просто случайно выберем площадь
};

enum Material{
    BLICK,
    NOT_BLICK,
};

// абстрактный класс
class Target
{
    protected:
        int distance_to_target;
        double size_target;
        FormFactor form_factor;
        Material material;
        double hit_chance;
        
        /*
            // расчётные параметры
            int size; // размер мишени
            int visibility_target; // видимость мишени на стрельбище
        */

        int health_point;     
        bool available;   
        // double visibility_target; // от 0 до 1 бесполезный параметр так как используется только для расчета вероятности попадания


    public:
        Target();
        //virtual ~Target() = 0;

        virtual double getChanceHitTarget(int time_from_start) = 0; //время произошедшее с начала прихода в тир
        virtual void getDamage(int damage) = 0;
        virtual bool isAvailable() = 0;

        virtual void view_data()=0;

};

Target::Target(){}


/*
    Какие могут быть мишени, как дочернии классы:
        - движущиеся вправо/влево (имееют горизонтальную скорость)
        - движущиеся вперед/назад (имеют скорость прибижения/отдаления)
        - появляющиеся/исчезающие (имеют время показывания и исчезновения)
        - (опционально статические (имеют наклон))
        - (и необязательно крутящиеся)
        - (и необязательно можно взять смешенные)
        - (так же необязательно можно сделать так, что есть места на мешенях за которых очки больше типо органы животых для мишеней с животными)
*/