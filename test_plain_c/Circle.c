// Circle.cpp - Реализация функций, осуществляющих обработку круга

#include "Circle.h"
#include <stdlib.h>

//------------------------------------------------------------------------------
//  Функции используемые для обработки круга

// Инициализация существующего круга
void InitCircle(Circle* c, int r) {
    c->r = r;
}


// Создание круга с инициализаций сторон
Circle* CreateCircleAndInit(int r) {
  Circle* pc = malloc(sizeof(Circle));
  InitCircle(pc, r);
  return pc;
}

// Ввод данных в существующий круг из потока
void InCircle(FILE* infile, Circle* c) {
  // TODO: Read from file
  fscanf_s(infile, "%d", &(c->r));
}

// Вывод данных о круге в поток
void OutCircle(FILE* outfile, Circle* c) {
  // TODO: Write circle data to file
  fprintf_s(outfile, "Circle. R: %d\n", c->r);
}
