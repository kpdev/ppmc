#ifndef __Figure__
#define __Figure__

#include <stdio.h>

CREATE_GENERALIZATION(Figure);
DECLARE_GEN_FUNC(CreateFigureUseFileMark, Figure*, int);
DECLARE_GEN_FUNC(InFigureValue, void, Figure*, FILE* ifst);
DECLARE_GEN_FUNC(OutFigure, void, Figure*, FILE* ofst);
DECLARE_GEN_FUNC(DeleteFigure, void, Figure*);

// Ввод обобщенной фигуры из потока
Figure* InFigure(FILE* ifst);

#endif
