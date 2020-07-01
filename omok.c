#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#define SIZE 19
int board[SIZE][SIZE] = { 0 };
void gameInit();
void gotoxy(int x, int y);
void setStone(int stoneColor);
BOOL checkGameover();
COORD getCursorXY();

int main() {
	gameInit(); //���� ���� �׸���
	int stoneColor = 0; // �� ����
	while (1) {
		if (stoneColor % 2 == 0) { // ¦���� �浹
			gotoxy(1, SIZE);
			printf("Black Turn");
		}
		else { // �ܴ̿� �Ͼᵹ
			gotoxy(1, SIZE);
			printf("White Turn");
		}
		setStone(stoneColor); // �� ��ġ
		stoneColor++;
		if (checkGameover() == TRUE) { // ���� ���� üũ
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
					printf("��");
				}
				else if (x == SIZE - 1) {
					printf("��");
				}
				else { 
					printf("��");
				}
			}
			else if (x == 0) { 
				if (y == SIZE - 1) { 
					printf("��");
				}
				else {
					printf("��");
				}
			}
			else if (x == SIZE - 1) {
				if (y == SIZE - 1) {
					printf("��");
				}
				else {
					printf("��");
				}
			}
			else if (y == SIZE - 1) {
				printf("��");
			}
			else {
				printf("��");
			}
		}
	}
	printf("\n");
}
void setStone(int stoneColor) {
	gotoxy(0, 0);
	COORD Cursor = getCursorXY();
	while (1) {
		char Key = _getch();
		if (Key == 75) { //��
			if (Cursor.X > 0) {
				Cursor.X--;
			}
		}
		else if (Key == 77) { //��
			if (Cursor.X < SIZE-1) {
				Cursor.X++;
			}
		}
		else if (Key == 72) { //��
			if (Cursor.Y > 0) {
				Cursor.Y--;
			}
		}
		else if (Key == 80) { //��
			if (Cursor.Y < SIZE - 1) {
				Cursor.Y++;
			}
		}
		else if (Key == 13) {
			if (stoneColor % 2 == 0) { // stoneColor�� ¦���� ���
				printf("��");
				board[Cursor.Y][Cursor.X] = 1; //���� ���忡 ��� ����
			}
			else {
				printf("��");	// �ܴ̿� �Ͼ��
				board[Cursor.Y][Cursor.X] = 2; //���� ���忡 �Ͼ�� ����
			}
			break;
		}
		gotoxy(Cursor.X, Cursor.Y); // Ŀ�� ������
	}
}

void gotoxy(int x, int y) {
	COORD pos = { x * 2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
COORD getCursorXY() {
	COORD Pos;
	CONSOLE_SCREEN_BUFFER_INFO a;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &a);
	Pos.X = a.dwCursorPosition.X;
	Pos.Y = a.dwCursorPosition.Y;
	return Pos;
}
BOOL checkGameover() {
	for (int y = 0; y < sizeof(board) / sizeof(board[y]); y++) { // Board�� ���� ũ�⸸ŭ �迭 �ݺ�
		for (int x = 0; x < sizeof(board[0]) / sizeof(int); x++) { //Board�� ���� ũ�⸸ŭ �迭 �ݺ�
			int cases[4] = { 0 }; // 4���� ���̽� ���� ���� ����
			int color = board[y][x]; // ���� ��ġ�� �� �� �޾ƿ�
			for (int i = 0; i < 5 && color != 0; i++) { //5�� �ݺ�
				if (x + i < SIZE && color == board[y][x + i]) { // �� ���� �������� ���� ������
					cases[0]++;
				}
				if (y + i < SIZE &&  color == board[y + i][x]) { // �� ��,�Ʒ��� �������� ���� ������
					cases[1]++;
				}
				if (x + i < SIZE && y + i < SIZE && color == board[y + i][x + i]) { // �밢������ ���� ���� ���� ������
					cases[2]++;
				}
				if (x - i >= 0 && y + i < SIZE && color == board[y + i][x - i]) { 
					cases[3]++;
				}
			}
			for (int i = 0; i < 4; i++) { // ������ ���̽��� ��ȸ
				if (cases[i] == 5) { // ���̽��� ������ ������ ��ġ�ϸ�
					gotoxy(1, SIZE); // ��� ���
					if (color == 1) {
						printf("Black Win!");
					}
					else {
						printf("White Win!");
					}
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}