#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>

#include "snake.h"
#include "enums.h"
#include "map.h"


using namespace std;


void render_char(HANDLE h, COORD c, char c_, int color=10) {

	// функция для отрисовки символа на экране свыбранным цветом

	SetConsoleTextAttribute(h, color);
	SetConsoleCursorPosition(h, c);
	putchar(c_);
	SetConsoleTextAttribute(h, 10);
}


int main()
{
	srand(time(0));
	rand();
	system("mode con cols=51 lines=31");

	MoveWindow(GetConsoleWindow(), 700, 300, 450, 550, true);

	Snake snake('@', '*');
	Map map(50, 30);

	snake.array_X[0] = map.width / 2;
	snake.array_Y[0] = map.height / 2;

	int fps = 100;

	do
	{
		// ставим первое яблоко в игре

		map.apple_c.X = rand() % (map.width - 2) + 1;
		map.apple_c.Y = rand() % (map.height - 2) + 1;
	} while (map.apple_c.X != snake.array_X[snake.length - 1] && map.apple_c.Y != snake.array_Y[snake.length - 1]);

	COORD c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci = { sizeof(cci), false };
	SetConsoleCursorInfo(h, &cci);


	map.generate_map(h);

	render_char(h, map.apple_c, map.apple, 12);

	c.X = snake.array_X[0];
	c.Y = snake.array_Y[0];
	
	render_char(h, c, snake.head);

	bool flag = true;
	do
	{
		Sleep(fps);

		if (_kbhit())
		{

			// обработка нажатой клавиши

			int k = _getch();
			if (k == 0 || k == 224)
				k = _getch();
			flag = snake.key_processing(k);
		}

		int X = snake.array_X[snake.length - 1] + snake.dx;
		int Y = snake.array_Y[snake.length - 1] + snake.dy;
		if (X == 0 || X == map.width - 1 || Y == 0 || Y == map.height - 1)
		{
			flag = false;
		}
		else if (X == map.apple_c.X && Y == map.apple_c.Y)
		{
			c.X = snake.array_X[snake.length - 1];
			c.Y = snake.array_Y[snake.length - 1];
			render_char(h, c, snake.body);

			snake.length++;
			c.X = snake.array_X[snake.length - 1] = X;
			c.Y = snake.array_Y[snake.length - 1] = Y;
			render_char(h, c, snake.head);

			if (snake.length == snake.max_length)
			{
				break;
			}
			map.set_apple(snake);


			render_char(h, map.apple_c, map.apple, 12);
		}
		else
		{
			int i = 1;
			for (; i < snake.length; i++)
				if (X == snake.array_X[i] && Y == snake.array_Y[i])
					break;
			if (i < snake.length)
			{
				break;
			}
			else
			{
				c.X = snake.array_X[0];
				c.Y = snake.array_Y[0];
				render_char(h, c, ' ');

				if (snake.length > 1)
				{
					c.X = snake.array_X[snake.length - 1];
					c.Y = snake.array_Y[snake.length - 1];
					render_char(h, c, snake.body);
				}

				for (int i = 0; i < snake.length - 1; i++)
				{
					snake.array_X[i] = snake.array_X[i + 1];
					snake.array_Y[i] = snake.array_Y[i + 1];
				}

				c.X = snake.array_X[snake.length - 1] = X;
				c.Y = snake.array_Y[snake.length - 1] = Y;
				
				render_char(h, c, snake.head);
			}
		}
	} while (flag);
	system("cls");
	cout << "GAME OVER";
	return 0;
}