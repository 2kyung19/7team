// 2048 GAME V7
// BY BTS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32 //Linux platform
#include <conio.h>
#include <windows.h>
#else  
#include <termios.h>
#include <unistd.h>
#endif

#define Left 75
#define Right 77
#define Up 72
#define Down 80

int num[4][4];
int num_v[4][4];//comparation
char direct;
int signal;
int score;
int express_row;
int express_column;


// goto 문을 함수로 작성
void to_right();
void to_left();
void to_up();
void to_down();
void get_wait();
void get_direct();
void start();
int newBlock();

void cheat_x();
// 여기까지
char get1char(void);
int rnd(int x);
void color_printf(int x);
void draw_canvas();
void bakup();
int compare();

//아래 두가지 함수는 다른 방법으로 고안에서 사용
void removeB(int k);
void sum(int k);

int main()
{
	start();
	while (1)
	{
		get_direct();
	}
	return 0;
}

void to_right()
{
	int k, j;
	for (k = 0; k <= 4; k++)
	{
		for (j = 3; j > 0; j--)
		{
			if (num[k][j] == 0)
			{
				num[k][j] = num[k][j - 1];
				num[k][j - 1] = 0;
			}
			else if (num[k][j] != 0)
			{
				if (num[k][j] == num[k][j - 1] && num[k][j] >0)
				{
					num[k][j] = num[k][j] * 2;
					score = score + num[k][j];
					num[k][j - 1] = 0;
					num[k][j] = num[k][j] * -1; // 수정부분
				}
			}
		}
	}
	if (compare() == 0)
	{
		get_wait();
		return;
	}

	bakup();
	signal = 1;
	to_right();
}
void to_left()
{
	int k, j;
	for (k = 0; k <4; k++)
	{
		for (j = 0; j < 3; j++)
		{
			if (num[k][j] == 0)
			{
				num[k][j] = num[k][j + 1];
				num[k][j + 1] = 0;
			}
			else if (num[k][j] != 0)
			{
				if (num[k][j] == num[k][j + 1] && num[k][j] >0)
				{
					num[k][j] = num[k][j] * 2;
					score = score + num[k][j];
					num[k][j + 1] = 0;
					num[k][j] = num[k][j] * -1; // 수정부분
				}
			}
		}
	}
	if (compare() == 0)
	{
		get_wait();
		return;
	}

	bakup();
	signal = 1;
	to_left();
}
void to_up()
{
	int k, j;
	for (j = 0; j <4; j++) //첫번째 열부터 4번째까지
	{
		for (k = 0; k <3; k++) // 해당 열의 첫번째 행부터 4번째 행까지
		{
			if (num[k][j] == 0) // 블럭이 비어있다면 
			{
				num[k][j] = num[k + 1][j]; // 아래 블럭을 가져옴
				num[k + 1][j] = 0;
			}
			else if (num[k][j] != 0)
			{
				if (num[k][j] == num[k + 1][j] && num[k][j] >0) // 아래 블럭과 같다면
				{
					num[k][j] = num[k][j] * 2; // 아래 블럭과 지금 블럭을 합침
					score = score + num[k][j];
					num[k + 1][j] = 0;
					num[k][j] = num[k][j] * -1; // 수정부분
				}
			}
		}
	}
	if (compare() == 0)
	{
		get_wait();
		return;
	}

	bakup();
	signal = 1;
	to_up();
}
void to_down()
{
	int k, j;
	for (j = 0; j < 4; j++) // 첫번째 열부터 4번째 열까지
	{
		for (k = 3; k >0; k--) // 해당 열의 마지막 행부터 첫번째 행까지
		{
			if (num[k][j] == 0) // 블럭이 비어있다면
			{
				num[k][j] = num[k - 1][j]; // 위 블럭을 가져옴
				num[k - 1][j] = 0;
			}
			else if (num[k][j] != 0)
			{
				if (num[k][j] == num[k - 1][j] && num[k][j] >0) // 아래 블럭과 같다면
				{
					num[k][j] = num[k][j] * 2; // 아래 블럭과 지금 블럭을 합침
					score = score + num[k][j];
					num[k - 1][j] = 0;
					num[k][j] = num[k][j] * -1;
				}
			}
		}
	}
	if (compare() == 0)
	{
		get_wait();
		return;
	} // 블럭이 하나도 이동되지 않았다면 get_wait로 이동
	bakup(); // 현재 배열을 백업
	signal = 1; // 1번 이상 이동되었음을 나타내는 변수
	to_down(); // 다시 실행함
}
void get_wait()
{
	int j, k, new_block;
	for (j = 0; j < 4; j++)
	{
		for (k = 0; k<4; k++) {
			if (num[j][k] < 0)
				num[j][k] *= -1;
		}
	}

	draw_canvas();
	if (signal == 0 || newBlock() == -1) {
		return;
	}

	else {
		new_block = newBlock();
	}

	Sleep(100);

	rnd(new_block);
	return;
}
void get_direct()
{
	draw_canvas();

	direct = get1char();

	signal = 0;
	bakup();

	switch (direct) {
	case 'h': case 'H':
		to_left(); break;
	case 'j': case 'J':
		to_down(); break;
	case 'k': case 'K':
		to_up(); break;
	case 'l': case 'L':
		to_right(); break;
	case 'r': case 'R':
		start(); break;
	case 'e': case 'E':
		exit(0);
	default: break;
	}

}
void start()
{
	int k, j;
	int rn;
	for (j = 0; j<4; j++) {
		for (k = 0; k < 4; k++) {
			num[j][k] = 0;
		}
	}
	srand(time(NULL));
	score = 0;
	//처음 3개 랜덤

	rnd(10);
	rnd(11);
	rnd(14);
	rnd(15);

	for (j = 0; j<4; j++) {
		for (k = 0; k < 4; k++) {
			num_v[j][k] = num[j][k];//bakup .old data
		}
	}
}


char get1char(void)
{
#ifdef _WIN32
	// Do nothing
#else   
	struct termios stored_settings;
	struct termios new_settings;
	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);
#endif
	int ret = 0;
	char c = -32;
	int express = 0;
#ifdef _WIN32
	c = getch();
	if (c == -32)
	{
		c = getch();
		if (c == 75) c = 104;
		if (c == 80) c = 106;
		if (c == 72) c = 107;
		if (c == 77) c = 108;
	}
#else 
	//c = getchar();
	putchar('\b');
#endif
	printf("[%c]\n", c);
	//system("sleep 0.2");
#ifdef _WIN32  
	// Do nothing  
#else  
	tcsetattr(0, TCSANOW, &stored_settings);
#endif
	return c;
}


int rnd(int x)
{
	int judge;
	int k, j;
	k = x / 4;
	j = x % 4;
	judge = rand() % 10 + 1;
	if (judge < 8) num[k][j] = 2;
	if (judge >= 8) num[k][j] = 4;
	return 0;
}


void color_printf(int x)
{
	express_column = 0;
	do
	{
		if (num[express_row][express_column] == 0)
			printf("      |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 2)
			printf(" \033[m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 4)
			printf(" \033[0;32;32m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 8)
			printf(" \033[1;32m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 16)
			printf(" \033[0;32;34m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 32)
			printf(" \033[0;35m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 64)
			printf(" \033[1;35m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 128)
			printf(" \033[0;32;31m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 256)
			printf(" \033[1;31m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 512)
			printf(" \033[0;33m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 1024)
			printf(" \033[1;30m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 2048)
			printf(" \033[0;37m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 4096)
			printf(" \033[1;34m%4d\033[0;33m |", num[express_row][express_column]);
		else printf(" \033[1;34m%4d\033[0;33m |", num[express_row][express_column]);

		express_column++;
	} while (express_column < x);
}

void draw_canvas()
{
#ifdef _WIN32
	system("cls");//clear sreen
#else
	system("clear");//clear screen
#endif
	express_row = 0;
	express_column = 0;
	printf("\033[m");
	printf("2048 CLI V7\n");
	printf("Built by Coder-BTS\n\n");
	printf("Use <HJKL> | E-Exit | R-Reset\n");
	printf("\033[0;33m");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(4);
	express_row++;
	printf("\n|      |      |      |      |\n");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(4);
	express_row++;
	printf("\n|      |      |      |      |\n");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(4);
	express_row++;
	printf("\n|      |      |      |      |\n");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(4);
	express_row++;
	printf("\n|      |      |      |      |\n");
	printf("-----------------------------\n");
	printf(">>> Score:   %d <<<\033[m\n", score);
	if (newBlock() == -1)
	{
		printf("\n\033[1;32mCan you make a forward move?\n");
	}
	printf("\033[m");
}


void bakup()
{
	int k;
	int j;
	for (k = 0; k < 4; k++) {
		for (j = 0; j < 4; j++) {
			num_v[k][j] = num[k][j];//bakup .old data
		}
	}
}

int compare()
{
	int k;
	int j;
	for (k = 0; k < 4; k++) {
		for (j = 0; j < 4; j++) {
			if (num_v[k][j] != num[k][j]) return 1;
		}

	}
	return 0;
}



int newBlock() {
	int new_block;
	int blank[16];
	int i, j;
	int n = 0;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (num[i][j] == 0) {
				blank[n] = i * 4 + j;
				n++;
			}
		}
	}

	if (n == 0) {
		return -1;
	}

	i = rand() % n;
	new_block = blank[i];

	return new_block;
}

