#pragma once
#include "functii_grafice.h"

#include "variabile_globale.h"

// butoane toolbar
void buton(int set_color_1, int setcolor_2, int set_color_3, int bck_color, int x_text, int y_text, char * text, int x1, int y1, int x2, int y2) {
	setbkcolor(bck_color);
	setcolor(set_color_1);

	outtextxy(x_text, y_text, text);


	 if(set_color_1==LIGHTRED)
    { setfillstyle(SOLID_FILL,LIGHTGRAY);
        bar(x1+1, 30, x2-1, y2+3);
         rectangle(x1, y1, x2, y2);
       }
       rectangle(x1, y1, x2, y2);

	while(mousex() >= x1 && mousex() <= x2 && mousey() > y1 && mousey() <= y2 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) usleep(100);

	setcolor(setcolor_2);
rectangle(x1, y1, x2, y2);
setcolor(set_color_3);
	outtextxy(x_text, y_text, text);
    if(set_color_1==LIGHTRED)
    { setfillstyle(SOLID_FILL,LIGHTGRAY);
        bar(x1+1, 30, x2-1, y2+3);
         rectangle(x1, y1, x2, y2);
       }


	usleep(100);
}
void ferestre(int cod) {
	if(mousex() >= 10 && mousex() <= 110 && !ismouseclick(WM_LBUTTONDOWN) && cod != 0) buton(GREEN, 5, 5, c_bk, 38, 12, const_cast < char * > ("File"), 10, 10, 110, 30);
	if(mousex() >= 120 && mousex() <= 230 && !ismouseclick(WM_LBUTTONDOWN) && cod != 1) buton(GREEN, 5, 5, c_bk, 151, 12, const_cast < char * > ("Edit"), 120, 10, 230, 30);
	if(mousex() >= 230 && mousex() <= 350 && !ismouseclick(WM_LBUTTONDOWN) && cod != 2) buton(GREEN, 5, 5, c_bk, 265, 12, const_cast < char * > ("Theme"), 240, 10, 350, 30);
	if(mousex() >= 360 && mousex() <= 470 && !ismouseclick(WM_LBUTTONDOWN) && cod != 3) buton(GREEN, 5, 5, c_bk, 385, 12, const_cast < char * > ("Color"), 360, 10, 470, 30);
	if(mousex() >= 480 && mousex() <= 590 && !ismouseclick(WM_LBUTTONDOWN) && cod != 4) buton(GREEN, 5, 5, c_bk, 499, 12, const_cast < char * > ("Window"), 480, 10, 590, 30);
	if(mousex() >= 600 && mousex() <= 710 && !ismouseclick(WM_LBUTTONDOWN) && cod != 5) buton(GREEN, 5, 5, c_bk, 631, 12, const_cast < char * > ("Wrap"), 600, 10, 710, 30);
}
void ver_tasta_si_click() {
	if(kbhit()) /// daca apas o tasta
	{
		char temporar;
		temporar = getch();
		if(temporar == 0 || temporar == 224) temporar = getch();
	}
	if(ismouseclick(WM_LBUTTONDBLCLK)) /// dublu click stanga
	{
		clearmouseclick(WM_LBUTTONDOWN);
		while(!ismouseclick(WM_LBUTTONUP));
		clearmouseclick(WM_LBUTTONUP);
		clearmouseclick(WM_LBUTTONDBLCLK);
	}
}
void tema(int color1, int color2, int color3) {
	c_bk = color1;
	c_text = color1;
	c_selectat = color3;
	setfillstyle(SOLID_FILL, c_bk);
	bar(0, 0, getmaxx(), getmaxy());
	setbkcolor(c_bk);
	cleardevice();
	setactivepage(0);
	cleardevice();
	setactivepage(1);
	cleardevice();
	setvisualpage(1);
	setbkcolor(c_bk);
	setcolor(c_text);
	if(active_page == 0) active_page = 1;
	else active_page = 0;
	setactivepage(active_page);
	setfillstyle(SOLID_FILL, c_bk);
	bar(0, 0, getmaxx(), getmaxy());
	setbkcolor(c_bk);
	cleardevice();
	setactivepage(0);
	cleardevice();
	setactivepage(1);
	cleardevice();
	setvisualpage(1);
	setbkcolor(c_bk);
	setcolor(c_text);
	c_bk = color1;
	c_text = color2;
	c_selectat = color3;
	setbkcolor(c_bk);
	cleardevice();
	setfillstyle(SOLID_FILL, c_bk);
	bar(0, 0, getmaxx(), getmaxy());
	doar_text();
	contor_linie_coloana();
	fereastra_tema = false;
	fereastra_deschisa = false;
}
