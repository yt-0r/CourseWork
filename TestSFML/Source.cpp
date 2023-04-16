#include <Graphics.hpp>
#include <iostream>

using namespace sf;

const int cellSize = 50; // размер €чеек
const int size = 10; // размер пол€
int win = 0;
int lose = 0;

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
                else if (computerGrid[x][y] == 4) { // попадание
                    cell.setFillColor(Color::Black);
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
            else if (playerGrid[x][y] == 4) { // попадание
                cell.setFillColor(Color::Black);
                cell.setOutlineColor(Color::Black);
            }
            window.draw(cell);
        }
    }
}

void Computer_placement(int b[size][size]) {
    int l = 0;      //count 4 ships
    while (l < 1) {
        int i = rand() % size; int j = rand() % size;
        b[i][j] = 1;
        if ((i >= 3 && i <= 6) && (j > 2 && j < 7)) {
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
        if ((i >= 0 && i <= 6) && (j >= 0 && j <= 2)) {
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
        if ((i >= 7 && i <= 9) && (j >= 0 && j <= 6)) {
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
        if ((i >= 3 && i <= 9) && (j >= 7 && j <= 9)) {
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
        if ((i >= 0 && i <= 2) && (j >= 3 && j <= 9)) {
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
        int i = rand() % size; int j = rand() % size;
        if ((b[i - 1][j - 1] == 1) or (b[i - 1][j] == 1) or (b[i - 1][j + 1] == 1) or (b[i][j - 1] == 1) or (b[i][j] == 1) or (b[i][j + 1] == 1) or (b[i + 1][j - 1] == 1) or (b[i + 1][j] == 1) or (b[i + 1][j + 1] == 1)) continue;
        else {
            if (i >= 2 && i <= 7 && j >= 2 && j <= 7) {
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
            if (i >= 0 && i <= 7 && j >= 0 && j <= 1) {
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
            if (i >= 8 && i <= 9 && j >= 0 && j <= 7) {
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
            if (i >= 1 && i <= 9 && j >= 8 && j <= 9) {
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
            if (i >= 0 && i <= 1 && j>=1 && j<=9) {
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
        int i = rand() % size; int j = rand() % size;
        if ((b[i - 1][j - 1] == 1) or (b[i - 1][j] == 1) or (b[i - 1][j + 1] == 1) or (b[i][j - 1] == 1) or (b[i][j] == 1) or (b[i][j + 1] == 1) or (b[i + 1][j - 1] == 1) or (b[i + 1][j] == 1) or (b[i + 1][j + 1] == 1)) continue;
        else {
            if (i >= 1 && i <= 8 && j >= 1 && j <= 8) {
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
            if (i >= 0 && i <= 8 && j == 0) {
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
            if (i == 9 && j >= 0 && j <= 8) {
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
            if (i >= 1 && i <= 9 && j == 9) {
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
            if (i == 0 && j >= 1 && j <= 9) {
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
        int i = rand() % size; int j = rand() % size;
        if ((b[i - 1][j - 1] == 1) or (b[i - 1][j] == 1) or (b[i - 1][j + 1] == 1) or (b[i][j - 1] == 1) or (b[i][j] == 1) or (b[i][j + 1] == 1) or (b[i + 1][j - 1] == 1) or (b[i + 1][j] == 1) or (b[i + 1][j + 1] == 1)) continue;
        else {
            b[i][j] = 1;
            l += 1;
        }
    }
}

void Player_placement(int b[size][size]) {
    int l = 0;      //count 4 ships
    while (l < 1) {
        int i = rand() % size; int j = rand() % size;
        b[i][j] = 1;
        if ((i >= 3 && i <= 6) && (j > 2 && j < 7)) {
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
        if ((i >= 0 && i <= 6) && (j >= 0 && j <= 2)) {
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
        if ((i >= 7 && i <= 9) && (j >= 0 && j <= 6)) {
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
        if ((i >= 3 && i <= 9) && (j >= 7 && j <= 9)) {
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
        if ((i >= 0 && i <= 2) && (j >= 3 && j <= 9)) {
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
        int i = rand() % size; int j = rand() % size;
        if ((b[i - 1][j - 1] == 1) or (b[i - 1][j] == 1) or (b[i - 1][j + 1] == 1) or (b[i][j - 1] == 1) or (b[i][j] == 1) or (b[i][j + 1] == 1) or (b[i + 1][j - 1] == 1) or (b[i + 1][j] == 1) or (b[i + 1][j + 1] == 1)) continue;
        else {
            if (i >= 2 && i <= 7 && j >= 2 && j <= 7) {
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
            if (i >= 0 && i <= 7 && j >= 0 && j <= 1) {
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
            if (i >= 8 && i <= 9 && j >= 0 && j <= 7) {
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
            if (i >= 1 && i <= 9 && j >= 8 && j <= 9) {
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
            if (i >= 0 && i <= 1 && j >= 1 && j <= 9) {
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
        int i = rand() % size; int j = rand() % size;
        if ((b[i - 1][j - 1] == 1) or (b[i - 1][j] == 1) or (b[i - 1][j + 1] == 1) or (b[i][j - 1] == 1) or (b[i][j] == 1) or (b[i][j + 1] == 1) or (b[i + 1][j - 1] == 1) or (b[i + 1][j] == 1) or (b[i + 1][j + 1] == 1)) continue;
        else {
            if (i >= 1 && i <= 8 && j >= 1 && j <= 8) {
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
            if (i >= 0 && i <= 8 && j == 0) {
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
            if (i == 9 && j >= 0 && j <= 8) {
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
            if (i >= 1 && i <= 9 && j == 9) {
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
            if (i == 0 && j >= 1 && j <= 9) {
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
        int i = rand() % size; int j = rand() % size;
        if ((b[i - 1][j - 1] == 1) or (b[i - 1][j] == 1) or (b[i - 1][j + 1] == 1) or (b[i][j - 1] == 1) or (b[i][j] == 1) or (b[i][j + 1] == 1) or (b[i + 1][j - 1] == 1) or (b[i + 1][j] == 1) or (b[i + 1][j + 1] == 1)) continue;
        else {
            b[i][j] = 1;
            l += 1;
        }
    }
}

bool isSunk(int x, int y, int Grid[10][10], int size) {
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

int main() {
    RenderWindow window(VideoMode(size * cellSize * 2.5, size * cellSize), "Battleships", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);
    // инициализируем поле игрока и компьютера
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            playerGrid[x][y] = 0;
            computerGrid[x][y] = 0;
        }
    }

    // рандомно размещаем корабли компьютера
    srand(time(NULL));

    Computer_placement(computerGrid);
    Player_placement(playerGrid);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (isPlayerTurn && event.type == Event::MouseButtonPressed && (event.mouseButton.x < ((size * 2) + 0.5f) * cellSize) && (event.mouseButton.x > (size + 0.5f) * cellSize)) { // если сейчас ход игрока и он нажал на €чейку
                int x = (event.mouseButton.x - (size + 0.5f) * cellSize) / cellSize;
                int y = event.mouseButton.y / cellSize;

                if (computerGrid[x][y] == 1) { // убил
                    computerGrid[x][y] = 3;
                    win += 1;
                }
                else if (computerGrid[x][y] == 4) {
                    computerGrid[x][y] = 4;
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

        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                if (computerGrid[x][y] == 3) {
                    if (isSunk(x, y, computerGrid, size) == true) {
                        computerGrid[x][y] = 4;
                        if (computerGrid[x + 1][y] == 0 && (x + 1) >= 0 && (x + 1) < 10 && y >= 0 && y < 10) {
                            computerGrid[x + 1][y] = 2;
                        }
                        if (computerGrid[x - 1][y] == 0 && (x - 1) >= 0 && (x - 1) < 10 && y >= 0 && y < 10) {
                            computerGrid[x - 1][y] = 2;
                        }
                        if (computerGrid[x][y + 1] == 0 && x >= 0 && x < 10 && (y + 1) >= 0 && (y + 1) < 10) {
                            computerGrid[x][y + 1] = 2;
                        }
                        if (computerGrid[x][y - 1] == 0 && x >= 0 && x < 10 && (y - 1) >= 0 && (y - 1) < 10) {
                            computerGrid[x][y - 1] = 2;
                        }
                        if (computerGrid[x + 1][y + 1] == 0 && (x + 1) >= 0 && (x + 1) < 10 && (y + 1) >= 0 && (y + 1) < 10) {
                            computerGrid[x + 1][y + 1] = 2;
                        }
                        if (computerGrid[x - 1][y - 1] == 0 && (x - 1) >= 0 && (x - 1) < 10 && (y - 1) >= 0 && (y - 1) < 10) {
                            computerGrid[x - 1][y - 1] = 2;
                        }
                        if (computerGrid[x - 1][y + 1] == 0 && (x - 1) >= 0 && (x - 1) < 10 && (y + 1) >= 0 && (y + 1) < 10) {
                            computerGrid[x - 1][y + 1] = 2;
                        }
                        if (computerGrid[x + 1][y - 1] == 0 && (x + 1) >= 0 && (x + 1) < 10 && (y - 1) >= 0 && (y - 1) < 10) {
                            computerGrid[x + 1][y - 1] = 2;
                        }
                    }
                }
            }
        }

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
                lose += 1;
            }
            else { // промах
                playerGrid[x][y] = 2;
                isPlayerTurn = true;
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