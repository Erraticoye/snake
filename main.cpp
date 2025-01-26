#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define CANVAS_WIDTH 10
#define CANVAS_HEIGHT 10

char canvas[CANVAS_WIDTH][CANVAS_HEIGHT]; //x,y
char pressed_key;
int snake_length = 0;
int snake_cords[2] = { 0,0 }; //x,y
int old_snake_cords[2] = { 0,0 }; //x,y
int food_cords[2];
clock_t old_time, now;
enum directions {up, down, left, right};
int direction = right;
int old_direction; //direction 1 frame before
int score;
int tail_length;
int length_counter = 0;
int check_cords[2];

void change_food_cords(int* cords);
void setCursorPosition(int x, int y);
void check_and_delete_extra_tail();

int main() {
	system("cls");
	old_time = clock();
	srand(time(NULL));
	for (size_t i = 0; i < CANVAS_WIDTH; i++) {
		for (size_t x = 0; x < CANVAS_HEIGHT; x++) {
			canvas[i][x] = '*';
		}
	}
	change_food_cords(food_cords);
	canvas[food_cords[0]][food_cords[1]] = '#';

	while (1) {
		while(!_kbhit()) {
			setCursorPosition(0, 0);
			now = clock();
			if (now - old_time >= 700) {
				old_time = now;
				old_snake_cords[0] = snake_cords[0];
				old_snake_cords[1] = snake_cords[1];
				//check snakes direction and change snakes cordinates
				printf("%d - %d - %d - %d\n", up, down, left, right);
				printf("%d", direction);

				if (old_direction != direction)	{
					/*
					old_direction == up && direction = right |
					*/
				}

				if (direction == up) {
					if (--snake_cords[1] < 0) {
						printf("aGame Over!");
						exit(1);
					}
				}
				else if (direction == down) {
					if (++snake_cords[1] >= CANVAS_HEIGHT) {
						printf("bGame Over!");
						exit(1);
					}
				}
				else if (direction == left) {
					if (--snake_cords[0] < 0) {
						printf("cGame Over!");
						exit(1);
					}
				}
				else if (direction == right) {
					if (++snake_cords[0] >= CANVAS_WIDTH) {
						printf("dGame Over!");
						exit(1);
					}
				}
				printf("\n%d %d\n", snake_cords[0], snake_cords[1]);
				//check if the char is food
				if (canvas[snake_cords[0]][snake_cords[1]] == '#') {
					++score;
					++snake_length;
					change_food_cords(food_cords);
					canvas[food_cords[0]][food_cords[1]] = '#';
					canvas[old_snake_cords[0]][old_snake_cords[1]] = 'O';

				}
				canvas[old_snake_cords[0]][old_snake_cords[1]] = 'O';
				canvas[snake_cords[0]][snake_cords[1]] = '@';

				for (size_t i = 0; i < CANVAS_WIDTH; i++) {
					printf("\n");
					for (size_t x = 0; x < CANVAS_HEIGHT; x++) {
						printf("%c ", canvas[x][i]);
					}
				}
				printf("Score: %d", score);
			}
		}

		pressed_key = _getch();
		old_direction = direction;
		if (pressed_key == 'w')
			direction = up;
		else if (pressed_key == 's') 
			direction = down;
		else if (pressed_key == 'a')
			direction = left;
		else if (pressed_key == 'd')
			direction = right;
		else if (pressed_key == 'q')
			break;
	}
}

void change_food_cords(int* cords) {
	cords[0] = rand() % 10;
	cords[1] = rand() % 10;
}

void setCursorPosition(int x, int y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void check_and_delete_extra_tail() {

}
