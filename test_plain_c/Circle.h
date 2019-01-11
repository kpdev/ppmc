#ifndef PPMC__Circle__
#define PPMC__Circle__

#include <stdio.h>

//------------------------------------------------------------------------------
// Структура Circle, определяющая содержимое круга
typedef struct {
  // Радиус круга
  int r;
} Circle;

//------------------------------------------------------------------------------
//  Функции используемые для обработки круга

// Инициализация существующего круга
void InitCircle(Circle* c, int r);

// Создание круга с инициализаций сторон
Circle* CreateCircleAndInit(int r);

// Ввод данных в существующий круг из потока
void InCircle(FILE* infile, Circle* c);

// Вывод данных о круг в поток
void OutCircle(FILE* outfile, Circle* c);

#endif
