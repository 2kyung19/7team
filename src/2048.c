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

int num[16];
int num_v[16];//comparation
char direct;
int signal;
int score;
int express;
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

int main()
{
	start();

	get_direct();

	return 0;
}

void to_right()
{
	int k, j;
	for (k = 0; k <= 12; k += 4)
	{
		for (j = k + 3; j >= k + 1; j--)
		{
			if (num[j] == 0)
			{
				num[j] = num[j - 1];
				num[j - 1] = 0;
			}
			if (num[j] != 0)
			{
				if (num[j] == num[j - 1] && num[j] >0)
				{
					num[j] = num[j] * 2;
					score = score + num[j];
					num[j - 1] = 0;
					num[j] = num[j] * -1; // 수정부분
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
	for (k = 0; k <= 12; k += 4)
	{
		for (j = k; j <= k + 2; j++)
		{
			if (num[j] == 0)
			{
				num[j] = num[j + 1];
				num[j + 1] = 0;
			}
			if (num[j] != 0)
			{
				if (num[j] == num[j + 1] && num[j] >0)
				{
					num[j] = num[j] * 2;
					score = score + num[j];
					num[j + 1] = 0;
					num[j] = num[j] * -1; // 수정부분
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
	for (k = 0; k <= 3; k++) //첫번째 열부터 4번째까지
	{
		for (j = k; j <= 11; j += 4) // 해당 열의 첫번째 행부터 4번째 행까지
		{
			if (num[j] == 0) // 블럭이 비어있다면 
			{
				num[j] = num[j + 4]; // 아래 블럭을 가져옴
				num[j + 4] = 0;
			}
			if (num[j] != 0)
			{
				if (num[j] == num[j + 4] && num[j] >0) // 아래 블럭과 같다면
				{
					num[j] = num[j] * 2; // 아래 블럭과 지금 블럭을 합침
					score = score + num[j];
					num[j + 4] = 0;
					num[j] = num[j] * -1; // 수정부분
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
	for (k = 12; k <= 15; k++) // 첫번째 열부터 4번째 열까지
	{
		for (j = k; j >= 4; j -= 4) // 해당 열의 마지막 행부터 첫번째 행까지
		{
			if (num[j] == 0) // 블럭이 비어있다면
			{
				num[j] = num[j - 4]; // 위 블럭을 가져옴
				num[j - 4] = 0;
			}
			if (num[j] != 0)
			{
				if (num[j] == num[j - 4] && num[j] >0) // 아래 블럭과 같다면
				{
					num[j] = num[j] * 2; // 아래 블럭과 지금 블럭을 합침
					score = score + num[j];
					num[j - 4] = 0;
					num[j] = num[j] * -1;
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
	int j, new_block;
	for (j = 0; j < 16; j++)
	{
		if (num[j] < 0)
			num[j] *= -1;
	}

	draw_canvas();
	if (signal == 0) get_direct();

	if (newBlock() == -1) {
		get_direct();
	}

	else {
		new_block = newBlock();
	}

	Sleep(100);

	rnd(new_block);
	get_direct();
}
void get_direct()
{
	//system("clear");//clear screen
	draw_canvas();
	//system("stty -icanon");
	//direct = get1char();

	scanf_s("%c", &direct); //수정한 내용
	getchar();

	//printf("%c",direct);
	signal = 0;
	bakup();
	if (direct == 'h' || direct == 'H' || direct == 68) to_left();
	else if (direct == 'j' || direct == 'J' || direct == 66) to_down();
	else if (direct == 'k' || direct == 'K' || direct == 65) to_up();
	else if (direct == 'l' || direct == 'L' || direct == 67) to_right();
	else if (direct == 'r' || direct == 'R') start();
	else if (direct == 'X') cheat_x();
	else if (direct == 'e' || direct == 'E')
	{
		//system("clear");
		exit(1);
	}
	get_direct();
}
void start()
{
	int k;
	int rn;
	for (k = 0; k < 16; k++)//init void
	{
		num[k] = 0;
	}
	srand(time(NULL));
	score = 0;
	//처음 3개 랜덤

	rnd(11);
	rnd(14);
	rnd(15);


	for (k = 0; k < 16; k++)
	{
		num_v[k] = num[k];//bakup .old data
	}
}
void cheat_x()
{
	num[0] = 16;
	num[1] = 128;
	num[2] = 1024;
	num[3] = 4096;
	num[4] = 0;
	num[5] = 256;
	num[6] = 0;
	num[7] = 2048;
	num[8] = 0;
	num[9] = 0;
	num[10] = 256;
	num[11] = 128;
	num[12] = 0;
	num[13] = 0;
	num[14] = 16;
	num[15] = 256;
	score = 67108864;
	get_wait();
	//quit_g:
	//exit(1);
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
	//c = getch();
	if (c == -32)
	{
		//c = getch();
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
	judge = rand() % 10 + 1;
	if (judge < 8) num[x] = 2;
	if (judge >= 8) num[x] = 4;
	return 0;
}

void color_printf(int x)
{
	do
	{
		if (num[express] == 2) printf(" \033[m%4d\033[0;33m |", num[express]);
		if (num[express] == 4) printf(" \033[0;32;32m%4d\033[0;33m |", num[express]);
		if (num[express] == 8) printf(" \033[1;32m%4d\033[0;33m |", num[express]);
		if (num[express] == 16) printf(" \033[0;32;34m%4d\033[0;33m |", num[express]);
		if (num[express] == 32) printf(" \033[0;35m%4d\033[0;33m |", num[express]);
		if (num[express] == 64) printf(" \033[1;35m%4d\033[0;33m |", num[express]);
		if (num[express] == 128) printf(" \033[0;32;31m%4d\033[0;33m |", num[express]);
		if (num[express] == 256) printf(" \033[1;31m%4d\033[0;33m |", num[express]);
		if (num[express] == 512) printf(" \033[0;33m%4d\033[0;33m |", num[express]);
		if (num[express] == 1024) printf(" \033[1;30m%4d\033[0;33m |", num[express]);
		if (num[express] == 2048) printf(" \033[0;37m%4d\033[0;33m |", num[express]);
		if (num[express] == 4096) printf(" \033[1;34m%4d\033[0;33m |", num[express]);
		if (num[express] == 0) printf("      |", num[express]);
		express++;
	} while (express < x);
}

void draw_canvas()
{
#ifdef _WIN32
	system("cls");//clear sreen
#else
	system("clear");//clear screen
#endif
	express = 0;
	printf("\033[m");
	printf("2048 CLI V7\n");
	printf("Built by Coder-BTS\n\n");
	printf("Use <HJKL> | E-Exit | R-Reset\n");
	printf("\033[0;33m");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(4);
	printf("\n|      |      |      |      |\n");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(8);
	printf("\n|      |      |      |      |\n");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(12);
	printf("\n|      |      |      |      |\n");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(16);
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
	for (k = 0; k < 16; k++)
	{
		num_v[k] = num[k];//bakup .old data
	}
}

int compare()
{
	int k;
	for (k = 0; k < 16; k++)
	{
		if (num_v[k] != num[k]) return 1;
	}
	return 0;
}

int newBlock() {
	int new_block;
	int blank[16];
	int i;
	int n = 0;

	for (i = 0; i < 16; i++) {
		if (num[i] == 0) {
			blank[n] = i;
			n++;
		}
	}

	if (n == 0) {
		return -1;
	}

	i = rand() % n;
	new_block = blank[i];

	return new_block;
}