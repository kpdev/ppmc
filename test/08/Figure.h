#ifndef __Figure__
#define __Figure__

#include <fstream>

#include "../../pplib/CreateGeneralization.h"
#include "../../pplib/CreateGenFunc.h"

using std::ifstream;
using std::ofstream;

CREATE_GENERALIZATION(Figure);
DECLARE_GEN_FUNC(CreateFigureUseFileMark, Figure*, int);
DECLARE_GEN_FUNC(InFigureValue, void, Figure&, ifstream&);
DECLARE_GEN_FUNC(OutFigure, void, Figure&, ofstream&);
DECLARE_GEN_FUNC(DeleteFigure, void, Figure&);

// Ввод обобщенной фигуры из потока
Figure* InFigure(ifstream &ifst);

#endif
