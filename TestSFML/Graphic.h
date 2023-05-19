#pragma once
#pragma warning(disable:6385)
#include <iostream>
#include <cmath>
#include <ctime>
#include <Graphics.hpp>
#include <Audio.hpp>

const int cellSize = 50; // размер €чеек
const int size = 10; // размер пол€

using namespace sf;

int drawGrid(RenderWindow& window, int Gridp[size + 2][size + 2], int Gridc[size + 2][size + 2], bool isPlayerGrid);

int init();