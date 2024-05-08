#include "pagina_start.h"
#include "variabile_globale.h"
#define BLUE 1
#define BLUEDR 2
#define BLUEBR 3
#define RED 4
#define REDDR 5
#define REDBR 6
#define GREENDR 8
#define GREENBR 9
#define PURPLE 10
#define PURPLEDR 11
#define PURPLEBR 12
#define YELLOW 13
#define YELLOWDR 14
#define YELLOWBR 15
#define BLANK 0
#define REFRESH 0
#define ROWS 20
#define COLS 15

// Shapes
#define SHAPE_I 100
#define SHAPE_T 101
#define SHAPE_L 102
#define SHAPE_L2 103
#define SHAPE_O 104
#define SHAPE_S 105
#define SHAPE_S2 106

// Directions
#define RIGHT 201
#define DOWN 203
#define TOP 30
#define LEFT 160

// Keys
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_SPACE 32

int scor_aux;
void PrintScore();
void InitScreenLayout();
void GetImages();
void DisplayInterface();
void AssignShape(int Shape, int Color);
int DetectCollision(int Direction);
int MoveBlock(int Direction);
void DisplayBlock(int x, int y);
void DisplayNextShape();
void GetNextBlock();
void RotateBlock();
void UpdateScreen();
void CheckForLine();
void RemoveLine(int Number);
int GetRandomColor();
int GetRandomShape();
int IncreaseSpeed();

void far *bmpBlueBrick;
void far *bmpRedBrick;
void far *bmpGreenBrick;
void far *bmpYellowBrick;
void far *bmpPurpleBrick;
void far *bmpBlankBrick;
void far *bmpScore;
void far *bmpSpeed;
void far *bmpLevel;
void far *bmpLinesCleared;
void far *bmpScreen;

int BlockMatrix[4][4];
int ScreenLayout[COLS][ROWS];
int ScreenBackgroundLayout[COLS][ROWS];
int PreviousScreenLayout[COLS][ROWS];
int LinesCleared = 0;
int Level = 1;
int LineScore = 100;
int Speed = 95;
int CurrentShape;
int NextShape;
int NextColor;
int BlockX = 7;
int BlockY = 0;
int Quit = 0;
int GameOver = 0;
int SoundOn = 1;
char lpszScore[40];
char lpszSpeed[40];
char lpszLevel[40];
char lpszLinesCleared[40];
unsigned long Score = 0;

int ShapeI[4][4] = {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0};
int ShapeT[4][4] = {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0};
int ShapeL[4][4] = {0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int ShapeL2[4][4] = {1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int ShapeS[4][4] = {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int ShapeS2[4][4] = {1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int ShapeO[4][4] = {1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void InitPalette();

void mini_game() {
        initwindow(630, getmaxheight() / 2 + 60, "Notepad", (getmaxwidth() - 630) / 2, (getmaxheight() - getmaxheight() / 2 - 60) / 2);

        settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        outtextxy(30, 30, "EXIT");
        rectangle(20, 25, 40 + textwidth("EXIT"), 35 + textheight("EXIT"));

        outtextxy(30, 35 + textheight("EXIT") + 5, "EXIT");
        rectangle(20, 35 + textheight("EXIT") + 10, 40 + textwidth("Reset"), 35 + textheight("EXIT") + 10 + 35 + textheight("EXIT"));

        int resetare = 0;

        int gd = DETECT, gm;
        int Return = 0;
        char Key, ScanCode;
        int Counter = 0;

        setbkcolor(c_bk);
        settextstyle(BOLD_FONT, HORIZ_DIR, 0);
        cleardevice();

        InitPalette();

        GetImages();

        cleardevice();
        setfillstyle(SOLID_FILL, 5);
        bar(0, 0, getmaxx(), 10);
        bar(0, getmaxy(), getmaxx(), getmaxy() - 10);
        setfillstyle(SOLID_FILL, WHITE);
        AssignShape(GetRandomShape(), GetRandomColor());
        NextShape = GetRandomShape();
        NextColor = GetRandomColor();
        DisplayInterface();
        DisplayNextShape();
        MoveBlock(LEFT);
        settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        outtextxy(30 + 10, 30 + 5, "Exit");
        rectangle(20, 25 + 5, 40 + textwidth("RESET"), 35 + textheight("Exit") + 5);

        outtextxy(30, 35 + 5 + textheight("RESET") + 5, "Reset");
        rectangle(20, 35 + 5 + textheight("RESET"), 40 + textwidth("RESET"), 35 + textheight("EXIT") + 10 + textheight("EXIT") + 5);

        PrintScore();
        settextstyle(BOLD_FONT, HORIZ_DIR, 0);

        while (kbhit())
                getch();

        while (!Quit && !GameOver) {
                if (ismouseclick(WM_LBUTTONUP)) {

                        if (mousex() >= 20 && mousex() <= 40 + textwidth("EXIT") && mousey() >= 25 + 5 && mousey() <= 35 + textheight("EXIT") + 5) {

                                for (int i = 0; i <= COLS; i++)

                                        for (int j = 0; j <= ROWS; j++)
                                                PreviousScreenLayout[i][j] = 0, ScreenLayout[i][j] = 0, ScreenBackgroundLayout[i][j] = 0;
                                closegraph();

                                draw_pagina_start();

                                break;
                        } else if (mousex() >= 20 && mousex() <= 40 + textwidth("EXIT") && mousey() >= 35 + 5 + textheight("RESET") && mousey() <= 35 + 5 + textheight("EXIT") + 10 + textheight("EXIT"))

                        {
                                resetare = 1;
                                break;
                        } else {
                                clearmouseclick(WM_LBUTTONDOWN);
                                clearmouseclick(WM_LBUTTONUP);
                        }
                } else {
                        if (mousex() >= 20 && mousex() <= 40 + textwidth("EXIT") && mousey() >= 25 + 5 && mousey() <= 35 + 5 + textheight("EXIT")) {
                                settextstyle(BOLD_FONT, HORIZ_DIR, 4);
                                setcolor(LIGHTRED);
                                outtextxy(30 + 10, 30 + 5, "Exit");
                                rectangle(20, 25 + 5, 40 + textwidth("RESET"), 35 + textheight("Exit") + 5);

                                while (mousex() >= 20 && mousex() <= 40 + textwidth("EXIT") && mousey() >= 25 + 5 && mousey() <= 35 + 5 + textheight("EXIT") && !ismouseclick(WM_LBUTTONUP))
                                        usleep(100);

                                setcolor(MAGENTA);
                                outtextxy(30 + 10, 30 + 5, "Exit");

                                rectangle(20, 25 + 5, 40 + textwidth("RESET"), 35 + textheight("Exit") + 5);

                        } else if (mousex() >= 20 && mousex() <= 40 + textwidth("EXIT") && mousey() >= 35 + 5 + textheight("RESET") && mousey() <= 35 + 5 + textheight("EXIT") + 10 + textheight("EXIT")) {
                                settextstyle(BOLD_FONT, HORIZ_DIR, 4);
                                setcolor(LIGHTRED);
                                outtextxy(30, 35 + 5 + textheight("RESET") + 5, "Reset");
                                rectangle(20, 35 + 5 + textheight("RESET"), 40 + textwidth("RESET"), 35 + textheight("EXIT") + 10 + textheight("EXIT") + 5);

                                while (mousex() >= 20 && mousex() <= 40 + textwidth("EXIT") && mousey() >= 35 + 5 + textheight("RESET") && mousey() <= 35 + 5 + textheight("EXIT") + 10 + textheight("EXIT") && !ismouseclick(WM_LBUTTONUP))
                                        usleep(100);

                                setcolor(MAGENTA);

                                outtextxy(30, 35 + 5 + textheight("RESET") + 5, "Reset");
                                rectangle(20, 35 + 5 + textheight("RESET"), 40 + textwidth("RESET"), 35 + 5 + textheight("EXIT") + 10 + textheight("EXIT"));
                        }
                }

                if (++Counter >= Speed) {
                        Counter = 0;
                        MoveBlock(DOWN);
                }

                if (kbhit()) {
                        Key = getch();

                        if (Key == 0) {
                                ScanCode = getch();

                                if (ScanCode == KEY_UP)
                                        RotateBlock();
                                else if (ScanCode == KEY_LEFT)
                                        Return = MoveBlock(LEFT);
                                else if (ScanCode == KEY_RIGHT)
                                        Return = MoveBlock(RIGHT);
                                else if (ScanCode == KEY_DOWN) {
                                        MoveBlock(DOWN);
                                }
                                Return = 0;
                        }
                }
                delay(5);
        }
        if (resetare == 1) {
                for (int i = 0; i <= COLS; i++)
                        for (int j = 0; j <= ROWS; j++)
                                PreviousScreenLayout[i][j] = 0, ScreenLayout[i][j] = 0, ScreenBackgroundLayout[i][j] = 0;

                Score = 0;
                closegraph();
                mini_game();
        }

        for (int i = 0; i <= COLS; i++)
                for (int j = 0; j <= ROWS; j++)
                        PreviousScreenLayout[i][j] = 0, ScreenLayout[i][j] = 0, ScreenBackgroundLayout[i][j] = 0;
        closegraph();

        draw_pagina_start();
}

void Brick(int x, int y, char Color) {
        int utri[6] = {x, y, x + 20, y, x, y + 20};
        int ltri[6] = {x + 20, y + 20, x + 20, y, x, y + 20};

        switch (Color) {

        case BLUE:
                setcolor(BLUEBR);
                setfillstyle(1, BLUEBR);
                fillpoly(3, utri);
                setcolor(BLUEDR);
                setfillstyle(1, BLUEDR);
                fillpoly(3, ltri);
                setcolor(BLUE);
                setfillstyle(1, BLUE);
                bar(x + 5, y + 5, x + 15, y + 15);
                break;

        case RED:
                setcolor(REDBR);
                setfillstyle(1, REDBR);
                fillpoly(3, utri);
                setcolor(REDDR);
                setfillstyle(1, REDDR);
                fillpoly(3, ltri);
                setcolor(RED);
                setfillstyle(1, RED);
                bar(x + 5, y + 5, x + 15, y + 15);
                break;

        case GREEN:
                setcolor(GREENBR);
                setfillstyle(1, GREENBR);
                fillpoly(3, utri);
                setcolor(GREENDR);
                setfillstyle(1, GREENDR);
                fillpoly(3, ltri);
                setcolor(GREEN);
                setfillstyle(1, GREEN);
                bar(x + 5, y + 5, x + 15, y + 15);
                break;

        case PURPLE:
                setcolor(PURPLEBR);
                setfillstyle(1, PURPLEBR);
                fillpoly(3, utri);
                setcolor(PURPLEDR);
                setfillstyle(1, PURPLEDR);
                fillpoly(3, ltri);
                setcolor(PURPLE);
                setfillstyle(1, PURPLE);
                bar(x + 5, y + 5, x + 15, y + 15);
                break;

        case YELLOW:
                setcolor(YELLOWBR);
                setfillstyle(1, YELLOWBR);
                fillpoly(3, utri);
                setcolor(YELLOWDR);
                setfillstyle(1, YELLOWDR);
                fillpoly(3, ltri);
                setcolor(YELLOW);
                setfillstyle(1, YELLOW);
                bar(x + 5, y + 5, x + 15, y + 15);
                break;
        }
}

void InitPalette() {

        // Blue Colors
        setpalette(BLUE, 1);   // Normal
        setpalette(BLUEDR, 8); // Dark
        setpalette(BLUEBR, 9); // Bright

        // Red Colors
        setpalette(RED, 4);    // Normal
        setpalette(REDDR, 32); // Dark
        setpalette(REDBR, 36); // Bright

        // Green Colors
        setpalette(GREEN, 2);    // Normal
        setpalette(GREENDR, 16); // Dark
        setpalette(GREENBR, 18); // Bright

        // Purple Colors
        setpalette(PURPLE, 13);   // Normal
        setpalette(PURPLEDR, 33); // Dark
        setpalette(PURPLEBR, 61); // Bright

        // Yellow Colors
        setpalette(YELLOW, 6);    // Normal
        setpalette(YELLOWDR, 48); // Dark
        setpalette(YELLOWBR, 62); // Bright
}

void GetImages() {
        Brick(100, 100, BLUE);
        Brick(130, 100, RED);
        Brick(160, 100, GREEN);
        Brick(190, 100, YELLOW);
        Brick(220, 100, PURPLE);

        bmpBlueBrick = malloc(imagesize(0, 0, 20, 20));
        bmpRedBrick = malloc(imagesize(0, 0, 20, 20));
        bmpGreenBrick = malloc(imagesize(0, 0, 20, 20));
        bmpYellowBrick = malloc(imagesize(0, 0, 20, 20));
        bmpPurpleBrick = malloc(imagesize(0, 0, 20, 20));
        bmpBlankBrick = malloc(imagesize(0, 0, 20, 20));
        bmpScore = malloc(imagesize(501, 51, 607, 69));
        bmpSpeed = malloc(imagesize(501, 51, 607, 69));
        bmpLevel = malloc(imagesize(501, 51, 607, 69));
        bmpLinesCleared = malloc(imagesize(501, 51, 607, 69));
        bmpScreen = malloc(imagesize(0, 0, 640, 480));

        getimage(100, 100, 120, 120, bmpBlueBrick);
        getimage(130, 100, 150, 120, bmpRedBrick);
        getimage(160, 100, 180, 120, bmpGreenBrick);
        getimage(190, 100, 210, 120, bmpYellowBrick);
        getimage(220, 100, 240, 120, bmpPurpleBrick);
        getimage(0, 0, 20, 20, bmpBlankBrick);
        getimage(501, 51, 607, 69, bmpScore);
        getimage(501, 51, 607, 69, bmpSpeed);
        getimage(501, 51, 607, 69, bmpLevel);
        getimage(501, 51, 607, 69, bmpLinesCleared);
}

void InitScreenLayout() {
        for (int x = 0; x < COLS; x++)
                for (int y = 0; y < ROWS; y++) {
                        ScreenLayout[x][y] = BLANK;
                        PreviousScreenLayout[x][y] = BLANK;
                        ScreenBackgroundLayout[x][y] = BLANK;
                }
}

void DisplayInterface() {
        settextstyle(BOLD_FONT, HORIZ_DIR, 0);

        setcolor(5);
        rectangle(158, 28, 476, 450);
        outtextxy(510, 280, "Next:");
        rectangle(478 + 5, 255 - 20, 620, 450);
        outtextxy(20, 265 - 20, "KEYS:");
        rectangle(10, 255 - 20, 150, 382 + 6 + 18 * 3 + 18 + 10 - 20);

        settextstyle(BOLD_FONT, HORIZ_DIR, 1);
        setcolor(5);
        outtextxy(20, 310 - 20, "Left   :");
        setcolor(LIGHTRED);
        outtextxy(20, 322 + 6 - 20, "Left arrow");
        setcolor(5);
        outtextxy(20, 330 + 18 - 20, "Right  :");
        setcolor(LIGHTRED);
        outtextxy(20, 342 + 6 + 18 - 20, "Right arrow");
        setcolor(5);
        outtextxy(20, 350 + 18 + 18 - 20, "Rotate :");
        setcolor(LIGHTRED);
        outtextxy(20, 362 + 6 + 18 + 18 - 20, "Up arrow");
        setcolor(5);

        outtextxy(20, 370 + 18 * 3 - 20, "Drop   :");
        setcolor(LIGHTRED);
        outtextxy(20, 382 + 6 + 18 * 3 - 20, "Down arrow");
        setcolor(5);
}

void AssignShape(int Shape, int Color) {
        int i, j;
        CurrentShape = Shape;
        switch (Shape) {
        case SHAPE_I:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                BlockMatrix[j][i] = ShapeI[i][j] * Color;
                break;
        case SHAPE_T:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                BlockMatrix[j][i] = ShapeT[i][j] * Color;
                break;
        case SHAPE_L:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                BlockMatrix[j][i] = ShapeL[i][j] * Color;
                break;
        case SHAPE_L2:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                BlockMatrix[j][i] = ShapeL2[i][j] * Color;
                break;
        case SHAPE_O:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                BlockMatrix[j][i] = ShapeO[i][j] * Color;
                break;
        case SHAPE_S:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                BlockMatrix[j][i] = ShapeS[i][j] * Color;
                break;
        case SHAPE_S2:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                BlockMatrix[j][i] = ShapeS2[i][j] * Color;
                break;
        default:
                break;
        }
}

int GetRandomColor() {
        int Color = rand() % 5;
        switch (Color) {
        case 0:
                return BLUE;
        case 1:
                return RED;
        case 2:
                return GREEN;
        case 3:
                return YELLOW;
        case 4:
                return PURPLE;
        }
        return 0;
}

int GetRandomShape() {
        int Shape = rand() % 7;
        switch (Shape) {
        case 0:
                return SHAPE_I;
        case 1:
                return SHAPE_L;
        case 2:
                return SHAPE_T;
        case 3:
                return SHAPE_O;
        case 4:
                return SHAPE_S;
        case 5:
                return SHAPE_S2;
        case 6:
                return SHAPE_L2;
        }
        return 0;
}

int MoveBlock(int Direction) {
        switch (Direction) {
        case LEFT:
                if (DetectCollision(LEFT))
                        return 1;
                DisplayBlock(--BlockX, BlockY);
                break;
        case RIGHT:
                if (DetectCollision(RIGHT))
                        return 1;
                DisplayBlock(++BlockX, BlockY);
                break;
        case DOWN:
                if (DetectCollision(DOWN)) {
                        GetNextBlock();
                        return 1;
                }
                DisplayBlock(BlockX, ++BlockY);
                break;
        case REFRESH:
                DisplayBlock(BlockX, BlockY);
                break;
        }
        return 0;
}

void RotateBlock() {
        int TempBlockMatrix[4][4];
        for (int i = 0; i < 4; i++)
                for (int j = 0; j < 4; j++)
                        TempBlockMatrix[i][j] = BlockMatrix[i][j];
        switch (CurrentShape) {
        case SHAPE_O:
                return;
        case SHAPE_L:
        case SHAPE_L2:
        case SHAPE_S:
        case SHAPE_S2:
        case SHAPE_T:
                BlockMatrix[0][0] = TempBlockMatrix[2][0];
                BlockMatrix[0][2] = TempBlockMatrix[0][0];
                BlockMatrix[2][2] = TempBlockMatrix[0][2];
                BlockMatrix[2][0] = TempBlockMatrix[2][2];

                BlockMatrix[0][1] = TempBlockMatrix[1][0];
                BlockMatrix[1][2] = TempBlockMatrix[0][1];
                BlockMatrix[2][1] = TempBlockMatrix[1][2];
                BlockMatrix[1][0] = TempBlockMatrix[2][1];
                break;
        case SHAPE_I:
                BlockMatrix[0][1] = TempBlockMatrix[1][0];
                BlockMatrix[1][0] = TempBlockMatrix[0][1];

                BlockMatrix[1][2] = TempBlockMatrix[2][1];
                BlockMatrix[2][1] = TempBlockMatrix[1][2];

                BlockMatrix[1][3] = TempBlockMatrix[3][1];
                BlockMatrix[3][1] = TempBlockMatrix[1][3];
                break;
        }
        if (DetectCollision(REFRESH)) {
                for (int i = 0; i < 4; i++)
                        for (int j = 0; j < 4; j++)
                                BlockMatrix[i][j] = TempBlockMatrix[i][j];
                return;
        }
        MoveBlock(REFRESH);
}

void DisplayBlock(int x, int y) {
        int i, j;
        for (i = 0; i < ROWS; i++)
                for (j = 0; j < COLS; j++)
                        ScreenLayout[j][i] = ScreenBackgroundLayout[j][i];

        for (i = 0; i < 4; i++) {
                if ((x + i) < 0 || (x + i) > COLS)
                        continue;
                for (j = 0; j < 4; j++) {
                        if ((y + j) > ROWS)
                                continue;
                        if (BlockMatrix[i][j] == 0)
                                continue;
                        ScreenLayout[x + i][y + j] = BlockMatrix[i][j];
                }
        }
        UpdateScreen();
}

int DetectCollision(int Direction) {
        int x, y;
        int Bx = BlockX;
        int By = BlockY;
        switch (Direction) {
        case LEFT:
                --Bx;
                break;
        case RIGHT:
                ++Bx;
                break;
        case DOWN:
                By++;
                break;
        default:
                break;
        }

        if (Bx < 0) {
                for (x = 0; (x + Bx) < 0; x++)
                        for (y = 0; y < 4; y++)
                                if (BlockMatrix[x][y] != 0)
                                        return 1;
        }

        if (Bx > COLS - 4) {
                for (x = Bx + 3; x >= COLS; x--)
                        for (y = 0; y < 4; y++)
                                if (BlockMatrix[x - Bx][y] != 0)
                                        return 1;
        }

        for (x = 0; x < 4; x++)
                for (y = 3; y >= 0; y--) {
                        if ((ScreenBackgroundLayout[Bx + x][By + y] != BLANK && BlockMatrix[x][y] != BLANK) || ((By + y) >= ROWS && BlockMatrix[x][y] != BLANK))
                                return 1;
                }

        return 0;
}

void GetNextBlock() {
        for (int x = 0; x < 4; x++)
                for (int y = 0; y < 4; y++)
                        if (BlockMatrix[x][y] != BLANK)
                                ScreenBackgroundLayout[BlockX + x][BlockY + y] = BlockMatrix[x][y];
        CheckForLine();
        AssignShape(NextShape, NextColor);
        NextShape = GetRandomShape();
        NextColor = GetRandomColor();
        DisplayNextShape();
        BlockX = 7;
        BlockY = 0;
        if (MoveBlock(LEFT)) {
                GameOver = 1;
                setcolor(RED);
                settextstyle(BOLD_FONT, HORIZ_DIR, 9);
                setfillstyle(SOLID_FILL, c_bk);
                bar((getmaxx() - textwidth("GAME OVER!")) / 2 - 50, (getmaxy() - textheight("GAME OVER!")) / 2 - 10, (getmaxx() - textwidth("GAME OVER!")) / 2 + 50 + textwidth("GAME OVER!"), (getmaxy() - textheight("GAME OVER!")) / 2 + 50 + textheight("GAME OVER!"));
                rectangle((getmaxx() - textwidth("GAME OVER!")) / 2 - 50, (getmaxy() - textheight("GAME OVER!")) / 2 - 10, (getmaxx() - textwidth("GAME OVER!")) / 2 + 50 + textwidth("GAME OVER!"), (getmaxy() - textheight("GAME OVER!")) / 2 + 50 + textheight("GAME OVER!"));

                outtextxy((getmaxx() - textwidth("GAME OVER!")) / 2, (getmaxy() - textheight("GAME OVER!")) / 2, "GAME OVER!");

                int mm1 = textheight("A");
                settextstyle(BOLD_FONT, HORIZ_DIR, 0);
                outtextxy((getmaxx() - textwidth("Press any key to return menu")) / 2, (getmaxy() - mm1) / 2 + mm1, "Press any key to return menu");
                getch();
        }
}

void DisplayNextShape() {
        int NextTop = 340;
        int NextLeft = 520;
        int TempMatrix[4][4];
        int i, j;

        switch (NextShape) {
        case SHAPE_I:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                TempMatrix[j][i] = ShapeI[i][j] * NextColor;
                break;
        case SHAPE_T:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                TempMatrix[j][i] = ShapeT[i][j] * NextColor;
                break;
        case SHAPE_L:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                TempMatrix[j][i] = ShapeL[i][j] * NextColor;
                break;
        case SHAPE_L2:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                TempMatrix[j][i] = ShapeL2[i][j] * NextColor;
                break;
        case SHAPE_O:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                TempMatrix[j][i] = ShapeO[i][j] * NextColor;
                break;
        case SHAPE_S:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                TempMatrix[j][i] = ShapeS[i][j] * NextColor;
                break;
        case SHAPE_S2:
                for (i = 0; i < 4; i++)
                        for (j = 0; j < 4; j++)
                                TempMatrix[j][i] = ShapeS2[i][j] * NextColor;
                break;
        default:
                break;
        }

        for (int x = 0; x < 4; x++)
                for (int y = 0; y < 4; y++) {
                        switch (TempMatrix[x][y]) {
                        case BLUE:
                                putimage(NextLeft + x * 21, NextTop + y * 21, bmpBlueBrick, 0);
                                break;
                        case RED:
                                putimage(NextLeft + x * 21, NextTop + y * 21, bmpRedBrick, 0);
                                break;
                        case GREEN:
                                putimage(NextLeft + x * 21, NextTop + y * 21, bmpGreenBrick, 0);
                                break;
                        case YELLOW:
                                putimage(NextLeft + x * 21, NextTop + y * 21, bmpYellowBrick, 0);
                                break;
                        case PURPLE:
                                putimage(NextLeft + x * 21, NextTop + y * 21, bmpPurpleBrick, 0);
                                break;
                        default:
                                putimage(NextLeft + x * 21, NextTop + y * 21, bmpBlankBrick, 0);
                        }
                }
}

void UpdateScreen() {
        for (int x = 0; x < COLS; x++)
                for (int y = 0; y < ROWS; y++) {
                        if (PreviousScreenLayout[x][y] == ScreenLayout[x][y])
                                continue;
                        PreviousScreenLayout[x][y] = ScreenLayout[x][y];
                        switch (ScreenLayout[x][y]) {
                        case BLUE:
                                putimage(LEFT + x * 21, TOP + y * 21, bmpBlueBrick, 0);
                                break;
                        case RED:
                                putimage(LEFT + x * 21, TOP + y * 21, bmpRedBrick, 0);
                                break;
                        case GREEN:
                                putimage(LEFT + x * 21, TOP + y * 21, bmpGreenBrick, 0);
                                break;
                        case YELLOW:
                                putimage(LEFT + x * 21, TOP + y * 21, bmpYellowBrick, 0);
                                break;
                        case PURPLE:
                                putimage(LEFT + x * 21, TOP + y * 21, bmpPurpleBrick, 0);
                                break;
                        default:
                                putimage(LEFT + x * 21, TOP + y * 21, bmpBlankBrick, 0);
                        }
                }
}

void CheckForLine() {
        int RemoveLines[10];
        int Remove;
        int x, y;
        int factor = 1;
        for (y = 0; y < ROWS; y++) {
                Remove = 1;
                for (x = 0; x < COLS; x++) {
                        if (ScreenLayout[x][y] == BLANK)
                                Remove = 0;
                }
                if (Remove) {
                        RemoveLine(y);

                        Score += LineScore * factor;
                        PrintScore();
                        factor++;
                }
        }
        while (kbhit())
                getch();
}

void RemoveLine(int LineNumber) {
        int i, j;
        int count = 0;
        int Temp[COLS];
        for (i = 0; i < COLS; i++) {
                Temp[i] = ScreenLayout[i][LineNumber];
        }
        for (j = 0; j < 6; j++) {
                for (i = 0; i < COLS; i++) {
                        ScreenLayout[i][LineNumber] = (count ? Temp[i] : BLANK);
                }
                count = !count;
                UpdateScreen();
                delay(50);
        }
        for (i = LineNumber; i > 0; i--)
                for (j = 0; j < COLS; j++) {
                        ScreenBackgroundLayout[j][i] = ScreenBackgroundLayout[j][i - 1];
                }
        for (j = 0; j < COLS; j++)
                ScreenBackgroundLayout[j][0] = BLANK;
        for (i = 0; i < COLS; i++)
                for (j = 0; j < ROWS; j++)
                        ScreenLayout[i][j] = ScreenBackgroundLayout[i][j];
        ++LinesCleared;

        if (!(LinesCleared % 20))
                IncreaseSpeed();
}

int IncreaseSpeed() {
        if (Speed - 5 <= 0)
                return 1;
        Speed -= 5;
        Level++;

        return 0;
}

void PrintScore() {
        sprintf(lpszScore, "%i", Score);
        int sssss = Score, counttt = 0;
        if (sssss == 0)
                counttt = 1;
        while (sssss) {
                counttt++;
                sssss /= 10;
        }

        counttt *= (textwidth("a"));
        outtextxy(getmaxx() - 40 - textwidth("RESET") + 10, 30 + 5, "Score");
        rectangle(getmaxx() - 40 - textwidth("RESET"), 25 + 5, getmaxx() - 20, 35 + textheight("EXIT") + 10 + textheight("EXIT") + 5);

        outtextxy(getmaxx() - 40 - textwidth("RESET") + (20 + textwidth("RESET") - counttt) / 2, 35 + 5 + textheight("RESET") + 5, lpszScore);
}
