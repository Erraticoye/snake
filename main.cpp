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
int old_direction;
int tail_length = 0;
int length_counter = 0;
int check_cords[2];
int tail_cords[CANVAS_HEIGHT * CANVAS_WIDTH - 1][2] = {};

void change_food_cords(int* cords);
void setCursorPosition(int x, int y);
void game_over(const char message[]);

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
		while (!_kbhit()) {
			setCursorPosition(0, 0);
			now = clock();
			if (now - old_time >= 700) {
				old_time = now;
				old_snake_cords[0] = snake_cords[0];
				old_snake_cords[1] = snake_cords[1];

				//check snakes direction and change snakes cordinates
				if (direction == up) {
					if (--snake_cords[1] < 0) 
						game_over("Don't try to eat walls.");
				}
				else if (direction == down) {
					if (++snake_cords[1] >= CANVAS_HEIGHT)
						game_over("Don't try to eat walls.");
				}
				else if (direction == left) {
					if (--snake_cords[0] < 0)
						game_over("Don't try to eat walls.");
				}
				else if (direction == right) {
					if (++snake_cords[0] >= CANVAS_WIDTH)
						game_over("Don't try to eat walls.");
				}

				for (size_t i = 0; i < CANVAS_WIDTH; i++) {
					for (size_t x = 0; x < CANVAS_HEIGHT; x++) {
						canvas[i][x] = '*';
					}
				}

				canvas[food_cords[0]][food_cords[1]] = '#';

				if (tail_length != 0) {
					tail_cords[tail_length - 1][0] = -1;
					tail_cords[tail_length - 1][1] = -1;

					for (int i = tail_length - 1; i > 0; i--) {
						tail_cords[i][0] = tail_cords[i - 1][0];
						tail_cords[i][1] = tail_cords[i - 1][1];
					}

					tail_cords[0][0] = old_snake_cords[0];
					tail_cords[0][1] = old_snake_cords[1];
				}

				printf("\n%d %d\n", snake_cords[0], snake_cords[1]);
				//check if the char is food
				if (canvas[snake_cords[0]][snake_cords[1]] == '#') {
					++tail_length;
					change_food_cords(food_cords);
					canvas[food_cords[0]][food_cords[1]] = '#';
				}

				for (size_t i = 0; i < tail_length; i++) {
					canvas[tail_cords[i][0]][tail_cords[i][1]] = 'o';
				}
				if (canvas[snake_cords[0]][snake_cords[1]] == 'o') 
					game_over("Stepped on tail.");

				canvas[snake_cords[0]][snake_cords[1]] = '@';

				for (size_t i = 0; i < CANVAS_WIDTH; i++) {
					printf("\n");
					for (size_t x = 0; x < CANVAS_HEIGHT; x++) {
						printf("%c ", canvas[x][i]);
					}
				}
				printf("Score: %d", tail_length);
			}
		}

		pressed_key = _getch();
		if (pressed_key == 'w') {
			if (direction == down && tail_length > 0)
				game_over("Don't try to eat yourself.");
			direction = up;
		}
		else if (pressed_key == 's') {
			if (direction == up && tail_length > 0)
				game_over("Don't try to eat yourself.");
			direction = down;
		}
		else if (pressed_key == 'a') {
			if (direction == right && tail_length > 0)
				game_over("Don't try to eat yourself.");
			direction = left;
		}
		else if (pressed_key == 'd') {
			if (direction == left && tail_length > 0)
				game_over("Don't try to eat yourself.");
			direction = right;
		}
		else if (pressed_key == 'q')
			game_over("You surrendered.");
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

void game_over(const char message[]) {
	setCursorPosition(0, CANVAS_HEIGHT + 5);
	printf("Game Over! - %s", message);
	exit(1);
}