#ifndef __FigCircle__
#define __FigCircle__

#include "Figure.h"
#include "Circle.h"


CREATE_SPECIALIZATION(FigCircle, Figure, Circle);

//------------------------------------------------------------------------------
//  Функции используемые для обработки круга как специализации фигуры

void InitFigCircle(FigCircle* fc, int r);

void InFigCircle(FigCircle* fc, FILE* ifst);

void OutFigCircle(FigCircle* fc, FILE* ofst);

void DeleteFigCircle(FigCircle* pfc);

#endif
