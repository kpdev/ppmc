// FigCircle.cpp - Реализация функций, осуществляющих обработку круга

#include <iostream>
#include "FigCircle.h"




CREATE_REG_MARK_METHOD(FigCircle);
REGISTER_SPECIALIZATION(Figure, FigCircle, "Registration of: FigCircle");

INIT_v2(FigCircle);

CREATE(FigCircle);

IN(FigCircle, Circle);
OUT(FigCircle, Circle);

DELETE(FigCircle);


REGISTER_METHOD_WITH_CHECK_RET_PTR(CreateFigureUseFileMark, CreateFigCircle, FigCircle, "Registration of CreateFigCircleUseFileMark", 3, Figure);
PP_REGISTER_METHOD_WITH_CHECK(InFigureValue, In, "Registration of InFigCircleValue", FigCircle, ifstream&);
PP_REGISTER_METHOD_WITH_CHECK(OutFigure, Out, "Registration of OutFigCircle", FigCircle, ofstream&);
PP_REGISTER_METHOD_WITH_CHECK(DeleteFigure, DeleteFigCircle, "Registration of DeleteFigCircleSkin", FigCircle, void); // TODO: Avoid using "void" placeholder

