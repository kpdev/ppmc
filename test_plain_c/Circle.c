// Circle.cpp - Реализация функций, осуществляющих обработку круга

#include "Circle.h"

//------------------------------------------------------------------------------
//  Функции используемые для обработки круга

// Инициализация существующего круга
void Init(Circle* c, int r) {
    c->r = r;
}


// Создание круга с инициализаций сторон
Circle* CreateCircleAndInit(int r) {
  Circle* pc = malloc(sizeof(Circle));
  Init(pc, r);  
  return pc;
}

// Ввод данных в существующий круг из потока
void In(FILE *infile, Circle* c) {
  // TODO: Read from file
}

// Вывод данных о круге в поток
void Out(FILE * outfile, Circle* c) {
  // TODO: Write circle data to file
}
