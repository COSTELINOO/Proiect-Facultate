#include "variabile_globale.h"

void drawRoundedRectangle(int left, int top, int right, int bottom, int radius, int culoare) {
        setcolor(culoare);
        /// Desenează partea superioară a dreptunghiului
        line(left + radius, top, right - radius, top);
        /// Desenează colțurile superioare stânga și dreapta
        arc(right - radius, top, 0, 90, radius);
        arc(left + radius, top, 90, 180, radius);
        /// Desenează partea dreaptă a dreptunghiului
        line(right, top + radius, right, bottom - radius);
        /// Desenează colțurile drepte sus și jos
        arc(right, bottom - radius, 270, 360, radius);
        arc(right, top + radius, 0, 90, radius);
        /// Desenează partea de jos a dreptunghiului
        line(right - radius, bottom, left + radius, bottom);
        /// Desenează colțurile de jos stânga și dreapta
        arc(left + radius, bottom, 180, 270, radius);
        arc(right - radius, bottom, 90, 180, radius);
        /// Desenează partea stângă a dreptunghiului
        line(left, bottom - radius, left, top + radius);
        /// Desenează colțurile stângi sus și jos
        arc(left, top + radius, 270, 360, radius);
        arc(left, bottom - radius, 180, 270, radius);
}

void draw_pagina_start() {
        initwindow(720, getmaxheight() / 2, "Notepad", (getmaxwidth() - 720) / 2, (getmaxheight() - getmaxheight() / 2) / 2);
        setfillstyle(SOLID_FILL, c_bk);
        setbkcolor(c_bk);
        setcolor(c_text);
        setactivepage(0);
        cleardevice();
        setactivepage(1);
        cleardevice();
        setvisualpage(1);
        setcolor(MAGENTA);
        line(0, 80, getmaxx(), 80);
        settextstyle(BOLD_FONT, HORIZ_DIR, 7);
        outtextxy((getmaxx() - textwidth("TEXT EDITOR")) / 2, 20, "TEXT EDITOR");
        settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        setfillstyle(SOLID_FILL, c_bk);
        bar(30, 120, getmaxx() / 2, 160);
        rectangle(30, 120, getmaxx() / 2, 160);
        outtextxy(80, 125, "New file");
        line(getmaxx() / 2 - 60, 120, getmaxx() / 2 - 60, 160);
        setfillstyle(SOLID_FILL, MAGENTA);
        bar(getmaxx() / 2 - 50, 137, getmaxx() / 2 - 10, 143);
        rectangle(getmaxx() / 2 - 50, 137, getmaxx() / 2 - 10, 143);
        bar(getmaxx() / 2 - 34, 125, getmaxx() / 2 - 28, 155);
        rectangle(getmaxx() / 2 - 34, 125, getmaxx() / 2 - 28, 155);
        setfillstyle(SOLID_FILL, c_bk);
        bar(30, 200, getmaxx() / 2, 240);
        rectangle(30, 200, getmaxx() / 2, 240);
        outtextxy(80, 205, "Open file");
        line(getmaxx() / 2 - 60, 200, getmaxx() / 2 - 60, 240);
        setfillstyle(SOLID_FILL, MAGENTA);
        bar(getmaxx() / 2 - 50, 218, getmaxx() / 2 - 10, 233);
        rectangle(getmaxx() / 2 - 50, 218, getmaxx() / 2 - 10, 233);
        setfillstyle(SOLID_FILL, c_bk);
        bar(getmaxx() / 2 - 50, 208, getmaxx() / 2 - 30, 218);
        rectangle(getmaxx() / 2 - 50, 208, getmaxx() / 2 - 30, 218);
        setfillstyle(SOLID_FILL, c_bk);
        bar(30, 280, getmaxx() / 2, 320);
        rectangle(30, 280, getmaxx() / 2, 320);
        outtextxy(80, 285, "Exit");
        line(getmaxx() / 2 - 60, 280, getmaxx() / 2 - 60, 320);
        setfillstyle(SOLID_FILL, MAGENTA);
        circle(getmaxx() / 2 - 30, 300, 17);
        floodfill(getmaxx() / 2 - 30, 300, MAGENTA);
        setcolor(c_bk);
        setfillstyle(SOLID_FILL, c_bk);
        circle(getmaxx() / 2 - 30, 300, 14);
        floodfill(getmaxx() / 2 - 30, 300, c_bk);
        setfillstyle(SOLID_FILL, MAGENTA);
        setcolor(MAGENTA);
        drawRoundedRectangle(getmaxx() / 2 - 30 - 5, 300 - 5, getmaxx() / 2 - 30 + 5, 300 + 5, 1, 5);
        floodfill(getmaxx() / 2 - 30, 300, MAGENTA);
        setfillstyle(SOLID_FILL, c_bk);
        bar(getmaxx() / 2 + 20, 120, getmaxx() - 13, 320);
        rectangle(getmaxx() / 2 + 20, 120, getmaxx() - 13, 320);
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        outtextxy(getmaxx() / 2 + 30, 130, "Project informations:");
        setcolor(MAGENTA);
        line(getmaxx() / 2 + 20, 155, getmaxx() - 13, 155);
        line(getmaxx() - 140, 155, getmaxx() - 140, 320);
        outtextxy(getmaxx() / 2 + getmaxx() / 3, 170, "Arseni");
        outtextxy(getmaxx() / 2 + getmaxx() / 3, 190, "Costel");
        outtextxy(getmaxx() / 2 + getmaxx() / 3, 210, "Ionut");
        rectangle(getmaxx() / 2 + getmaxx() / 3 - 5, 165, getmaxx() / 2 + getmaxx() / 3 + textwidth("Faculty") + 5, 235);
        outtextxy(getmaxx() / 2 + getmaxx() / 3, 250, "My");
        outtextxy(getmaxx() / 2 + getmaxx() / 3, 270, "Faculty");
        outtextxy(getmaxx() / 2 + getmaxx() / 3, 290, "Project");
        rectangle(getmaxx() / 2 + getmaxx() / 3 - 5, 245, getmaxx() / 2 + getmaxx() / 3 + textwidth("Faculty") + 5, 315);
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        rectangle(getmaxx() / 2 + 25, 165, getmaxx() - 145, 235);
        outtextxy(getmaxx() / 2 + 33, 170, "Project number:");
        settextstyle(BOLD_FONT, HORIZ_DIR, 5);
        outtextxy(getmaxx() / 2 + 90, 190, "34");
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        rectangle(getmaxx() / 2 + 25, 245, getmaxx() - 145, 315);
        outtextxy(getmaxx() / 2 + 50, 250, "Team letter:");
        settextstyle(BOLD_FONT, HORIZ_DIR, 5);
        outtextxy(getmaxx() / 2 + 110, 270, "B");
        setfillstyle(SOLID_FILL, MAGENTA);
        bar(0, getmaxy() - 10, getmaxx(), getmaxy());
        rectangle(0, getmaxy() - 10, getmaxx(), getmaxy());
        bar(0, 0, getmaxx(), 10);
        rectangle(0, 0, getmaxx(), 10);
}
void buton_meniu(int cod, int x_txt, int y_txt, char *text1, int x1, int y1, int y2) {
        settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        setcolor(LIGHTRED);
        rectangle(x1, y1, getmaxx() / 2, y2);
        outtextxy(x_txt, y_txt, text1);
        line(getmaxx() / 2 - 60, y1, getmaxx() / 2 - 60, y2);
        setfillstyle(SOLID_FILL, LIGHTRED);

        if (cod == 0) {
                bar(getmaxx() / 2 - 50, 137, getmaxx() / 2 - 10, 143);
                rectangle(getmaxx() / 2 - 50, 137, getmaxx() / 2 - 10, 143);
                bar(getmaxx() / 2 - 34, 125, getmaxx() / 2 - 28, 155);
                rectangle(getmaxx() / 2 - 34, 125, getmaxx() / 2 - 28, 155);
                setfillstyle(SOLID_FILL, c_bk);
        } else if (cod == 1) {
                bar(getmaxx() / 2 - 50, 218, getmaxx() / 2 - 10, 233);
                rectangle(getmaxx() / 2 - 50, 218, getmaxx() / 2 - 10, 233);
                setfillstyle(SOLID_FILL, c_bk);
                bar(getmaxx() / 2 - 50, 208, getmaxx() / 2 - 30, 218);
                rectangle(getmaxx() / 2 - 50, 208, getmaxx() / 2 - 30, 218);
                setfillstyle(SOLID_FILL, c_bk);
        } else if (cod == 2) {
                circle(getmaxx() / 2 - 30, 300, 17);
                floodfill(getmaxx() / 2 - 30, 300, LIGHTRED);
                setcolor(c_bk);
                setfillstyle(SOLID_FILL, c_bk);
                circle(getmaxx() / 2 - 30, 300, 14);
                floodfill(getmaxx() / 2 - 30, 300, c_bk);
                setfillstyle(SOLID_FILL, LIGHTRED);
                setcolor(MAGENTA);
                drawRoundedRectangle(getmaxx() / 2 - 30 - 5, 300 - 5, getmaxx() / 2 - 30 + 5, 300 + 5, 1, LIGHTRED);
                floodfill(getmaxx() / 2 - 30, 300, LIGHTRED);
                setfillstyle(SOLID_FILL, c_bk);
        }

        while (mousex() > x1 && mousex() < getmaxx() / 2 && mousey() >= y1 && mousey() <= y2 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit())
                usleep(100);

        setcolor(5);
        rectangle(x1, y1, getmaxx() / 2, y2);
        outtextxy(x_txt, y_txt, text1);
        line(getmaxx() / 2 - 60, y1, getmaxx() / 2 - 60, y2);
        setfillstyle(SOLID_FILL, 5);

        if (cod == 0) {
                bar(getmaxx() / 2 - 50, 137, getmaxx() / 2 - 10, 143);
                rectangle(getmaxx() / 2 - 50, 137, getmaxx() / 2 - 10, 143);
                bar(getmaxx() / 2 - 34, 125, getmaxx() / 2 - 28, 155);
                rectangle(getmaxx() / 2 - 34, 125, getmaxx() / 2 - 28, 155);
                setfillstyle(SOLID_FILL, c_bk);
        } else if (cod == 1) {
                bar(getmaxx() / 2 - 50, 218, getmaxx() / 2 - 10, 233);
                rectangle(getmaxx() / 2 - 50, 218, getmaxx() / 2 - 10, 233);
                setfillstyle(SOLID_FILL, c_bk);
                bar(getmaxx() / 2 - 50, 208, getmaxx() / 2 - 30, 218);
                rectangle(getmaxx() / 2 - 50, 208, getmaxx() / 2 - 30, 218);
                setfillstyle(SOLID_FILL, c_bk);
        } else if (cod == 2) {
                circle(getmaxx() / 2 - 30, 300, 17);
                floodfill(getmaxx() / 2 - 30, 300, MAGENTA);
                setcolor(c_bk);
                setfillstyle(SOLID_FILL, c_bk);
                circle(getmaxx() / 2 - 30, 300, 14);
                floodfill(getmaxx() / 2 - 30, 300, c_bk);
                setfillstyle(SOLID_FILL, MAGENTA);
                setcolor(MAGENTA);
                drawRoundedRectangle(getmaxx() / 2 - 30 - 5, 300 - 5, getmaxx() / 2 - 30 + 5, 300 + 5, 1, 5);
                floodfill(getmaxx() / 2 - 30, 300, MAGENTA);
                setfillstyle(SOLID_FILL, c_bk);
        }
}

void buton_3_cuvinte(char *t1, char *t2, char *t3, int y1, int y2, int y3) {
        setcolor(CYAN);
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        outtextxy(getmaxx() / 2 + getmaxx() / 3, y1, t1);
        outtextxy(getmaxx() / 2 + getmaxx() / 3, y2, t2);
        outtextxy(getmaxx() / 2 + getmaxx() / 3, y3, t3);
        rectangle(getmaxx() / 2 + getmaxx() / 3 - 5, y1 - 5, getmaxx() / 2 + getmaxx() / 3 + textwidth("Faculty") + 5, y3 + 25);

        while (mousex() >= getmaxx() / 2 + getmaxx() / 3 - 5 && mousex() <= 687 && mousey() >= y1 - 5 && mousey() <= y3 + 25 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit())
                usleep(100);

        setcolor(MAGENTA);
        outtextxy(getmaxx() / 2 + getmaxx() / 3, y1, t1);
        outtextxy(getmaxx() / 2 + getmaxx() / 3, y2, t2);
        outtextxy(getmaxx() / 2 + getmaxx() / 3, y3, t3);
        rectangle(getmaxx() / 2 + getmaxx() / 3 - 5, y1 - 5, getmaxx() / 2 + getmaxx() / 3 + textwidth("Faculty") + 5, y3 + 25);
}

void buton_2_cuvinte(char *t1, char *t2, int x1, int y1, int x2, int y2) {
        setcolor(CYAN);
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        rectangle(getmaxx() / 2 + 25, y1, getmaxx() - 145, y2);
        outtextxy(x1, y1 + 5, t1);
        settextstyle(BOLD_FONT, HORIZ_DIR, 5);
        outtextxy(x2, y1 + 25, t2);

        while (mousex() >= getmaxx() / 2 + 25 && mousex() <= getmaxx() - 145 && mousey() >= y1 - 5 && mousey() <= y2 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit())
                usleep(100);

        setcolor(5);
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        rectangle(getmaxx() / 2 + 25, y1, getmaxx() - 145, y2);
        outtextxy(x1, y1 + 5, t1);
        settextstyle(BOLD_FONT, HORIZ_DIR, 5);
        outtextxy(x2, y1 + 25, t2);
}
