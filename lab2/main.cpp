#include <iostream>
#include <cmath>

using namespace std;

/*
 * Получение от пользователя целое численное значение
 *
 * @param Фраза показывающая что нужно ввести.
 * @return Введённое с клавиатуры целое численное значение.
 */
int getConstInputInt(char* phrase);

/*
 * Выводит на экран массив целочисленных значений
 *
 * @param *arr указатель на нужный массив.
 * @param n размер нужного массива.
 */
void print2NArray(int** arr, int n);

/*
 * Восстановление прямого порядка
 *
 * @param **arr указатель на нужный двумерный массив.
 * @param n размер нужного массива.
 */
void directOrderOfValues(int** arr, int n);

/*
 * Получение обратного порядок элементов
 *
 * @param **arr указатель на нужный двумерный массив.
 * @param n размер нужного массива.
 */
void reverseOrderOfElements(int** arr, int n);

/*
 * Получение матрицы, где порядок элементов такой, что они выложены вдоль побочной диагонали
 *
 * @param **arr указатель на нужный двумерный массив.
 * @param n размер нужного массива.
 */
void orderAlongTheSideDiagonal(int** arr, int n);

/*
 * Получение матрицы, отраженной по горизонтали
 *
 * @param **arr указатель на нужный двумерный массив.
 * @param n размер нужного массива.
 */
void horizontalReflectionOfTheArray(int** arr, int n);

/*
 * Получение матрицы, с числами от одного до n*n выложенных по спирали по часовой стрелке
 *
 * @param **arr указатель на нужный двумерный массив.
 * @param n размер нужного массива.
 */
void getTheSpiralClockwise(int** arr, int n);

int main()
{
    char size_question[] = "\nEnter the size of the two-dimensional array = ";
    int n = getConstInputInt(size_question);
    
    int** arr_nn = new int* [n];
    for (int i = 0; i < n; i++){
        arr_nn[i] = new int[n];
    }

    //заполняем массив значениями от 1 до n*n
    directOrderOfValues(arr_nn, n);
    print2NArray(arr_nn, n);


    char text_for_choise[] = "\nSelect an action with an array:\n1. Restore the direct order of the elements.\n2. Make the reverse order of the elements (i.e. the element [N - 1][N - 1] will have the value 1)\n3. Make the order of the elements so that they are laid out along the main diagonal.\n4. Make the order of the elements so that they are laid out along the side diagonal.\n5. Make the order of the elements such that all values spiral clockwise from the element [0,0].\n6. Exit.\n\n Your choise: ";

    int num_for_choise = getConstInputInt(text_for_choise);

    while (num_for_choise!=6)
    {
        switch (num_for_choise)
        {
            case 1:
                //заполняем массив значениями от 1 до n*n
                directOrderOfValues(arr_nn, n);
                break;
            case 2:
                //инвертируем массив и выводим от n*n до 1
                directOrderOfValues(arr_nn, n);
                reverseOrderOfElements(arr_nn, n);
                break;
            case 3:
                //элементы вдоль главной диагонали
                orderAlongTheSideDiagonal(arr_nn,n);
                horizontalReflectionOfTheArray(arr_nn,n);
                break;
            case 4:
                //массив со значениями от 1 до n*n вдоль побочной диагонали
                orderAlongTheSideDiagonal(arr_nn,n);
                break;
            case 5:
                //спиралька
                getTheSpiralClockwise(arr_nn, n);
                break;
            default:
                cout<<"\nYou have entered an invalid value, try again\n";
                break;
        }
        print2NArray(arr_nn,n);

        num_for_choise = getConstInputInt(text_for_choise);
    }

    for (int i = 0; i < n; i++)
        delete[] arr_nn[i];
    
    delete[] arr_nn;
    
    //cout<<*(*(arr_nn)+3);
    // сначала внутренние массивы, потом внешние

    return 0;
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

void print2NArray(int** arr, int n){
    for (int j = 0; j < n; j++){
        for (int i = 0; i < n; i++)
            cout<<arr[j][i]<<'\t';
        cout<<endl;
    }    
    cout<<endl;
    return; 
}

void directOrderOfValues(int** arr, int n){
    for (int j = 0; j < n; j++)
        for (int i = 0; i < n; i++)
            arr[i][j] = j + 1 + i*n;
    return; 
}

void reverseOrderOfElements(int** arr, int n){

    int new_n; 
    new_n = (n%2==1) ? (n*n-1)/2 : n*n/2;

    for (int i = 0; i < new_n; i++)
    {        
        int i_x = i%n;
        int i_y = (i - i_x)/n;
        int pereh_x = *(*(arr+i_y)+i_x);
        *(*(arr+i_y)+i_x) = *(*(arr+n-1-i_y)+n-1-i_x); 
        *(*(arr+n-1-i_y)+n-1-i_x) = pereh_x;
    }
        
    return; 
}

void orderAlongTheSideDiagonal(int** arr, int n){
    if(n==1)return;

    int num = 1;
    int coor_x = 0, coor_y = 0;

    *(*(arr+coor_y)+coor_x) = num;
    num++;coor_y++;

    while(true){
        //arr[coor_x][coor_y] = num;
        *(*(arr+coor_y)+coor_x) = num;
        num++;

        if(coor_x==n-1 && coor_y==n-1) break;

        do{
            coor_y--;
            coor_x++;
            //arr[coor_x][coor_y] = num;
            *(*(arr+coor_y)+coor_x) = num;
            num++;            
        }while(coor_y!=0 && coor_x!=n-1);    

        coor_y++;
        while(coor_y!=n-1 && coor_x!=0){
            coor_y++;
            coor_x--;
        }
    }
    
    /*
    y;x
    y+1;x       y-1;x+1
    y+2;x-1     y-1;x+1     y-1;x+1
    y+3;x-2     y-1;x+1     y-1;x+1     y-1;x+1
    y+4;x-3     y-1;x+1     y-1;x+1     y-1;x+1     y-1;x+1
    y+4;x-3     y-1;x+1     y-1;x+1     y-1;x+1
    y+3;x-2     y-1;x+1     y-1;x+1
    y+2;x-1     y-1;x+1
    y+1;x
    */
    
    return;    
}

void horizontalReflectionOfTheArray(int** arr, int n){
    if(n==1) return;

    int half_n = (n%2==0) ? (n/2) : ((n-1)/2);

    for (int i = 0; i < half_n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int c;
            c = arr[i][j];
            arr[i][j] = arr[n-i-1][j];
            arr[n-i-1][j] = c;
        }
        
    }

    return;
}

void getTheSpiralClockwise(int** arr, int n){
    if(n==1)return;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j]=0; //заполняем ноликами

    int num = 1;

    unsigned short orientation = 1;//1-вправо 2-вниз 3-влево 4 вверх
    int coor_x = 0, coor_y = 0;
    arr[0][0]=num;num++;

    while (true)
    {
        if(
            (arr[coor_y][coor_x+1] != 0 || coor_x+1 == n) &&
            (coor_y+1 == n || arr[coor_y+1][coor_x] != 0) &&
            (arr[coor_y][coor_x-1] != 0 || coor_x-1 == -1) &&
            (arr[coor_y-1][coor_x] != 0 || coor_y-1 == -1) 
        ) return;

        switch (orientation)
        {
            case 1:
                if(arr[coor_y][coor_x+2] != 0 || coor_x+2 == n)
                    orientation = 2;
                coor_x++;
                break;
            case 2:
                if(coor_y+2 == n || arr[coor_y+2][coor_x] != 0)
                    orientation = 3;
                coor_y++;
                break;
            case 3:
                if(arr[coor_y][coor_x-2] != 0 || coor_x-2 == -1)
                    orientation = 4;
                coor_x--;
                break;
            case 4:
                if(arr[coor_y-2][coor_x] != 0 || coor_y-2 == -1)
                    orientation = 1;
                coor_y--;
                break;
            default:
                break;
        }

        arr[coor_y][coor_x] = num;
        num++;
        //print2NArray(arr,n);
    }
 
}