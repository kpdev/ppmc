//------------------------------------------------------------------------------
// Main.cpp - содержит главную функцию (клиентскую часть программы), 
// обеспечивающую использование разработанных программных объектов и функций
//------------------------------------------------------------------------------

#include <stdio.h>

#include "Container.h"


//================================================================================
// Изменение клиентского кода, обусловленного добавлением новой функциональности
//------------------------------------------------------------------------------
// Тестовая функция мультиметода, обеспечивающая обход всех комбинаций фигур,
// размещенных в контейнере.
// Задается с использованием прототипа только для требуемой функции
void MultimethodTestOut(FILE* ofst, Container* c);
//================================================================================

//------------------------------------------------------------------------------

// TODO: REPLACE C++ TO PLAIN C
int main(int argc, char* argv[])
{
    if(argc != 3) {
        printf("incorrect command line! Waited: command infile outfile\n");
        return 1;
    }
    printf("Files: %s %s\n", argv[1], argv[2]);
    FILE* ifst;
    FILE* ofst;
    errno_t ifsterr = fopen_s(&ifst, argv[1], "rw");
    errno_t ofsterr = fopen_s(&ofst, argv[2], "rw");

    printf("Start\n");

    if (ifsterr != 0 || ofsterr != 0)
    {
      printf("ERROR. Files cannot be opened\n");
      return 1;
    }

    Container c;
    Init(&c);
    In(ifst, &c);

    printf("Filled container.\n");
    Out(ofst, &c);

    // Добавление в клиентский код вызова мультиметода
    printf("Test of multimethods.\n");
    MultimethodTestOut(ofst, &c);

    ClearContainer(&c);

    printf("Empty container.\n");
    Out(ofst, &c);

    printf("Stop\n");

    fclose(ofst);
    fclose(ifst);
    return 0;
}