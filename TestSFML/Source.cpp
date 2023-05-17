#pragma warning(disable:4244)
#pragma warning(disable:6385)
#include <Graphics.hpp>
#include <Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

using namespace sf;

const int cellSize = 50; // ������ �����
const int size = 10; // ������ ����
int win = 0;
int lose = 0;
bool isPaused = 0;

int playerGrid[size+2][size+2]; // ������� ���� ������
int computerGrid[size+2][size+2]; // ������� ���� ����������

bool isPlayerTurn = true; // ��� ������

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

void Ship_placement(int b[size+2][size+2]) {
    int l = 0;      //count 4 ships
    while (l < 1) {
        int i = rand() % size + 1; int j = rand() % size + 1;
        b[i][j] = 1;
        if ((i >= 4 && i <= 7) && (j >= 4 && j <= 7)) {
            int v = rand() % 2;
            if (v == 0) {    //vertical
                int r = rand() % 2;   //down 0, up 1
                if (r == 0) {    //down
                    b[i + 1][j] = 1; b[i + 2][j] = 1; b[i + 3][j] = 1;
                    l += 1;
                }
                if (r == 1) {   //up
                    b[i - 1][j] = 1; b[i - 2][j] = 1; b[i - 3][j] = 1;
                    l += 1;
                }
            }
            if (v == 1) {   //horizont
                int r = rand() % 2;   //left 0, right 1
                if (r == 0) {      //left
                    b[i][j - 1] = 1; b[i][j - 2] = 1; b[i][j - 3] = 1;
                    l += 1;
                }
                if (r == 1) {   //right
                    b[i][j + 1] = 1; b[i][j + 2] = 1; b[i][j + 3] = 1;
                    l += 1;
                }
            }
        }
        if ((i >= 1 && i <= 7) && (j >= 1 && j <= 3)) {
            int v = rand() % 2;     //down 0, right 1
            if (v == 0) {     //down
                b[i + 1][j] = 1; b[i + 2][j] = 1; b[i + 3][j] = 1;
                l += 1;
            }
            if (v == 1) {     //right
                b[i][j + 1] = 1; b[i][j + 2] = 1; b[i][j + 3] = 1;
                l += 1;
            }
        }
        if ((i >= 8 && i <= 10) && (j >= 1 && j <= 7)) {
            int v = rand() % 2;     //up 0, right 1
            if (v == 0) {     //up
                b[i - 1][j] = 1; b[i - 2][j] = 1; b[i - 3][j] = 1;
                l += 1;
            }
            if (v == 1) {     //right
                b[i][j + 1] = 1; b[i][j + 2] = 1; b[i][j + 3] = 1;
                l += 1;
            }
        }
        if ((i >= 4 && i <= 10) && (j >= 8 && j <= 10)) {
            int v = rand() % 2;     //up 0, left 1
            if (v == 0) {     //up
                b[i - 1][j] = 1; b[i - 2][j] = 1; b[i - 3][j] = 1;
                l += 1;
            }
            if (v == 1) {     //left
                b[i][j - 1] = 1; b[i][j - 2] = 1; b[i][j - 3] = 1;
                l += 1;
            }

        }
        if ((i >= 1 && i <= 3) && (j >= 4 && j <= 10)) {
            int v = rand() % 2;     //down 0, left 1
            if (v == 0) {     //down
                b[i + 1][j] = 1; b[i + 2][j] = 1; b[i + 3][j] = 1;
                l += 1;
            }
            if (v == 1) {     //left
                b[i][j - 1] = 1; b[i][j - 2] = 1; b[i][j - 3] = 1;
                l += 1;
            }
        }


    }
    l = 0;      //count 3 ships
    while (l < 2) {
        int i = rand() % size + 1; int j = rand() % size + 1;
        if ((b[i - 1][j - 1] == 1) or (b[i - 1][j] == 1) or (b[i - 1][j + 1] == 1) or (b[i][j - 1] == 1) or (b[i][j] == 1) or (b[i][j + 1] == 1) or (b[i + 1][j - 1] == 1) or (b[i + 1][j] == 1) or (b[i + 1][j + 1] == 1)) continue;
        else {
            if (i >= 3 && i <= 8 && j >= 3 && j <= 8) {
                int v = rand() % 2;     //vertical 0, horizont 1
                if (v == 0) {    //vertical
                    int r = rand() % 2;   //down 0, up 1
                    if (r == 0) {    //down
                        if ((b[i + 2][j - 1] == 1) or (b[i + 2][j] == 1) or (b[i + 2][j + 1] == 1) or (b[i + 3][j - 1] == 1) or (b[i + 3][j] == 1) or (b[i + 3][j + 1] == 1)) continue;
                        else {
                            b[i][j] = 1; b[i + 1][j] = 1; b[i + 2][j] = 1;
                            l += 1;
                            continue;
                        }
                    }
                    if (r == 1) {   //up
                        if ((b[i - 2][j - 1] == 1) or (b[i - 2][j] == 1) or (b[i - 2][j + 1] == 1) or (b[i - 3][j - 1] == 1) or (b[i - 3][j] == 1) or (b[i - 3][j + 1] == 1)) continue;
                        else {
                            b[i][j] = 1; b[i - 1][j] = 1; b[i - 2][j] = 1;
                            l += 1;
                            continue;
                        }
                    }
                }
                if (v == 1) {   //horizont
                    int r = rand() % 2;   //left 0, right 1
                    if (r == 0) {       //left
                        if ((b[i - 1][j - 2] == 1) or (b[i][j - 2] == 1) or (b[i + 1][j - 2] == 1) or (b[i - 1][j - 3] == 1) or (b[i][j - 3] == 1) or (b[i + 1][j - 3] == 1)) continue;
                        else {
                            b[i][j] = 1; b[i][j - 1] = 1; b[i][j - 2] = 1;
                            l += 1;
                            continue;
                        }
                    }
                    if (r == 1) {       //right
                        if ((b[i - 1][j + 2] == 1) or (b[i][j + 2] == 1) or (b[i + 1][j + 2] == 1) or (b[i - 1][j + 3] == 1) or (b[i][j + 3] == 1) or (b[i + 1][j + 3] == 1)) continue;
                        else {
                            b[i][j] = 1; b[i][j + 1] = 1; b[i][j + 2] = 1;
                            l += 1;
                            continue;
                        }
                    }
                }
            }
            if (i >= 1 && i <= 8 && j >= 1 && j <= 2) {
                int v = rand() % 2;     //down 0, right 1
                if (v == 0) {   //down
                    if ((b[i + 2][j - 1] == 1) or (b[i + 2][j] == 1) or (b[i + 2][j + 1] == 1) or (b[i + 3][j - 1] == 1) or (b[i + 3][j] == 1) or (b[i + 3][j + 1] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i + 1][j] = 1; b[i + 2][j] = 1;
                        l += 1;
                        continue;
                    }
                }
                if (v == 1) {   //right
                    if ((b[i - 1][j + 2] == 1) or (b[i][j + 2] == 1) or (b[i + 1][j + 2] == 1) or (b[i - 1][j + 3] == 1) or (b[i][j + 3] == 1) or (b[i + 1][j + 3] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i][j + 1] = 1; b[i][j + 2] = 1;
                        l += 1;
                        continue;
                    }
                }
            }
            if (i >= 9 && i <= 10 && j >= 1 && j <= 8) {
                int v = rand() % 2;     //up 0, right 1
                if (v == 0) {       //up
                    if ((b[i - 2][j - 1] == 1) or (b[i - 2][j] == 1) or (b[i - 2][j + 1] == 1) or (b[i - 3][j - 1] == 1) or (b[i - 3][j] == 1) or (b[i - 3][j + 1] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i - 1][j] = 1; b[i - 2][j] = 1;
                        l += 1;
                        continue;
                    }
                }
                if (v == 1) {       //right
                    if ((b[i - 1][j + 2] == 1) or (b[i][j + 2] == 1) or (b[i + 1][j + 2] == 1) or (b[i - 1][j + 3] == 1) or (b[i][j + 3] == 1) or (b[i + 1][j + 3] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i][j + 1] = 1; b[i][j + 2] = 1;
                        l += 1;
                        continue;
                    }
                }
            }
            if (i >= 3 && i <= 10 && j >= 9 && j <= 10) {
                int v = rand() % 2;     //up 0, left 1
                if (v == 0) {   //up
                    if ((b[i - 2][j - 1] == 1) or (b[i - 2][j] == 1) or (b[i - 2][j + 1] == 1) or (b[i - 3][j - 1] == 1) or (b[i - 3][j] == 1) or (b[i - 3][j + 1] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i - 1][j] = 1; b[i - 2][j] = 1;
                        l += 1;
                        continue;
                    }
                }
                if (v == 1) {   //left
                    if ((b[i - 1][j - 2] == 1) or (b[i][j - 2] == 1) or (b[i + 1][j - 2] == 1) or (b[i - 1][j - 3] == 1) or (b[i][j - 3] == 1) or (b[i + 1][j - 3] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i][j - 1] = 1; b[i][j - 2] = 1;
                        l += 1;
                        continue;
                    }
                }
            }
            if (i >= 1 && i <= 2 && j >= 3 && j <= 10) {
                int v = rand() % 2;      //down 0, left 1
                if (v == 0) {   //down
                    if ((b[i + 2][j - 1] == 1) or (b[i + 2][j] == 1) or (b[i + 2][j + 1] == 1) or (b[i + 3][j - 1] == 1) or (b[i + 3][j] == 1) or (b[i + 3][j + 1] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i + 1][j] = 1; b[i + 2][j] = 1;
                        l += 1;
                        continue;
                    }
                }
                if (v == 1) {  //left
                    if ((b[i - 1][j - 2] == 1) or (b[i][j - 2] == 1) or (b[i + 1][j - 2] == 1) or (b[i - 1][j - 3] == 1) or (b[i][j - 3] == 1) or (b[i + 1][j - 3] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i][j - 1] = 1; b[i][j - 2] = 1;
                        l += 1;
                        continue;
                    }
                }
            }
        }
    }
    l = 0;      //count 2 ships
    while (l < 3) {
        int i = rand() % size + 1; int j = rand() % size + 1;
        if ((b[i - 1][j - 1] == 1) or (b[i - 1][j] == 1) or (b[i - 1][j + 1] == 1) or (b[i][j - 1] == 1) or (b[i][j] == 1) or (b[i][j + 1] == 1) or (b[i + 1][j - 1] == 1) or (b[i + 1][j] == 1) or (b[i + 1][j + 1] == 1)) continue;
        else {
            if (i >= 2 && i <= 9 && j >= 2 && j <= 9) {
                int v = rand() % 2;     //vertical 0, horizont 1
                if (v == 0) {    //vertical
                    int r = rand() % 2;   //down 0, up 1
                    if (r == 0) {    //down
                        if ((b[i + 2][j - 1] == 1) or (b[i + 2][j] == 1) or (b[i + 2][j + 1] == 1)) continue;
                        else {
                            b[i][j] = 1; b[i + 1][j] = 1;
                            l += 1;
                            continue;
                        }
                    }
                    if (r == 1) {   //up
                        if ((b[i - 2][j - 1] == 1) or (b[i - 2][j] == 1) or (b[i - 2][j + 1] == 1)) continue;
                        else {
                            b[i][j] = 1; b[i - 1][j] = 1;
                            l += 1;
                            continue;
                        }
                    }
                }
                if (v == 1) {   //horizont
                    int r = rand() % 2;   //left 0, right 1
                    if (r == 0) {       //left
                        if ((b[i - 1][j - 2] == 1) or (b[i][j - 2] == 1) or (b[i + 1][j - 2] == 1)) continue;
                        else {
                            b[i][j] = 1; b[i][j - 1] = 1;
                            l += 1;
                            continue;
                        }
                    }
                    if (r == 1) {       //right
                        if ((b[i - 1][j + 2] == 1) or (b[i][j + 2] == 1) or (b[i + 1][j + 2] == 1)) continue;
                        else {
                            b[i][j] = 1; b[i][j + 1] = 1;
                            l += 1;
                            continue;
                        }
                    }
                }
            }
            if (i >= 1 && i <= 9 && j == 1) {
                int v = rand() % 2;     //down 0, right 1
                if (v == 0) {   //down
                    if ((b[i + 2][j - 1] == 1) or (b[i + 2][j] == 1) or (b[i + 2][j + 1] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i + 1][j] = 1;
                        l += 1;
                        continue;
                    }
                }
                if (v == 1) {   //right
                    if ((b[i - 1][j + 2] == 1) or (b[i][j + 2] == 1) or (b[i + 1][j + 2] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i][j + 1] = 1;
                        l += 1;
                        continue;
                    }
                }
            }
            if (i == 10 && j >= 1 && j <= 9) {
                int v = rand() % 2;     //up 0, right 1
                if (v == 0) {       //up
                    if ((b[i - 2][j - 1] == 1) or (b[i - 2][j] == 1) or (b[i - 2][j + 1] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i - 1][j] = 1;
                        l += 1;
                        continue;
                    }
                }
                if (v == 1) {       //right
                    if ((b[i - 1][j + 2] == 1) or (b[i][j + 2] == 1) or (b[i + 1][j + 2] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i][j + 1] = 1;
                        l += 1;
                        continue;
                    }
                }
            }
            if (i >= 2 && i <= 10 && j == 10) {
                int v = rand() % 2;     //up 0, left 1
                if (v == 0) {   //up
                    if ((b[i - 2][j - 1] == 1) or (b[i - 2][j] == 1) or (b[i - 2][j + 1] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i - 1][j] = 1;
                        l += 1;
                        continue;
                    }
                }
                if (v == 1) {   //left
                    if ((b[i - 1][j - 2] == 1) or (b[i][j - 2] == 1) or (b[i + 1][j - 2] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i][j - 1] = 1;
                        l += 1;
                        continue;
                    }
                }
            }
            if (i == 1 && j >= 2 && j <= 10) {
                int v = rand() % 2;      //down 0, left 1
                if (v == 0) {   //down
                    if ((b[i + 2][j - 1] == 1) or (b[i + 2][j] == 1) or (b[i + 2][j + 1] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i + 1][j] = 1;
                        l += 1;
                        continue;
                    }
                }
                if (v == 1) {  //left
                    if ((b[i - 1][j - 2] == 1) or (b[i][j - 2] == 1) or (b[i + 1][j - 2] == 1)) continue;
                    else {
                        b[i][j] = 1; b[i][j - 1] = 1;
                        l += 1;
                        continue;
                    }
                }

            }
        }
    }
    l = 0;      //count 1 ships
    while (l < 4) {
        int i = rand() % size + 1; int j = rand() % size + 1;
        if ((b[i - 1][j - 1] == 1) or (b[i - 1][j] == 1) or (b[i - 1][j + 1] == 1) or (b[i][j - 1] == 1) or (b[i][j] == 1) or (b[i][j + 1] == 1) or (b[i + 1][j - 1] == 1) or (b[i + 1][j] == 1) or (b[i + 1][j + 1] == 1)) continue;
        else {
            b[i][j] = 1;
            l += 1;
        }
    }
}

bool isSunk(int x, int y, int Grid[size+2][size+2], int size) {
    if (Grid[x + 1][y] != 1) {
        if (Grid[x + 1][y] == 3 || Grid[x + 1][y] == 4) {
            if (Grid[x + 2][y] != 1) {
                if (Grid[x + 2][y] == 3 || Grid[x + 2][y] == 4) {
                    if (Grid[x + 3][y] != 1) {
                        if (Grid[x + 3][y] == 3 || Grid[x + 3][y] == 4) {
                            return true;
                        }
                    }
                    else if (Grid[x + 3][y] == 1) {
                        return false;
                    }
                }
            }
            else if (Grid[x + 2][y] == 1) {
                return false;
            }
        }
    }
    else if (Grid[x + 1][y] == 1) {
        return false;
    }
    if (Grid[x - 1][y] != 1) {
        if (Grid[x - 1][y] == 3 || Grid[x - 1][y] == 4) {
            if (Grid[x - 2][y] != 1) {
                if (Grid[x - 2][y] == 3 || Grid[x - 2][y] == 4) {
                    if (Grid[x - 3][y] != 1) {
                        if (Grid[x - 3][y] == 3 || Grid[x - 3][y] == 4) {
                            return true;
                        }
                    }
                    else if (Grid[x - 3][y] == 1) {
                        return false;
                    }
                }
            }
            else if (Grid[x - 2][y] == 1) {
                return false;
            }
        }
    }
    else if (Grid[x - 1][y] == 1) {
        return false;
    }
    if (Grid[x][y + 1] != 1) {
        if (Grid[x][y + 1] == 3 || Grid[x][y + 1] == 4) {
            if (Grid[x][y + 2] != 1) {
                if (Grid[x][y + 2] == 3 || Grid[x][y + 2] == 4) {
                    if (Grid[x][y + 3] != 1) {
                        if (Grid[x][y + 3] == 3 || Grid[x][y + 3] == 4) {
                            return true;
                        }
                    }
                    else if (Grid[x][y + 3] == 1) {
                        return false;
                    }
                }
            }
            else if (Grid[x][y + 2] == 1) {
                return false;
            }
        }
    }
    else if (Grid[x][y + 1] == 1) {
        return false;
    }
    if (Grid[x][y - 1] != 1) {
        if (Grid[x][y - 1] == 3 || Grid[x][y - 1] == 4) {
            if (Grid[x][y - 2] != 1) {
                if (Grid[x][y - 2] == 3 || Grid[x][y - 2] == 4) {
                    if (Grid[x][y - 3] != 1) {
                        if (Grid[x][y - 3] == 3 || Grid[x][y - 3] == 4) {
                            return true;
                        }
                    }
                    else if (Grid[x][y - 3] == 1) {
                        return false;
                    }
                }
            }
            else if (Grid[x][y - 2] == 1) {
                return false;
            }
        }
    }
    else if (Grid[x][y - 1] == 1) {
        return false;
    }
    return true;
}

void drawGrid(RenderWindow& window, int grid[size + 2][size + 2], bool isPlayerGrid) {
    Sprite cell;
    cell.setPosition(sf::Vector2f(cellSize, cellSize));

    float x_offset = 0.f;
    if (!isPlayerGrid) {
        x_offset = (size + 2) * cellSize;
        for (int x = 0; x < size + 2; x++) {
            for (int y = 0; y < size + 2; y++) {
                cell.setPosition(x * cellSize + x_offset, y * cellSize);
                if (computerGrid[x][y] == 0 || computerGrid[x][y] == 1) { // ���������� ������ ��� ������� ����������
                    cell.setTexture(sea);
                }
                else if (computerGrid[x][y] == 2) { // ������
                    cell.setTexture(miss);
                }
                else if (computerGrid[x][y] == 3) { // ���������
                    cell.setTexture(explosion);
                }
                else if (computerGrid[x][y] == 4
                    && computerGrid[x + 1][y] != 1
                    && computerGrid[x - 1][y] != 1
                    && computerGrid[x][y + 1] != 1
                    && computerGrid[x][y - 1] != 1
                    && computerGrid[x + 1][y] != 3
                    && computerGrid[x - 1][y] != 3
                    && computerGrid[x][y + 1] != 3
                    && computerGrid[x][y - 1] != 3
                    && computerGrid[x + 1][y] != 4
                    && computerGrid[x - 1][y] != 4
                    && computerGrid[x][y + 1] != 4
                    && computerGrid[x][y - 1] != 4) { // ������ �������
                    cell.setTexture(ship1exp);
                }
                else if (computerGrid[x][y] == 4
                    && (computerGrid[x + 1][y] == 1
                        || computerGrid[x + 1][y] == 3
                        || computerGrid[x + 1][y] == 4)
                    && computerGrid[x - 1][y] != 1
                    && computerGrid[x][y + 1] != 1
                    && computerGrid[x][y - 1] != 1
                    && computerGrid[x - 1][y] != 3
                    && computerGrid[x][y + 1] != 3
                    && computerGrid[x][y - 1] != 3
                    && computerGrid[x - 1][y] != 4
                    && computerGrid[x][y + 1] != 4
                    && computerGrid[x][y - 1] != 4) { // ������ �������
                    cell.setTexture(shipedgerexp);
                }
                else if (computerGrid[x][y] == 4
                    && (computerGrid[x - 1][y] == 1
                        || computerGrid[x - 1][y] == 3
                        || computerGrid[x - 1][y] == 4)
                    && computerGrid[x + 1][y] != 1
                    && computerGrid[x][y + 1] != 1
                    && computerGrid[x][y - 1] != 1
                    && computerGrid[x + 1][y] != 3
                    && computerGrid[x][y + 1] != 3
                    && computerGrid[x][y - 1] != 3
                    && computerGrid[x + 1][y] != 4
                    && computerGrid[x][y + 1] != 4
                    && computerGrid[x][y - 1] != 4) { // ������ �������
                    cell.setTexture(shipedgelexp);
                }
                else if (computerGrid[x][y] == 4
                    && (computerGrid[x][y - 1] == 1
                        || computerGrid[x][y - 1] == 3
                        || computerGrid[x][y - 1] == 4)
                    && computerGrid[x - 1][y] != 1
                    && computerGrid[x][y + 1] != 1
                    && computerGrid[x + 1][y] != 1
                    && computerGrid[x - 1][y] != 3
                    && computerGrid[x][y + 1] != 3
                    && computerGrid[x + 1][y] != 3
                    && computerGrid[x - 1][y] != 4
                    && computerGrid[x][y + 1] != 4
                    && computerGrid[x + 1][y] != 4) { // ������ �������
                    cell.setTexture(shipedgetexp);
                }
                else if (computerGrid[x][y] == 4
                    && (computerGrid[x][y + 1] == 1
                        || computerGrid[x][y + 1] == 3
                        || computerGrid[x][y + 1] == 4)
                    && computerGrid[x - 1][y] != 1
                    && computerGrid[x + 1][y] != 1
                    && computerGrid[x][y - 1] != 1
                    && computerGrid[x - 1][y] != 3
                    && computerGrid[x + 1][y] != 3
                    && computerGrid[x][y - 1] != 3
                    && computerGrid[x - 1][y] != 4
                    && computerGrid[x + 1][y] != 4
                    && computerGrid[x][y - 1] != 4) { // ������ �������
                    cell.setTexture(shipedgedexp);
                }
                else if (computerGrid[x][y] == 4
                    && computerGrid[x][y + 1] != 1
                    && computerGrid[x][y - 1] != 1
                    && computerGrid[x][y + 1] != 3
                    && computerGrid[x][y - 1] != 3
                    && computerGrid[x][y + 1] != 4
                    && computerGrid[x][y - 1] != 4
                    && ((computerGrid[x + 1][y] == 1
                        && computerGrid[x - 1][y] == 1)
                        || (computerGrid[x + 1][y] == 3
                            && computerGrid[x - 1][y] == 3)
                        || (computerGrid[x + 1][y] == 1
                            && computerGrid[x - 1][y] == 3)
                        || (computerGrid[x + 1][y] == 3
                            && computerGrid[x - 1][y] == 1)
                        || (computerGrid[x + 1][y] == 4
                            && computerGrid[x - 1][y] == 4))) { // ������ �������
                    cell.setTexture(shipmidlrexp);
                }
                else if (computerGrid[x][y] == 4
                    && computerGrid[x + 1][y] != 1
                    && computerGrid[x - 1][y] != 1
                    && computerGrid[x + 1][y] != 3
                    && computerGrid[x - 1][y] != 3
                    && computerGrid[x + 1][y] != 4
                    && computerGrid[x - 1][y] != 4
                    && ((computerGrid[x][y + 1] == 1
                        && computerGrid[x][y - 1] == 1)
                        || (computerGrid[x][y + 1] == 3
                            && computerGrid[x][y - 1] == 3)
                        || (computerGrid[x][y + 1] == 1
                            && computerGrid[x][y - 1] == 3)
                        || (computerGrid[x][y + 1] == 3
                            && computerGrid[x][y - 1] == 1)
                        || (computerGrid[x][y + 1] == 4
                            && computerGrid[x][y - 1] == 4))) { // ������ �������
                    cell.setTexture(shipmidtdexp);
                }
                else if (computerGrid[x][y] == -1) {
                    cell.setTexture(sand);
                }
                window.draw(cell);
            }
        }
    }

    for (int x = 0; x < size + 2; x++) {
        for (int y = 0; y < size + 2; y++) {
            cell.setPosition(x * cellSize, y * cellSize);
            if (playerGrid[x][y] == 0) { // ���������� ������
                cell.setTexture(sea);
            }
            else if (playerGrid[x][y] == 1 
                && playerGrid[x + 1][y] != 1 
                && playerGrid[x - 1][y] != 1 
                && playerGrid[x][y + 1] != 1 
                && playerGrid[x][y - 1] != 1
                && playerGrid[x + 1][y] != 3
                && playerGrid[x - 1][y] != 3
                && playerGrid[x][y + 1] != 3
                && playerGrid[x][y - 1] != 3
                && playerGrid[x + 1][y] != 4
                && playerGrid[x - 1][y] != 4
                && playerGrid[x][y + 1] != 4
                && playerGrid[x][y - 1] != 4) { // ������ �������
                cell.setTexture(ship1);
            }
            else if (playerGrid[x][y] == 4
                && playerGrid[x + 1][y] != 1
                && playerGrid[x - 1][y] != 1
                && playerGrid[x][y + 1] != 1
                && playerGrid[x][y - 1] != 1
                && playerGrid[x + 1][y] != 3
                && playerGrid[x - 1][y] != 3
                && playerGrid[x][y + 1] != 3
                && playerGrid[x][y - 1] != 3
                && playerGrid[x + 1][y] != 4
                && playerGrid[x - 1][y] != 4
                && playerGrid[x][y + 1] != 4
                && playerGrid[x][y - 1] != 4) { // ������ �������
                cell.setTexture(ship1exp);
            }
            else if (playerGrid[x][y] == 1 
                && (playerGrid[x + 1][y] == 1
                    || playerGrid[x + 1][y] == 3)
                && playerGrid[x - 1][y] != 1 
                && playerGrid[x][y + 1] != 1 
                && playerGrid[x][y - 1] != 1 
                && playerGrid[x - 1][y] != 3 
                && playerGrid[x][y + 1] != 3 
                && playerGrid[x][y - 1] != 3
                && playerGrid[x - 1][y] != 4
                && playerGrid[x][y + 1] != 4
                && playerGrid[x][y - 1] != 4) { // ������ �������
                cell.setTexture(shipedger);
            }
            else if (playerGrid[x][y] == 1
                && (playerGrid[x - 1][y] == 1
                    || playerGrid[x - 1][y] == 3)
                && playerGrid[x + 1][y] != 1
                && playerGrid[x][y + 1] != 1
                && playerGrid[x][y - 1] != 1
                && playerGrid[x + 1][y] != 3
                && playerGrid[x][y + 1] != 3
                && playerGrid[x][y - 1] != 3
                && playerGrid[x + 1][y] != 4
                && playerGrid[x][y + 1] != 4
                && playerGrid[x][y - 1] != 4) { // ������ �������
                cell.setTexture(shipedgel);
            }
            else if (playerGrid[x][y] == 1
                && (playerGrid[x][y - 1] == 1
                    || playerGrid[x][y - 1] == 3)
                && playerGrid[x - 1][y] != 1
                && playerGrid[x][y + 1] != 1
                && playerGrid[x + 1][y] != 1
                && playerGrid[x - 1][y] != 3
                && playerGrid[x][y + 1] != 3
                && playerGrid[x + 1][y] != 3
                && playerGrid[x - 1][y] != 4
                && playerGrid[x][y + 1] != 4
                && playerGrid[x + 1][y] != 4) { // ������ �������
                cell.setTexture(shipedget);
            }
            else if (playerGrid[x][y] == 1
                && (playerGrid[x][y + 1] == 1
                    || playerGrid[x][y + 1] == 3)
                && playerGrid[x - 1][y] != 1
                && playerGrid[x + 1][y] != 1
                && playerGrid[x][y - 1] != 1
                && playerGrid[x - 1][y] != 3
                && playerGrid[x + 1][y] != 3
                && playerGrid[x][y - 1] != 3
                && playerGrid[x - 1][y] != 4
                && playerGrid[x + 1][y] != 4
                && playerGrid[x][y - 1] != 4) { // ������ �������
                cell.setTexture(shipedged);
            }

            else if ((playerGrid[x][y] == 3 || playerGrid[x][y] == 4)
                && (playerGrid[x + 1][y] == 1
                    || playerGrid[x + 1][y] == 3
                    || playerGrid[x + 1][y] == 4)
                && playerGrid[x - 1][y] != 1
                && playerGrid[x][y + 1] != 1
                && playerGrid[x][y - 1] != 1
                && playerGrid[x - 1][y] != 3
                && playerGrid[x][y + 1] != 3
                && playerGrid[x][y - 1] != 3
                && playerGrid[x - 1][y] != 4
                && playerGrid[x][y + 1] != 4
                && playerGrid[x][y - 1] != 4) { // ������ �������
                cell.setTexture(shipedgerexp);
            }
            else if ((playerGrid[x][y] == 3 || playerGrid[x][y] == 4)
                && (playerGrid[x - 1][y] == 1
                    || playerGrid[x - 1][y] == 3
                    || playerGrid[x - 1][y] == 4)
                && playerGrid[x + 1][y] != 1
                && playerGrid[x][y + 1] != 1
                && playerGrid[x][y - 1] != 1
                && playerGrid[x + 1][y] != 3
                && playerGrid[x][y + 1] != 3
                && playerGrid[x][y - 1] != 3
                && playerGrid[x + 1][y] != 4
                && playerGrid[x][y + 1] != 4
                && playerGrid[x][y - 1] != 4) { // ������ �������
                cell.setTexture(shipedgelexp);
            }
            else if ((playerGrid[x][y] == 3 || playerGrid[x][y] == 4)
                && (playerGrid[x][y - 1] == 1
                    || playerGrid[x][y - 1] == 3
                    || playerGrid[x][y - 1] == 4)
                && playerGrid[x - 1][y] != 1
                && playerGrid[x][y + 1] != 1
                && playerGrid[x + 1][y] != 1
                && playerGrid[x - 1][y] != 3
                && playerGrid[x][y + 1] != 3
                && playerGrid[x + 1][y] != 3
                && playerGrid[x - 1][y] != 4
                && playerGrid[x][y + 1] != 4
                && playerGrid[x + 1][y] != 4) { // ������ �������
                cell.setTexture(shipedgetexp);
            }
            else if ((playerGrid[x][y] == 3 || playerGrid[x][y] == 4)
                && (playerGrid[x][y + 1] == 1
                    || playerGrid[x][y + 1] == 3
                    || playerGrid[x][y + 1] == 4)
                && playerGrid[x - 1][y] != 1
                && playerGrid[x + 1][y] != 1
                && playerGrid[x][y - 1] != 1
                && playerGrid[x - 1][y] != 3
                && playerGrid[x + 1][y] != 3
                && playerGrid[x][y - 1] != 3
                && playerGrid[x - 1][y] != 4
                && playerGrid[x + 1][y] != 4
                && playerGrid[x][y - 1] != 4) { // ������ �������
                cell.setTexture(shipedgedexp);
            }

            else if (playerGrid[x][y] == 1 
                && playerGrid[x][y + 1] != 1
                && playerGrid[x][y - 1] != 1
                && playerGrid[x][y + 1] != 3
                && playerGrid[x][y - 1] != 3
                && playerGrid[x][y + 1] != 4
                && playerGrid[x][y - 1] != 4
                && ((playerGrid[x + 1][y] == 1
                && playerGrid[x - 1][y] == 1)
                || (playerGrid[x + 1][y] == 3
                && playerGrid[x - 1][y] == 3)
                || (playerGrid[x + 1][y] == 1
                && playerGrid[x - 1][y] == 3)
                || (playerGrid[x + 1][y] == 3
                && playerGrid[x - 1][y] == 1))) { // ������ �������
                cell.setTexture(shipmidlr);
            }
            else if (playerGrid[x][y] == 1 
                && playerGrid[x + 1][y] != 1
                && playerGrid[x - 1][y] != 1
                && playerGrid[x + 1][y] != 3
                && playerGrid[x - 1][y] != 3
                && playerGrid[x + 1][y] != 4
                && playerGrid[x - 1][y] != 4
                && ((playerGrid[x][y + 1] == 1
                && playerGrid[x][y - 1] == 1)
                || (playerGrid[x][y + 1] == 3
                && playerGrid[x][y - 1] == 3)
                || (playerGrid[x][y + 1] == 1
                && playerGrid[x][y - 1] == 3)
                || (playerGrid[x][y + 1] == 3
                && playerGrid[x][y - 1] == 1))) { // ������ �������
                cell.setTexture(shipmidtd);
            }

            else if ((playerGrid[x][y] == 3 || playerGrid[x][y] == 4)
                && playerGrid[x][y + 1] != 1
                && playerGrid[x][y - 1] != 1
                && playerGrid[x][y + 1] != 3
                && playerGrid[x][y - 1] != 3
                && playerGrid[x][y + 1] != 4
                && playerGrid[x][y - 1] != 4
                && ((playerGrid[x + 1][y] == 1
                && playerGrid[x - 1][y] == 1)
                || (playerGrid[x + 1][y] == 3
                && playerGrid[x - 1][y] == 3)
                || (playerGrid[x + 1][y] == 1
                && playerGrid[x - 1][y] == 3)
                || (playerGrid[x + 1][y] == 3
                && playerGrid[x - 1][y] == 1)
                || (playerGrid[x + 1][y] == 4
                && playerGrid[x - 1][y] == 4))) { // ������ �������
                    cell.setTexture(shipmidlrexp);
                    }
            else if ((playerGrid[x][y] == 3 || playerGrid[x][y] == 4)
                && playerGrid[x + 1][y] != 1
                && playerGrid[x - 1][y] != 1
                && playerGrid[x + 1][y] != 3
                && playerGrid[x - 1][y] != 3
                && playerGrid[x + 1][y] != 4
                && playerGrid[x - 1][y] != 4
                && ((playerGrid[x][y + 1] == 1
                && playerGrid[x][y - 1] == 1)
                || (playerGrid[x][y + 1] == 3
                && playerGrid[x][y - 1] == 3)
                || (playerGrid[x][y + 1] == 1
                && playerGrid[x][y - 1] == 3)
                || (playerGrid[x][y + 1] == 3
                && playerGrid[x][y - 1] == 1)
                || (playerGrid[x][y + 1] == 4
                && playerGrid[x][y - 1] == 4))) { // ������ �������
                    cell.setTexture(shipmidtdexp);
                    }

            else if (playerGrid[x][y] == 2) { // ������
                cell.setTexture(miss);
            }
            else if (playerGrid[x][y] == -1) { // ���������
                cell.setTexture(sand);
            }
            window.draw(cell);
        }
    }
}

void timer() {
    clock_t start_time = clock(); // ��������� �������� �������
    while (clock() < start_time + 2 * CLOCKS_PER_SEC) {} // �������� 2 ������
}

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
    /*sea.loadFromFile("../resources/textures/sea.jpg");
    sand.loadFromFile("../resources/textures/sand.jpg");
    miss.loadFromFile("../resources/textures/miss.jpg");
    ship1.loadFromFile("../resources/textures/ship1.jpg");
    ship1exp.loadFromFile("../resources/textures/ship1exp.jpg");
    shipedger.loadFromFile("../resources/textures/shipedge(r).jpg");
    shipedgerexp.loadFromFile("../resources/textures/shipedge(r)exp.jpg");
    shipedgel.loadFromFile("../resources/textures/shipedge(l).jpg");
    shipedgelexp.loadFromFile("../resources/textures/shipedge(l)exp.jpg");
    shipedget.loadFromFile("../resources/textures/shipedge(t).jpg");
    shipedgetexp.loadFromFile("../resources/textures/shipedge(t)exp.jpg");
    shipedged.loadFromFile("../resources/textures/shipedge(d).jpg");
    shipedgedexp.loadFromFile("../resources/textures/shipedge(d)exp.jpg");
    shipmidlr.loadFromFile("../resources/textures/shipmid(lr).jpg");
    shipmidlrexp.loadFromFile("../resources/textures/shipmid(lr)exp.jpg");
    shipmidtd.loadFromFile("../resources/textures/shipmid(td).jpg");
    shipmidtdexp.loadFromFile("../resources/textures/shipmid(td)exp.jpg");
    explosion.loadFromFile("../resources/textures/explosion.jpg");
    buffer.loadFromFile("../resources/sfx/shoot.wav");*/
    shoot.setBuffer(buffer);
}

void zeroGrid() {
    for (int x = 1; x < size + 1; x++) {
        for (int y = 1; y < size + 1; y++) {
            playerGrid[x][y] = 0;
            computerGrid[x][y] = 0;
        }
    }
    for (int x = 0; x < size + 2; x++) {
        playerGrid[x][0] = -1;
        computerGrid[x][0] = -1;
        playerGrid[x][size + 1] = -1;
        computerGrid[x][size + 1] = -1;
    }
    for (int y = 0; y < size + 2; y++) {
        playerGrid[0][y] = -1;
        computerGrid[0][y] = -1;
        playerGrid[size + 1][y] = -1;
        computerGrid[size + 1][y] = -1;
    }
}

void aroundHit(int Grid[size + 2][size + 2], int x, int y) {
    Grid[x][y] = 4;
    if (Grid[x + 1][y] == 0 && (x + 1) >= 1 && (x + 1) < size + 1 && y >= 1 && y < size + 1) {
        Grid[x + 1][y] = 2;
    }
    if (Grid[x - 1][y] == 0 && (x - 1) >= 1 && (x - 1) < size + 1 && y >= 1 && y < size + 1) {
        Grid[x - 1][y] = 2;
    }
    if (Grid[x][y + 1] == 0 && x >= 1 && x < size + 1 && (y + 1) >= 1 && (y + 1) < size + 1) {
        Grid[x][y + 1] = 2;
    }
    if (Grid[x][y - 1] == 0 && x >= 1 && x < size + 1 && (y - 1) >= 1 && (y - 1) < size + 1) {
        Grid[x][y - 1] = 2;
    }
    if (Grid[x + 1][y + 1] == 0 && (x + 1) >= 1 && (x + 1) < size + 1 && (y + 1) >= 1 && (y + 1) < size + 1) {
        Grid[x + 1][y + 1] = 2;
    }
    if (Grid[x - 1][y - 1] == 0 && (x - 1) >= 1 && (x - 1) < size + 1 && (y - 1) >= 1 && (y - 1) < size + 1) {
        Grid[x - 1][y - 1] = 2;
    }
    if (Grid[x - 1][y + 1] == 0 && (x - 1) >= 1 && (x - 1) < size + 1 && (y + 1) >= 1 && (y + 1) < size + 1) {
        Grid[x - 1][y + 1] = 2;
    }
    if (Grid[x + 1][y - 1] == 0 && (x + 1) >= 1 && (x + 1) < size + 1 && (y - 1) >= 1 && (y - 1) < size + 1) {
        Grid[x + 1][y - 1] = 2;
    }
}

int main() {
    RenderWindow window(VideoMode((size+2) * cellSize * 2, (size + 2) * cellSize), "Battleships", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    srand(time(NULL));

    zeroGrid();

    init();

    Ship_placement(computerGrid);
    Ship_placement(playerGrid);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (isPlayerTurn && event.type == Event::MouseButtonPressed && (event.mouseButton.x < ((size + 2) * 2) * cellSize) && (event.mouseButton.x > (size + 2) * cellSize)) { // ���� ������ ��� ������ � �� ����� �� ������
                int x = (event.mouseButton.x - (size+2) * cellSize) / cellSize;
                int y = event.mouseButton.y / cellSize;

                if (computerGrid[x][y] == 1) { // ����
                    computerGrid[x][y] = 3;
                    win += 1;
                    isPaused = 1;
                    shoot.play();
                }
                else if (computerGrid[x][y] == 0) { // ������
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
                        aroundHit(computerGrid, x, y);
                    }
                }
                if (playerGrid[x][y] == 3) {
                    if (isSunk(x, y, playerGrid, size) == true) {
                        aroundHit(playerGrid, x, y);
                    }
                }
            }
        }
        drawGrid(window, playerGrid, true); // ������ ���� ������
        drawGrid(window, computerGrid, false); // ������ ���� ����������
        window.display();
        if (isPaused == 1) {
            timer();
            isPaused = 0;
        }
        if (!isPlayerTurn) { // ���� ������ ��� ����������
            
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
                if (playerGrid[x][y] == 1) { // �����
                    playerGrid[x][y] = 3;
                    lose += 1;
                    isPaused = 1;
                    shoot.play();
                }
                else { // ������
                    playerGrid[x][y] = 2;
                    isPlayerTurn = true;
                    isPaused = 1;
                    shoot.play();
                }

            }
            else if (flaggg == 0) {

                int x = rand() % size + 1;
                int y = rand() % size + 1;
                while (playerGrid[x][y] == 2 || playerGrid[x][y] == 3 || playerGrid[x][y] == 4) { // �� �������� �� ��� �������� �������
                    x = rand() % size + 1;
                    y = rand() % size + 1;
                }
                if (playerGrid[x][y] == 1) { // �����
                    playerGrid[x][y] = 3;
                    lose += 1;
                    isPaused = 1;
                    shoot.play();
                }
                else { // ������
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