#ifndef __FigCircle__
#define __FigCircle__

#include "Figure.h"
#include "Circle.h"


CREATE_SPECIALIZATION(FigCircle, Figure, Circle);

//------------------------------------------------------------------------------
//  Функции используемые для обработки круга как специализации фигуры

void Init(FigCircle& fc, int r);

void In(FigCircle& fc, ifstream &ifst);

void Out(FigCircle& fc, ofstream &ofst);

void DeleteFigCircle(FigCircle& pfc);

#endif
