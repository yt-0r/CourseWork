#pragma warning(disable:4244)
#pragma warning(disable:6385)
#include <Graphics.hpp>
#include <Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include "Logic.h"
#include "Graphic.h"

using namespace sf;

int win = 0;
int lose = 0;
bool isPaused = 0;

bool isPlayerTurn = true; // ход игрока

Sound shoot;
SoundBuffer buffer;

int main() {

    if (!buffer.loadFromFile("../resources/sfx/shoot.wav")) {
        return 1;
    }
    shoot.setBuffer(buffer);

    int playerGrid[size + 2][size + 2]; // игровое поле игрока
    int computerGrid[size + 2][size + 2]; // игровое поле компьютера

    RenderWindow window(VideoMode((size+2) * cellSize * 2, (size + 2) * cellSize), "Battleships", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    srand(time(NULL));

    if (zeroGrid(playerGrid, computerGrid) != 0) {
        return 1;
    }

    if (init() != 0) {
        return 1;
    }

    if (Ship_placement(computerGrid, size) != 0 || Ship_placement(playerGrid, size) != 0) {
        return 1;
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (isPlayerTurn && event.type == Event::MouseButtonPressed && (event.mouseButton.x < ((size + 2) * 2) * cellSize) && (event.mouseButton.x > (size + 2) * cellSize)) { // если сейчас ход игрока и он нажал на €чейку
                int x = (event.mouseButton.x - (size+2) * cellSize) / cellSize;
                int y = event.mouseButton.y / cellSize;

                if (computerGrid[x][y] == 1) { // убил
                    computerGrid[x][y] = 3;
                    win += 1;
                    isPaused = 1;
                    shoot.play();
                }
                else if (computerGrid[x][y] == 0) { // промах
                    computerGrid[x][y] = 2;
                    isPlayerTurn = false;
                    isPaused = 1;
                    shoot.play();
                }
            }
        }
        window.clear(Color::White);

        for (int x = 1; x < size + 1; x++) {
            for (int y = 1; y < size + 1; y++) {
                if ((computerGrid[x][y] == 3 && isSunk(x, y, computerGrid, size) == true && aroundHit(computerGrid, x, y) != 0)
                    || (playerGrid[x][y] == 3 && isSunk(x, y, playerGrid, size) == true && aroundHit(playerGrid, x, y) != 0)) {
                    return 1;
                }
            }
        }

        if (drawGrid(window, playerGrid, computerGrid, true) != 0 || drawGrid(window, playerGrid, computerGrid, false) != 0) {
            return 1;
        }
        
        window.display();
        if (isPaused == 1) {
            if (timer() != 0) {
                return 1;
            }
            isPaused = 0;
        }

        if (!isPlayerTurn) { // если сейчас ход компьютера

            int x = rand() % size + 1;
            int y = rand() % size + 1;

            computerHit(playerGrid, checkforHit(playerGrid), x, y);

            if (playerGrid[x][y] == 1) { // попал
                playerGrid[x][y] = 3;
                lose += 1;
                isPaused = 1;
                shoot.play();
            }
            else { // промах
                playerGrid[x][y] = 2;
                isPlayerTurn = true;
                isPaused = 1;
                shoot.play();
            }

        }
        if (win == 20) {
            std::cout << "You won!";
            window.close();
        }
        if (lose == 20) {
            std::cout << "You lost!";
            window.close();
        }
    }

    return 0;
}