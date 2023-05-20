#pragma once
#include <Graphics.hpp>
#include "PublicVar.h"

using namespace sf;

int drawGrid(RenderWindow& window, int Gridp[size + 2][size + 2], int Gridc[size + 2][size + 2], bool isPlayerGrid);

int initGraphic();