#ifndef __FigTriangle__
#define __FigTriangle__

#include "Figure.h"
#include "Triangle.h"


CREATE_SPECIALIZATION(FigTriangle, Figure, Triangle);

//------------------------------------------------------------------------------
//  Функции используемые для обработки треугольника как специализации фигуры

// Инициализация существующей фигуры-треугольника
void Init(FigTriangle& ft, int a, int b, int c);

// Ввод специализации фигуры-треугольника из потока
void In(FigTriangle& ft, ifstream &ifst);

// Вывод специализации фигуры-треугольника в поток
void Out(FigTriangle& ft, ofstream &ofst);

// Удаление специализации фигуры-треугольника
void DeleteFigTriangle(FigTriangle& pft);

#endif
