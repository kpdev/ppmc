// FigTrianRectMm.cpp - Реализация обработчиков специализаций мультиметода
// для всех комбинаций треугольника и прямоугольника
// сделано в одном файле, но может быть и разнесено

#include "FigTriangle.h"
#include "FigRectangle.h"
#include "FigMm.h"
#include <iostream>


//------------------------------------------------------------------------------
// Функции-обработчики специализаций

//  Обработчик специализации, вычисляющий отношения между двумя треугольниками
void TrianTrianOut(FigTriangle& ft1, FigTriangle& ft2, ofstream &ofst) {
    ofst << "This is two Triangles" << endl;
    ofst << "     ";
    Out(ft1, ofst);
    ofst << "     ";
    Out(ft2, ofst);
}

//  Обработчик специализации, вычисляющий отношения между треугольником и прямоугольником
void TrianRectOut(FigTriangle& ft1, FigRectangle& fr2, ofstream &ofst) {
    ofst << "We have Triangle and Rectangle" << endl;
    ofst << "     ";
    Out(ft1, ofst);
    ofst << "     ";
    Out(fr2, ofst);
}

//  Обработчик специализации, вычисляющий отношения между прямоугольником и треугольником
void RectTrianOut(FigRectangle& fr1, FigTriangle& ft2, ofstream &ofst) {
    ofst << "The first figure is Rectangle and second is Triangle" << endl;
    ofst << "     ";
    Out(fr1, ofst);
    ofst << "     ";
    Out(ft2, ofst);
}

//  Обработчик специализации, вычисляющий отношения между двумя прямоугольниками
void RectRectOut(FigRectangle& fr1, FigRectangle& fr2, ofstream &ofst) {
    ofst << "Rectangle + Rectangle = Two Rectangles" << endl;
    ofst << "     ";
    Out(fr1, ofst);
    ofst << "     ";
    Out(fr2, ofst);
}

//------------------------------------------------------------------------------
// Функции-оболочки над обработчикаи специализаций

// Оболочка вокруг обработчика двух треугольников
CREATE_MM_SPEC(MmTrianTrianSpecOut, FigTriangle, FigTriangle, TrianTrianOut);

// Оболочка вокруг обработчика треугольника с прямоугольником
CREATE_MM_SPEC(MmTrianRectSpecOut, FigTriangle, FigRectangle, TrianRectOut);

// Оболочка вокруг обработчика прямоугольника с треугольником
CREATE_MM_SPEC(MmRectTrianSpecOut, FigRectangle, FigTriangle, RectTrianOut);

// Оболочка вокруг обработчика двух прямоугольников
CREATE_MM_SPEC(MmRectRectSpecOut, FigRectangle, FigRectangle, RectRectOut);

//------------------------------------------------------------------------------
// Организация регистрации функции вычисления периметра, 
// обеспечивающей процедурно-параметрический полиморфизм

BEGIN_REG_MM(MultimethodFunc);
REG_MM_SPEC(MmTrianTrianSpecOut, FigTriangle, FigTriangle);
REG_MM_SPEC(MmTrianRectSpecOut, FigTriangle, FigRectangle);
REG_MM_SPEC(MmRectTrianSpecOut, FigRectangle, FigTriangle);
REG_MM_SPEC(MmRectRectSpecOut, FigRectangle, FigRectangle);
END_REG_MM("Registration of: Different combination of Triangle and Rectangle in  Multimethod");














