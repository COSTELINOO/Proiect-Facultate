#pragma once
#include "functii_grafice.h"

#include "variabile_globale.h"

void drawToolbar();
void sepLine();
void contor_linie_coloana();
void scroll_oriz();
void scroll_vert();
void scroll_vert() /// functia care afiseaza scrollbar-ul verticals
{
	lungime_scroll_vert = (getmaxy() - 152) - (max(0, dim_max_y - dim_y)) / 21 + 1;
	pozitie_scroll_vert = 76 + (poz_min_y - 65) / 21;
	lungime_scroll_vert = max(5, lungime_scroll_vert);
	pozitie_scroll_vert = min(getmaxy() - 81, pozitie_scroll_vert);
	int m_poz;
	if(mouse_click_vert == true) {
		while(!ismouseclick(WM_LBUTTONUP)) {
			while(kbhit()) {
				char temporar;
				temporar = getch();
				if(temporar == 0 || temporar == 224) temporar = getch();
			}
			if((mousey() - (lungime_scroll_vert) / 2) < 76) m_poz = 76 + (lungime_scroll_vert) / 2;
			else if((mousey() + (lungime_scroll_vert) / 2) > getmaxy() - 76) m_poz = getmaxy() - 76 - (lungime_scroll_vert) / 2;
			else m_poz = mousey();
			if(active_page == 0) active_page = 1;
			else active_page = 0;
			setactivepage(active_page);
			setbkcolor(WHITE);
			poz_min_y = (pozitie_scroll_vert - 76) * 21 + 65;
			poz_max_y = poz_min_y + dim_y - 65;
			poz_min_x = (pozitie_scroll_oriz - 26) * 12;
			poz_max_x = poz_min_x + dim_x;
			if(text_selectat == false && text_cautat == false) {
				cleardevice();
				drawToolbar();
				scroll_oriz();
				sepLine();
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				setbkcolor(c_bk);
				setcolor(c_text);
				text_selectat = false;
				setbkcolor(c_bk);
				x = 0;
				y = 65;
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
				contor_linie_coloana();
			} else if(text_cautat == true && !cautatt.empty()) {
				string cautare = cautatt;
				cleardevice();
				drawToolbar();
				scroll_oriz();
				sepLine();
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				setbkcolor(c_bk);
				setcolor(c_text);
				text_cautat = true;
				setbkcolor(c_bk);
				cnt = 0;
				int hau = 0;
				cnt = 0;
				x = 0;
				y = 65;
				for(int i = 0; i < text.size(); i++) {
					if(x + 36 == (getmaxx() - 20) / 36 * 36 && wrap_mode == true) {
						x = 0;
						y += 21;
					}
					if(cnt < aparitii.size()) {
						if(i >= aparitii[cnt] && (i <= aparitii[cnt] + cautare.size() - 1)) {
							setbkcolor(LIGHTMAGENTA);
							if(i == aparitii[cnt] + cautare.size() - 1) {
								cnt++;
							}
						} else setbkcolor(c_bk);
					} else setbkcolor(c_bk);
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
				contor_linie_coloana();
			} else {
				x_caret_i = pozitii[pozitie_i].first;
				y_caret_i = pozitii[pozitie_i].second;
				x_caret = pozitii[pozitie].first;
				y_caret = pozitii[pozitie].second;
				cleardevice();
				drawToolbar();
				sepLine();
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				setbkcolor(c_bk);
				setcolor(c_text);
				scroll_oriz();
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
				contor_linie_coloana();
			}
			pozitie_scroll_vert = m_poz - lungime_scroll_vert / 2;
			setcolor(MAGENTA);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(getmaxx() - 20, 70, getmaxx() - 5, getmaxy() - 70);
			rectangle(getmaxx() - 20, 70, getmaxx() - 5, getmaxy() - 70);
			setfillstyle(SOLID_FILL, MAGENTA);
			bar(getmaxx() - 20, 70, getmaxx() - 5, 76);
			rectangle(getmaxx() - 20, 70, getmaxx() - 5, 76);
			bar(getmaxx() - 20, getmaxy() - 76, getmaxx() - 5, getmaxy() - 70);
			rectangle(getmaxx() - 20, getmaxy() - 76, getmaxx() - 5, getmaxy() - 70);
			setfillstyle(SOLID_FILL, LIGHTRED);
			bar(getmaxx() - 19, pozitie_scroll_vert, getmaxx() - 6, pozitie_scroll_vert + lungime_scroll_vert);
			rectangle(getmaxx() - 19, pozitie_scroll_vert, getmaxx() - 6, pozitie_scroll_vert + lungime_scroll_vert);
			scroll_oriz();
			setvisualpage(active_page);
			usleep(10);
		}
		if(ismouseclick(WM_LBUTTONUP)) {
			clearmouseclick(WM_LBUTTONUP);
			clearmouseclick(WM_LBUTTONDOWN);
		}
	}
	setcolor(MAGENTA);
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(getmaxx() - 20, 70, getmaxx() - 5, getmaxy() - 70);
	rectangle(getmaxx() - 20, 70, getmaxx() - 5, getmaxy() - 70);
	setfillstyle(SOLID_FILL, MAGENTA);
	bar(getmaxx() - 20, 70, getmaxx() - 5, 76);
	rectangle(getmaxx() - 20, 70, getmaxx() - 5, 76);
	bar(getmaxx() - 20, getmaxy() - 76, getmaxx() - 5, getmaxy() - 70);
	rectangle(getmaxx() - 20, getmaxy() - 76, getmaxx() - 5, getmaxy() - 70);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(getmaxx() - 19, pozitie_scroll_vert, getmaxx() - 6, pozitie_scroll_vert + lungime_scroll_vert);
	rectangle(getmaxx() - 19, pozitie_scroll_vert, getmaxx() - 6, pozitie_scroll_vert + lungime_scroll_vert);
	setcolor(c_text);
	setfillstyle(SOLID_FILL, c_bk);
}
void scroll_oriz() /// functia care afiseaza scrollbar-ul orizontal
{
	if(wrap_mode == true) lungime_scroll_oriz = (getmaxx() - 52);
	else lungime_scroll_oriz = (getmaxx() - 52) - (max(0, dim_max_x - dim_x)) / 12 + 1;
	pozitie_scroll_oriz = 26 + (poz_min_x) / 12;
	lungime_scroll_oriz = max(5, lungime_scroll_oriz);
	pozitie_scroll_oriz = min(pozitie_scroll_oriz, getmaxx() - 31);
	if(mouse_click_oriz == false) {
		setcolor(MAGENTA);
		setfillstyle(SOLID_FILL, DARKGRAY);
		bar(20, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
		setfillstyle(SOLID_FILL, DARKGRAY);
		bar(20, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
		rectangle(20, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
		setfillstyle(SOLID_FILL, MAGENTA);
		bar(20, getmaxy() - 55, 26, getmaxy() - 40);
		rectangle(20, getmaxy() - 55, 26, getmaxy() - 40);
		bar(getmaxx() - 26, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
		rectangle(getmaxx() - 26, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
		setfillstyle(SOLID_FILL, LIGHTGRAY);
		bar(pozitie_scroll_oriz, getmaxy() - 54, pozitie_scroll_oriz + lungime_scroll_oriz, getmaxy() - 41);
		rectangle(pozitie_scroll_oriz, getmaxy() - 54, pozitie_scroll_oriz + lungime_scroll_oriz, getmaxy() - 41);
	}
	int m_poz;
	if(mouse_click_oriz == true) {
		while(!ismouseclick(WM_LBUTTONUP)) {
			if(kbhit()) {
				char temporar;
				temporar = getch();
				if(temporar == 0 || temporar == 224) temporar = getch();
			}
			if((mousex() - (lungime_scroll_oriz) / 2) < 26) m_poz = 26 + (lungime_scroll_oriz) / 2;
			else if((mousex() + (lungime_scroll_oriz) / 2) > getmaxx() - 26) m_poz = getmaxx() - 26 - (lungime_scroll_oriz) / 2;
			else m_poz = mousex();
			if(active_page == 0) active_page = 1;
			else active_page = 0;
			setactivepage(active_page);
			poz_min_y = (pozitie_scroll_vert - 76) * 21 + 65;
			poz_max_y = poz_min_y + dim_y - 65;
			poz_min_x = (pozitie_scroll_oriz - 26) * 12;
			poz_max_x = poz_min_x + dim_x;
			if(text_selectat == false && text_cautat == false) {
				cleardevice();
				drawToolbar();
				scroll_vert();
				sepLine();
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				setbkcolor(c_bk);
				setcolor(c_text);
				text_selectat = false;
				setbkcolor(c_bk);
				x = 0;
				y = 65;
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
				contor_linie_coloana();
			} else if(text_cautat == true && !cautatt.empty()) {
				cleardevice();
				drawToolbar();
				scroll_vert();
				sepLine();
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				setbkcolor(c_bk);
				setcolor(c_text);
				text_selectat = false;
				setbkcolor(c_bk);
				string cautare = cautatt;
				cnt = 0;
				int hau = 0;
				cnt = 0;
				x = 0;
				y = 65;
				for(int i = 0; i < text.size(); i++) {
					if(x + 36 == (getmaxx() - 20) / 36 * 36 && wrap_mode == true) {
						x = 0;
						y += 21;
					}
					if(cnt < aparitii.size()) {
						if(i >= aparitii[cnt] && (i <= aparitii[cnt] + cautare.size() - 1)) {
							setbkcolor(LIGHTMAGENTA);
							if(i == aparitii[cnt] + cautare.size() - 1) {
								cnt++;
							}
						} else setbkcolor(c_bk);
					} else setbkcolor(c_bk);
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
				contor_linie_coloana();
			} else {
				x_caret_i = pozitii[pozitie_i].first;
				y_caret_i = pozitii[pozitie_i].second;
				x_caret = pozitii[pozitie].first;
				y_caret = pozitii[pozitie].second;
				cleardevice();
				drawToolbar();
				sepLine();
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				setbkcolor(c_bk);
				setcolor(c_text);
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
				contor_linie_coloana();
				contor_linie_coloana();
			}
			pozitie_scroll_oriz = max(26, m_poz - lungime_scroll_oriz / 2);
			if(pozitie_scroll_oriz + lungime_scroll_oriz > getmaxx() - 26) pozitie_scroll_oriz = getmaxx() - 26 - lungime_scroll_oriz;
			setcolor(MAGENTA);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(20, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
			setfillstyle(SOLID_FILL, DARKGRAY);
			bar(20, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
			rectangle(20, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
			setfillstyle(SOLID_FILL, MAGENTA);
			bar(20, getmaxy() - 55, 26, getmaxy() - 40);
			rectangle(20, getmaxy() - 55, 26, getmaxy() - 40);
			bar(getmaxx() - 26, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
			rectangle(getmaxx() - 26, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
			setfillstyle(SOLID_FILL, LIGHTRED);
			bar(pozitie_scroll_oriz, getmaxy() - 54, pozitie_scroll_oriz + lungime_scroll_oriz, getmaxy() - 41);
			rectangle(pozitie_scroll_oriz, getmaxy() - 54, pozitie_scroll_oriz + lungime_scroll_oriz, getmaxy() - 41);
			scroll_vert();
			contor_linie_coloana();
			setvisualpage(active_page);
			usleep(10);
		}
		mouse_click_oriz == false;
		clearmouseclick(WM_LBUTTONUP);
		clearmouseclick(WM_LBUTTONDOWN);
	}
	setcolor(MAGENTA);
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(20, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
	setfillstyle(SOLID_FILL, DARKGRAY);
	bar(20, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
	rectangle(20, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
	setfillstyle(SOLID_FILL, MAGENTA);
	bar(20, getmaxy() - 55, 26, getmaxy() - 40);
	rectangle(20, getmaxy() - 55, 26, getmaxy() - 40);
	bar(getmaxx() - 26, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
	rectangle(getmaxx() - 26, getmaxy() - 55, getmaxx() - 20, getmaxy() - 40);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(pozitie_scroll_oriz, getmaxy() - 54, pozitie_scroll_oriz + lungime_scroll_oriz, getmaxy() - 41);
	rectangle(pozitie_scroll_oriz, getmaxy() - 54, pozitie_scroll_oriz + lungime_scroll_oriz, getmaxy() - 41);
	setcolor(c_text);
	setfillstyle(SOLID_FILL, c_bk);
}
