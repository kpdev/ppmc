// Container.cpp - Реализация функций, осуществляющих обработку контейнера

#include "Container.h"
#include <iostream>

using std::endl;

//------------------------------------------------------------------------------
//  Функции используемые для обработки котейнера

// Инициализация существующего контейнера
void Init(Container& c) {
    c.size = 0;
}

// Создание контейнера
Container* CreateContainer(int x, int y) {
    Container* pc = new Container;
    Init(*pc);
    return pc;
}

// Очистка контейнера от фигур
void ClearContainer(Container& c) {
    for(int i = 0; i < c.size; i++) {
        delete c.storage[i];
    }
    Init(c);
}

// Ввод фигур в контейнер из потока
void In(ifstream &ifst, Container& c) {
  std::cerr << "cerr In\n";
  std::cout << "cout In\n";
    while(!ifst.eof()) {
      std::cerr << "cerr In2\n";
      std::cout << "cout In2\n";
        if((c.storage[c.size] = InFigure(ifst)) != 0) {
          std::cerr << "cerr In3\n";
          std::cout << "cout In3\n";
            c.size++;
        }
    }
}

// Вывод фигур из контейнера в поток
void Out(ofstream &ofst, Container& c) {
    ofst << "Container is containing " << c.size << " elements." << endl;
    for(int i = 0; i < c.size; i++) {
      ofst << i << ": ";
      OutFigure(*(c.storage[i]), ofst);
    }
}

