#pragma once
#include "functionalitati.h"

#include "variabile_globale.h"

void scriere_text() /// coloreaza textul in functie de unde este plasat cursorul mouse-ului
{
	aux[1] = 0;
	while(inchidere_fereastra == false) {
		if(hex_view == false) {
			text_aux = text;
			c_text_aux = c_text;
		}
		if(text_selectat == false && !kbhit() && text_cautat == false && pozitii[pozitie - 1].first >= poz_min_x && pozitii[pozitie - 1].first <= poz_max_x + 12 && pozitii[pozitie - 1].second >= poz_min_y && pozitii[pozitie - 1].second <= poz_max_y) /// desenare caret
		{
			using namespace std::chrono;
			uint64_t after = duration_cast < milliseconds > (system_clock::now().time_since_epoch()).count();
			if(after % 100 == 0 && after % 200 != 0) {
				setcolor(c_bk);
				line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
			} else if(after % 200 == 0) {
				setcolor(c_text);
				line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
			}
			setcolor(c_text);
		}
		if(!ismouseclick(WM_LBUTTONDOWN)) /// daca nu fac click, doar trec cu cursorul
		{
			if(mousey() >= 10 && mousey() <= 30 && mousex() >= 10 && mousex() <= 710) /// culorile pentru Toolbar
			{
				if(mousex() >= 10 && mousex() <= 110) /// FILE
				{
					setcolor(LIGHTRED);
					rectangle(10, 10, 110, 30);
					setcolor(LIGHTRED);
					outtextxy(38, 12, "File");
					while(mousey() >= 10 && mousey() <= 30 && mousex() >= 10 && mousex() <= 110 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) {}
					setcolor(5);
					rectangle(10, 10, 110, 30);
					outtextxy(38, 12, "File");
				} else if(mousex() >= 120 && mousex() <= 230) /// EDIT
				{
					setcolor(LIGHTRED);
					rectangle(120, 10, 230, 30);
					setcolor(LIGHTRED);
					outtextxy(151, 12, "Edit");
					while(mousey() >= 10 && mousey() <= 30 && mousex() >= 120 && mousex() <= 230 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) {}
					setcolor(5);
					rectangle(120, 10, 230, 30);
					outtextxy(151, 12, "Edit");
				} else if(mousex() >= 240 && mousex() <= 350) /// THEME
				{
					setcolor(LIGHTRED);
					rectangle(240, 10, 350, 30);
					setcolor(LIGHTRED);
					outtextxy(265, 12, "Theme");
					while(mousey() >= 10 && mousey() <= 30 && mousex() >= 240 && mousex() <= 350 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) {}
					setcolor(5);
					rectangle(240, 10, 350, 30);
					outtextxy(265, 12, "Theme");
				} else if(mousex() >= 360 && mousex() <= 470) /// COLOR
				{
					setcolor(LIGHTRED);
					rectangle(360, 10, 470, 30);
					setcolor(LIGHTRED);
					outtextxy(385, 12, "Color");
					while(mousey() >= 10 && mousey() <= 30 && mousex() >= 360 && mousex() <= 470 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) {}
					setcolor(5);
					rectangle(360, 10, 470, 30);
					outtextxy(385, 12, "Color");
				} else if(mousex() >= 480 && mousex() <= 590) /// WINDOW
				{
					setcolor(LIGHTRED);
					rectangle(480, 10, 590, 30);
					setcolor(LIGHTRED);
					outtextxy(499, 12, "Window");
					while(mousey() >= 10 && mousey() <= 30 && mousex() >= 480 && mousex() <= 590 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) {}
					setcolor(5);
					rectangle(480, 10, 590, 30);
					outtextxy(499, 12, "Window");
				} else if(mousex() >= 600 && mousex() <= 710) /// WRAP
				{
					setcolor(LIGHTRED);
					rectangle(600, 10, 710, 30);
					setcolor(LIGHTRED);
					outtextxy(631, 12, "Wrap");
					while(mousey() >= 10 && mousey() <= 30 && mousex() >= 600 && mousex() <= 710 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) {}
					setcolor(5);
					rectangle(600, 10, 710, 30);
					outtextxy(631, 12, "Wrap");
				}
			}
			if(mousey() >= getmaxy() - 40) /// culorile pentru meniul de jos(linie, coloana, pozitie)
			{
				int tmp = 0;
				char * nr;
				string numar;
				if(pozitii.empty()) {
					tmp = 1;
					pozitii.push_back({
						0,
						65
					});
				}
				if(mousex() >= 0 && mousex() <= getmaxx() / 3) /// ne aflam in prima treime:LINIE
				{
					setcolor(CYAN);
					number(numar, (pozitii[max(0, pozitie - 1)].second - 65) / 21 + 1);
					nr = & numar[0];
					outtextxy(30, getmaxy() - 30, "Line: ");
					outtextxy(30 + textwidth("Line: "), getmaxy() - 30, nr);
					rectangle(0, getmaxy() - 35, getmaxx() / 3, getmaxy());
					numar.erase(numar.begin(), numar.end());
					while(mousey() >= getmaxy() - 40 && mousex() >= 0 && mousex() <= getmaxx() / 3 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) usleep(100);
					setcolor(5);
					number(numar, (pozitii[max(0, pozitie - 1)].second - 65) / 21 + 1);
					nr = & numar[0];
					outtextxy(30, getmaxy() - 30, "Line: ");
					outtextxy(30 + textwidth("Line: "), getmaxy() - 30, nr);
					rectangle(0, getmaxy() - 35, getmaxx() / 3, getmaxy());
					numar.erase(numar.begin(), numar.end());
				}
				if(mousex() >= getmaxx() / 3 && mousex() <= getmaxx() / 3 * 2) /// ne aflam in a doua treime:COLOANA
				{
					setcolor(CYAN);
					number(numar, (pozitii[max(0, pozitie - 1)].first) / 12 + 1);
					nr = & numar[0];
					rectangle(getmaxx() / 3, getmaxy() - 35, getmaxx() / 3 * 2, getmaxy());
					outtextxy(getmaxx() / 3 + 30, getmaxy() - 30, "Column: ");
					outtextxy(getmaxx() / 3 + 30 + textwidth("Column: "), getmaxy() - 30, nr);
					numar.erase(numar.begin(), numar.end());
					while(mousey() >= getmaxy() - 40 && mousex() >= getmaxx() / 3 && mousex() <= getmaxx() / 3 * 2 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) usleep(100);
					setcolor(5);
					number(numar, (pozitii[max(0, pozitie - 1)].first) / 12 + 1);
					nr = & numar[0];
					rectangle(getmaxx() / 3, getmaxy() - 35, getmaxx() / 3 * 2, getmaxy());
					outtextxy(getmaxx() / 3 + 30, getmaxy() - 30, "Column: ");
					outtextxy(getmaxx() / 3 + 30 + textwidth("Column: "), getmaxy() - 30, nr);
					numar.erase(numar.begin(), numar.end());
				}
				if(mousex() >= getmaxx() / 3 * 2) /// ne aflam in a treia treime: POZITIE
				{
					setcolor(CYAN);
					number(numar, pozitie + 1);
					nr = & numar[0];
					outtextxy(getmaxx() / 3 * 2 + 30, getmaxy() - 30, "Position: ");
					rectangle(getmaxx() / 3 * 2, getmaxy() - 35, getmaxx(), getmaxy());
					outtextxy(getmaxx() / 3 * 2 + 30 + textwidth("Position: "), getmaxy() - 30, nr);
					numar.erase(numar.begin(), numar.end());
					while(mousey() >= getmaxy() - 40 && mousex() >= getmaxx() / 3 * 2 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) usleep(100);
					setcolor(5);
					number(numar, pozitie + 1);
					nr = & numar[0];
					rectangle(getmaxx() / 3 * 2, getmaxy() - 35, getmaxx(), getmaxy());
					outtextxy(getmaxx() / 3 * 2 + 30, getmaxy() - 30, "Position: ");
					outtextxy(getmaxx() / 3 * 2 + 30 + textwidth("Position: "), getmaxy() - 30, nr);
					numar.erase(numar.begin(), numar.end());
				}
			}
			if(mousey() >= 35 && mousey() <= 45) /// culoare pentru linia de separare dintre Toolbar si zona de executie
			{
				setcolor(CYAN);
				line(0, 40, getmaxx(), 40);
				while(mousey() >= 35 && mousey() <= 45 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) usleep(100);
				setcolor(5);
				line(0, 40, getmaxx(), 40);
			}
			if(mousey() >= 76 && mousey() <= getmaxy() - 76 && mousex() >= getmaxx() - 20 && mousex() <= getmaxx() - 5) /// culoare scrollbar vertical
			{
				setcolor(5);
				setfillstyle(SOLID_FILL, DARKGRAY);
				bar(getmaxx() - 20, 70, getmaxx() - 5, getmaxy() - 70);
				rectangle(getmaxx() - 20, 70, getmaxx() - 5, getmaxy() - 70);
				setfillstyle(SOLID_FILL, 5);
				bar(getmaxx() - 20, 70, getmaxx() - 5, 76);
				rectangle(getmaxx() - 20, 70, getmaxx() - 5, 76);
				bar(getmaxx() - 20, getmaxy() - 76, getmaxx() - 5, getmaxy() - 70);
				rectangle(getmaxx() - 20, getmaxy() - 76, getmaxx() - 5, getmaxy() - 70);
				setfillstyle(SOLID_FILL, LIGHTRED);
				bar(getmaxx() - 19, pozitie_scroll_vert, getmaxx() - 6, pozitie_scroll_vert + lungime_scroll_vert);
				rectangle(getmaxx() - 19, pozitie_scroll_vert, getmaxx() - 6, pozitie_scroll_vert + lungime_scroll_vert);
				while(mousey() >= 76 && mousey() <= getmaxy() - 76 && mousex() >= getmaxx() - 20 && mousex() <= getmaxx() - 5 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) usleep(100);
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
			}
			if(mousey() >= getmaxy() - 55 && mousey() <= getmaxy() - 40 && mousex() >= 26 && mousex() <= getmaxx() - 26) /// culoare scrollbar orizontal
			{
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
				while(mousey() >= getmaxy() - 55 && mousey() <= getmaxy() - 40 && mousex() >= 26 && mousex() <= getmaxx() - 26 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit()) usleep(100);
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
			setfillstyle(SOLID_FILL, c_bk);
		} /// sfarsit daca nu fac click, doar trec cu cursorul
		if(ismouseclick(WM_LBUTTONDBLCLK)) /// la dublu click
		{
			clearmouseclick(WM_LBUTTONDOWN);
			while(!ismouseclick(WM_LBUTTONUP));
			clearmouseclick(WM_LBUTTONUP);
			clearmouseclick(WM_LBUTTONDBLCLK);
		}
		if(ismouseclick(WM_LBUTTONDOWN)) /// click stanga
		{
			mouse_click_vert = false;
			mouse_click_oriz = false;
			if(kbhit()) {
				char temporar;
				temporar = getch();
				if(temporar == 0 || temporar == 224) temporar = getch();
			}
			if(mousey() >= 76 && mousey() <= getmaxy() - 76 && mousex() >= getmaxx() - 20 && mousex() <= getmaxx() - 5) /// scroll vertical
			{
				mouse_click_vert = true;
				scroll_vert();
				mouse_click_vert = false;
			} else if(mousey() >= getmaxy() - 55 && mousey() <= getmaxy() - 40 && mousex() >= 26 && mousex() <= getmaxx() - 26) /// scroll orizontal
			{
				mouse_click_oriz = true;
				scroll_oriz();
				mouse_click_oriz = false;
			} else if(mousey() >= 10 && mousey() <= 30) {
				if(text_cautat == true) {
					text_cautat = false;
					doar_text();
				}
				x = mousex();
				y = mousey();
				fereastra_deschisa = true;
				if(ismouseclick(WM_LBUTTONDBLCLK)) {
					clearmouseclick(WM_LBUTTONDOWN);
					while(!ismouseclick(WM_LBUTTONUP));
					clearmouseclick(WM_LBUTTONUP);
					clearmouseclick(WM_LBUTTONDBLCLK);
				} else {
					clearmouseclick(WM_LBUTTONDOWN);
					while(!ismouseclick(WM_LBUTTONUP));
					clearmouseclick(WM_LBUTTONUP);
				}
				return;
			} else {
				if(text_cautat == true) {
					text_cautat = false;
					doar_text();
				}
				setcolor(c_bk);
				line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
				setcolor(c_text);
				x = mousex();
				y = mousey();
				int a = -1, b = -1, max_x = 0, cnt = 0;
				/// de aici
				x = max(x - 12, 0);
				if(x < ((x / 12 + 1) * 12 - 6)) x = x / 12 * 12;
				else x = (x / 12 + 1) * 12;
				if(poz_max_x > dim_x) dif_x = poz_max_x - dim_x;
				else dif_x = 0;
				if(poz_max_y > dim_y) dif_y = poz_max_y - dim_y;
				else dif_y = 0;
				if(!text.empty()) {
					if(y + 21 > 65 && y <= max(65 + 21, pozitii[text.size() - 1].second - dif_y)) {
						setcolor(c_bk); //?
						setcolor(c_text);
						x_caret = x;
						y_caret = 65 + (y - 66) / 21 * 21;
						if(x == 0) {
							cnt = -1;
							max_x = 0;
							for(int i = 0; i < text.size(); i++)
								if(text[i] == '\n') {
									if(pozitii[i].second - dif_y == y_caret) {
										pozitie = i + 1, cnt = 1;
										i = text.size();
									}
								} else if(x_caret + 12 == pozitii[i].first - dif_x && y_caret == pozitii[i].second - dif_y) {
								pozitie = i;
								cnt = 1;
								i = text.size();
							} else if(y_caret == pozitii[i].second - dif_y) {
								a = i;
								max_x = pozitii[i].first - dif_x;
							}
							if(cnt == -1) {
								pozitie = a + 1;
								x_caret = max_x;
							}
						} else {
							cnt = -1;
							for(int i = 0; i < text.size(); i++)
								if(pozitii[i].first - dif_x == x_caret && pozitii[i].second - dif_y == y_caret) {
									pozitie = i + 1;
									cnt = 1;
									i = text.size();
								} else if(y_caret == pozitii[i].second - dif_y) {
								a = i;
								max_x = pozitii[i].first - dif_x;
							}
							if(cnt == -1) {
								pozitie = a + 1;
								x_caret = min(x_caret, max_x);
							}
							contor_linie_coloana();
						}
					} else if(y + 21 >= pozitii[text.size() - 1].second - dif_y) {
						y_caret = pozitii[text.size() - 1].second - dif_y;
						if(x <= pozitii[text.size() - 1].first - dif_x)
							for(int i = 0; i < text.size(); i++) {
								if(pozitii[i].second - dif_y == y_caret && pozitii[i].first - dif_x == x) {
									pozitie = i + 1;
									x_caret = x;
									i = text.size();
								}
							}
						else {
							x_caret = min(x, pozitii[text.size() - 1].first - dif_x);
							pozitie = text.size();
						}
					}
				} else {
					x_caret = 0;
					y_caret = 65;
					pozitie = 0;
					contor_linie_coloana();
				}
				x_caret_i = x_caret, y_caret_i = y_caret;
				pozitie_i = pozitie;
				while(!ismouseclick(WM_LBUTTONUP)) {
					usleep(100);
					contor_linie_coloana();
					if(mousey() >= 46 && mousey() < getmaxy() - 55 && mousex() >= 12 && mousex() < getmaxx() - 20) {
						a = -1, b = -1, max_x = 0, cnt = 0;
						x = mousex(), y = mousey();
						x = max(x - 12, 0);
						if(x < ((x / 12 + 1) * 12 - 6)) x = x / 12 * 12;
						else x = (x / 12 + 1) * 12;
						if(x <= 0) {
							if(pozitie >= 0) {
								poz_min_x = max(0, poz_min_x - 12);
								poz_max_x = max(dim_x, poz_max_x - 12);
							}
						} else if(x + 12 >= (getmaxx() - 20) / 12 * 12) {
							if(pozitie < text.size() && pozitii[pozitie].second == pozitii[pozitie - 1].second) {
								poz_min_x = poz_min_x + 12;
								poz_max_x = poz_max_x + 12;
							}
						}
						if(y <= 65) {
							if(poz_min_y - 21 >= 65) {
								poz_min_y = max(0, poz_min_y - 21);
								poz_max_y = max(dim_y, poz_max_y - 21);
							}
						} else if(y >= (getmaxy() - 55) / 21 * 21) {
							if(pozitie < text.size() && poz_max_y + 21 <= dim_max_y) {
								poz_min_y = poz_min_y + 21;
								poz_max_y = poz_max_y + 21;
							}
						}
						if(poz_max_x > dim_x) dif_x = poz_max_x - dim_x;
						else dif_x = 0;
						if(poz_max_y > dim_y) dif_y = poz_max_y - dim_y;
						else dif_y = 0;
						if(!text.empty()) {
							if(y + 21 > 65 && y <= max(65 + 21, pozitii[text.size() - 1].second - dif_y)) {
								setcolor(c_bk); //?
								setcolor(c_text);
								x_caret = x;
								y_caret = 65 + (y - 66) / 21 * 21;
								if(x == 0) {
									cnt = -1;
									max_x = 0;
									for(int i = 0; i < text.size(); i++)
										if(text[i] == '\n') {
											if(pozitii[i].second - dif_y == y_caret) {
												pozitie = i + 1, cnt = 1;
												i = text.size();
											}
										} else if(x_caret + 12 == pozitii[i].first - dif_x && y_caret == pozitii[i].second - dif_y) {
										pozitie = i;
										cnt = 1;
										i = text.size();
									} else if(y_caret == pozitii[i].second - dif_y) {
										a = i;
										max_x = pozitii[i].first - dif_x;
									}
									if(cnt == -1) {
										pozitie = a + 1;
										x_caret = max_x;
									}
								} else {
									cnt = -1;
									for(int i = 0; i < text.size(); i++)
										if(pozitii[i].first - dif_x == x_caret && pozitii[i].second - dif_y == y_caret) {
											pozitie = i + 1;
											cnt = 1;
											i = text.size();
										} else if(y_caret == pozitii[i].second - dif_y) {
										a = i;
										max_x = pozitii[i].first - dif_x;
									}
									if(cnt == -1) {
										pozitie = a + 1;
										x_caret = min(x_caret, max_x);
									}
								}
							} else if(y + 21 >= pozitii[text.size() - 1].second - dif_y) {
								y_caret = pozitii[text.size() - 1].second - dif_y;
								if(x <= pozitii[text.size() - 1].first - dif_x)
									for(int i = 0; i < text.size(); i++) {
										if(pozitii[i].second - dif_y == y_caret && pozitii[i].first - dif_x == x) {
											pozitie = i + 1;
											x_caret = x;
											i = text.size();
										}
									}
								else {
									x_caret = min(x, pozitii[text.size() - 1].first - dif_x);
									pozitie = text.size();
								}
							}
						} else {
							x_caret = 0;
							y_caret = 65;
							pozitie = 0;
							contor_linie_coloana();
						}
						if(x_caret != x_caret_i || y_caret_i != y_caret) {
							if(active_page == 0) active_page = 1;
							else active_page = 0;
							setactivepage(active_page);
							cleardevice();
							drawToolbar();
							sepLine();
							settextstyle(BOLD_FONT, HORIZ_DIR, 2);
							setbkcolor(c_bk);
							setcolor(c_text);
							text_selectat = true;
							if(pozitie_i < pozitie) {
								aux[1] = 0;
								x = 0;
								y = 65;
								for(int i = 0; i < text.size(); i++) {
									if(i == 0 && x_caret_i == 0 && pozitie_i == 1) setbkcolor(c_selectat);
									else if(i >= pozitie_i && i < pozitie) setbkcolor(c_selectat);
									else setbkcolor(c_bk);
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
									if(x >= poz_min_x && x <= poz_max_x && y >= poz_min_y && y <= poz_max_y) outtextxy(x - poz_min_x + 12, y - poz_min_y + 65, aux);
									x = x + 12;
								}
							} else {
								aux[1] = 0;
								x = 0;
								y = 65;
								for(int i = 0; i < text.size(); i++) {
									if(i == 0 && x_caret == 0 && pozitie == 1) setbkcolor(c_selectat);
									else if(i < pozitie_i && i >= pozitie) setbkcolor(c_selectat);
									else setbkcolor(c_bk);
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
									if(x >= poz_min_x && x <= poz_max_x && y >= poz_min_y && y <= poz_max_y) outtextxy(x - poz_min_x + 12, y - poz_min_y + 65, aux);
									x = x + 12;
								}
							}
							scroll_oriz();
							scroll_vert();
							setbkcolor(c_bk);
							setvisualpage(active_page);
							contor_linie_coloana();
						} else if(text_selectat == true) {
							if(active_page == 0) active_page = 1;
							else active_page = 0;
							setactivepage(active_page);
							cleardevice();
							drawToolbar();
							sepLine();
							settextstyle(BOLD_FONT, HORIZ_DIR, 2);
							setbkcolor(c_bk);
							setcolor(c_text);
							text_selectat = false;
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
								if(x >= poz_min_x && x <= poz_max_x && y >= poz_min_y && y <= poz_max_y) outtextxy(x - poz_min_x + 12, y - poz_min_y + 65, aux);
								x = x + 12;
							}
							scroll_oriz();
							scroll_vert();
							setvisualpage(active_page);
							contor_linie_coloana();
						}
					}
				}
				clearmouseclick(WM_LBUTTONDOWN);
				clearmouseclick(WM_LBUTTONUP);
			}
		} /// sfarsit click stanga
		else if(kbhit() && hex_view == false) /// verificare tasta sau combinatii de taste
		{
			c = getch();
			if(text_cautat == true) {
				text_cautat = false;
				doar_text();
			}
			if((c != 1) && (c != 3) && (c != 22) && (c != 24) && (c != 26) && (c != 25) && (c != 6)) {
				if(c == 0 || c == 224) {
					c = getch();
					if(c == 72) // sageata sus
					{
						text_selectat = false;
						if(pozitie - 1 >= 0) {
							y_caret = pozitii[pozitie - 1].second - 21;
							x_caret = pozitii[pozitie - 1].first;
							if(y >= 65) {
								if(text[pozitie - 1] == '\n') {
									if(pozitie - 2 >= 0) {
										if(text[pozitie - 2] == '\n') pozitie--;
										else {
											x_caret = 0;
											int a = 0;
											for(int i = 0; i < pozitie - 1; i++)
												if(pozitii[i].first == x_caret + 12 && pozitii[i].second == y_caret) {
													pozitie = i + 1;
													cnt = 1;
													i = text.size();
												} else if(pozitii[i].second == y_caret) {
												a = i + 1;
												cnt = 2;
											}
											if(cnt == 2);
											pozitie = a;
										}
									} else pozitie = 0;
								} else {
									int a = 0;
									cnt = 0;
									x_caret = pozitii[pozitie - 1].first;
									for(int i = 0; i <= pozitie - 1; i++)
										if(pozitii[i].first == x_caret + 12 && pozitii[i].second == y_caret) {
											pozitie = i + 1;
											cnt = 1;
											i = text.size();
										} else if(pozitii[i].second == y_caret) {
										a = i + 1;
										cnt = 2;
									}
									if(cnt != 1);
									pozitie = a;
								}
							}
						}
						contor_linie_coloana();
					} else if(c == 80) // sageata jos
					{
						text_selectat = false;
						if(pozitie + 1 <= text.size()) {
							if(pozitie - 1 >= 0) {
								y_caret = pozitii[pozitie - 1].second + 21;
								x_caret = pozitii[pozitie - 1].first;
							} else {
								x_caret = 0;
								y_caret = 65 + 21;
							}
							if(y <= pozitii[text.size() - 1].second) {
								if(text[pozitie - 1] == '\n') {
									if(pozitie < text.size()) {
										if(text[pozitie] == '\n' || pozitie == 0) pozitie++;
										else {
											x_caret = 0;
											int a = text.size();
											for(int i = pozitie; i < text.size(); i++)
												if(pozitii[i].first == x_caret + 12 && pozitii[i].second == y_caret) {
													pozitie = i;
													cnt = 1;
													i = text.size();
												} else if(pozitii[i].second == y_caret) {
												a = i + 1;
												cnt = 2;
											}
											if(cnt == 2);
											pozitie = a;
										}
									} else pozitie = text.size();
								} else {
									int a = text.size();
									cnt = 0;
									x_caret = pozitii[pozitie - 1].first;
									if(pozitie == 0) x_caret = 0;
									for(int i = pozitie; i < text.size(); i++)
										if(pozitii[i].first == x_caret + 12 && pozitii[i].second == y_caret) {
											pozitie = i + 1;
											cnt = 1;
											i = text.size();
										} else if(pozitii[i].second == y_caret) {
										a = i + 1;
										cnt = 2;
									}
									if(cnt != 1);
									pozitie = a;
								}
							}
						}
						contor_linie_coloana();
					} else if(c == KEY_DELETE) // tasta delete
					{
						if(redo != NULL) {
							nod * q = new nod;
							q = redo;
							while(q -> ant != NULL) {
								q = q -> ant;
							}
							while(undo1 != NULL) {
								push_stiva(undo, undo1 -> x_caret, undo1 -> y_caret, undo1 -> x_caret_i, undo1 -> y_caret_i, undo1 -> pozitie, undo1 -> pozitie_i, undo1 -> text, undo1 -> pozitii);
								undo1 = undo1 -> ant;
							}
							while(q != NULL) {
								push_stiva(undo, q -> x_caret, q -> y_caret, q -> x_caret_i, q -> y_caret_i, q -> pozitie, q -> pozitie_i, q -> text, q -> pozitii);
								q = q -> urm;
							}
							delete(undo1);
							undo1 = NULL;
							delete(redo);
							redo = NULL;
						}
						push_stiva(undo, x_caret, y_caret, x_caret_i, y_caret_i, pozitie, pozitie_i, text, pozitii);
						if(text_selectat == true) {
							delete_selectat(pozitie_i, pozitie);
							text_selectat = false;
						} else if(pozitie < text.size()) text.erase(pozitie, 1);
					} else if(c == 75) // sageata_stanga
					{
						text_selectat = false;
						pozitie = max(0, pozitie - 1);
					} else if(c == 77) // sageata dreapta
					{
						text_selectat = false;
						pozitie = min((int) text.size(), pozitie + 1);
					}
				} else if(c == 9) // tab
				{
					if(text_cautat == true) {
						text_cautat = false;
						doar_text();
					}
					if(redo != NULL) {
						nod * q = new nod;
						q = redo;
						while(q -> ant != NULL) {
							q = q -> ant;
						}
						while(undo1 != NULL) {
							push_stiva(undo, undo1 -> x_caret, undo1 -> y_caret, undo1 -> x_caret_i, undo1 -> y_caret_i, undo1 -> pozitie, undo1 -> pozitie_i, undo1 -> text, undo1 -> pozitii);
							undo1 = undo1 -> ant;
						}
						while(q != NULL) {
							push_stiva(undo, q -> x_caret, q -> y_caret, q -> x_caret_i, q -> y_caret_i, q -> pozitie, q -> pozitie_i, q -> text, q -> pozitii);
							q = q -> urm;
						}
						delete(undo1);
						undo1 = NULL;
						delete(redo);
						redo = NULL;
					}
					push_stiva(undo, x_caret, y_caret, x_caret_i, y_caret_i, pozitie, pozitie_i, text, pozitii);
					if(text_selectat == true) {
						delete_selectat(pozitie_i, pozitie);
						text_selectat = false;
					}
					int a = 12 * 8;
					for(int i = pozitie; i <= pozitie + 7; i++) {
						text.insert(text.begin() + i, ' ');
					}
					pozitie += 8;
				} else if(c == 8) // backspace
				{
					if(redo != NULL) {
						nod * q = new nod;
						q = redo;
						while(q -> ant != NULL) {
							q = q -> ant;
						}
						while(undo1 != NULL) {
							push_stiva(undo, undo1 -> x_caret, undo1 -> y_caret, undo1 -> x_caret_i, undo1 -> y_caret_i, undo1 -> pozitie, undo1 -> pozitie_i, undo1 -> text, undo1 -> pozitii);
							undo1 = undo1 -> ant;
						}
						while(q != NULL) {
							push_stiva(undo, q -> x_caret, q -> y_caret, q -> x_caret_i, q -> y_caret_i, q -> pozitie, q -> pozitie_i, q -> text, q -> pozitii);
							q = q -> urm;
						}
						delete(undo1);
						undo1 = NULL;
						delete(redo);
						redo = NULL;
					}
					push_stiva(undo, x_caret, y_caret, x_caret_i, y_caret_i, pozitie, pozitie_i, text, pozitii);
					if(text_selectat == true) {
						delete_selectat(pozitie_i, pozitie);
						text_selectat = false;
					} else {
						pozitie = pozitie - 1;
						if(pozitie >= 0) text.erase(pozitie, 1);
						else pozitie = 0;
					}
				} else if(c == 13) // enter
				{
					if(redo != NULL) {
						nod * q = new nod;
						q = redo;
						while(q -> ant != NULL) {
							q = q -> ant;
						}
						while(undo1 != NULL) {
							push_stiva(undo, undo1 -> x_caret, undo1 -> y_caret, undo1 -> x_caret_i, undo1 -> y_caret_i, undo1 -> pozitie, undo1 -> pozitie_i, undo1 -> text, undo1 -> pozitii);
							undo1 = undo1 -> ant;
						}
						while(q != NULL) {
							push_stiva(undo, q -> x_caret, q -> y_caret, q -> x_caret_i, q -> y_caret_i, q -> pozitie, q -> pozitie_i, q -> text, q -> pozitii);
							q = q -> urm;
						}
						delete(undo1);
						undo1 = NULL;
						delete(redo);
						redo = NULL;
					}
					push_stiva(undo, x_caret, y_caret, x_caret_i, y_caret_i, pozitie, pozitie_i, text, pozitii);
					if(text_selectat == true) {
						delete_selectat(pozitie_i, pozitie);
						text_selectat = false;
					}
					text.insert(text.begin() + pozitie, '\n');
					pozitie++;
				} else if(c == 27) // esc
				{
					inchidere_fereastra = true;
					closegraph();
					return;
				} else if((c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == ' ' || strchr(caractere, c)) && c != 0) {
					if(redo != NULL) {
						nod * q = new nod;
						q = redo;
						while(q -> ant != NULL) {
							q = q -> ant;
						}
						while(undo1 != NULL) {
							push_stiva(undo, undo1 -> x_caret, undo1 -> y_caret, undo1 -> x_caret_i, undo1 -> y_caret_i, undo1 -> pozitie, undo1 -> pozitie_i, undo1 -> text, undo1 -> pozitii);
							undo1 = undo1 -> ant;
						}
						while(q != NULL) {
							push_stiva(undo, q -> x_caret, q -> y_caret, q -> x_caret_i, q -> y_caret_i, q -> pozitie, q -> pozitie_i, q -> text, q -> pozitii);
							q = q -> urm;
						}
						delete(undo1);
						undo1 = NULL;
						delete(redo);
						redo = NULL;
					}
					push_stiva(undo, x_caret, y_caret, x_caret_i, y_caret_i, pozitie, pozitie_i, text, pozitii);
					if(text_selectat == true) {
						delete_selectat(pozitie_i, pozitie);
						text_selectat = false;
					}
					text.insert(text.begin() + pozitie, c);
					text_aux = text;
					pozitie++;
				}
				setbkcolor(c_bk);
				setcolor(c_text);
				if(active_page == 0) active_page = 1;
				else active_page = 0;
				setactivepage(active_page);
				cleardevice();
				drawToolbar();
				sepLine();
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				setbkcolor(c_bk);
				setcolor(c_text);
				dim_max_x = 0;
				dim_max_y = 65;
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
				x = 0;
				y = 65;
				if(pozitie != 0) {
					if(pozitii[pozitie - 1].first > poz_max_x + 12)
						while(pozitii[pozitie - 1].first > poz_max_x + 12) {
							poz_min_x += 12;
							poz_max_x += 12;
						}
					else if(pozitii[pozitie - 1].first < poz_min_x)
						while(pozitii[pozitie - 1].first < poz_min_x) {
							poz_min_x -= 12;
							poz_max_x -= 12;
						}
					if(pozitii[pozitie - 1].second > poz_max_y)
						while(pozitii[pozitie - 1].second > poz_max_y) {
							poz_min_y += 21;
							poz_max_y += 21;
						}
					else if(pozitii[pozitie - 1].second < poz_min_y)
						while(pozitii[pozitie - 1].second < poz_min_y) {
							poz_min_y -= 21;
							poz_max_y -= 21;
						}
				} else {
					poz_min_x = 0;
					poz_max_x = dim_x;
					poz_min_y = 65;
					poz_max_y = dim_y;
				}
				settextstyle(BOLD_FONT, HORIZ_DIR, 2);
				setbkcolor(c_bk);
				setcolor(c_text);
				x = 0;
				y = 65;
				for(int i = 0; i < text.size(); i++) {
					if(x + 36 == (getmaxx() - 20) / 36 * 36 && wrap_mode == true) {
						x = 0;
						y += 21;
					}
					if(text[i] == 10 || text[i] == '$') {
						y = y + 21;
						x = 0;
					} else {
						aux[0] = text[i];
						if(x >= poz_min_x && x <= poz_max_x && y >= poz_min_y && y <= poz_max_y) outtextxy(x - poz_min_x + 12, y - poz_min_y + 65, aux);
						x = x + 12;
					}
				}
				if(pozitie != 0) {
					x_caret = pozitii[pozitie - 1].first - poz_min_x;
					y_caret = pozitii[pozitie - 1].second - poz_min_y + 65;
				} else {
					x_caret = 0;
					y_caret = 65;
				}
				scroll_oriz();
				scroll_vert();
				contor_linie_coloana();
				setvisualpage(active_page);
				setcolor(c_text);
				line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
			} else {
				if(c == 1) // ctrl+a
				{
					select_all();
				} else if(c == 3 && text_selectat == true) // ctrl+c
				{
					ctrl_c_x('C', control_c, pozitie_i, pozitie);
				} else if(c == 24 && text_selectat == true) // ctrl+x
				{
					decupati();
				} else if(c == 25) // redo
				{
					refaceti();
				} else if(c == 26) // undo
				{
					anulati();
				} else if(c == 22) // ctrl+v
				{
					lipire();
				} else if(c == 6) // ctrl+f
				{
					cautare_text();
				}
			}
		} else if(kbhit() && hex_view == true) {
			char ll;
			ll = getch();
		}
	}
}
