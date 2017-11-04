#ifndef __FigCircle__
#define __FigCircle__

#include "Figure.h"
#include "Circle.h"


CREATE_SPECIALIZATION(FigCircle, Figure, Circle);

FUNC_TES(Init, void, FigCircle);
FUNC_TES(In, void, FigCircle, ifstream&);
FUNC_TES(Out, void, FigCircle, ofstream&);
FUNC_TES(DeleteFigCircle, void, FigCircle);

//------------------------------------------------------------------------------
//  Функции используемые для обработки круга как специализации фигуры

// Инициализация существующей фигуры-круга
//void Init(FigCircle& fc, int r);


// Ввод специализации фигуры-круга из потока
//void In(FigCircle& fc, ifstream &ifst);

// Вывод специализации фигуры-круга в поток
//void Out(FigCircle& fc, ofstream &ofst);

// Удаление специализации фигуры-прямоугольника
//void DeleteFigCircle(FigCircle& pfc);

#endif
