#pragma once
#include <iostream>
#include <cmath>
#include <ctime>
#include <Graphics.hpp>
#include <Audio.hpp>

const int cellSize = 50; // ������ �����
const int size = 10; // ������ ����

using namespace sf;

int drawGrid(RenderWindow& window, int Gridp[size + 2][size + 2], int Gridc[size + 2][size + 2], bool isPlayerGrid);

int init();