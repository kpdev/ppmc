#ifndef __FigRectangle__
#define __FigRectangle__

#include "Figure.h"
#include "Rectangle.h"



CREATE_SPECIALIZATION(FigRectangle, Figure, Rectangle);

//------------------------------------------------------------------------------
//  Функции используемые для обработки прямоугольника как специализации фигуры

// Инициализация существующей фигуры-прямоугольника
void Init(FigRectangle& fr, int x, int y);

// Ввод специализации фигуры-прямоугольника из потока
void In(FigRectangle& fr, ifstream &ifst);

// Вывод специализации фигуры-прямоугольника в поток
void Out(FigRectangle& fr, ofstream &ofst);

// Удаление специализации фигуры-прямоугольника
void DeleteFigRectangle(FigRectangle& fr);

#endif
