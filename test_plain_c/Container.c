// Container.cpp - Реализация функций, осуществляющих обработку контейнера
#include <stdlib.h>
#include "Container.h"

//------------------------------------------------------------------------------
//  Функции используемые для обработки котейнера

// Инициализация существующего контейнера
void Init(Container* c) {
    c->size = 0;
}

// Создание контейнера
Container* CreateContainer(int x, int y) {
    Container* pc = malloc(sizeof(Container));
    Init(pc);
    return pc;
}

// Очистка контейнера от фигур
void ClearContainer(Container* c) {
    for(int i = 0; i < c->size; i++) {
        free(c->storage[i]);
    }
    Init(c);
}

// Ввод фигур в контейнер из потока
void In(FILE* ifst, Container* c) {
  printf("cout In\n");
    while(feof(ifst)) {
      printf("cout In2\n");
        if((c->storage[c->size] = InFigure(ifst)) != 0) {
          printf("cout In3\n");
            c->size++;
        }
    }
}

// Вывод фигур из контейнера в поток
void Out(FILE* ofst, Container* c) {
  fprintf(ofst, "Container is containing %d elements\n", c->size);
    for(int i = 0; i < c->size; i++) {
      fprintf(ofst, "%d : ", i);
      OutFigure(c->storage[i], ofst);
    }
}

