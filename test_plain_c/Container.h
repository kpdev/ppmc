#ifndef __Container__
#define __Container__

#include "Figure.h"

//------------------------------------------------------------------------------
// Структура Container, обеспечивающая хранение геометрических фигур в одномерном массиве
// фиксированной размерности
#define maxSize 100   // Размерность массива
typedef struct {
    // Массив, состоящий из указателей на фигуры
    Figure* storage[maxSize];
    // Текущее число элементов в контейнере
    int size;
} Container;

//------------------------------------------------------------------------------
//  Функции используемые для обработки контейнера

// Инициализация существующего контейнера
void Init(Container* c);

// Создание контейнера
Container* CreateContainer(int x, int y);

// Очистка контейнера от фигур
void ClearContainer(Container* c);

// Ввод фигур в контейнер из потока
void In(FILE* ifst, Container* c);

// Вывод фигур из контейнера в поток
void Out(FILE* ofst, Container* c);

#endif
