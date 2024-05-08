#pragma once
#include "tetris.h"

#include "butoane.h"

#include "functii_grafice.h"

#include "keyboard_mouse_input.h"

int main() {

    bool exit = false;
    draw_pagina_start();

    while(exit == false) {
        while(true) {

            if(kbhit()) {
                char amn;
                amn = getch();
                if(amn == 0 || amn == 224)
                    amn = getch();
            }

            if(ismouseclick(WM_LBUTTONUP)) /// am apasat click-ul
            {
                if(mousex() >= 0 && mousex() <= getmaxx() && mousey() >= 10 && mousey() <= 80) /// am apsat pe TEXT EDITOR(se deschide jocul tetris)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONUP);
                    closegraph();
                    mini_game();
                }
                else if(mousex() > 30 && mousex() < getmaxx() / 2) /// Ne aflam in meniul cu optiuni
                {
                    if(mousey() >= 120 && mousey() <= 160) /// NEW FILE
                    {
                        closegraph();
                        initializare_fereastra(720, getmaxheight() / 2);
                        break;
                    }
                    else if(mousey() >= 200 && mousey() <= 240) /// OPEN FILE
                    {
                        closegraph();
                        initializare_fereastra(720, getmaxheight() / 2);
                        open_file();
                        contor_linie_coloana();
                        doar_text();
                        break;
                    }
                    else if(mousey() >= 280 && mousey() <= 320) /// EXIT
                    {
                        closegraph();
                        exit = true;
                        break;
                    }
                    else /// Niciuna dintre optiunile de mai sus
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        clearmouseclick(WM_LBUTTONUP);
                    }
                }
                else /// nu ne aflam in meniul cu optiuni
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(WM_LBUTTONUP);
                }
            }

            if(!ismouseclick(WM_LBUTTONDOWN)) /// daca mergem cu cursorul, trebuie sa coloram optiunile
            {
                if(mousex() > 30 && mousex() < getmaxx() / 2 && mousey() >= 120 && mousey() <= 160) /// NEW FILE
                    buton_meniu(0, 80, 125, const_cast < char * > ("New file"), 30, 120, 160);

                if(mousex() > 30 && mousex() < getmaxx() / 2 && mousey() >= 200 && mousey() <= 240) /// OPEN FILE
                    buton_meniu(1, 80, 205, const_cast < char * > ("Open file"), 30, 200, 240);

                if(mousex() > 30 && mousex() < getmaxx() / 2 && mousey() >= 280 && mousey() <= 320) /// EXIT
                    buton_meniu(2, 80, 285, const_cast < char * > ("Exit"), 30, 280, 320);

                if(mousex() >= getmaxx() / 2 + getmaxx() / 3 - 5 && mousex() <= 687 && mousey() >= 165 && mousey() <= 235) /// Arseni Costel-Ionut
                    buton_3_cuvinte(const_cast < char * > ("Arseni"), const_cast < char * > ("Costel"), const_cast < char * > ("Ionut"), 170, 190, 210);

                if(mousex() >= getmaxx() / 2 + getmaxx() / 3 - 5 && mousex() <= 687 && mousey() >= 245 && mousey() <= 315)
                    buton_3_cuvinte(const_cast < char * > ("My"), const_cast < char * > ("Faculty"), const_cast < char * > ("Project"), 250, 270, 290); /// My Faculty Project

                if(mousex() >= 0 && mousex() <= getmaxx() && mousey() >= 10 && mousey() <= 80) /// TEXT EDITOR
                {
                    setcolor(LIGHTGREEN);
                    line(0, 80, 146, 80);
                    line(578, 80, getmaxx(), 80);
                    settextstyle(BOLD_FONT, HORIZ_DIR, 7);
                    rectangle(0, getmaxy() - 10, getmaxx(), getmaxy());
                    rectangle(0, 0, getmaxx(), 10);
                    outtextxy((getmaxx() - textwidth("TEXT EDITOR")) / 2, 20, "TEXT EDITOR");
                    setfillstyle(SOLID_FILL, 5);
                    bar(0, getmaxy() - 10, getmaxx(), getmaxy());
                    bar(0, 0, getmaxx(), 10);

                    while(mousex() >= 0 && mousex() <= getmaxx() && mousey() >= 10 && mousey() <= 80 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit())
                        usleep(100);

                    setfillstyle(SOLID_FILL, MAGENTA);
                    bar(0, getmaxy() - 10, getmaxx(), getmaxy());
                    rectangle(0, getmaxy() - 10, getmaxx(), getmaxy());
                    bar(0, 0, getmaxx(), 10);
                    rectangle(0, 0, getmaxx(), 10);
                    setcolor(5);
                    line(0, 80, 146, 80);
                    line(578, 80, getmaxx(), 80);
                    settextstyle(BOLD_FONT, HORIZ_DIR, 7);
                    outtextxy((getmaxx() - textwidth("TEXT EDITOR")) / 2, 20, "TEXT EDITOR");
                }
                setfillstyle(SOLID_FILL, WHITE);

                if(mousex() >= getmaxx() / 2 + 25 && mousex() <= getmaxx() - 145 && mousey() >= 165 && mousey() <= 235) /// Project number
                    buton_2_cuvinte(const_cast < char * > ("Project number:"), const_cast < char * > ("34"), getmaxx() / 2 + 33, 165, getmaxx() / 2 + 90, 235);

                if(mousex() >= getmaxx() / 2 + 25 && mousex() <= getmaxx() - 145 && mousey() >= 245 && mousey() <= 315) /// Team letter
                    buton_2_cuvinte(const_cast < char * > ("Team letter:"), const_cast < char * > ("B"), getmaxx() / 2 + 50, 245, getmaxx() / 2 + 110, 315);

                if(mousex() >= getmaxx() / 2 + 20 && mousex() <= getmaxx() - 20 && mousey() >= 120 && mousey() <= 170) /// Project informations
                {
                    setcolor(CYAN);
                    rectangle(getmaxx() / 2 + 20, 120, getmaxx() - 13, 320);
                    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
                    outtextxy(getmaxx() / 2 + 30, 130, "Project informations:");
                    line(getmaxx() / 2 + 20, 155, getmaxx() - 13, 155);
                    line(getmaxx() - 140, 155, getmaxx() - 140, 320);

                    while(mousex() >= getmaxx() / 2 + 20 && mousex() <= getmaxx() - 20 && mousey() >= 120 && mousey() <= 170 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit())
                        usleep(100);

                    setcolor(5);
                    rectangle(getmaxx() / 2 + 20, 120, getmaxx() - 13, 320);
                    line(getmaxx() / 2 + 20, 155, getmaxx() - 20, 155);
                    line(getmaxx() - 140, 155, getmaxx() - 140, 320);
                    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
                    outtextxy(getmaxx() / 2 + 30, 130, "Project informations:");
                }
            }
        }

        if(exit == false) /// daca nu am iesit
        {
            while(inchidere_fereastra == false) {

                if(fereastra_deschisa == false) /// scriu in partea de sub meniu
                    scriere_text();
                else if((y < 10) || (y > 30) || (x < 10 || x > 710) || (x > 110 && x < 120) || (x > 230 && x < 240) || (x > 350 && x < 360) || (x > 470 && x < 480) || (x > 590 && x < 600)) /// daca ies din zona de scriere
                {
                    int j = true;
                    fereastra_deschisa = false;
                }
                else if(x >= 10 && x <= 110 && fereastra_fisier == false) /// daca apas FILE in timp ce ruleaza zona de scriere
                {
                    displayFileMenu();
                    fereastra_fisier = true;

                    while(fereastra_fisier) /// FISIER+FISIER_MENU
                    {
                        ver_tasta_si_click();

                        if(ismouseclick(WM_LBUTTONDOWN)) /// click stanga
                        {
                            x = mousex(), y = mousey();

                            if(x >= 10 && x <= 110) /// FISIER_MENU
                            {

                                if(y >= 30 && y <= 70) /// FILA NOUA
                                    new_file();
                                else if(y >= 70 && y <= 90) /// DESCHIDETI FILA EXISTENTA
                                {
                                    open_file();
                                    fereastra_fisier = false;
                                    fereastra_deschisa = false;
                                    contor_linie_coloana();
                                    doar_text();
                                }
                                else if(y >= 90 && y <= 110) /// SALVATI CA
                                    salvare_fisier();
                                else if(y >= 110 && y <= 140) /// IESIRE
                                {
                                    fereastra_fisier = false;
                                    fereastra_deschisa = false;
                                    inchidere_fereastra = true;
                                    clearmouseclick(WM_LBUTTONDOWN);

                                    while(ismouseclick(WM_LBUTTONUP));

                                    clearmouseclick(WM_LBUTTONUP);
                                    closegraph();
                                    draw_pagina_start();
                                }
                                else /// revenim in zona de scriere
                                {
                                    contor_linie_coloana();
                                    fereastra_fisier = false;
                                    fereastra_deschisa = false;
                                    doar_text();
                                }
                            }
                            else {
                                int lx = x, ly = y;
                                contor_linie_coloana();
                                fereastra_fisier = false;
                                doar_text();
                                x = lx;
                                y = ly;
                            }
                        }
                        else /// daca doar trec cu cursorul
                        {
                            if(mousex() >= 10 && mousex() <= 110 && mousey() >= 10 && mousey() <= 130) /// FILE+FILE_MENU
                            {
                                if(mousey() >= 10 && mousey() <= 30 && !ismouseclick(WM_LBUTTONDOWN)) /// FILE
                                    buton(LIGHTRED, 5, 5, c_bk, 38, 12, const_cast < char * > ("File"), 10, 10, 110, 30);

                                if(mousey() >= 50 && mousey() <= 70 && !ismouseclick(WM_LBUTTONDOWN)) /// NEW
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 20, 50, const_cast < char * > ("New"), 11, 50, 109, 70);

                                if(mousey() > 70 && mousey() <= 90 && !ismouseclick(WM_LBUTTONDOWN)) /// OPEN
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 20, 70, const_cast < char * > ("Open"), 11, 70, 109, 90);

                                if(mousey() > 90 && mousey() <= 110 && !ismouseclick(WM_LBUTTONDOWN)) /// SAVE
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 20, 90, const_cast < char * > ("Save"), 11, 90, 109, 110);

                                if(mousey() > 110 && mousey() <= 130 && !ismouseclick(WM_LBUTTONDOWN)) /// EXIT
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 20, 110, const_cast < char * > ("Exit"), 11, 110, 109, 130);
                            }

                            if(mousey() >= 10 && mousey() <= 30)
                                ferestre(0);
                        }
                    }
                    ver_tasta_si_click();

                    if((y < 110 || y > 140)) {
                        clearmouseclick(WM_LBUTTONDOWN);

                        while(!ismouseclick(WM_LBUTTONUP));

                        clearmouseclick(WM_LBUTTONUP);
                    }
                }
                else if(x >= 120 && x <= 230 && fereastra_editati == false) /// daca apas EDIT in timp ce ruleaza zona de scriere
                {
                    displayEditatiMenu();
                    fereastra_editati = true;
                    bool cct = false;

                    while(fereastra_editati) /// EDIT+EDIT_MENU
                    {
                        ver_tasta_si_click();

                        if(ismouseclick(WM_LBUTTONDOWN)) /// click stanga
                        {
                            x = mousex(), y = mousey();

                            if(x >= 120 && x <= 230) /// EDIT_MENU
                            {
                                if(y >= 30 && y <= 70 && hex_view == false) /// UNDO
                                {
                                    anulati();
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                }
                                else if(y >= 70 && y <= 90 && hex_view == false) /// REDO
                                {
                                    refaceti();
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                }
                                else if(y >= 90 && y <= 110 && text_selectat == true) /// COPIATI
                                {
                                    ctrl_c_x('C', control_c, pozitie_i, pozitie);

                                    if(active_page == 0)
                                        active_page = 1;
                                    else
                                        active_page = 0;

                                    setactivepage(active_page);
                                    cleardevice();
                                    drawToolbar();
                                    sepLine();
                                    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
                                    setbkcolor(c_bk);
                                    setcolor(c_text);
                                    contor_linie_coloana();
                                    scroll_oriz();
                                    scroll_vert();
                                    doar_text();
                                    setvisualpage(active_page);
                                    setcolor(c_text);
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                }
                                else if(y >= 110 && y <= 130 && hex_view == false) /// LIPITI
                                {
                                    lipire();
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                }
                                else if(y >= 130 && y <= 150 && text_selectat == true && hex_view == false) /// decupati(ctrl+x)
                                {
                                    decupati();
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                    text_selectat = false;
                                }
                                else if(y >= 150 && y <= 170 && hex_view == false) /// REPLACE
                                {
                                    clearmouseclick(WM_LBUTTONDOWN);
                                    inlocuire(cct);
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                }
                                else if(y >= 170 && y <= 190) /// FIND
                                {
                                    clearmouseclick(WM_LBUTTONDOWN);

                                    while(!ismouseclick(WM_LBUTTONUP));

                                    clearmouseclick(WM_LBUTTONUP);
                                    cct = true;
                                    cautare_text();
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                }
                                else if(y >= 190 && y <= 210) /// SELECT
                                {
                                    clearmouseclick(WM_LBUTTONDOWN);
                                    selectare_pozitii(cct);
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                }
                                else if(y >= 210 && y <= 230) {
                                    text_selectat = false;
                                    hex_view = true;
                                    c_text = GREEN;
                                    text = text_aux;
                                    binar();
                                    pozitie = text.size();
                                    text = text_binar;
                                    wrap_mode = true;
                                    poz_max_x = ((getmaxx() - 20) / 36 * 36 - 36);
                                    dim_x = poz_max_x;
                                    poz_min_x = 0;
                                    doar_text();
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                }
                                else if(y >= 230 && y <= 260) {
                                    c_text = c_text_aux;
                                    hex_view = false;
                                    text_selectat = false;
                                    text = text_aux;
                                    wrap_mode = false;

                                    if(wrap_wrap == true)
                                        wrap_mode = true;

                                    doar_text();
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                    pozitie = text.size();
                                    doar_text();
                                }
                                else {
                                    contor_linie_coloana();
                                    fereastra_editati = false;
                                    fereastra_deschisa = false;
                                    doar_text();
                                }
                            }
                            else {
                                int lx = x, ly = y;
                                contor_linie_coloana();
                                fereastra_editati = false;
                                doar_text();
                                x = lx;
                                y = ly;
                            }
                        }
                        else /// doar trec cu cursorul
                        {
                            if(mousex() >= 120 && mousex() <= 230 && mousey() >= 10 && mousey() <= 250) /// EDIT
                            {
                                if(mousey() >= 10 && mousey() <= 30 && !ismouseclick(WM_LBUTTONDOWN)) /// EDIT
                                    buton(LIGHTRED, 5, 5, c_bk, 151, 12, const_cast < char * > ("Edit"), 120, 10, 230, 30);

                                if(mousey() >= 50 && mousey() <= 70 && !ismouseclick(WM_LBUTTONDOWN)) /// UNDO
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 130, 50, const_cast < char * > ("Undo"), 121, 50, 229, 70);

                                if(mousey() > 70 && mousey() <= 90 && !ismouseclick(WM_LBUTTONDOWN)) /// REDO
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 130, 70, const_cast < char * > ("Redo"), 121, 70, 229, 90);

                                if(mousey() > 90 && mousey() <= 110 && !ismouseclick(WM_LBUTTONDOWN)) /// COPY
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 130, 90, const_cast < char * > ("Copy"), 121, 90, 229, 110);

                                if(mousey() > 110 && mousey() <= 130 && !ismouseclick(WM_LBUTTONDOWN)) /// PASTE
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 130, 110, const_cast < char * > ("Paste"), 121, 110, 229, 130);

                                if(mousey() > 130 && mousey() <= 150 && !ismouseclick(WM_LBUTTONDOWN)) /// CUT
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 130, 130, const_cast < char * > ("Cut"), 121, 130, 229, 150);

                                if(mousey() > 150 && mousey() <= 170 && !ismouseclick(WM_LBUTTONDOWN)) /// REPLACE
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 130, 150, const_cast < char * > ("Replace"), 121, 150, 229, 170);

                                if(mousey() > 170 && mousey() <= 190 && !ismouseclick(WM_LBUTTONDOWN)) /// FIND
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 130, 170, const_cast < char * > ("Find"), 121, 170, 229, 190);

                                if(mousey() > 190 && mousey() <= 210 && !ismouseclick(WM_LBUTTONDOWN)) /// SELECT
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 130, 190, const_cast < char * > ("Select"), 121, 190, 229, 210);

                                if(mousey() >= 210 && mousey() <= 230 && !ismouseclick(WM_LBUTTONDOWN)) /// EDIT
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 130, 210, const_cast < char * > ("Hex view"), 121, 210, 229, 230);

                                if(mousey() >= 230 && mousey() <= 250 && !ismouseclick(WM_LBUTTONDOWN)) /// EDIT
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 130, 230, const_cast < char * > ("Normal"), 121, 230, 229, 250);
                            }
                        }

                        if(mousey() >= 10 && mousey() <= 30) /// sunt inca in Toolbar
                            ferestre(1);
                    }

                    if(ismouseclick(WM_LBUTTONDBLCLK) && cct == false) {
                        clearmouseclick(WM_LBUTTONDOWN);

                        while(!ismouseclick(WM_LBUTTONUP));

                        clearmouseclick(WM_LBUTTONUP);
                        clearmouseclick(WM_LBUTTONDBLCLK);
                    }
                    else if(cct == false) {
                        clearmouseclick(WM_LBUTTONDOWN);

                        while(!ismouseclick(WM_LBUTTONUP));

                        clearmouseclick(WM_LBUTTONUP);
                    }
                }
                else if(x >= 240 && x <= 350 && fereastra_tema == false) /// daca apas THEME in timp ce ruleaza zona de scriere
                {
                    displayTemaMenu();
                    fereastra_tema = true;

                    while(fereastra_tema) {
                        if(kbhit()) {
                            char temporar;
                            temporar = getch();

                            if(temporar == 0 || temporar == 224)
                                temporar = getch();
                        }

                        ver_tasta_si_click();

                        if(ismouseclick(WM_LBUTTONDOWN)) {
                            x = mousex(), y = mousey();

                            if(x >= 240 && x <= 350) {

                                if(y >= 30 && y <= 70) // dark
                                    tema(BLACK, WHITE, 8);
                                else if(y >= 70 && y <= 100) // light
                                    tema(WHITE, BLACK, LIGHTBLUE);
                                else {
                                    fereastra_tema = false;
                                    fereastra_deschisa = false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                            }
                            else {
                                int lx = x, ly = y;
                                contor_linie_coloana();
                                fereastra_tema = false;
                                doar_text();
                                x = lx;
                                y = ly;
                            }
                        }
                        else {
                            if(mousex() >= 240 && mousex() <= 350 && mousey() >= 10 && mousey() <= 90) {

                                if(mousey() >= 10 && mousey() <= 30 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(LIGHTRED, 5, 5, c_bk, 265, 12, const_cast < char * > ("Theme"), 240, 10, 350, 30);

                                if(mousey() >= 50 && mousey() <= 70 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 250, 50, const_cast < char * > ("Dark"), 241, 50, 349, 70);

                                if(mousey() > 70 && mousey() <= 90 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 250, 70, const_cast < char * > ("Light"), 241, 70, 349, 90);
                            }
                            if(mousey() >= 10 && mousey() <= 30)
                                ferestre(2);
                        }
                    }
                }
                else if(x >= 360 && x <= 470 && fereastra_culoare == false) /// daca apas COLOR in timp ce ruleaza zona de scriere
                {
                    displayCuloareMenu();
                    fereastra_culoare = true;

                    while(fereastra_culoare) {
                        if(kbhit()) {
                            char temporar;
                            temporar = getch();

                            if(temporar == 0 || temporar == 224)
                                temporar = getch();
                        }

                        ver_tasta_si_click();

                        if(ismouseclick(WM_LBUTTONDOWN)) {
                            x = mousex(), y = mousey();

                            if(x >= 360 && x <= 470) {

                                if(y >= 30 && y <= 70 && hex_view == false) // rosu
                                {
                                    c_text = RED;
                                    c_selectat = 13;
                                    fereastra_culoare = false;
                                    fereastra_deschisa = false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                                else if(y >= 70 && y <= 90 & hex_view == false) // cyan
                                {
                                    c_text = CYAN;
                                    c_selectat = 10;
                                    fereastra_culoare = false;
                                    fereastra_deschisa = false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                                else if(y >= 90 && y <= 120 & hex_view == false) // maro
                                {
                                    c_text = BROWN;
                                    c_selectat = 1;
                                    fereastra_culoare = false;
                                    fereastra_deschisa = false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                                else {
                                    fereastra_culoare = false;
                                    fereastra_deschisa = false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                            }
                            else {
                                int lx = x, ly = y;
                                contor_linie_coloana();
                                fereastra_culoare = false;
                                doar_text();
                                x = lx;
                                y = ly;
                            }
                        }
                        else {
                            if(mousex() >= 360 && mousex() <= 470 && mousey() >= 10 && mousey() <= 110) {

                                if(mousey() >= 10 && mousey() <= 30 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(LIGHTRED, 5, 5, c_bk, 385, 12, const_cast < char * > ("Color"), 360, 10, 470, 30);

                                if(mousey() >= 50 && mousey() <= 70 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 370, 50, const_cast < char * > ("Red"), 361, 50, 469, 70);

                                if(mousex() >= 360 && mousex() <= 470 && mousey() > 70 && mousey() <= 90 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 370, 70, const_cast < char * > ("Cyan"), 361, 70, 469, 90);

                                if(mousex() >= 360 && mousex() <= 470 && mousey() >= 90 && mousey() <= 110 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 370, 90, const_cast < char * > ("Brown"), 361, 90, 469, 110);
                            }

                            if(mousey() >= 10 && mousey() <= 30)
                                ferestre(3);
                        }
                    }
                    ver_tasta_si_click();
                    clearmouseclick(WM_LBUTTONDOWN);

                    while(!ismouseclick(WM_LBUTTONUP));

                    clearmouseclick(WM_LBUTTONUP);
                }
                else if(x >= 480 && x <= 590 && fereastra_dimensiune == false) /// daca apas DIMENSIUNE in timp ce ruleaza zona de scriere
                {
                    displayDimensiuneMenu();
                    fereastra_dimensiune = true;

                    while(fereastra_dimensiune) {
                        ver_tasta_si_click();

                        if(ismouseclick(WM_LBUTTONDOWN)) {
                            x = mousex(), y = mousey();

                            if(x >= 480 && x <= 590) {

                                if(y >= 30 && y <= 70) // full
                                    resize_window(getmaxwidth(), getmaxheight());
                                else if(y >= 70 && y <= 90) // medium
                                    resize_window(getmaxwidth() / 4 * 3, getmaxheight() / 4 * 3 + 5);
                                else if(y >= 90 && y <= 120) // minim
                                    resize_window(720, getmaxheight() / 2);
                                else {
                                    clearmouseclick(WM_LBUTTONDOWN);

                                    while(!ismouseclick(WM_LBUTTONUP));

                                    clearmouseclick(WM_LBUTTONUP);
                                    fereastra_dimensiune = false;
                                    fereastra_deschisa = false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                            }
                            else {
                                clearmouseclick(WM_LBUTTONDOWN);

                                while(!ismouseclick(WM_LBUTTONUP));

                                clearmouseclick(WM_LBUTTONUP);
                                int lx = x, ly = y;
                                contor_linie_coloana();
                                fereastra_dimensiune = false;
                                doar_text();
                                x = lx;
                                y = ly;
                            }
                        }
                        else {
                            if(mousex() >= 480 && mousex() <= 590 && mousey() >= 10 && mousey() <= 110) {

                                if(mousey() >= 10 && mousey() <= 30 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(LIGHTRED, 5, 5, c_bk, 499, 12, const_cast < char * > ("Window"), 480, 10, 590, 30);

                                if(mousey() >= 50 && mousey() <= 70 && !ismouseclick(WM_LBUTTONDOWN) && !kbhit())
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 490, 50, const_cast < char * > ("Maximum"), 481, 50, 589, 70);

                                if(mousey() > 70 && mousey() <= 90 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 490, 70, const_cast < char * > ("Middle"), 481, 70, 589, 90);

                                if(mousey() >= 90 && mousey() <= 110 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 490, 90, const_cast < char * > ("Minimum"), 481, 90, 589, 110);
                            }

                            if(mousey() >= 10 && mousey() <= 30)
                                ferestre(4);
                        }
                    }
                }
                else if(x >= 600 && x <= 710 && fereastra_wrap == false) /// daca apas WRAP in timp ce ruleaza zona de scriere
                {
                    displayWrapMenu();
                    fereastra_wrap = true;

                    while(fereastra_wrap) {
                        ver_tasta_si_click();

                        if(ismouseclick(WM_LBUTTONDOWN)) {
                            x = mousex(), y = mousey();

                            if(x >= 600 && x <= 710) {

                                if(y >= 30 && y <= 70) // on
                                {
                                    wrap_mode = true;
                                    wrap_wrap = true;
                                    poz_max_x = ((getmaxx() - 20) / 36 * 36 - 36);
                                    dim_x = poz_max_x;
                                    poz_min_x = 0;
                                    fereastra_wrap = false;
                                    fereastra_deschisa = false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                                else if(y >= 70 && y <= 100) // off
                                {
                                    wrap_mode = false;
                                    wrap_wrap = false;
                                    fereastra_wrap = false;

                                    if(hex_view == true) {
                                        poz_max_x = ((getmaxx() - 20) / 36 * 36 - 36);
                                        dim_x = poz_max_x;
                                        poz_min_x = 0;
                                        wrap_mode = true;
                                    }

                                    fereastra_deschisa = false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                                else {
                                    fereastra_wrap = false;
                                    fereastra_deschisa = false;
                                    doar_text();
                                    contor_linie_coloana();
                                }
                            }
                            else {
                                int lx = x, ly = y;
                                contor_linie_coloana();
                                fereastra_wrap = false;
                                doar_text();
                                x = lx;
                                y = ly;
                            }
                        }
                        else {
                            if(mousex() >= 600 && mousex() <= 710 && mousey() >= 10 && mousey() <= 110) {

                                if(mousey() >= 10 && mousey() <= 30 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(LIGHTRED, 5, 5, c_bk, 631, 12, const_cast < char * > ("Wrap"), 600, 10, 710, 30);

                                if(mousey() >= 50 && mousey() <= 70 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 610, 50, const_cast < char * > ("On"), 601, 50, 709, 70);

                                if(mousey() > 70 && mousey() <= 90 && !ismouseclick(WM_LBUTTONDOWN))
                                    buton(BLACK, LIGHTGRAY, 5, LIGHTGRAY, 610, 70, const_cast < char * > ("Off"), 601, 70, 709, 90);
                            }

                            if(mousey() >= 10 && mousey() <= 30)
                                ferestre(5);
                        }
                    }
                    ver_tasta_si_click(); {
                        clearmouseclick(WM_LBUTTONDOWN);

                        while(!ismouseclick(WM_LBUTTONUP));

                        clearmouseclick(WM_LBUTTONUP);
                    }
                }
                else /// altfel
                {
                    fereastra_fisier = false;
                    fereastra_deschisa = false;
                    fereastra_editati = false;
                    fereastra_tema = false;
                    fereastra_culoare = false;
                    fereastra_dimensiune = false;
                    fereastra_wrap = false;
                    contor_linie_coloana();
                    doar_text();
                }
            }
        }
        inchidere_fereastra = false;;
    }
}
