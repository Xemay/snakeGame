#pragma once
#include<iostream>
#include <windows.h>
#include<conio.h>


#include "snake.h"



class Map {

public:
	int width, height;
	COORD apple_c;

	const char apple = 'o';


	Map(int width, int height) {

		this->height = height;
		this->width = width;
	}

	void generate_map(HANDLE h) {

		// фкнция для генерации карты

		SetConsoleTextAttribute(h, 4);
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				char s;
				if (x == 0 && y == 0)
					s = 218;
				else if (x == 0 && y == height - 1)
					s = 192;
				else if (y == 0 && x == width - 1)
					s = 191;
				else if (y == height - 1 && x == width - 1)
					s = 217;
				else if (y == 0 || y == height - 1)
					s = 196;
				else if (x == 0 || x == width - 1)
					s = 179;
				else s = ' ';
				putchar(s);
			}
			std::cout << std::endl;
		}
}

	void set_apple(Snake snake) {
		int i;
		do
		{
			apple_c.X = rand() % (width - 2) + 1;
			apple_c.Y = rand() % (height - 2) + 1;
			i = 0;
			for (; i < snake.length; i++)
				if (apple_c.X == snake.array_X[i] && apple_c.Y == snake.array_Y[i])
					break;
		} while (i < snake.length);
	}
};