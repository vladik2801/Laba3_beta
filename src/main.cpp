#include "../include/sandpile.h"

#include "../include/deq.h"  // Подключаем вашу реализацию Deque
#include <cstdlib>
#include "create_bmp.cpp"

int main(int argc, char** argv) {
    getInfo arguments;
    Parsing(argc, argv, arguments);

    Deque<Deque<uint64_t>> basic;  // Используем вашу реализацию Deque
    Sandpile sandpile = ReadingInput(arguments.input, basic);
    int now_iterations = 0;
    int count_cells_more4 = 0;

    // Подсчет ячеек с количеством песчинок >= 4
    for (uint16_t i = 0; i < sandpile.width; i++) {
        for (uint16_t j = 0; j < sandpile.height; j++) {
            if (basic[i].front() >= 4) {
                count_cells_more4++;
            }
        }
    }

    // Основной цикл итераций
    while (count_cells_more4 != 0) {
        Iteration(basic, sandpile, count_cells_more4);  // Вызов итерации с sandpile и count_cells_more4
        now_iterations++;

        // Проверка на частоту сохранения изображения
        if (arguments.flag[Freq] && arguments.freq != 0 && now_iterations % arguments.freq == 0) {
            CreateBmp(arguments.output, basic, sandpile);
        }

        // Проверка на максимальное количество итераций
        if (arguments.flag[Max_iter] && now_iterations == arguments.max_iter) {
            break;
        }
    }

    CreateBmp(arguments.output, basic, sandpile);  // Создание финального изображения

    return 0;
}