#ifndef __FigMm__
#define __FigMm__

#include "Figure.h"


//------------------------------------------------------------------------------
// Описание типа обобщенной функции, реализующей мультиметод
/*
// Указатель на функцию, реализующую мультиметод
typedef void (*MultimethodFunc)(ofstream& ofst, Figure& f1, Figure& f2);
// Описание переменной, используемой для регистрации функций вычисления периметра
extern MultimethodFunc multimethodFunc[][10];
*/

DECLARE_MM(MultimethodFunc, 10, Figure, ofstream&)

//------------------------------------------------------------------------------
//  Функция, реализующая мультиметод для двух обобщенных фигур
//void Multimethod(ofstream& ofst, Figure& f1, Figure& f2);

#endif
