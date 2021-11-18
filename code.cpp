#include <iostream>
#include <string>
#include <math.h>
float criteria[50][50];
//string name_criteria[50];
int quantity;
int shift = 0;

using namespace std;

int line_amount(float criteria[50][50], int quantity)//функция находит сумму строки, и сумму сумм строк
{
    for (int j = 0; j < quantity; j++)// цикл находит сумму строки
    {
        for (int i = 0; i < quantity; i++)
        {
            criteria[quantity][j] = criteria[quantity][j] + criteria[i][j];
        }
    }
    for (int k = 0; k < quantity; k++)//цикл находит сумму сумм строк
    {
        criteria[quantity][quantity] = criteria[quantity][quantity] + criteria[quantity][k];
        
    }
    return 0;
    
}

int most(float criteria[50][50], int quantity, float maximum, int index)//функция находит максимальный весовой коэфициент
{
    maximum = criteria[quantity + 1][0];
    for (int g = 1; g < quantity; g++)
    {
        if (maximum < criteria[quantity + 1][g] )
        {
            maximum = criteria[quantity + 1][g];
            index = g;
        }
    }
    return 0;    
}
 
int weight_coefficients(float criteria[50][50], int quantity)//функция находит весовые коэфициенты
{
    float surplus;//остаток или избыток от суммы весовых коэфициентов 
    float maximum;//максимальный весовой коэфициент
    int index;//индекс максимального весового коэфициента
    
    for (int k = 0; k < quantity; k++)//цикл находит весовые коэфициенты
    {
        criteria[quantity + 1][k] = criteria[quantity][k] / criteria[quantity][quantity];
        criteria[quantity + 1][k] = round(criteria[quantity + 1][k]*100)/100;
    }
    for (int s = 0; s < quantity; s++)//цикл находит сумму весовых коэфициентов
    {
        criteria[quantity + 1][quantity] = criteria[quantity + 1][quantity] + criteria[quantity + 1][s];     
    }
    surplus = criteria[quantity + 1][quantity] - 1;
    
    if ((surplus > 0) || (surplus < 0))//лог.оператор определяет, есть ли избыток или недостаток
    {
        most(criteria, quantity, maximum, index);
        criteria[quantity + 1][index] = criteria[quantity + 1][index] - surplus;
    }
    return 0;    
}


int input(float criteria[50][50], int quantity, int shift)//функция ввода таблицы
{   
    for (int j = 0; j < quantity - 1; j++)//цикл введения с клавиатуры 
    {
        for (int i = 1 + shift; i < quantity; i++)
        {
            cin >> criteria[i][j];
            criteria[i][j] = round(criteria[i][j]*100)/100;
            criteria[j][i] = 1 / criteria[i][j];//заполнение второй половины таблицы
            criteria[j][i] = round(criteria[j][i]*100)/100;
        }
        shift++;//переменная сдвигающая элементы, каждую итерацию
    }
    for (int g = 0; g < quantity; g++)//цикл заполняет диогональ таблицы единицами
        criteria[g][g] = 1;
    return 0;
}

int output(float criteria[50][50], int quantity)//функция вывода таблицы
{
    for (int s = 0; s <= quantity  ; s++)
    {
        for (int k = 0; k <= quantity + 1 ; k++)
        {
            cout <<"|";
            cout.width(5);
            cout <<  criteria[k][s];
            cout <<"|";  
        }
        cout << endl;
    }
    return 0;
}

int main()
{
    cout<<"Введите кол-во критериев: ";
    cin >> quantity;
    /*for (int f = 0; 0 < quantity; f++)
    {
        cout << "Введите название критерия "<<f + 1<<": ";
        cin >> name_criteria[f];   
    }*/
    input(criteria, quantity, shift);
    line_amount(criteria, quantity);
    weight_coefficients(criteria, quantity);
    output(criteria, quantity);
    return 0;
}

