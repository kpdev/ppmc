// FigCircle.cpp - Реализация функций, осуществляющих обработку круга

#include <iostream>
#include "FigCircle.h"




CREATE_REG_MARK_METHOD(FigCircle);
REGISTER_SPECIALIZATION(Figure, FigCircle, "Registration of: FigCircle");

INIT_v2(FigCircle);

v1_CREATE(FigCircle);

v1_IN(FigCircle, Circle);
OUT(FigCircle, Circle);

DELETE(FigCircle);

START_REGISTER_METHODS();
REGISTER_METHOD_WITH_CHECK_RET_PTR(CreateFigureUseFileMark, CreateFigCircle, FigCircle, "Registration of CreateFigCircleUseFileMark", 3, Figure);
PP_REGISTER_METHOD_WITH_CHECK(InFigureValue, In, "Registration of InFigCircleValue", FigCircle, ifstream&);
PP_REGISTER_METHOD_WITH_CHECK(OutFigure, Out, "Registration of OutFigCircle", FigCircle, ofstream&);
PP_v2_REGISTER_METHOD_WITH_CHECK(DeleteFigure, DeleteFigCircle, "Registration of DeleteFigCircleSkin", FigCircle); // TODO: Avoid using "void" placeholder

