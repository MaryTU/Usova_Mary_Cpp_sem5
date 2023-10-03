#include <iostream>
#include "include/structFigure.h"
#include <cmath>

#define PI 3.14159265

using namespace std;

const int N = 10;
const int MAX_UNITS = 100;

/*
 * Нахождение площади квадрата
 *
 * @fig элемент структуры квадрата.
 */
double squareFig(Square fig);
/*
 * Нахождение площади прямоугольника
 *
 * @fig элемент структуры прямоугольника.
 */
double squareFig(Rectangle fig);
/*
 * Нахождение площади треугольника
 *
 * @fig элемент структуры треугольника.
 */
double squareFig(Triangle fig);
/*
 * Нахождение площади круга
 *
 * @fig элемент структуры круга.
 */
double squareFig(Circle fig);


/*
 * Находит сумму всех площадей заданных фигур
 *
 * @figures данные о кажой фигуре в виде структур
 * @figure_types массив идентификаторов всех заданных фигур 
 * @N количество фигур (элементов в массиве)
 * @return площадь всех заданных фигур.
 */
double theAreaOfAllFigures(void** figures, Figure* figure_types,const int N);
/*
 * Находит количество каждого типа фигур
 *
 * @figure_types массив идентификаторов всех заданных фигур 
 * @N количество фигур (элементов в массиве)
 */
void findAmountFigures(Figure* figure_types, const int N);
/*
 * Получение от пользователя численное значение
 *
 * @phrase Фраза показывающая что нужно ввести.
 * @return Введённое с клавиатуры численное значение.
 */
double getConstInput(char* phrase);
/*
 * Показывает все данные о заданных фигурах, площадь которых превышает значение ведённое пользователем
 *
 * @figures данные о кажой фигуре в виде структур
 * @figure_types массив идентификаторов всех заданных фигур 
 * @N количество фигур (элементов в массиве)
 * @s параметр веденный пользователем
 */
void showAllFigureMoreAreaS(void** figures, Figure* figure_types,const int N, double s);
/*
 * Находит радиус окружности в которую можно вписать любую фигуру, из заданных
 *
 * @figures данные о кажой фигуре в виде структур
 * @figure_types массив идентификаторов всех заданных фигур 
 * @N количество фигур (элементов в массиве)
 * @return радиус окружности в которую можно вписать любую фигуру, из заданных.
 */
double findRadiusCircleWhereAnyFigCanBeInscribed(void** figures, Figure* figure_types,const int N);



/*
 * Генерация заданного количество произвольных фигур из доступных типов.
 *
 * @figures данные о кажой фигуре в виде структур
 * @figure_types массив идентификаторов всех заданных фигур 
 */
void generateFigures(void** figures, Figure* figure_types, const int N);



int main()
{
    srand(time(NULL));

    void* figures[N];
    Figure* figure_types = new Figure[N];

    // генерируем фигуры
    generateFigures(figures, figure_types, N);


    // // показываем все сгенерированные фигуры
    // showAllFigure(figures,figure_types,N);

    //выводим общую площадь всех фигур
    cout<<endl<<"rez all area = "<<theAreaOfAllFigures(figures,figure_types,N)<<endl;

    // вывод количества каждой фигуры
    findAmountFigures(figure_types,N);

    // вывод всех фигур с площодью большей, чем введённое значение
    char s_input_text[] = "\n Enter the minimum area for the shape = ";
    double s = getConstInput(s_input_text);
    showAllFigureMoreAreaS(figures,figure_types,N,s);

    // Найти радиус окружности в которую можно вписать все сгенерированные фигуры
    cout<<"\n\n radius total inscribed circle = "<<findRadiusCircleWhereAnyFigCanBeInscribed(figures,figure_types,N);



    // очищаем память
    for (int i = 0; i < N; i++) {
        switch (figure_types[i]) {
        case SQUARE:
            delete (Square*)(figures[i]);
            break;
        case RECTANGLE:
            delete (Rectangle*)(figures[i]);
            break;
        case TRIANGLE:
            delete (Triangle*)(figures[i]);
            break;
        case CIRCLE:
            delete (Circle*)(figures[i]);
            break;
        default:
            break;
        }
    }
    delete[] figure_types;

    return 0;
}


double squareFig(Square fig){
    return fig.side_length*fig.side_length;
}

double squareFig(Rectangle fig){
    return fig.side_length_a*fig.side_length_b;
}

double squareFig(Triangle fig){
    return 0.5*fig.side_length_a*fig.side_length_b*sin(fig.the_angle_between_a_b*PI/180);
}

double squareFig(Circle fig){
    return PI*fig.radius*fig.radius;
}



/*
void showAllFigure(void** figures, Figure* figure_types,const int N){
    for (int i = 0; i < N; i++)
    {
        if (figure_types[i]==SQUARE)
        {
            cout<<"\nSquare\na = "<<(*((Square*)figures[i])).side_length<<endl;
            cout<<"S(sq) = "<<squareFig(*((Square*)figures[i]))<<endl;
        }else if(figure_types[i]==RECTANGLE)
        {
            cout<<"\nRectangle\na = "<<(*((Rectangle*)figures[i])).side_length_a<<endl;
            cout<<"b = "<<(*((Rectangle*)figures[i])).side_length_b<<endl;
            cout<<"S(re) = "<<squareFig(*((Rectangle*)figures[i]))<<endl;
        }else if(figure_types[i]==TRIANGLE)
        {
            cout<<"\nTriangle\na = "<<(*((Triangle*)figures[i])).side_length_a<<endl;
            cout<<"b = "<<(*((Triangle*)figures[i])).side_length_b<<endl;
            cout<<"angel = "<<(*((Triangle*)figures[i])).the_angle_between_a_b<<endl;
            cout<<"S(re) = "<<squareFig(*((Triangle*)figures[i]))<<endl;   
        }else if(figure_types[i]==CIRCLE)
        {
            cout<<"\nCircle\nr = "<<(*((Circle*)figures[i])).radius<<endl;
            cout<<"S(re) = "<<squareFig(*((Circle*)figures[i]))<<endl;  
        }
        
    }
    return;
}
*/

double theAreaOfAllFigures(void** figures, Figure* figure_types,const int N){
    double rezSum = 0;
    
    for (int i = 0; i < N; i++)
    {
        if (figure_types[i]==SQUARE)
            rezSum += squareFig(*((Square*)figures[i]));
        else if(figure_types[i]==RECTANGLE)
            rezSum += squareFig(*((Rectangle*)figures[i]));
        else if(figure_types[i]==TRIANGLE)
            rezSum += squareFig(*((Triangle*)figures[i]));   
        else if(figure_types[i]==CIRCLE)
            rezSum += squareFig(*((Circle*)figures[i]));     
    }
    return rezSum;
}

void findAmountFigures(Figure* figure_types, const int N){
    int arr[4]{0,0,0,0};
    for (int i = 0; i < N; i++)
    {
        switch (figure_types[i])
        {
        case SQUARE:
            arr[SQUARE]++;
            break;
        case RECTANGLE:
            arr[RECTANGLE]++;
            break;
        case TRIANGLE:
            arr[TRIANGLE]++;
            break;
        case CIRCLE:
            arr[CIRCLE]++;
            break;
        default: break;
        }
    }

    cout<<endl<<arr[SQUARE]<<" squares";
    cout<<endl<<arr[RECTANGLE]<<" rectangles";
    cout<<endl<<arr[TRIANGLE]<<" triangles";
    cout<<endl<<arr[CIRCLE]<<" circles";

    return;
}

double getConstInput(char* phrase){
    //тут бы проверку на ввод int
    // double received_input;
    // cout << phrase;
    // cin >> received_input;
    // if (cin.fail())
    // {
    //     // user didn't input a number
    //     cin.clear(); // reset failbit - используется для сброса флага failbit 
    //     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
    //     // next, request user reinput
    // }


    // while (1) {
    //     if (cin >> received_input) {
    //         // valid number
    //         break;
    //     } else {
    //         // not a valid number
    //         cout << "Invalid Input! Please input a numerical value." << endl;
    //         cin.clear();
    //         while (cin.get() != '\n') ; // empty loop
    //     }
    // }

    double received_input;
    bool input_successful = false;

    do {
        std::cout << phrase;
        if (!(std::cin >> received_input)) {
            std::cin.clear(); // Сброс флага ошибки ввода
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Пропустить некорректный ввод
            std::cout << "Invalide input, please try again" << std::endl;
        } else {
            input_successful = true;
        }
    } while (!input_successful);


    return received_input;
}

void showAllFigureMoreAreaS(void** figures, Figure* figure_types,const int N, double s){
    double pereh = 0;
    
    for (int i = 0; i < N; i++)
    {
        if (figure_types[i]==SQUARE)
        {
            pereh = squareFig(*((Square*)figures[i]));
            if(pereh>s){
                cout<<"\nSquare\na = "<<(*((Square*)figures[i])).side_length<<endl;
            }
        }else if(figure_types[i]==RECTANGLE)
        {
            pereh = squareFig(*((Rectangle*)figures[i]));
            if(pereh>s){
                cout<<"\nRectangle\na = "<<(*((Rectangle*)figures[i])).side_length_a<<endl;
                cout<<"b = "<<(*((Rectangle*)figures[i])).side_length_b<<endl;
            }
        }else if(figure_types[i]==TRIANGLE)
        {
            pereh = squareFig(*((Triangle*)figures[i]));
            if(pereh>s){
                cout<<"\nTriangle\na = "<<(*((Triangle*)figures[i])).side_length_a<<endl;
                cout<<"b = "<<(*((Triangle*)figures[i])).side_length_b<<endl;
                cout<<"angel = "<<(*((Triangle*)figures[i])).the_angle_between_a_b<<endl;
            } 
        }else if(figure_types[i]==CIRCLE)
        {
            pereh = squareFig(*((Circle*)figures[i]));
            if(pereh>s){
                cout<<"\nCircle\nr = "<<(*((Circle*)figures[i])).radius<<endl;   
            }
        }

        if(pereh>s) cout<<"S(re) = "<<pereh<<endl;        
    }
    return;
}

double findRadiusCircleWhereAnyFigCanBeInscribed(void** figures, Figure* figure_types,const int N){
    double rez_radius = 0;
    double pereh = 0;

    for (int i = 0; i < N; i++)
    {
        switch(figure_types[i])
        {
            case SQUARE:
            {
                int side_a = (*((Square*)figures[i])).side_length;
                pereh = sqrt(2*side_a*side_a)/2;
                break;
            }
            case RECTANGLE:
            { 
                int side_a2 = (*((Rectangle*)figures[i])).side_length_a;
                int side_b2 = (*((Rectangle*)figures[i])).side_length_b;
                pereh = sqrt(2*side_a2*side_b2)/2;
                break;
            }
            case TRIANGLE:
            {
                // r = abc/(4*s) или r = c/(2*sin(ab))
                int side_a3 = (*((Triangle*)figures[i])).side_length_a;
                int side_b3 = (*((Triangle*)figures[i])).side_length_b;
                int angel = (*((Triangle*)figures[i])).the_angle_between_a_b;
                double s = squareFig(*((Triangle*)figures[i]));
                double c = sqrt(side_a3*side_a3 + side_b3*side_b3 - 2*side_a3*side_b3*cos(angel*PI/180));
                pereh = side_a3*side_b3*c/(4*s);
                break;
            }
            case CIRCLE:
            {
                pereh = (*((Circle*)figures[i])).radius;
                break;
            }
            default:
                break;
        }

        if(pereh>rez_radius)
            rez_radius = pereh;
    }

    return rez_radius;
    
}




void generateFigures(void** figures, Figure* figure_types, const int N){
    for (int i = 0; i < N; i++)
    {
        switch (rand()%N_FIGURES)
        {
        case Figure(SQUARE):
            figures[i] = new Square{rand()%MAX_UNITS+1};
            figure_types[i] = SQUARE; 
            break;
        case Figure(RECTANGLE):
            figures[i] = new Rectangle{rand()%MAX_UNITS+1,rand()%MAX_UNITS+1};
            figure_types[i] = RECTANGLE;
            break;
        case Figure(TRIANGLE):
            figures[i] = new Triangle{rand()%MAX_UNITS+1,rand()%MAX_UNITS+1,rand()%MAX_UNITS+1};
            figure_types[i] = TRIANGLE;
            break;
        case Figure(CIRCLE):
            figures[i] = new Circle{rand()%MAX_UNITS+1};
            figure_types[i] = CIRCLE;
            break;
        default:
            break;
        }
    }
    return;
}
