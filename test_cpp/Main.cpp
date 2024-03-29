//------------------------------------------------------------------------------
// Main.cpp - содержит главную функцию (клиентскую часть программы), 
// обеспечивающую использование разработанных программных объектов и функций
//------------------------------------------------------------------------------

#include <iostream>
using namespace std;

#include "Container.h"

//================================================================================
// Изменение клиентского кода, обусловленного добавлением новой функциональности
//------------------------------------------------------------------------------
// Тестовая функция мультиметода, обеспечивающая обход всех комбинаций фигур,
// размещенных в контейнере.
// Задается с использованием прототипа только для требуемой функции
void MultimethodTestOut(ofstream& ofst, Container& c);
//================================================================================

//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    if(argc !=3) {
        cout << "incorrect command line! Wated: command infile outfile" << endl;
        return 1;
    }
    cout << "Files: " << argv[1] << " " << argv[2] << "\n";
    ifstream ifst(argv[1]);
    ofstream ofst(argv[2]);


    cout << "Start"<< endl;

    if (ifst.is_open())
    {
      cout << "File OPEN!\n";
    }
    else
    {
      cout << "File CLOSED\n";
      return 0;
    }
    Container c;
    Init(c);
    In(ifst, c);

    ofst << "Filled container. " << endl;
    Out(ofst, c);

    // Добавление в клиентский код вызова мультиметода
    ofst << "Test of multimethods. " << endl;
    MultimethodTestOut(ofst, c);

    ClearContainer(c);

    ofst << "Empty container. " << endl;
    Out(ofst, c);

    cout << "Stop"<< endl;
    return 0;
}