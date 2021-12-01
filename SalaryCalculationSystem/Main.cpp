#define NOMINMAX
#include <vector>
#include <stdexcept>
#include <string>
#include <conio.h>
#include <iostream>
#include <Windows.h>
#include "Menu.h"


int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu();
	return 0;
}