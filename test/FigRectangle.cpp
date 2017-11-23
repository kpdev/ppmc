// FigRectangle.cpp - Реализация функций, осуществляющих обработку прямоугольника

#include <iostream>
#include "FigRectangle.h"



CREATE_REG_MARK_METHOD(FigRectangle);
REGISTER_SPECIALIZATION(Figure, FigRectangle, "Registration of: FigRectangle");

//------------------------------------------------------------------------------
//  Функции используемые для обработки прямоугольника как специализации фигуры

// Инициализация существующей фигуры-прямоугольника
void Init(FigRectangle& fr, int x, int y) {
    fr.mark = GetRegMarkFigRectangle();
    Rectangle& r = fr._spec;
    Init(r, x, y);
}

// Создание фигуры-прямоугольника без инициализации сторон
FigRectangle* CreateFigRectangle() {
    FigRectangle* pfr = new FigRectangle;
    Init(*pfr, 0, 0);
    return pfr;
}

// Создание фигуры-прямоугольника с инициализаций сторон
FigRectangle* CreateFigRectangleAndInit(int x, int y) {
    FigRectangle* pfr = CreateFigRectangle();
    Init(*pfr, x, y);
    return pfr;
}

// Ввод специализации фигуры-прямоугольника из потока
void In(FigRectangle& fr, ifstream &ifst) {
    Rectangle& r = fr._spec;
    In(ifst, r);
}

// Вывод специализации фигуры-прямоугольника в поток
void Out(FigRectangle& fr, ofstream &ofst) {
    ofst << "Rectangle is as Specialization of Figure: x = " << fr._spec.x << ", y = " << fr._spec.y << endl;
}

// Удаление специализации фигуры-прямоугольника
void DeleteFigRectangle(FigRectangle& pfr) {
    delete &pfr;
}


//=============================================================================
// Функции - оболочки, используемые для параметризации данной специализации,
// Регистрируемые в соответствующих параметрических массивах
//=============================================================================

REGISTER_METHOD_WITH_CHECK_RET_PTR(CreateFigureUseFileMark, CreateFigRectangle, FigRectangle, "Registration of CreateFigRectangleUseFileMark", 1, Figure);
PP_REGISTER_METHOD_WITH_CHECK(InFigureValue, In, "Registration of InFigRectangleValue", FigRectangle, ifstream&);
PP_REGISTER_METHOD_WITH_CHECK(OutFigure, Out, "Registration of OutFigRectangle", FigRectangle, ofstream&);
PP_REGISTER_METHOD_WITH_CHECK(DeleteFigure, DeleteFigRectangle,"Registration of DeleteFigRectangle", FigRectangle, void);

