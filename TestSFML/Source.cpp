#include <Graphics.hpp>
#include <iostream>

using namespace sf;

const int cellSize = 50; // размер €чеек
const int size = 10; // размер пол€


int playerGrid[size][size]; // игровое поле игрока
int computerGrid[size][size]; // игровое поле компьютера

bool isPlayerTurn = true; // ход игрока

void drawGrid(RenderWindow& window, int grid[size][size], bool isPlayerGrid) {
    RectangleShape cell(Vector2f(cellSize, cellSize));
    cell.setOutlineThickness(1.f);

    float x_offset = 0.f;
    if (!isPlayerGrid) {
        x_offset = (size + 0.5f) * cellSize;
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                cell.setPosition(x * cellSize + x_offset, y * cellSize);
                if (computerGrid[x][y] == 0 || computerGrid[x][y] == 1) { // неоткрыта€ €чейка или корабль компьютера
                    cell.setFillColor(Color::White);
                    cell.setOutlineColor(Color::Black);
                }
                else if (computerGrid[x][y] == 2) { // промах
                    cell.setFillColor(Color::Yellow);
                    cell.setOutlineColor(Color::Black);
                }
                else if (computerGrid[x][y] == 3) { // попадание
                    cell.setFillColor(Color::Red);
                    cell.setOutlineColor(Color::Black);
                }
                window.draw(cell);
            }
        }
    }

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            cell.setPosition(x * cellSize, y * cellSize);
            if (playerGrid[x][y] == 0) { // неоткрыта€ €чейка
                cell.setFillColor(Color::White);
                cell.setOutlineColor(Color::Black);
            }
            else if (playerGrid[x][y] == 1) { // палуба корабл€
                cell.setFillColor(Color::Blue);
                cell.setOutlineColor(Color::Black);
            }
            else if (playerGrid[x][y] == 2) { // промах
                cell.setFillColor(Color::Yellow);
                cell.setOutlineColor(Color::Black);
            }
            else if (playerGrid[x][y] == 3) { // попадание
                cell.setFillColor(Color::Red);
                cell.setOutlineColor(Color::Black);
            }
            window.draw(cell);
        }
    }
}

int main() {
    RenderWindow window(VideoMode(size * cellSize * 2.5, size * cellSize), "Battleships");

    // инициализируем поле игрока и компьютера
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            playerGrid[x][y] = 0;
            computerGrid[x][y] = 0;
        }
    }

    // рандомно размещаем корабли компьютера
    srand(time(NULL));
    for (int i = 0; i < 5; i++) { // 5 кораблей
        int x = rand() % size;
        int y = rand() % size;
        while (computerGrid[x][y] == 1 || computerGrid[x][y] == 2 || computerGrid[x][y] == 3) { // не ставим корабли на зан€тые клетки
            x = rand() % size;
            y = rand() % size;
        }
        computerGrid[x][y] = 1;
    }
    for (int i = 0; i < 5; i++) { // 5 кораблей
        int x = rand() % size;
        int y = rand() % size;
        while (playerGrid[x][y] == 1 || playerGrid[x][y] == 2 || playerGrid[x][y] == 3) { // не ставим корабли на зан€тые клетки
            x = rand() % size;
            y = rand() % size;
        }
        playerGrid[x][y] = 1;
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (isPlayerTurn && event.type == Event::MouseButtonPressed && (event.mouseButton.x < (size * 2) * cellSize + 0.5f) && (event.mouseButton.x > (size +0.5f) * cellSize)) { // если сейчас ход игрока и он нажал на €чейку
                int x = (event.mouseButton.x - (size + 0.5f) * cellSize) / cellSize;
                int y = event.mouseButton.y / cellSize;
                if (computerGrid[x][y] == 1) { // попал
                    computerGrid[x][y] = 3;
                }
                else if (computerGrid[x][y] == 3) {
                    computerGrid[x][y] = 3;
                }
                else if (computerGrid[x][y] == 2) {
                    computerGrid[x][y] = 2;
                }
                else { // промах
                    computerGrid[x][y] = 2;
                    isPlayerTurn = false;
                }
            }
        }
        window.clear(Color::White);

        drawGrid(window, playerGrid, true); // рисуем поле игрока
        drawGrid(window, computerGrid, false); // рисуем поле компьютера

        window.display();

        if (!isPlayerTurn) { // если сейчас ход компьютера
            int x = rand() % size;
            int y = rand() % size;
            while (playerGrid[x][y] == 2 || playerGrid[x][y] == 3) { // не стрел€ем по уже открытым €чейкам
                x = rand() % size;
                y = rand() % size;
            }
            if (playerGrid[x][y] == 1) { // попал
                playerGrid[x][y] = 3;
            }
            else { // промах
                playerGrid[x][y] = 2;
                isPlayerTurn = true;
            }
        }
    }

    return 0;
}