# ppmc
Metacompiler for using procedural-parametric features

[![Build Status](https://travis-ci.org/kpdev/ppmc.svg?branch=master)](https://travis-ci.org/kpdev/ppmc)

Как использовать:

1) Скомпилировать ppmc.cpp с помощью gcc-6. Строка для компиляции gcc-6 core/ppmc.cpp -o ppmc.out -std=c++17 -lstdc++fs

2) Запустить ./ppmc.out

3) Программа прочитает все файлы из директории test, произведет в них замену макросов, результат работы запишет в директорию output.
