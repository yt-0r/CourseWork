#pragma once
#pragma warning(disable:6385)
#pragma warning(disable:6386)
#pragma warning(disable:4244)
#include <cmath>
#include <ctime>
#include "PublicVar.h"

int Ship_placement(int b[size + 2][size + 2], int size);

bool isSunk(int x, int y, int Grid[size + 2][size + 2], int size);

int timer();

int zeroGrid(int Gridp[size + 2][size + 2], int Gridc[size + 2][size + 2]);

int aroundHit(int Grid[size + 2][size + 2], int x, int y);

int checkforHit(int Grid[size + 2][size + 2]);

int computerHit(int Grid[size + 2][size + 2], int hits, int& x, int& y);