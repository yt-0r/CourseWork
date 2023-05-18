#pragma warning(disable:4244)
#pragma warning(disable:6385)
#include <Graphics.hpp>
#include <Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include "Header.h"

using namespace sf;

int win = 0;
int lose = 0;
bool isPaused = 0;

bool isPlayerTurn = true; // ход игрока

Texture sand;
Texture sea;
Texture miss;
Texture explosion;
Texture ship1;
Texture ship1exp;
Texture shipedger;
Texture shipedgerexp;
Texture shipedgel;
Texture shipedgelexp;
Texture shipedget;
Texture shipedgetexp;
Texture shipedged;
Texture shipedgedexp;
Texture shipmidlr;
Texture shipmidlrexp;
Texture shipmidtd;
Texture shipmidtdexp;
Sound shoot;
SoundBuffer buffer;

int init() {
    if (!sea.loadFromFile("../resources/textures/sea.jpg") 
        || !sand.loadFromFile("../resources/textures/sand.jpg")
        || !miss.loadFromFile("../resources/textures/miss.jpg")
        || !ship1.loadFromFile("../resources/textures/ship1.jpg")
        || !ship1exp.loadFromFile("../resources/textures/ship1exp.jpg")
        || !shipedger.loadFromFile("../resources/textures/shipedge(r).jpg")
        || !shipedgerexp.loadFromFile("../resources/textures/shipedge(r)exp.jpg")
        || !shipedgel.loadFromFile("../resources/textures/shipedge(l).jpg")
        || !shipedgelexp.loadFromFile("../resources/textures/shipedge(l)exp.jpg")
        || !shipedget.loadFromFile("../resources/textures/shipedge(t).jpg")
        || !shipedgetexp.loadFromFile("../resources/textures/shipedge(t)exp.jpg")
        || !shipedged.loadFromFile("../resources/textures/shipedge(d).jpg")
        || !shipedgedexp.loadFromFile("../resources/textures/shipedge(d)exp.jpg")
        || !shipmidlr.loadFromFile("../resources/textures/shipmid(lr).jpg")
        || !shipmidlrexp.loadFromFile("../resources/textures/shipmid(lr)exp.jpg")
        || !shipmidtd.loadFromFile("../resources/textures/shipmid(td).jpg")
        || !shipmidtdexp.loadFromFile("../resources/textures/shipmid(td)exp.jpg")
        || !explosion.loadFromFile("../resources/textures/explosion.jpg")
        || !buffer.loadFromFile("../resources/sfx/shoot.wav")) {
        return 1;
    }
    shoot.setBuffer(buffer);
    return 0;
}

int drawGrid(RenderWindow& window, int Gridp[size + 2][size + 2], int Gridc[size + 2][size + 2], bool isPlayerGrid) {
    Sprite cell;
    cell.setPosition(sf::Vector2f(cellSize, cellSize));

    float x_offset = 0.f;
    if (!isPlayerGrid) {
        x_offset = (size + 2) * cellSize;
        for (int x = 0; x < size + 2; x++) {
            for (int y = 0; y < size + 2; y++) {
                cell.setPosition(x * cellSize + x_offset, y * cellSize);
                if (Gridc[x][y] == 0 || Gridc[x][y] == 1) { // неоткрытая ячейка или корабль компьютера
                    cell.setTexture(sea);
                    if (Gridc[x][y] != 0 && Gridc[x][y] != 1) {
                        return 1;
                    }
                }
                else if (Gridc[x][y] == 2) { // промах
                    if (Gridc[x][y] != 2) {
                        return 1;
                    }
                    cell.setTexture(miss);
                }
                else if (Gridc[x][y] == 3) { // попадание
                    if (Gridc[x][y] != 3) {
                        return 1;
                    }
                    cell.setTexture(explosion);
                }
                else if (Gridc[x][y] == 4
                    && Gridc[x + 1][y] != 1
                    && Gridc[x - 1][y] != 1
                    && Gridc[x][y + 1] != 1
                    && Gridc[x][y - 1] != 1
                    && Gridc[x + 1][y] != 3
                    && Gridc[x - 1][y] != 3
                    && Gridc[x][y + 1] != 3
                    && Gridc[x][y - 1] != 3
                    && Gridc[x + 1][y] != 4
                    && Gridc[x - 1][y] != 4
                    && Gridc[x][y + 1] != 4
                    && Gridc[x][y - 1] != 4) { // палуба корабля
                    cell.setTexture(ship1exp);
                }
                else if (Gridc[x][y] == 4
                    && (Gridc[x + 1][y] == 1
                        || Gridc[x + 1][y] == 3
                        || Gridc[x + 1][y] == 4)
                    && Gridc[x - 1][y] != 1
                    && Gridc[x][y + 1] != 1
                    && Gridc[x][y - 1] != 1
                    && Gridc[x - 1][y] != 3
                    && Gridc[x][y + 1] != 3
                    && Gridc[x][y - 1] != 3
                    && Gridc[x - 1][y] != 4
                    && Gridc[x][y + 1] != 4
                    && Gridc[x][y - 1] != 4) { // палуба корабля
                    cell.setTexture(shipedgerexp);
                }
                else if (Gridc[x][y] == 4
                    && (Gridc[x - 1][y] == 1
                        || Gridc[x - 1][y] == 3
                        || Gridc[x - 1][y] == 4)
                    && Gridc[x + 1][y] != 1
                    && Gridc[x][y + 1] != 1
                    && Gridc[x][y - 1] != 1
                    && Gridc[x + 1][y] != 3
                    && Gridc[x][y + 1] != 3
                    && Gridc[x][y - 1] != 3
                    && Gridc[x + 1][y] != 4
                    && Gridc[x][y + 1] != 4
                    && Gridc[x][y - 1] != 4) { // палуба корабля
                    cell.setTexture(shipedgelexp);
                }
                else if (Gridc[x][y] == 4
                    && (Gridc[x][y - 1] == 1
                        || Gridc[x][y - 1] == 3
                        || Gridc[x][y - 1] == 4)
                    && Gridc[x - 1][y] != 1
                    && Gridc[x][y + 1] != 1
                    && Gridc[x + 1][y] != 1
                    && Gridc[x - 1][y] != 3
                    && Gridc[x][y + 1] != 3
                    && Gridc[x + 1][y] != 3
                    && Gridc[x - 1][y] != 4
                    && Gridc[x][y + 1] != 4
                    && Gridc[x + 1][y] != 4) { // палуба корабля
                    cell.setTexture(shipedgetexp);
                }
                else if (Gridc[x][y] == 4
                    && (Gridc[x][y + 1] == 1
                        || Gridc[x][y + 1] == 3
                        || Gridc[x][y + 1] == 4)
                    && Gridc[x - 1][y] != 1
                    && Gridc[x + 1][y] != 1
                    && Gridc[x][y - 1] != 1
                    && Gridc[x - 1][y] != 3
                    && Gridc[x + 1][y] != 3
                    && Gridc[x][y - 1] != 3
                    && Gridc[x - 1][y] != 4
                    && Gridc[x + 1][y] != 4
                    && Gridc[x][y - 1] != 4) { // палуба корабля
                    cell.setTexture(shipedgedexp);
                }
                else if (Gridc[x][y] == 4
                    && Gridc[x][y + 1] != 1
                    && Gridc[x][y - 1] != 1
                    && Gridc[x][y + 1] != 3
                    && Gridc[x][y - 1] != 3
                    && Gridc[x][y + 1] != 4
                    && Gridc[x][y - 1] != 4
                    && ((Gridc[x + 1][y] == 1
                        && Gridc[x - 1][y] == 1)
                        || (Gridc[x + 1][y] == 3
                            && Gridc[x - 1][y] == 3)
                        || (Gridc[x + 1][y] == 1
                            && Gridc[x - 1][y] == 3)
                        || (Gridc[x + 1][y] == 3
                            && Gridc[x - 1][y] == 1)
                        || (Gridc[x + 1][y] == 4
                            && Gridc[x - 1][y] == 4))) { // палуба корабля
                    cell.setTexture(shipmidlrexp);
                }
                else if (Gridc[x][y] == 4
                    && Gridc[x + 1][y] != 1
                    && Gridc[x - 1][y] != 1
                    && Gridc[x + 1][y] != 3
                    && Gridc[x - 1][y] != 3
                    && Gridc[x + 1][y] != 4
                    && Gridc[x - 1][y] != 4
                    && ((Gridc[x][y + 1] == 1
                        && Gridc[x][y - 1] == 1)
                        || (Gridc[x][y + 1] == 3
                            && Gridc[x][y - 1] == 3)
                        || (Gridc[x][y + 1] == 1
                            && Gridc[x][y - 1] == 3)
                        || (Gridc[x][y + 1] == 3
                            && Gridc[x][y - 1] == 1)
                        || (Gridc[x][y + 1] == 4
                            && Gridc[x][y - 1] == 4))) { // палуба корабля
                    cell.setTexture(shipmidtdexp);
                }
                else if (Gridc[x][y] == -1) {
                    if (Gridc[x][y] != -1) {
                        return 1;
                    }
                    cell.setTexture(sand);
                }
                window.draw(cell);
            }
        }
    }

    for (int x = 0; x < size + 2; x++) {
        for (int y = 0; y < size + 2; y++) {
            cell.setPosition(x * cellSize, y * cellSize);
            if (Gridp[x][y] == 0) { // неоткрытая ячейка
                if (Gridp[x][y] != 0) {
                    return 1;
                }
                cell.setTexture(sea);
            }
            else if (Gridp[x][y] == 1
                && Gridp[x + 1][y] != 1
                && Gridp[x - 1][y] != 1
                && Gridp[x][y + 1] != 1
                && Gridp[x][y - 1] != 1
                && Gridp[x + 1][y] != 3
                && Gridp[x - 1][y] != 3
                && Gridp[x][y + 1] != 3
                && Gridp[x][y - 1] != 3
                && Gridp[x + 1][y] != 4
                && Gridp[x - 1][y] != 4
                && Gridp[x][y + 1] != 4
                && Gridp[x][y - 1] != 4) { // палуба корабля
                cell.setTexture(ship1);
            }
            else if (Gridp[x][y] == 4
                && Gridp[x + 1][y] != 1
                && Gridp[x - 1][y] != 1
                && Gridp[x][y + 1] != 1
                && Gridp[x][y - 1] != 1
                && Gridp[x + 1][y] != 3
                && Gridp[x - 1][y] != 3
                && Gridp[x][y + 1] != 3
                && Gridp[x][y - 1] != 3
                && Gridp[x + 1][y] != 4
                && Gridp[x - 1][y] != 4
                && Gridp[x][y + 1] != 4
                && Gridp[x][y - 1] != 4) { // палуба корабля
                cell.setTexture(ship1exp);
            }
            else if (Gridp[x][y] == 1
                && (Gridp[x + 1][y] == 1
                    || Gridp[x + 1][y] == 3)
                && Gridp[x - 1][y] != 1
                && Gridp[x][y + 1] != 1
                && Gridp[x][y - 1] != 1
                && Gridp[x - 1][y] != 3
                && Gridp[x][y + 1] != 3
                && Gridp[x][y - 1] != 3
                && Gridp[x - 1][y] != 4
                && Gridp[x][y + 1] != 4
                && Gridp[x][y - 1] != 4) { // палуба корабля
                cell.setTexture(shipedger);
            }
            else if (Gridp[x][y] == 1
                && (Gridp[x - 1][y] == 1
                    || Gridp[x - 1][y] == 3)
                && Gridp[x + 1][y] != 1
                && Gridp[x][y + 1] != 1
                && Gridp[x][y - 1] != 1
                && Gridp[x + 1][y] != 3
                && Gridp[x][y + 1] != 3
                && Gridp[x][y - 1] != 3
                && Gridp[x + 1][y] != 4
                && Gridp[x][y + 1] != 4
                && Gridp[x][y - 1] != 4) { // палуба корабля
                cell.setTexture(shipedgel);
            }
            else if (Gridp[x][y] == 1
                && (Gridp[x][y - 1] == 1
                    || Gridp[x][y - 1] == 3)
                && Gridp[x - 1][y] != 1
                && Gridp[x][y + 1] != 1
                && Gridp[x + 1][y] != 1
                && Gridp[x - 1][y] != 3
                && Gridp[x][y + 1] != 3
                && Gridp[x + 1][y] != 3
                && Gridp[x - 1][y] != 4
                && Gridp[x][y + 1] != 4
                && Gridp[x + 1][y] != 4) { // палуба корабля
                cell.setTexture(shipedget);
            }
            else if (Gridp[x][y] == 1
                && (Gridp[x][y + 1] == 1
                    || Gridp[x][y + 1] == 3)
                && Gridp[x - 1][y] != 1
                && Gridp[x + 1][y] != 1
                && Gridp[x][y - 1] != 1
                && Gridp[x - 1][y] != 3
                && Gridp[x + 1][y] != 3
                && Gridp[x][y - 1] != 3
                && Gridp[x - 1][y] != 4
                && Gridp[x + 1][y] != 4
                && Gridp[x][y - 1] != 4) { // палуба корабля
                cell.setTexture(shipedged);
            }

            else if ((Gridp[x][y] == 3 || Gridp[x][y] == 4)
                && (Gridp[x + 1][y] == 1
                    || Gridp[x + 1][y] == 3
                    || Gridp[x + 1][y] == 4)
                && Gridp[x - 1][y] != 1
                && Gridp[x][y + 1] != 1
                && Gridp[x][y - 1] != 1
                && Gridp[x - 1][y] != 3
                && Gridp[x][y + 1] != 3
                && Gridp[x][y - 1] != 3
                && Gridp[x - 1][y] != 4
                && Gridp[x][y + 1] != 4
                && Gridp[x][y - 1] != 4) { // палуба корабля
                cell.setTexture(shipedgerexp);
            }
            else if ((Gridp[x][y] == 3 || Gridp[x][y] == 4)
                && (Gridp[x - 1][y] == 1
                    || Gridp[x - 1][y] == 3
                    || Gridp[x - 1][y] == 4)
                && Gridp[x + 1][y] != 1
                && Gridp[x][y + 1] != 1
                && Gridp[x][y - 1] != 1
                && Gridp[x + 1][y] != 3
                && Gridp[x][y + 1] != 3
                && Gridp[x][y - 1] != 3
                && Gridp[x + 1][y] != 4
                && Gridp[x][y + 1] != 4
                && Gridp[x][y - 1] != 4) { // палуба корабля
                cell.setTexture(shipedgelexp);
            }
            else if ((Gridp[x][y] == 3 || Gridp[x][y] == 4)
                && (Gridp[x][y - 1] == 1
                    || Gridp[x][y - 1] == 3
                    || Gridp[x][y - 1] == 4)
                && Gridp[x - 1][y] != 1
                && Gridp[x][y + 1] != 1
                && Gridp[x + 1][y] != 1
                && Gridp[x - 1][y] != 3
                && Gridp[x][y + 1] != 3
                && Gridp[x + 1][y] != 3
                && Gridp[x - 1][y] != 4
                && Gridp[x][y + 1] != 4
                && Gridp[x + 1][y] != 4) { // палуба корабля
                cell.setTexture(shipedgetexp);
            }
            else if ((Gridp[x][y] == 3 || Gridp[x][y] == 4)
                && (Gridp[x][y + 1] == 1
                    || Gridp[x][y + 1] == 3
                    || Gridp[x][y + 1] == 4)
                && Gridp[x - 1][y] != 1
                && Gridp[x + 1][y] != 1
                && Gridp[x][y - 1] != 1
                && Gridp[x - 1][y] != 3
                && Gridp[x + 1][y] != 3
                && Gridp[x][y - 1] != 3
                && Gridp[x - 1][y] != 4
                && Gridp[x + 1][y] != 4
                && Gridp[x][y - 1] != 4) { // палуба корабля
                cell.setTexture(shipedgedexp);
            }

            else if (Gridp[x][y] == 1
                && Gridp[x][y + 1] != 1
                && Gridp[x][y - 1] != 1
                && Gridp[x][y + 1] != 3
                && Gridp[x][y - 1] != 3
                && Gridp[x][y + 1] != 4
                && Gridp[x][y - 1] != 4
                && ((Gridp[x + 1][y] == 1
                    && Gridp[x - 1][y] == 1)
                    || (Gridp[x + 1][y] == 3
                        && Gridp[x - 1][y] == 3)
                    || (Gridp[x + 1][y] == 1
                        && Gridp[x - 1][y] == 3)
                    || (Gridp[x + 1][y] == 3
                        && Gridp[x - 1][y] == 1))) { // палуба корабля
                cell.setTexture(shipmidlr);
            }
            else if (Gridp[x][y] == 1
                && Gridp[x + 1][y] != 1
                && Gridp[x - 1][y] != 1
                && Gridp[x + 1][y] != 3
                && Gridp[x - 1][y] != 3
                && Gridp[x + 1][y] != 4
                && Gridp[x - 1][y] != 4
                && ((Gridp[x][y + 1] == 1
                    && Gridp[x][y - 1] == 1)
                    || (Gridp[x][y + 1] == 3
                        && Gridp[x][y - 1] == 3)
                    || (Gridp[x][y + 1] == 1
                        && Gridp[x][y - 1] == 3)
                    || (Gridp[x][y + 1] == 3
                        && Gridp[x][y - 1] == 1))) { // палуба корабля
                cell.setTexture(shipmidtd);
            }

            else if ((Gridp[x][y] == 3 || Gridp[x][y] == 4)
                && Gridp[x][y + 1] != 1
                && Gridp[x][y - 1] != 1
                && Gridp[x][y + 1] != 3
                && Gridp[x][y - 1] != 3
                && Gridp[x][y + 1] != 4
                && Gridp[x][y - 1] != 4
                && ((Gridp[x + 1][y] == 1
                    && Gridp[x - 1][y] == 1)
                    || (Gridp[x + 1][y] == 3
                        && Gridp[x - 1][y] == 3)
                    || (Gridp[x + 1][y] == 1
                        && Gridp[x - 1][y] == 3)
                    || (Gridp[x + 1][y] == 3
                        && Gridp[x - 1][y] == 1)
                    || (Gridp[x + 1][y] == 4
                        && Gridp[x - 1][y] == 4))) { // палуба корабля
                cell.setTexture(shipmidlrexp);
            }
            else if ((Gridp[x][y] == 3 || Gridp[x][y] == 4)
                && Gridp[x + 1][y] != 1
                && Gridp[x - 1][y] != 1
                && Gridp[x + 1][y] != 3
                && Gridp[x - 1][y] != 3
                && Gridp[x + 1][y] != 4
                && Gridp[x - 1][y] != 4
                && ((Gridp[x][y + 1] == 1
                    && Gridp[x][y - 1] == 1)
                    || (Gridp[x][y + 1] == 3
                        && Gridp[x][y - 1] == 3)
                    || (Gridp[x][y + 1] == 1
                        && Gridp[x][y - 1] == 3)
                    || (Gridp[x][y + 1] == 3
                        && Gridp[x][y - 1] == 1)
                    || (Gridp[x][y + 1] == 4
                        && Gridp[x][y - 1] == 4))) { // палуба корабля
                cell.setTexture(shipmidtdexp);
            }
            else if (Gridp[x][y] == 2) { // промах
                if (Gridp[x][y] != 2) {
                    return 1;
                }
                cell.setTexture(miss);
            }
            else if (Gridp[x][y] == -1) { // попадание
                if (Gridp[x][y] != -1) {
                    return 1;
                }
                cell.setTexture(sand);
            }
            window.draw(cell);
        }
    }
    return 0;
}

int main() {

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
            if (isPlayerTurn && event.type == Event::MouseButtonPressed && (event.mouseButton.x < ((size + 2) * 2) * cellSize) && (event.mouseButton.x > (size + 2) * cellSize)) { // если сейчас ход игрока и он нажал на ячейку
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

        for (int x = 1; x < size+1; x++) {
            for (int y = 1; y < size+1; y++) {
                if (computerGrid[x][y] == 3) {
                    if (isSunk(x, y, computerGrid, size) == true) {
                        if (aroundHit(computerGrid, x, y) != 0) {
                            return 1;
                        }
                    }
                }
                if (playerGrid[x][y] == 3) {
                    if (isSunk(x, y, playerGrid, size) == true) {
                        if (aroundHit(playerGrid, x, y) != 0) {
                            return 1;
                        }
                    }
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
            
            bool flaggg = 0;

            for (int x = 1; x < size+1; x++) {
                for (int y = 1; y < size+1; y++) {
                    if (playerGrid[x][y] == 3) {
                        flaggg = 1;
                    }
                }
            }
            if (flaggg == 1) {

                int x = rand() % size + 1;
                int y = rand() % size + 1;
                while (1) {
                    x = rand() % size + 1;
                    y = rand() % size + 1;
                    if ((playerGrid[x][y] != 2 && playerGrid[x][y] != 3 && playerGrid[x][y] != 4) &&
                        (playerGrid[x + 1][y] == 3 || playerGrid[x - 1][y] == 3 || playerGrid[x][y + 1] == 3 || playerGrid[x][y - 1] == 3) &&
                        (playerGrid[x + 1][y + 1] != 3 && playerGrid[x - 1][y - 1] != 3 && playerGrid[x - 1][y + 1] != 3 && playerGrid[x + 1][y - 1] != 3)) {
                        break;
                    }
                }
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
            else if (flaggg == 0) {

                int x = rand() % size + 1;
                int y = rand() % size + 1;
                while (playerGrid[x][y] == 2 || playerGrid[x][y] == 3 || playerGrid[x][y] == 4) { // не стреляем по уже открытым ячейкам
                    x = rand() % size + 1;
                    y = rand() % size + 1;
                }
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