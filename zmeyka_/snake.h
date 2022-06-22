#pragma once

#include "enums.h"


class Snake {
	
public:
	char head, body;

	int length = 1;
	int dx = 1, dy = 0;

	const int max_length = 50;

	int array_X[50];
	int array_Y[50];
	


	Snake(char head, char body) {
		this->head = head;
		this->body = body;
	}


	bool key_processing(int key) {

		// функция для обработки нажатой клавиши

		switch (key)
		{
		case DOWN:
			dy = 1;
			dx = 0;
			break;
		case UP:
			dy = -1;
			dx = 0;
			break;
		case LEFT:
			dy = 0;
			dx = -1;
			break;
		case RIGHT:
			dy = 0;
			dx = 1;
			break;
		case 27: // ESC
			return false;
			break;
		}
		return true;

	}



};