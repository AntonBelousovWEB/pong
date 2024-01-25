#include "global.h"

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void drawBoard(int paddle2Y, int ballX, int ballY) {
    system("cls");

    for (int i = 0; i < 24; i++) {
        gotoxy(0, i);
        printf("|");
    }

    gotoxy(78, paddle2Y);
    printf("|");

    gotoxy(ballX, ballY);
    printf("O");

    for (int i = 0; i < 80; i++) {
        gotoxy(i, 0);
        printf("-");
        gotoxy(i, 24);
        printf("-");
    }
}