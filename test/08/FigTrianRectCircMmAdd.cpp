// FigTrianRectCircMmAdd.cpp - Реализация обработчиков специализаций мультиметода
// для всех комбинаций треугольника, прямоугольника и круга, добавленного уже 
// существующим обработчикам только треугольника и прямоугольника.
// Сделано в одном файле, но может быть и разнесено.

#include "FigTriangle.h"
#include "FigRectangle.h"
#include "FigCircle.h"
#include "FigMm.h"
#include <iostream>

#include "../../pplib/CreateMMSpec.h"

//------------------------------------------------------------------------------
// Функции-обработчики специализаций

//  Обработчик специализации, вычисляющий отношения между треугольником и кругом
void TrianCircOut(FigTriangle& ft1, FigCircle& fc2, ofstream &ofst) {
    ofst << "Triangle & Circle Company" << endl;
    ofst << "     ";
    Out(ft1, ofst);
    ofst << "     ";
    Out(fc2, ofst);
}

//  Обработчик специализации, вычисляющий отношения между прямоугольником и кругом
void RectCircOut(FigRectangle& fr1, FigCircle& fc2, ofstream &ofst) {
    ofst << "We have Rectangle & Circle after its" << endl;
    ofst << "     ";
    Out(fr1, ofst);
    ofst << "     ";
    Out(fc2, ofst);
}

//  Обработчик специализации, вычисляющий отношения между кругом и треугольником
void CircTrianOut(FigCircle& fc1, FigTriangle& ft2, ofstream &ofst) {
    ofst << "This Circle is before Triangle" << endl;
    ofst << "     ";
    Out(fc1, ofst);
    ofst << "     ";
    Out(ft2, ofst);
}

//  Обработчик специализации, вычисляющий отношения между кругом и прямоугольником
void CircRectOut(FigCircle& fc1, FigRectangle& fr2, ofstream &ofst) {
    ofst << "Circle + Rectanle = 4 Angles" << endl;
    ofst << "     ";
    Out(fc1, ofst);
    ofst << "     ";
    Out(fr2, ofst);
}

//  Обработчик специализации, вычисляющий отношения между двумя кругами
void CircCircOut(FigCircle& fc1, FigCircle& fc2, ofstream &ofst) {
    ofst << "2 * Circle = 8" << endl;
    ofst << "     ";
    Out(fc1, ofst);
    ofst << "     ";
    Out(fc2, ofst);
}

//------------------------------------------------------------------------------
// Функции-оболочки над обработчикаи специализаций
// Оболочка вокруг обработчика треугольника и круга
CREATE_MM_SPEC(MmTrianCircSpecOut, FigTriangle, FigCircle, TrianCircOut);

// Оболочка вокруг обработчика прямоугольника и круга
CREATE_MM_SPEC(MmRectCircSpecOut, FigRectangle, FigCircle, RectCircOut);

// Оболочка вокруг обработчика круга с треугольником
CREATE_MM_SPEC(MmCircTrianSpecOut, FigCircle, FigTriangle, CircTrianOut);

// Оболочка вокруг обработчика круга с прямоугольником
CREATE_MM_SPEC(MmCircRectSpecOut, FigCircle, FigRectangle, CircRectOut);

// Оболочка вокруг обработчика двух кругов
CREATE_MM_SPEC(MmCircCircSpecOut, FigCircle, FigCircle, CircCircOut);

//------------------------------------------------------------------------------
// Организация регистрации функции вычисления периметра, 
// обеспечивающей процедурно-параметрический полиморфизм
BEGIN_REG_MM(MultimethodFunc);
REG_MM_SPEC(MmTrianCircSpecOut, FigTriangle, FigCircle);
REG_MM_SPEC(MmRectCircSpecOut, FigRectangle, FigCircle);
REG_MM_SPEC(MmCircTrianSpecOut, FigCircle, FigTriangle);
REG_MM_SPEC(MmCircRectSpecOut, FigCircle, FigRectangle);
REG_MM_SPEC(MmCircCircSpecOut, FigCircle, FigCircle);
END_REG_MM("Registration of: Extended combinations of Triangle; Rectangle; Circle in  Multimethod"); // TODO: ADD ',' SUPPORT






