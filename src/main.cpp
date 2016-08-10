#include <cstdlib>
#include <iostream>
#include <fstream>
#include "game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <time.h>
#include <Windows.h>
using namespace std;

int main() {
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);
	Game game;
	game.mainLoop();
	return 0;
}