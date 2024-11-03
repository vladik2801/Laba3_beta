#include "../include/sandpile.h"
#include "../include/deq.h"  // Подключаем вашу реализацию Deque
#include <cstdint>
#include <iostream>
#include <fstream>

Sandpile ReadingInput(const char* path, Deque<Deque<uint64_t>>& basic) {
    Sandpile sandpile;
    sandpile.count_iter = 0;
    
    int16_t x = 0;
    int16_t y = 0;
    uint64_t pixels;
    std::ifstream infile(path);
    std::string line;

    while (std::getline(infile, line)) {
        sscanf(line.c_str(), "%d\t%d\t%lu", &x, &y, &pixels);
        while (x >= sandpile.grid.size()) {
            Deque<uint64_t> newRow;
            for (int i = 0; i < sandpile.grid.front().size(); ++i) {
                newRow.push_back(0);
            }
            sandpile.grid.push_back(newRow);
        }
        while (y >= sandpile.grid.front().size()) {
            for (size_t i = 0; i < sandpile.grid.size(); ++i) {
                Deque<uint64_t>& row = sandpile.grid[i];
                row.push_back(0);
            }
        }

        // Добавление песчинок
         sandpile.grid[x][y] += pixels;
    }
     sandpile.width = sandpile.grid.size();
     if (sandpile.grid.head) {
        sandpile.height = sandpile.grid.head->data.size();
    } else {
        sandpile.height = 0;
    }
    return sandpile;

}


void AddPlace(Deque<Deque<uint64_t>>& basic, Sandpile& sandpile, KeysOfAdd key) {
    Deque<uint64_t> newRow;  // Создаем новую строку или колонку
    newRow.push_back(0);

    switch (key) {
        case up:
            basic.push_front(newRow);
            sandpile.width++;  // Увеличиваем ширину
            break;
        case down:
            basic.push_back(newRow);
            sandpile.width++;  // Увеличиваем ширину
            break;
        case left:
            for (uint16_t i = 0; i < sandpile.width; i++) {
                basic[i].push_front(0);
            }
            sandpile.height++;  // Увеличиваем высоту
            break;
        case right:
            for (uint16_t i = 0; i < sandpile.width; i++) {
                basic[i].push_back(0);
            }
            sandpile.height++;  // Увеличиваем высоту
            break;
    }
}

void Iteration(Deque<Deque<uint64_t>>& basic, Sandpile& sandpile, int& count_cells_more4) {
    Deque<std::pair<uint16_t, uint16_t>> ignoring; // Дек для игнорируемых координат
    std::pair<uint16_t, uint16_t> temporary;

    for (uint16_t i = 0; i < sandpile.width; i++) {
        for (uint16_t j = 0; j < sandpile.height; j++) {
            temporary = std::make_pair(i, j);

            // Проверка, есть ли координаты в деке игнорируемых
            bool is_ignored = false;
            for (size_t k = 0; k < ignoring.size(); ++k) {
                if (ignoring[k] == temporary) {
                    is_ignored = true;
                    break;
                }
            }
            if (is_ignored) {
                continue;
            }

            if (basic[i].front() >= 4) {
                if (i == 0) {
                    AddPlace(basic, sandpile, up);
                    i++;  // Увеличиваем индекс, чтобы не зациклиться
                }
                if (j == 0) {
                    AddPlace(basic, sandpile, left);
                    j++;  // Увеличиваем индекс, чтобы не зациклиться
                }
                if (i == sandpile.width - 1) {
                    AddPlace(basic, sandpile, down);
                }
                if (j == sandpile.height - 1) {
                    AddPlace(basic, sandpile, right);
                }

                // Обновляем значения в деке
                basic[i].front() -= 4;
                if (i > 0) basic[i - 1].push_back(1);
                if (i < sandpile.width - 1) basic[i + 1].push_back(1);
                basic[i].push_back(1);

                // Проверяем соседние ячейки
                if (i < sandpile.width - 1 && basic[i + 1].front() == 4) {
                    temporary = std::make_pair(i + 1, j);
                    ignoring.push_back(temporary);
                    count_cells_more4++;
                }
                if (j < sandpile.height - 1 && basic[i][j + 1] == 4) {
                    temporary = std::make_pair(i, j + 1);
                    ignoring.push_back(temporary);
                    count_cells_more4++;
                }
                if (basic[i].front() < 4) {
                    count_cells_more4--;
                }
                if (i > 0 && basic[i - 1].front() == 4) {
                    count_cells_more4++;
                }
                if (j > 0 && basic[i][j - 1] == 4) {
                    count_cells_more4++;
                }
            }
        }
    }
}