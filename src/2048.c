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
	int j,k, new_block;
	for (j = 0; j < 4; j++)
	{
		for(k=0;k<4;k++){
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
				goto to_left; break;
			case 'j': case 'J':
				goto to_down; break;
			case 'k': case 'K':
				goto to_up; break;
			case 'l': case 'L':
				goto to_right; break;
			case 'r': case 'R':
				goto start; break;
			case 'X':
				goto cheat_x; break;
			case 'e': case 'E':
				exit(0);
			default: break;
	}
	
	get_direct();
}
void start()
{
	int k,j;
	int rn;
	for(j=0;j<4;j++){
		for (k = 0; k < 4; k++){	
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

	 for(j=0;j<4;j++){
		for (k = 0; k < 4; k++){
			num_v[j][k] = num[j][k];//bakup .old data
		}
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
#ifdef _WIN32
	c = _getch();
	if (c == -32)
	{
		c = _getch();
		case Left: c = 'h'; break; 
		case Down: c = 'j'; break; 
		case Up: c = 'k'; break; 
		case Right: c = 'l'; break; 
	}
#else 
	//c = getchar();
	putchar('\b');
#endif
	//printf("[%c]\n", c);
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
	int k,j;
	k=x/4;
	j=x%4;
	judge = rand() % 10 + 1;
	if (judge < 8) num[k][j] = 2;
	if (judge >= 8) num[k][j] = 4;
	return 0;
}


void color_printf(int x)
{
	express_column=0;
	do
	{
		if (num[express_row][express_column] == 0)
int compare()
OBOBOBOBOBOB{
	int k;
	int j;
	for (k = 0;k < 4;k++) {
		for (j = 0;j < 4;j++) {
OBOBOB			if (num_v[k][j] != num[k][j]) return 1;
	}
	return 0;
}			printf("      |", num[express_row][express_column]);
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
int compare()
OBOBOBOBOBOB{
	int k;
	int j;
	for (k = 0;k < 4;k++) {
OBOBOB		for (j = 0;j < 4;j++) {
			if (num_v[k][j] != num[k][j]) return 1;
	}
	return 0;
}	color_printf(4);
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
	for (k = 0;k < 4;k++) {
		for (j = 0;j < 4;j++) {
			num_v[k][j] = num[k][j];//bakup .old data
		}
	}
}

               if (num_v[k] != num[k]) return 1;
        }
        return 0;
}

int compare()
{
	int k;
	int j;
	for (k = 0;k < 4;k++) {
		for (j = 0;j < 4;j++) {
			if (num_v[k][j] != num[k][j]) return 1;
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

//다른 방법으로 고안한 코드
//빈 칸 지우기
void removeB(int k) { 
	int i;
	int j;

	if (direct == 'h' || direct == 'H' || direct == 68) { //왼쪽
		for (i = k;i < k + 3;i++) { 
			if (num[i] == 0) { //빈 칸이면
				for (j = i + 1;j < k + 4;j++) {
					if (num[j] != 0) { //빈 칸이 아닌 값을
						num[i] = num[j]; //왼쪽으로
						num[j] = 0; //옮긴 칸은 빈 칸으로 수정

						break;
					}
				}
			}
		}
	}
	else if (direct == 'j' || direct == 'J' || direct == 66) { //아래
		for (i = k;i > k - 12;i -= 4) {
			if (num[i] == 0) { //빈 칸이면
				for (j = i - 4;j >= k - 12;j -= 4) {
					if (num[j] != 0) { //빈 칸이 아닌 값을
						num[i] = num[j]; //아래쪽으로
						num[j] = 0; //옮긴 칸은 빈 칸으로 수정

						break;
					}
				}
			}
		}
	}
	else if (direct == 'k' || direct == 'K' || direct == 65) { //위
		for (i = k;i < k + 9;i += 4) { 
			if (num[i] == 0) { //빈 칸이면
				for (j = i + 4;j <= k + 12;j += 4) {
					if (num[j] != 0) { //빈 칸이 아닌 값을
						num[i] = num[j]; //위쪽으로
						num[j] = 0; //옮긴 칸은 빈 칸으로 수정

						break;
					}
				}
			}
		}
	}
	else if (direct == 'l' || direct == 'L' || direct == 67) { //오른쪽
		for (i = k;i > k - 3;i--) {
			if (num[i] == 0) { //빈 칸이면
				for (j = i - 1;j > k - 4;j--) {
					if (num[j] != 0) { //빈 칸이 아닌 값을
						num[i] = num[j]; //오른쪽으로
						num[j] = 0; //옮긴 칸은 빈 칸으로 수정

						break;
					}
				}
			}
		}
	}
}
//진행 방향으로 더하기
void sum(int k) { 
	int i;

	if (direct == 'h' || direct == 'H' || direct == 68) { //왼쪽
		for (i = k;i < k + 3;i++) {
			if (num[i] == 0) {} //빈 칸이면 실행 없음
			else if (num[i] == num[i + 1]) { //오른쪽 칸과 같은 값이면
				num[i] *= 2; //왼쪽으로 더하고
				num[i + 1] = 0; //오른쪽은 빈 칸 처리

				score += num[i]; //스코어 처리
				i++; //빈 칸으로 만든 칸은 건너뛰기
			}
		}
	}
	else if (direct == 'j' || direct == 'J' || direct == 66) { //아래
		for (i = k;i > k - 9;i -= 4) {
			if (num[i] == 0) {} //빈 칸이면 실행 없음
			else if (num[i] == num[i - 4]) { //위쪽 칸과 같은 값이면
				num[i] *= 2; //아래쪽으로 더하고
				num[i - 4] = 0; //위쪽은 빈 칸 처리

				score += num[i]; //스코어 처리
				i -= 4; //빈 칸으로 만든 칸은 건너뛰기
			}
		}
	}
	else if (direct == 'k' || direct == 'K' || direct == 65) { //위
		for (i = k;i < k + 9;i += 4) {
			if (num[i] == 0) {} //빈 칸이면 실행 없음
			else if (num[i] == num[i + 4]) { //아래쪽 칸과 같은 값이면
				num[i] *= 2; //위쪽으로 더하고
				num[i + 4] = 0; //아래쪽은 빈 칸 처리

				score += num[i]; //스코어 처리
				i += 4; //빈 칸으로 만든 칸은 건너뛰기
			}
		}
	}
	else if (direct == 'l' || direct == 'L' || direct == 67) { //오른쪽
		for (i = k;i > k - 3;i--) {
			if (num[i] == 0) {} //빈 칸이면 실행 없음
			else if (num[i] == num[i - 1]) { //왼쪽 칸과 같은 값이면
				num[i] *= 2; //오른쪽으로 더하고
				num[i - 1] = 0; //왼쪽은 빈 칸 처리

				score += num[i]; //스코어 처리
				i--; //빈 칸으로 만든 칸은 건너뛰기
			}
		}
	}
}
//TEST_GIWON
