// FigTriangle.cpp - Реализация функций, осуществляющих обработку треугольника

#include <iostream>
#include "FigTriangle.h"

#include "../../pplib/CreateRegMarkMethod.h"
#include "../../pplib/RegisterSpecialization.h"
#include "../../pplib/RegisterMethod.h"

/*
namespace {
    // Признак, зарегистрированный для данной фигуры (вместо глобальной переменной)
    int regMark = -1;
}

// Функция возвращающая значение признака для зарегистрированной фигуры
int GetRegMarkFigTriangle() {
    return regMark;
}

namespace {
    // Класс, обеспечивающий регистрацию данной фигуры-специализации
    class RegFigTriangle {
    public:
        RegFigTriangle(const char* regInfo) {
            cout << regInfo << endl;
            regMark = GetSpecNumAndIncrement();
            cout << "    FigTriangle was registered using number " << regMark << endl;
        }
    };

    RegFigTriangle regFigTriangle("Registration of: FigTriangle");
}
*/

CREATE_REG_MARK_METHOD(FigTriangle);
REGISTER_SPECIALIZATION(Figure, FigTriangle, "Registration of: FigTriangle");

//------------------------------------------------------------------------------
//  Функции используемые для обработки треугольника как специализации фигуры

// Инициализация существующей фигуры-треугольника
void Init(FigTriangle& ft, int a, int b, int c) {
    ft.mark = GetRegMarkFigTriangle();
    Triangle& t = ft._spec;
    Init(t, a, b, c);
}

// Создание фигуры-треугольника без инициализации сторон
FigTriangle* CreateFigTriangle() {
    FigTriangle* pft = new FigTriangle;
    Init(*pft, 0, 0, 0);
    return pft;
}

// Создание фигуры-треугольника с инициализаций сторон
FigTriangle* CreateFigTriangleAndInit(int a, int b, int c) {
    FigTriangle* pft = CreateFigTriangle();
    Init(*pft, a, b, c);
    return pft;
}

// Ввод специализации фигуры-треугольника из потока
void In(FigTriangle& ft, ifstream &ifst) {
    Triangle& t = ft._spec;
    In(ifst, t);
}

// Вывод специализации фигуры-треугольника в поток
void Out(FigTriangle& ft, ofstream &ofst) {
    ofst << "Triangle is as Specialization of Figure: a = " << ft._spec.a 
         << ", b = " << ft._spec.b << ", c = " << ft._spec.c << endl;
}

// Удаление специализации фигуры-треугольника
void DeleteFigTriangle(FigTriangle& pft) {
    delete &pft;
}

//=============================================================================
// Функции - оболочки, используемые для параметризации данной специализации,
// Регистрируемые в соответствующих параметрических массивах
//=============================================================================


REGISTER_METHOD_WITH_CHECK_RET_PTR(CreateFigureUseFileMark, CreateFigTriangle, FigTriangle, "Registration of CreateFigTriangleUseFileMark", 2, Figure);
REGISTER_METHOD_WITH_CHECK(InFigureValue, In, "Registration of InFigTriangleValue", FigTriangle, ifstream&);
REGISTER_METHOD_WITH_CHECK(OutFigure, Out, "Registration of OutFigTriangle", FigTriangle, ofstream&);
REGISTER_METHOD_WITH_CHECK(DeleteFigure, DeleteFigTriangle, "Registration of DeleteFigTriangle", FigTriangle);




