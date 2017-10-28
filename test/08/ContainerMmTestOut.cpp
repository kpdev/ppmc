// Файл ContainerMmTestOut.cpp, содержащий функцию обхода фигур 
// с выводом только треугольников-специализаций

#include "Container.h"

#include "../../pplib/CreateMM.h"

// Прототип мультиметода, осуществляющего сопоставление двух фигур
// с выводом информации об их комбинации

//void MultimethodFuncMM(Figure& f1, Figure& f2, ofstream &o);

DECLARE_MM(MultimethodFunc, 10, Figure, ofstream&)


// Функция, осуществляющая перебор парных комбинаций для всех элементов контейнера
// Запускает мультиметод для каждой пары
void MultimethodTestOut(ofstream& ofst, Container& c) {
    for(int i = 0; i < c.size; i++) {
        for(int j = 0; j < c.size; j++) {
            Figure* pf1 = c.storage[i];
            Figure* pf2 = c.storage[j];
            ofst << "[" << i << "][" << j << "]: ";
            MultimethodFuncMM<ofstream&>(*pf1, *pf2, ofst);
        }
    }
}
