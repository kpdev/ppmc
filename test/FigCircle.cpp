// FigCircle.cpp - Реализация функций, осуществляющих обработку круга

#include <iostream>
#include "FigCircle.h"




CREATE_REG_MARK_METHOD(FigCircle);
REGISTER_SPECIALIZATION(Figure, FigCircle, "Registration of: FigCircle");

void Init(FigCircle& ft, int r) {
  ft.mark = GetRegMarkFigCircle();
  Circle& t = ft._spec;
  Init(t, r);
}

// Создание фигуры-треугольника без инициализации сторон
FigCircle* CreateFigCircle() {
  FigCircle* pft = new FigCircle;
  Init(*pft, 0);
  return pft;
}

// Создание фигуры-треугольника с инициализаций сторон
FigCircle* CreateFigCircleAndInit(int r) {
  FigCircle* pft = CreateFigCircle();
  Init(*pft, r);
  return pft;
}

// Ввод специализации фигуры-треугольника из потока
void In(FigTriangle& ft, ifstream &ifst) {
  Circle& t = ft._spec;
  In(ifst, t);
}

// Вывод специализации фигуры-треугольника в поток
void Out(FigCircle& ft, ofstream &ofst) {
  ofst << "Circle is as Specialization of Figure: r = " << ft._spec.r << endl;
}

// Удаление специализации фигуры-треугольника
void DeleteFigCircle(FigCircle& pft) {
  delete &pft;
}


START_REGISTER_METHODS();
REGISTER_METHOD_WITH_CHECK_RET_PTR(CreateFigureUseFileMark, CreateFigCircle, FigCircle, "Registration of CreateFigCircleUseFileMark", 3, Figure);
PP_REGISTER_METHOD_WITH_CHECK(InFigureValue, In, "Registration of InFigCircleValue", FigCircle, ifstream&);
PP_REGISTER_METHOD_WITH_CHECK(OutFigure, Out, "Registration of OutFigCircle", FigCircle, ofstream&);
PP_v2_REGISTER_METHOD_WITH_CHECK(DeleteFigure, DeleteFigCircle, "Registration of DeleteFigCircleSkin", FigCircle); // TODO: Avoid using "void" placeholder

