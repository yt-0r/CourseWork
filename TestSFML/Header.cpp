#include "Header.h"


int Ship_placement(int b[size + 2][size + 2], int size)
{
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
    int num = 20;
    int currentnum = 0;
    for (int i = 1; i < 11; i++) {
        for (int j = 1; j < 11; j++) {
            if (b[i][j] == 1) {
                currentnum++;
            }
        }
    }
    if (currentnum == num) {
        return 0;
    }
    else {
        return 1;
    }
}

int timer() {
    clock_t start_time = clock(); // Получение текущего времени
    while (clock() < start_time + 1.2 * CLOCKS_PER_SEC) {} // Ожидание 1.2 секунд
    if (clock() > start_time + 1.2 * CLOCKS_PER_SEC) {
        return 1;
    }
    return 0;
}

int zeroGrid(int Gridp[size + 2][size + 2], int Gridc[size + 2][size + 2]) {
    for (int x = 1; x < size + 1; x++) {
        for (int y = 1; y < size + 1; y++) {
            Gridp[x][y] = 0;
            Gridc[x][y] = 0;
        }
    }
    for (int x = 1; x < size + 1; x++) {
        for (int y = 1; y < size + 1; y++) {
            if (Gridp[x][y] != 0 || Gridc[x][y] != 0) {
                return 1;
            }
        }
    }
    for (int x = 0; x < size + 2; x++) {
        Gridp[x][0] = -1;
        Gridc[x][0] = -1;
        Gridp[x][size + 1] = -1;
        Gridc[x][size + 1] = -1;
    }
    for (int x = 0; x < size + 2; x++) {
        if (Gridp[x][0] != -1 || Gridc[x][0] != -1 || Gridp[x][size + 1] != -1 || Gridc[x][size + 1] != -1) {
            return 1;
        }
    }
    for (int y = 0; y < size + 2; y++) {
        Gridp[0][y] = -1;
        Gridc[0][y] = -1;
        Gridp[size + 1][y] = -1;
        Gridc[size + 1][y] = -1;
    }
    for (int y = 0; y < size + 2; y++) {
        if (Gridp[0][y] != -1 || Gridc[0][y] != -1 || Gridp[size + 1][y] != -1 || Gridc[size + 1][y] != -1) {
            return 1;
        }
    }
    return 0;
}

int aroundHit(int Grid[size + 2][size + 2], int x, int y) {
    if (x > size + 1 || y > size + 1 || x < 1 || y < 1) {
        return 1;
    }
    Grid[x][y] = 4;
    if (Grid[x + 1][y] == 0 && (x + 1) >= 1 && (x + 1) < size + 1 && y >= 1 && y < size + 1) {
        Grid[x + 1][y] = 2;
        if (x + 1 >= size + 2) {
            return 1;
        }
    }
    if (Grid[x - 1][y] == 0 && (x - 1) >= 1 && (x - 1) < size + 1 && y >= 1 && y < size + 1) {
        Grid[x - 1][y] = 2;
        if (x - 1 <= 0) {
            return 1;
        }
    }
    if (Grid[x][y + 1] == 0 && x >= 1 && x < size + 1 && (y + 1) >= 1 && (y + 1) < size + 1) {
        Grid[x][y + 1] = 2;
        if (y + 1 >= size + 2) {
            return 1;
        }
    }
    if (Grid[x][y - 1] == 0 && x >= 1 && x < size + 1 && (y - 1) >= 1 && (y - 1) < size + 1) {
        Grid[x][y - 1] = 2;
        if (y - 1 <= 0) {
            return 1;
        }
    }
    if (Grid[x + 1][y + 1] == 0 && (x + 1) >= 1 && (x + 1) < size + 1 && (y + 1) >= 1 && (y + 1) < size + 1) {
        Grid[x + 1][y + 1] = 2;
        if (x + 1 >= size + 2 || y + 1 >= size + 2) {
            return 1;
        }
    }
    if (Grid[x - 1][y - 1] == 0 && (x - 1) >= 1 && (x - 1) < size + 1 && (y - 1) >= 1 && (y - 1) < size + 1) {
        Grid[x - 1][y - 1] = 2;
        if (x - 1 <= 0 || y - 1 <= 0) {
            return 1;
        }
    }
    if (Grid[x - 1][y + 1] == 0 && (x - 1) >= 1 && (x - 1) < size + 1 && (y + 1) >= 1 && (y + 1) < size + 1) {
        Grid[x - 1][y + 1] = 2;
        if (x - 1 <= 0 || y + 1 >= size + 2) {
            return 1;
        }
    }
    if (Grid[x + 1][y - 1] == 0 && (x + 1) >= 1 && (x + 1) < size + 1 && (y - 1) >= 1 && (y - 1) < size + 1) {
        Grid[x + 1][y - 1] = 2;
        if (x + 1 >= size + 2 || y - 1 <= 0) {
            return 1;
        }
    }
    return 0;
}

bool isSunk(int x, int y, int Grid[size + 2][size + 2], int size) {
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