#pragma once
#include <Graphics.hpp>
#include <Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

const int cellSize = 50; // размер €чеек
const int size = 10; // размер пол€

int Ship_placement(int b[size + 2][size + 2], int size);

bool isSunk(int x, int y, int Grid[size + 2][size + 2], int size);

int timer();

int zeroGrid(int Gridp[size + 2][size + 2], int Gridc[size + 2][size + 2]);

int aroundHit(int Grid[size + 2][size + 2], int x, int y);
