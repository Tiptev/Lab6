#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
float criteria[50][50];//коэфициент критерия
char name_criteria[50][50];//название критерия
int quantity ;//кол-во критериев
int shift = 0;//сдвиг 
char inerr[50];//переменная для обнаружения ошибки ввода
int choice;//счетчик ошибок ввода

using namespace std;

int line_amount(float criteria[50][50], int quantity)//функция находит сумму строки, и сумму сумм строк
{
    for (int j = 0; j < quantity; j++)// цикл находит сумму строки
    {
        for (int i = 0; i < quantity; i++)
            criteria[quantity][j] = criteria[quantity][j] + criteria[i][j];
    }
    for (int k = 0; k < quantity; k++)//цикл находит сумму сумм строк
        criteria[quantity][quantity] = criteria[quantity][quantity] + criteria[quantity][k];
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
        criteria[quantity + 1][quantity] = criteria[quantity + 1][quantity] + criteria[quantity + 1][s];     
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
    cout << "Заполните таблицу Томаса Саати. Вводите по одному числу. От 1-го до 9-ти.";
    cout << "  1 - равная важность;"<<endl;
    cout << "  3 - умеренное превосходство одного над другим;"<<endl;
    cout << "  5 - существенное превосходство одного над другим;"<<endl;
    cout << "  7 - значительное превосходство одного над другим;"<<endl;
    cout << "  9 - очень сильное превосходство одного над другим;"<<endl;
    cout << "  2, 4, 6, 8 - соответствующие промежуточные значения."<<endl;
    for (int j = 0; j < quantity - 1; j++)//цикл введения с клавиатуры 
    { 
        for (int i = 1 + shift; i < quantity; i++)
        {
            cout <<"Введите коэфициент отношнения ' ";
            for (int c = 0; c < 4; c++)//цикл выводит назване критерия
                cout << name_criteria[j][c];
            cout << " ' к ' ";
            for (int d = 0; d < 5; d++)//цикл выводит назване критерия
                cout << name_criteria[i][d];
            cout << " ' : ";
            for(;;)//цикл проверяет есть ли ошибка при вводе коэфициента
            {
                choice = 0;//переменная считает ошибки
                cin.getline(inerr,50);
                for (int l = 0; l < 50; l++)
                { 
                    switch(inerr[l])
                    {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':
                        case '.':
                        case '\0':
                            break;
                            
                        default:
                            choice++;
                            break;
                    }
                }
                if (choice == 0)//если ошибок нет
                {
                    criteria[i][j] = atof(inerr);//char в float
                    choice = 0;
                    if (criteria[i][j] > 0 && criteria[i][j] <= 9)//коэфициент входит в возможный диапазон?
                        break;
                    else
                    {
                        cout << "   Коэфициент должен находиться в диапазоне от 1-го до 9-ти! "<<endl;
                        cout << "Введите коэфициент: ";
                    }
                }
                if (choice != 0)//если ошибки есть
                {
                    cout << "   Вы можете ввести коэфициенты от 1-го до 9-ти! Помните, что дробные коэфициенты вводятся через запятую!";
                    cout << endl << "Введите коэфициент: ";
                    choice = 0;
                    continue;
                }
            }
            criteria[i][j] = round(criteria[i][j]*100)/100;//округляет число до 2-ух знаков после запятой
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
    cout<< endl <<"    ";
    for (int f = 0; f < quantity; f++)//вывод названия критерия
    {
        cout <<"|";
        for (int d = 0; d < 5; d++)
        {   
            if(name_criteria[f][d] != '\0')
                cout <<  name_criteria[f][d]; 
            else
                cout << " ";     
        }
        cout <<"|";    
    }
    cout <<"|Сумма||Коэф.|"<< endl;
    for (int s = 0; s <= quantity  ; s++)
    {   
        for (int i = 0; i < 4; i++)//вывод названия критерия
        {   
            if(name_criteria[s][i] != '\0')
                cout << name_criteria[s][i];
            else
                cout << " ";
        }
        for (int k = 0; k <= quantity + 1 ; k++)//вывод коэфициентов критерия
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

int title(char name_criteria[50][50], int quantity)
{   
    cout <<endl<<"  Введите названия критериев, которые вы хотите сравнить."<< endl; 
    cout <<"Название критерия состоит из 4-ех символов, вы можете вводить симмволы латиницей, кириллицей, а также цифры."<<endl; 
    cout <<"В случае, если вы введете больше 4-ех символов, программа будет игнорировать последующие, начиная с 5-го символа."<< endl;
    for(int i = 0; i < quantity; i++)
    {
        cout <<endl<< " Название критерия №" << i + 1  << ": ";
        cin.getline(name_criteria[i],50);
    }
    return 0;
}


int main()
{   
    for (;;)
    {   
        choice = 0;
        cout<<"\nВведите кол-во критериев: ";
        cin.getline(inerr,50);
        for (int i = 0; i < 50; i++)
        { 
            switch(inerr[i])
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '\0':
                    break;
                    
                default:
                    choice++;
                    break;
            }
        }
        if (choice == 0)
        {
            quantity = atoi(inerr);//char в int
        }
        else 
            cout << "Вы ввели недопустимый символ!";
        
        if (quantity > 50)//если ввели больше 50-ти критериев
            cout << endl <<"   Максимальное кол-во критериев = 50!"<<endl;
        else if ((quantity < 2) && (quantity >= 0) && (choice == 0) )//если ввели 1 или 2 критерия
            cout << endl <<"   Что бы сравнить критерии, их должно быть, как минимум 2-а!"<<endl;
        else if(choice != 0)
            continue;
        else
            break;
    }
    title(name_criteria, quantity);
    input(criteria, quantity, shift);
    line_amount(criteria, quantity);
    weight_coefficients(criteria, quantity);
    output(criteria, quantity);
    return 0;
}