#pragma once
#include "functionalitati.h"

#include "scroll_bar.h"

void drawToolbar();
void sepLine();
void contor_linie_coloana();
void doar_text();
void echilibrare_pozitii();
void echilibrare_caret();
void initializare_fereastra(int dim_xx, int dim_yy) {
	/// afisarea ferestrei principale de executie
	/// dim_xx, dim_yy vor fi folosite pentru dimensiunea ferestrei(mic, mediu, maxim)
	mainWindowHandle = initwindow(dim_xx, dim_yy, "Notepad", (getmaxwidth() - dim_xx) / 2, (getmaxheight() - dim_yy) / 2, false);
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
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	drawToolbar();
	sepLine();
	dim_x = (dim_xx - 20) / 12 * 12 - 24;
	dim_y = (dim_yy - 55 - 65) / 21 * 21 + 65 - 21;
	lungime_scroll_vert = (getmaxy() - 152) - (max(0, dim_max_y - dim_y)) / 21;
	lungime_scroll_oriz = (getmaxx() - 52) - (max(0, dim_max_x - dim_x)) / 12;
	pozitie_scroll_vert = 76 - (poz_min_y - 65) / 21;
	pozitie_scroll_oriz = 26 - (poz_min_x) / 12;
	poz_min_x = 0;
	poz_min_y = 65;
	poz_max_x = dim_x;
	poz_max_y = dim_y;
	scroll_oriz();
	scroll_vert();
	contor_linie_coloana();
}
void drawToolbar() /// Aceasta functie deseneaza meniul din partea de sus.
{
	setbkcolor(c_bk);
	setfillstyle(SOLID_FILL, c_bk);
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setcolor(LIGHTGRAY);
	bar(0, 0, getmaxx(), getmaxy());
	setcolor(5);
	line(0, getmaxy() - 35, getmaxx(), getmaxy() - 35);
	line(getmaxx() / 3, getmaxy() - 35, getmaxx() / 3, getmaxy());
	line(getmaxx() / 3 * 2, getmaxy() - 35, getmaxx() / 3 * 2, getmaxy());
	rectangle(10, 10, 110, 30);
	setcolor(5);
	setbkcolor(c_bk);
	outtextxy(30, getmaxy() - 30, "Line: ");
	outtextxy(getmaxx() / 3 + 30, getmaxy() - 30, "Column: ");
	outtextxy(getmaxx() / 3 * 2 + 30, getmaxy() - 30, "Position: ");
	outtextxy(38, 12, "File");
	rectangle(120, 10, 230, 30);
	setcolor(5);
	setbkcolor(c_bk);
	outtextxy(151, 12, "Edit");
	rectangle(240, 10, 350, 30);
	setcolor(5);
	setbkcolor(c_bk);
	outtextxy(265, 12, "Theme");
	rectangle(360, 10, 470, 30);
	setcolor(5);
	setbkcolor(c_bk);
	outtextxy(385, 12, "Color");
	rectangle(480, 10, 590, 30);
	setcolor(5);
	setbkcolor(c_bk);
	outtextxy(499, 12, "Window");
	rectangle(600, 10, 710, 30);
	setcolor(5);
	setbkcolor(c_bk);
	outtextxy(631, 12, "Wrap");
}
void doar_text() {
	setbkcolor(c_bk);
	cleardevice();
	x = 0;
	y = 65;
	pozitii.erase(pozitii.begin(), pozitii.end());
	for(int i = 0; i < text.size(); i++) {
		if(x + 36 == (getmaxx() - 20) / 36 * 36 && wrap_mode == true) {
			x = 0;
			y += 21;
		}
		pozitii.push_back({
			x,
			y
		});
		dim_max_x = max(dim_max_x, x);
		dim_max_y = max(dim_max_y, y);
		if(text[i] == 10 || text[i] == '$') {
			y = y + 21;
			x = 0;
		} else {
			pozitii[i].first = x;
			pozitii[i].second = y;
			x = x + 12;
		}
		pozitii[i].first = x;
		pozitii[i].second = y;
		dim_max_x = max(dim_max_x, x);
		dim_max_y = max(dim_max_y, y);
	}
	echilibrare_pozitii();
	if(text_selectat == false) {
		if(active_page == 0) active_page = 1;
		else active_page = 0;
		setactivepage(active_page);
		setbkcolor(c_bk);
		cleardevice();
		drawToolbar();
		sepLine();
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		setbkcolor(c_bk);
		setcolor(c_text);
		text_selectat = false;
		setbkcolor(c_bk);
		x = 0;
		y = 65;
		echilibrare_pozitii();
		for(int i = 0; i < text.size(); i++) {
			if(x + 36 == (getmaxx() - 20) / 36 * 36 && wrap_mode == true) {
				x = 0;
				y += 21;
			}
			if(text[i] == 10) {
				y = y + textheight(aux);
				x = -12;
			}
			if(text[i] == '\n') aux[0] = ' ';
			else aux[0] = text[i];
			if(aux[0] != '\n')
				if(x >= poz_min_x && x <= poz_max_x && y >= poz_min_y && y <= poz_max_y) outtextxy(x - poz_min_x + 12, y - poz_min_y + 65, aux);
			x = x + 12;
		}
		if(mouse_click_oriz == false && mouse_click_vert == false) {
			scroll_oriz();
			scroll_vert();
		}
		setvisualpage(active_page);
		contor_linie_coloana();
	} else {
		if(pozitie_i != 0) {
			x_caret_i = pozitii[pozitie_i - 1].first - poz_min_x;
			y_caret_i = pozitii[pozitie_i - 1].second - poz_min_y + 65;
		} else {
			x_caret_i = 0;
			y_caret_i = 65;
		}
		echilibrare_pozitii();
		echilibrare_caret();
		if(active_page == 0) active_page = 1;
		else active_page = 0;
		setactivepage(active_page);
		cleardevice();
		drawToolbar();
		sepLine();
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		setbkcolor(c_bk);
		setcolor(c_text);
		scroll_oriz();
		scroll_vert();
		text_selectat = true;
		if(pozitie_i < pozitie) {
			aux[1] = 0;
			x = 0;
			y = 65;
			for(int i = 0; i < text.size(); i++) {
				if(x + 36 == (getmaxx() - 20) / 36 * 36 && wrap_mode == true) {
					x = 0;
					y += 21;
				}
				if(i == 0 && x_caret_i == 0 && pozitie_i == 1) setbkcolor(c_selectat);
				else if(i >= pozitie_i && i < pozitie) setbkcolor(c_selectat);
				else setbkcolor(c_bk);
				if(text[i] == 10) {
					y = y + textheight(aux);
					x = -12;
				}
				if(text[i] == '\n') aux[0] = ' ';
				else aux[0] = text[i];
				if(aux[0] != '\n')
					if(x >= poz_min_x && x <= poz_max_x && y >= poz_min_y && y <= poz_max_y) outtextxy(x - poz_min_x + 12, y - poz_min_y + 65, aux);
				x = x + 12;
			}
		} else {
			aux[1] = 0;
			x = 0;
			y = 65;
			for(int i = 0; i < text.size(); i++) {
				if(x + 36 == (getmaxx() - 20) / 36 * 36 && wrap_mode == true) {
					x = 0;
					y += 21;
				}
				if(i == 0 && x_caret == 0 && pozitie == 1) setbkcolor(c_selectat);
				else if(i < pozitie_i && i >= pozitie) setbkcolor(c_selectat);
				else setbkcolor(c_bk);
				if(text[i] == 10) {
					y = y + textheight(aux);
					x = -12;
				}
				if(text[i] == '\n') aux[0] = ' ';
				else aux[0] = text[i];
				if(aux[0] != '\n')
					if(x >= poz_min_x && x <= poz_max_x && y >= poz_min_y && y <= poz_max_y) outtextxy(x - poz_min_x + 12, y - poz_min_y + 65, aux);
				x = x + 12;
			}
		}
		setbkcolor(c_bk);
		if(mouse_click_oriz == false && mouse_click_vert == false) {
			scroll_oriz();
			scroll_vert();
		}
		contor_linie_coloana();
		setvisualpage(active_page);
	}
	echilibrare_caret();
}
void sepLine() /// linia de separare intre Toolbar si zona de executie a programului
{
	setcolor(5);
	line(0, 40, getmaxx(), 40);
	if(wrap_mode == true) {
		outtextxy((getmaxx() - 20) / 36 * 36 - 18 + 5, 40 + 5, "Wrap");
		outtextxy((getmaxx() - 20) / 36 * 36 - 18 + 4, 40 + 5 + 21, "On");
		y = 66 + 21;
		while(y < getmaxy() - 40) {
			outtextxy((getmaxx() - 20) / 36 * 36 - 18 + 4 + 6, y, "^");
			y += 21;
		}
		line((getmaxx() - 20) / 36 * 36 - 18, 40, (getmaxx() - 20) / 36 * 36 - 18, getmaxy() - 40);
	}
}
void displayTemaMenu() /// meniul pentru optiunea TEMA
{
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setfillstyle(SOLID_FILL, 7);
	setbkcolor(7);
	setcolor(5);
	bar(240, 30, 350, 100);
	rectangle(240, 30, 350, 100);
	outtextxy(250, 50, "Dark");
	outtextxy(250, 70, "Light");
	setfillstyle(SOLID_FILL, c_bk);
	setbkcolor(c_bk);
}
void displayCuloareMenu() /// meniul pentru optiunea CULOARE
{
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setfillstyle(SOLID_FILL, 7);
	setbkcolor(7);
	setcolor(5);
	bar(360, 30, 470, 120);
	rectangle(360, 30, 470, 120);
	outtextxy(370, 50, "Red");
	outtextxy(370, 70, "Cyan");
	outtextxy(370, 90, "Brown");
	setfillstyle(SOLID_FILL, c_bk);
	setbkcolor(c_bk);
}
void displayWrapMenu() /// Meniul pentru optiunea WRAP
{
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setfillstyle(SOLID_FILL, 7);
	setbkcolor(7);
	setcolor(5);
	bar(600, 30, 710, 100);
	rectangle(600, 30, 710, 100);
	outtextxy(610, 50, "On");
	outtextxy(610, 70, "Off");
	setfillstyle(SOLID_FILL, c_bk);
	setbkcolor(c_bk);
}
void displayDimensiuneMenu() /// Meniul pentru optiunea DIMENSIUNE
{
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setfillstyle(SOLID_FILL, 7);
	setbkcolor(7);
	setcolor(5);
	bar(480, 30, 590, 120);
	rectangle(480, 30, 590, 120);
	outtextxy(490, 50, "Maximum");
	outtextxy(490, 70, "Middle");
	outtextxy(490, 90, "Minimum");
	setfillstyle(SOLID_FILL, c_bk);
	setbkcolor(c_bk);
}
void displayFileMenu() /// Meniul pentru optiunea FILE
{
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setfillstyle(SOLID_FILL, 7);
	setbkcolor(7);
	setcolor(5);
	bar(10, 30, 110, 140);
	rectangle(10, 30, 110, 140);
	outtextxy(20, 50, "New");
	outtextxy(20, 70, "Open");
	outtextxy(20, 90, "Save");
	outtextxy(20, 110, "Exit");
	setfillstyle(SOLID_FILL, c_bk);
	setbkcolor(c_bk);
}
void displayEditatiMenu() /// Meniul pentru optiunea EDITATI
{
	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
	setfillstyle(SOLID_FILL, 7);
	setbkcolor(7);
	setcolor(5);
	bar(120, 30, 230, 260);
	rectangle(120, 30, 230, 260);
	outtextxy(130, 50, "Undo");
	outtextxy(130, 70, "Redo");
	outtextxy(130, 90, "Copy");
	outtextxy(130, 110, "Paste");
	outtextxy(130, 130, "Cut");
	outtextxy(130, 150, "Replace");
	outtextxy(130, 170, "Find");
	outtextxy(130, 190, "Select");
	outtextxy(130, 210, "Hex view");
	outtextxy(130, 230, "Normal");
	setfillstyle(SOLID_FILL, c_bk);
	setbkcolor(c_bk);
}
