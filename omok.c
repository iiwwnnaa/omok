#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#define SIZE 19 // SIZE는 가변
int board[SIZE][SIZE] = { 0 };
void gameInit();
void gotoxy(int x, int y);
void setStone(int stoneColor);
BOOL checkGameover();

int main() {
	gameInit(); //게임 보드 그리기
	int stoneColor = 0; // 돌 색깔
	while (1) {
		if (stoneColor % 2 == 0) { // 짝수면 흑돌
			gotoxy(1, SIZE);
			printf("Black Turn");
		}
		else { // 이외는 흰돌
			gotoxy(1, SIZE);
			printf("White Turn");
		}
		setStone(stoneColor); // 돌 설치
		stoneColor++;
		if (checkGameover() == TRUE) { // 게임 오버 체크
			break;
		}
	}
	return 0;
}

void gameInit() {
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			gotoxy(x, y);
			if (y == 0) { 
				if (x == 0) { 
					printf("┌");
				}
				else if (x == SIZE - 1) {
					printf("┐");
				}
				else { 
					printf("┬");
				}
			}
			else if (x == 0) { 
				if (y == SIZE - 1) { 
					printf("└");
				}
				else {
					printf("├");
				}
			}
			else if (x == SIZE - 1) {
				if (y == SIZE - 1) {
					printf("┘");
				}
				else {
					printf("┤");
				}
			}
			else if (y == SIZE - 1) {
				printf("┴");
			}
			else {
				printf("┼");
			}
		}
	}
	printf("\n");
}
void setStone(int stoneColor) {
	COORD Cursor = { 0,0 };
	gotoxy(Cursor.X, Cursor.Y);
	while (1) {
		char Key = _getch();
		if (Key == 75) { //좌
			if (Cursor.X > 0) {
				Cursor.X--;
			}
		}
		else if (Key == 77) { //우
			if (Cursor.X < SIZE-1) {
				Cursor.X++;
			}
		}
		else if (Key == 72) { //상
			if (Cursor.Y > 0) {
				Cursor.Y--;
			}
		}
		else if (Key == 80) { //하
			if (Cursor.Y < SIZE - 1) {
				Cursor.Y++;
			}
		}
		else if (Key == 13) {
			if (board[Cursor.Y][Cursor.X] == 0) {
				if (stoneColor % 2 == 0) { // stoneColor가 짝수면 흑돌
					printf("○");
					board[Cursor.Y][Cursor.X] = 1; //게임 보드에 흑돌 누적
				}
				else {
					printf("●");	// 이외는 흰돌
					board[Cursor.Y][Cursor.X] = 2; //게임 보드에 흰돌 누적
				}
				gotoxy(1, SIZE + 1);
				printf("             ");
				break;
			}
			else { // 중복돌 방지
				gotoxy(1, SIZE + 1);
				printf("Already exist");
			}
		}
		gotoxy(Cursor.X, Cursor.Y); // 커서 움직임
	}
}

void gotoxy(int x, int y) {
	COORD pos = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

BOOL checkGameover() {
	int count = 0;
	for (int y = 0; y < sizeof(board) / sizeof(board[y]); y++) { // Board의 세로 크기만큼 배열 반복
		for (int x = 0; x < sizeof(board[0]) / sizeof(int); x++) { //Board의 가로 크기만큼 배열 반복
			int cases[4] = { 0 }; // 4개의 케이스 누적 전용 변수
			int color = board[y][x]; // 현재 위치의 돌 색 받아옴
			if (color == 1 || color == 2) {
				count++;
			}
			for (int i = 0; i < 5 && color != 0; i++) { //5번 반복
				if (x + i < SIZE && color == board[y][x + i]) { // 돌 옆에 같은색의 돌이 있으면
					cases[0]++;
				}
				if (y + i < SIZE &&  color == board[y + i][x]) { // 돌 위,아래에 같은색의 돌이 있으면
					cases[1]++;
				}
				if (x + i < SIZE && y + i < SIZE && color == board[y + i][x + i]) { // 대각선으로 같은 색의 돌이 있으면
					cases[2]++;
				}
				if (x - i >= 0 && y + i < SIZE && color == board[y + i][x - i]) { 
					cases[3]++;
				}
			}
			for (int i = 0; i < 4; i++) { // 누적된 케이스를 순회
				gotoxy(1, SIZE); 
				if (cases[i] == 5) { // 케이스중 오목의 조건이 일치하면
					if (color == 1) {
						printf("Black Win!");
					}
					else {
						printf("White Win!");
					}
					return TRUE;
				}
				else if (count >= SIZE*SIZE) { // 보드가 돌로 꽉차면 비김
					printf("DRAW!    ");
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}