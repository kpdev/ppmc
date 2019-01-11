// FigCircle.cpp - Реализация функций, осуществляющих обработку круга

#include <stdio.h>
#include "FigCircle.h"



CREATE_REG_MARK_METHOD(FigCircle);
REGISTER_SPECIALIZATION(Figure, FigCircle, "Registration of: FigCircle");

void InitFigCircle(FigCircle* ft, int r) {
  ft->_base.mark = GetRegMarkFigCircle();
  Circle* t = &(ft->_spec);
  InitCircle(t, r);
}

// Создание фигуры-треугольника без инициализации сторон
FigCircle* CreateFigCircle() {
  FigCircle* pft = malloc(sizeof(FigCircle));
  InitFigCircle(pft, 0);
  return pft;
}

// Создание фигуры-треугольника с инициализаций сторон
FigCircle* CreateFigCircleAndInit(int r) {
  FigCircle* pft = CreateFigCircle();
  InitFigCircle(pft, r);
  return pft;
}

// Ввод специализации фигуры-треугольника из потока
void InFigCircle(FigCircle* ft, FILE* ifst) {
  Circle* t = &(ft->_spec);
  InCircle(ifst, t);
}

// Вывод специализации фигуры-треугольника в поток
void OutFigCircle(FigCircle* ft, FILE* ofst) {
  fprintf_s(ofst, "Circle is as Specialization of Figure: r = %d\n", ft->_spec.r);
}

// Удаление специализации фигуры-треугольника
void DeleteFigCircle(FigCircle* pft) {
  free(pft);
}


START_REGISTER_METHODS();
REGISTER_METHOD_WITH_CHECK_RET_PTR(CreateFigureUseFileMark, CreateFigCircle, FigCircle, "Registration of CreateFigCircleUseFileMark", 3, Figure);
PP_REGISTER_METHOD_WITH_CHECK(InFigureValue, InFigCircle, "Registration of InFigCircleValue", FigCircle, ifstream&);
PP_REGISTER_METHOD_WITH_CHECK(OutFigure, OutFigCircle, "Registration of OutFigCircle", FigCircle, ofstream&);
PP_v2_REGISTER_METHOD_WITH_CHECK(DeleteFigure, DeleteFigCircle, "Registration of DeleteFigCircleSkin", FigCircle); // TODO: Avoid using "void" placeholder

