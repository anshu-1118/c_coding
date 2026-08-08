#include <stdio.h>
#include <stdlib.h>

// 1. CROSS-PLATFORM LIBRARIES
#ifdef _WIN32
	#include <conio.h>   // console input output functions
	#include <windows.h>
#else                   //Linux library
	#include <unistd.h>
	#include <termios.h>
	#include <fcntl.h>
#endif

// --- Data Structure ---
typedef struct node
{
	int x;
	int y;
	struct node* next;
} node;

node* tailTip = NULL;
node* snakeHead = NULL;

// --- Global Variables ---
int gameOver;
const int width = 20;
const int height = 20;
int fruitX, fruitY, score, highScore;

enum eDirection
{
	STOP = 0, 
	LEFT, 
	RIGHT, 
	UP, 
	DOWN
};

enum eDirection dir;

// 2. CROSS-PLATFORM TERMINAL SETUP
#ifndef _WIN32
	struct termios orig_termios;
	
	void disable_raw_mode()
	{
		tcsetattr(0, TCSAFLUSH, &orig_termios);
		printf("\033[?25h");
	}
	
	void enable_raw_mode()
	{
		tcgetattr(0, &orig_termios);
		atexit(disable_raw_mode);
		struct termios raw = orig_termios;
		raw.c_lflag &= ~(ECHO | ICANON);
		tcsetattr(0, TCSAFLUSH, &raw);
		int flags = fcntl(0, F_GETFL, 0);
		fcntl(0, F_SETFL, flags | O_NONBLOCK);
		printf("\033[?25l");
	}
#else
	void hide_cursor()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(hConsole, &cursorInfo);
		cursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(hConsole, &cursorInfo);
	}
#endif

// 3. CROSS-PLATFORM UTILS
void reset_cursor()
{
#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {0, 0};
	SetConsoleCursorPosition(hConsole, pos);
#else
	printf("\033[H");
#endif
}

void sleep_ms(int milliseconds)
{
#ifdef _WIN32
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif
}

// --- File I/O: High Score Management ---
void loadHighScore()
{
	FILE* file = fopen("highscore.txt", "r");
	
	if (file != NULL)
	{
		fscanf(file, "%d", &highScore);
		fclose(file);
	}
	else
	{
		highScore = 0;
	}
}

void saveHighScore()
{
	FILE* file = fopen("highscore.txt", "w");
	
	if (file != NULL)
	{
		fprintf(file, "%d", highScore);
		fclose(file);
	}
}

// --- Linked List Operations ---
void addNode(int x, int y)
{
	node* newNode = (node*)malloc(sizeof(node));
	newNode->x = x;
	newNode->y = y;
	newNode->next = NULL;

	if (snakeHead == NULL)
	{
		tailTip = newNode;
		snakeHead = newNode;
		return;
	}
	
	snakeHead->next = newNode;
	snakeHead = newNode;
}

void removeTail()
{
	if (tailTip == NULL)
	{
		return;
	}
	
	node* temp = tailTip;
	tailTip = tailTip->next;
	
	if (tailTip == NULL)
	{
		snakeHead = NULL;
	}
	
	free(temp);
}

int isBody(int x, int y)
{
	node* current = tailTip;
	
	while (current != NULL && current != snakeHead)
	{
		if (current->x == x && current->y == y)
		{
			return 1;
		}
		
		current = current->next;
	}
	
	return 0;
}

// --- Game Logic ---
void Setup()
{
	gameOver = 0;
	dir = STOP;
	score = 0;

	loadHighScore();

	addNode(width / 2, height / 2);
	fruitX = rand() % width;
	fruitY = rand() % height;

#ifdef _WIN32
	hide_cursor();
	system("cls");
#else
	enable_raw_mode();
	printf("\033[2J");
#endif
}

void Draw()
{
	reset_cursor();

	for (int i = 0; i < width + 2; i++)
	{
		printf("#");
	}
	
	printf("\n");

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				printf("#");
			}
			if (snakeHead != NULL && i == snakeHead->y && j == snakeHead->x)
			{
				printf("O");
			}
			else if (i == fruitY && j == fruitX)
			{
				printf("\033[91m*\033[0m");
			}
			else if (isBody(j, i))
			{
				printf("o");
			}
			else
			{
				printf(" ");
			}

			if (j == width - 1)
			{
				printf("#");
			}
		}
		
		printf("\n");
	}

	for (int i = 0; i < width + 2; i++)
	{
		printf("#");
	}

	printf("\nScore: %d   |   High Score: %d     \n", score, highScore);
}

void Input()
{
	char c = 0;
	
#ifdef _WIN32
	if (_kbhit())
	{
		c = _getch();
	}
#else
	c = getchar();
#endif

	if (c != 0 && c != EOF)
	{
		switch (c)
		{
			case 'a':
				if (dir != RIGHT)
				{
					dir = LEFT;
				}
				break;
			case 'd':
				if (dir != LEFT)
				{
					dir = RIGHT;
				}
				break;
			case 'w':
				if (dir != DOWN)
				{
					dir = UP;
				}
				break;
			case 's':
				if (dir != UP)
				{
					dir = DOWN;
				}
				break;
			case 'x':
				gameOver = 1;
				break;
		}
	}
}

void Logic()
{
	if (dir == STOP || snakeHead == NULL)
	{
		return;
	}

	int newX = snakeHead->x;
	int newY = snakeHead->y;

	switch (dir)
	{
		case LEFT:
			newX--;
			break;
		case RIGHT:
			newX++;
			break;
		case UP:
			newY--;
			break;
		case DOWN:
			newY++;
			break;
	}

	// Screen Wrapping
	if (newX >= width)
	{
		newX = 0;
	}
	else if (newX < 0)
	{
		newX = width - 1;
	}

	if (newY >= height)
	{
		newY = 0;
	}
	else if (newY < 0)
	{
		newY = height - 1;
	}

	// Self Collision
	if (isBody(newX, newY))
	{
		gameOver = 1;
		return;
	}

	addNode(newX, newY);

	if (newX == fruitX && newY == fruitY)
	{
		score += 10;

		if (score > highScore)
		{
			highScore = score;
		}

		fruitX = rand() % width;
		fruitY = rand() % height;
	}
	else
	{
		removeTail();
	}
}

int main()
{
	Setup();

	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		sleep_ms(100);
	}

	printf("\nGAME OVER!\n");

	saveHighScore();

	while (tailTip != NULL)
	{
		removeTail();
	}

	return 0;
}
