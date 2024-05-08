#pragma once
#include "functii_grafice.h"

#include "scroll_bar.h"

#include "variabile_globale.h"

void echilibrare_caret();
void echilibrare_pozitii();
void doar_text();
void drawToolbar();
void initializare_fereastra(int dim_xx, int dim_yy);
void open_file() {
    text.erase(text.begin(), text.end());
    pozitii.erase(pozitii.begin(), pozitii.end());
    echilibrare_pozitii();
    echilibrare_caret();
    char szFile[260];
    delete(undo);
    delete(redo);
    undo = NULL;
    redo = NULL;
    OPENFILENAME ofn;
    ZeroMemory( & ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Fisiere text\0*.txt\0Toate fisierele\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    ofn.lpstrDefExt = "txt"; // extensia implicită
    if(GetOpenFileName( & ofn) == TRUE) {
        text.erase(text.begin(), text.end());
        ifstream fin(szFile);
        if(fin.is_open()) {
            char p[10000];
            while(fin.getline(p, sizeof(p))) {
                for(int i = 0; i < strlen(p); i++) {
                    text.push_back(p[i]);
                }
                text.push_back('\n');
            }
            fin.close();
        }
        x = 0;
        y = 65;
        if(active_page == 0) active_page = 1;
        else active_page = 0;
        setactivepage(active_page);
        cleardevice();
        drawToolbar();
        scroll_oriz();
        scroll_vert();
        sepLine();
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        setbkcolor(c_bk);
        setcolor(c_text);
        pozitie = pozitie_i = 0;
        pozitii.erase(pozitii.begin(), pozitii.end());
        for(int i = 0; i < text.size(); i++) {
            pozitii.push_back({
                x,
                y
            });
            dim_max_x = max(dim_max_x, x);
            dim_max_y = max(dim_max_y, y);
            if(text[i] == 10) {
                y = y + 21;
                x = 0;
            }
            else {
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
        }
        else {
            poz_min_x = 0;
            poz_max_x = dim_x;
            poz_min_y = 65;
            poz_max_y = dim_y;
        }
        setvisualpage(active_page);
        setcolor(c_text);
        line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
    }
}
void new_file() {
    delete(undo);
    delete(redo);
    dim_max_x = 0;
    dim_max_y = 0;
    poz_min_x = 0;
    poz_min_y = 65;
    poz_max_x = dim_x;
    poz_max_y = dim_y;
    x_caret = 0;
    y_caret = 65;
    pozitie = 0;
    undo = NULL;
    redo = NULL;
    fereastra_fisier = false;
    fereastra_deschisa = false;
    cleardevice();
    drawToolbar();
    sepLine();
    scroll_oriz();
    scroll_vert();
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setbkcolor(c_bk);
    setcolor(c_text);
    text.erase(text.begin(), text.end());
    pozitii.erase(pozitii.begin(), pozitii.end());
    echilibrare_pozitii();
    echilibrare_caret();
    contor_linie_coloana();
}
void salvare_fisier() {
    delete(undo);
    delete(redo);
    undo = NULL;
    redo = NULL;
    char szFile[260];
    OPENFILENAME ofn;
    ZeroMemory( & ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Fisiere text\0*.txt\0Toate fisierele\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "txt"; // extensia implicită
    if(GetSaveFileName( & ofn) == TRUE) {
        ofstream fout(szFile);
        if(fout.is_open()) {
            fout << text;
            fout.close();
        }
    }
    else {}
    fereastra_fisier = false;
    fereastra_deschisa = false;
    contor_linie_coloana();
    if(active_page == 0) active_page = 1;
    else active_page = 0;
    setactivepage(active_page);
    cleardevice();
    drawToolbar();
    scroll_oriz();
    scroll_vert();
    sepLine();
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setbkcolor(c_bk);
    setcolor(c_text);
    doar_text();
    setvisualpage(active_page);
    setcolor(c_text);
    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
}
void resize_window(int dimensiune_x, int dimensiune_y) {
    clearmouseclick(WM_LBUTTONDOWN);
    while(!ismouseclick(WM_LBUTTONUP));
    clearmouseclick(WM_LBUTTONUP);
    closegraph();
    initializare_fereastra(dimensiune_x, dimensiune_y);
    if(wrap_mode == true) {
        poz_max_x = ((getmaxx() - 20) / 36 * 36 - 36);
        dim_x = poz_max_x;
        poz_min_x = 0;
    }
    echilibrare_pozitii();
    echilibrare_caret();
    setfillstyle(SOLID_FILL, c_bk);
    cleardevice();
    bar(0, 0, getmaxx(), getmaxy());
    if(active_page == 0) active_page = 1;
    else active_page = 0;
    setactivepage(active_page);
    setfillstyle(SOLID_FILL, c_bk);
    cleardevice();
    bar(0, 0, getmaxx(), getmaxy());
    setvisualpage(active_page);
    fereastra_dimensiune = false;
    fereastra_deschisa = false;
    doar_text();
    contor_linie_coloana();
}
void echilibrare_pozitii() {
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
    }
    else {
        poz_min_x = 0;
        poz_max_x = dim_x;
        poz_min_y = 65;
        poz_max_y = dim_y;
    }
}
void echilibrare_caret() {
    if(pozitie != 0) {
        x_caret = pozitii[pozitie - 1].first - poz_min_x;
        y_caret = pozitii[pozitie - 1].second - poz_min_y + 65;
    }
    else {
        x_caret = 0;
        y_caret = 65;
    }
}
void binar() {
    vector < int > character;
    stringstream ss;
    const std::string s = ss.str();
    for(int i = 0; i < text.size(); i++) {
        character.push_back(int(text[i]));
        ss << hex << character.at(i) << ' ';
    }
    text_binar = ss.str();
}
void number(string & v, int x) {
    string v1;
    if(x == 0) {
        v.push_back(48);
    }
    else {
        while(x) {
            v1.push_back(x % 10 + 48);
            x /= 10;
        }
        for(int i = v1.size() - 1; i >= 0; i--) v.push_back(v1[i]);
    }
}
void contor_linie_coloana() {
    setcolor(c_bk);
    outtextxy(30 + textwidth("Line: "), getmaxy() - 30, "100000000");
    outtextxy(getmaxx() / 3 + 30 + textwidth("Column: "), getmaxy() - 30, "100000000");
    outtextxy(getmaxx() / 3 * 2 + 30 + textwidth("Position: "), getmaxy() - 30, "100000000");
    setcolor(MAGENTA);
    int tmp = 0;
    setcolor(5);
    setbkcolor(c_bk);
    char * nr;
    string numar;
    if(pozitii.empty()) {
        tmp = 1;
        pozitii.push_back({
            0,
            65
        });
    }
    number(numar, (pozitii[max(0, pozitie - 1)].second - 65) / 21 + 1);
    nr = & numar[0];
    outtextxy(30 + textwidth("Line: "), getmaxy() - 30, nr);
    numar.erase(numar.begin(), numar.end());
    number(numar, (pozitii[max(0, pozitie - 1)].first) / 12 + 1);
    nr = & numar[0];
    outtextxy(getmaxx() / 3 + 30 + textwidth("Column: "), getmaxy() - 30, nr);
    numar.erase(numar.begin(), numar.end());
    number(numar, pozitie + 1);
    nr = & numar[0];
    outtextxy(getmaxx() / 3 * 2 + 30 + textwidth("Position: "), getmaxy() - 30, nr);
}
void ctrl_v(nod1 z, int & poz, int & b) {
    if(!z.text.empty()) {
        for(int i = 0; i < z.text.size(); i++) {
            text.insert(text.begin() + b, z.text[i]);
            b++;
        }
        poz += z.text.size();
    }
}
void delete_selectat(int & e, int & f) {
    if(e < f) {
        if(f == text.size()) text.erase(text.begin() + e, text.end()), f = e;
        else text.erase(text.begin() + e, text.begin() + f), f = e;
    }
    else if(e == text.size()) text.erase(text.begin() + f, text.end()), e = f;
    else text.erase(text.begin() + f, text.begin() + e), e = f;
}
void ctrl_c_x(char c, nod1 & z, int & e, int & f) {
    z.text.erase(z.text.begin(), z.text.end());
    if(e < f)
        for(int i = e; i < f; i++) {
            z.text.push_back(text[i]);
        }
    else
        for(int i = f; i < e; i++) {
            z.text.push_back(text[i]);
        }
    if(c == 'X') {
        if(e < f) {
            if(f == text.size()) text.erase(text.begin() + e, text.end()), f = e;
            else text.erase(text.begin() + e, text.begin() + f), f = e;
        }
        else if(e == text.size()) text.erase(text.begin() + f, text.end()), e = f;
        else text.erase(text.begin() + f, text.begin() + e), e = f;
    }
}
void push_stiva(nod * & m, int a, int b, int c, int d, int e, int f, string t, vector < pair < int, int > > p) {
    nod * z = new nod;
    z -> urm = NULL;
    z -> ant = NULL;
    z -> x_caret = a;
    z -> y_caret = b;
    z -> x_caret_i = c;
    z -> y_caret_i = d;
    z -> pozitie = e;
    z -> pozitie_i = f;
    for(int i = 0; i < t.size(); i++) z -> text.push_back(t[i]);
    for(int i = 0; i < p.size(); i++) z -> pozitii.push_back({
        p[i].first,
        p[i].second
    });
    if(m == NULL) m = z;
    else {
        m -> urm = z;
        z -> ant = m;
        m = m -> urm;
    }
}
void utilizare_undo_redo(nod * & a1, nod * & a2, int & a, int & b, int & c, int & d, int & e, int & f, int operatie) {
    if(a1 != NULL) {
        if(operatie == 1) push_stiva(a2, a1 -> x_caret, a1 -> y_caret, a1 -> x_caret_i, a1 -> y_caret_i, a1 -> pozitie, a1 -> pozitie_i, a1 -> text, a1 -> pozitii);
        text.erase(text.begin(), text.end());
        pozitii.erase(pozitii.begin(), pozitii.end());
        a = a1 -> x_caret;
        b = a1 -> y_caret;
        c = a1 -> x_caret_i;
        d = a1 -> y_caret_i;
        e = a1 -> pozitie;
        f = a1 -> pozitie_i;
        for(int i = 0; i < a1 -> text.size(); i++) text.push_back(a1 -> text[i]);
        for(int i = 0; i < a1 -> pozitii.size(); i++) pozitii.push_back({
            a1 -> pozitii[i].first,
            a1 -> pozitii[i].second
        });
        if(a1 -> ant == NULL) {
            delete(a1);
            a1 = NULL;
        }
        else {
            nod * q = new nod;
            q = a1;
            a1 = a1 -> ant;
            a1 -> urm = NULL;
            delete(q);
        }
    }
}
void replaceAll(string & source,
    const string & from,
        const string & to) {
    string newString;
    newString.reserve(source.length());
    string::size_type lastPos = 0;
    string::size_type findPos;
    while(string::npos != (findPos = source.find(from, lastPos))) {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }
    newString += source.substr(lastPos);
    source.swap(newString);
}
void anulati() {
    if(undo != NULL) {
        nod * q;
        push_stiva(redo, x_caret, y_caret, x_caret_i, y_caret_i, pozitie, pozitie_i, text, pozitii);
        utilizare_undo_redo(undo, undo1, x_caret, y_caret, x_caret_i, y_caret_i, pozitie, pozitie_i, 1);
    }
    x = 0;
    y = 65;
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
        if(text[i] == 10) {
            y = y + 21;
            x = 0;
        }
        else {
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
    }
    else {
        poz_min_x = 0;
        poz_max_x = dim_x;
        poz_min_y = 65;
        poz_max_y = dim_y;
    }
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setbkcolor(c_bk);
    setcolor(c_text);
    for(int i = 0; i < text.size(); i++) {
        if(x + 36 == (getmaxx() - 20) / 36 * 36 && wrap_mode == true) {
            x = 0;
            y += 21;
        }
        if(text[i] == 10) {
            y = y + 21;
            x = 0;
        }
        else {
            aux[0] = text[i];
            if(x >= poz_min_x && x <= poz_max_x && y >= poz_min_y && y <= poz_max_y) outtextxy(x - poz_min_x + 12, y - poz_min_y + 65, aux);
            x = x + 12;
        }
    }
    if(pozitie != 0) {
        x_caret = pozitii[pozitie - 1].first - poz_min_x;
        y_caret = pozitii[pozitie - 1].second - poz_min_y + 65;
    }
    else {
        x_caret = 0;
        y_caret = 65;
    }
    contor_linie_coloana();
    scroll_oriz();
    scroll_vert();
    setvisualpage(active_page);
    setcolor(c_text);
    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
}
void refaceti() {
    if(redo != NULL) {
        nod * q;
        push_stiva(undo, x_caret, y_caret, x_caret_i, y_caret_i, pozitie, pozitie_i, text, pozitii);
        utilizare_undo_redo(redo, q, x_caret, y_caret, x_caret_i, y_caret_i, pozitie, pozitie_i, 0);
    }
    x = 0;
    y = 65;
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
        if(text[i] == 10) {
            y = y + 21;
            x = 0;
        }
        else {
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
    }
    else {
        poz_min_x = 0;
        poz_max_x = dim_x;
        poz_min_y = 65;
        poz_max_y = dim_y;
    }
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setbkcolor(c_bk);
    setcolor(c_text);
    for(int i = 0; i < text.size(); i++) {
        if(x + 36 == (getmaxx() - 20) / 36 * 36 && wrap_mode == true) {
            x = 0;
            y += 21;
        }
        if(text[i] == 10) {
            y = y + 21;
            x = 0;
        }
        else {
            aux[0] = text[i];
            if(x >= poz_min_x && x <= poz_max_x && y >= poz_min_y && y <= poz_max_y) outtextxy(x - poz_min_x + 12, y - poz_min_y + 65, aux);
            x = x + 12;
        }
    }
    if(pozitie != 0) {
        x_caret = pozitii[pozitie - 1].first - poz_min_x;
        y_caret = pozitii[pozitie - 1].second - poz_min_y + 65;
    }
    else {
        x_caret = 0;
        y_caret = 65;
    }
    contor_linie_coloana();
    scroll_oriz();
    scroll_vert();
    setvisualpage(active_page);
    setcolor(c_text);
    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
    fereastra_editati = false;
    fereastra_deschisa = false;
}
void decupati() {
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
    ctrl_c_x('X', control_c, pozitie_i, pozitie);
    x = 0;
    y = 65;
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
        if(text[i] == 10) {
            y = y + 21;
            x = 0;
        }
        else {
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
    }
    else {
        poz_min_x = 0;
        poz_max_x = dim_x;
        poz_min_y = 65;
        poz_max_y = dim_y;
    }
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setbkcolor(c_bk);
    setcolor(c_text);
    for(int i = 0; i < text.size(); i++) {
        if(x + 36 == (getmaxx() - 20) / 36 * 36 && wrap_mode == true) {
            x = 0;
            y += 21;
        }
        if(text[i] == 10) {
            y = y + 21;
            x = 0;
        }
        else {
            aux[0] = text[i];
            if(x >= poz_min_x && x <= poz_max_x && y >= poz_min_y && y <= poz_max_y) outtextxy(x - poz_min_x + 12, y - poz_min_y + 65, aux);
            x = x + 12;
        }
    }
    if(pozitie != 0) {
        x_caret = pozitii[pozitie - 1].first - poz_min_x;
        y_caret = pozitii[pozitie - 1].second - poz_min_y + 65;
    }
    else {
        x_caret = 0;
        y_caret = 65;
    }
    contor_linie_coloana();
    scroll_oriz();
    scroll_vert();
    setvisualpage(active_page);
    setcolor(c_text);
    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
    text_selectat = false;
}
void cautare_text() {
    string cautare;
    int act = true;
    int j = initwindow(800, 50, "Find", (getmaxwidth() - 800) / 2, (getmaxheight() - 50) / 2, false, false);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setbkcolor(c_bk);
    setcolor(c_text);
    cleardevice();
    textwidth("Find word: ");
    while(act) {
        setcolor(5);
        outtext("Find word: ");
        setcolor(c_text);
        c = getch();
        char * sir = & cautare[0];
        if(c == 13 || c == 27) {
            act = false;
            closegraph(j);
            setcurrentwindow(mainWindowHandle);
        }
        else if((c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == ' ' || strchr(caractere, c)) && c != 0) {
            cleardevice();
            cautare.push_back(c);
            outtextxy(textwidth("Find word: "), 0, sir);
            x += 12;
        }
        else if(c == 8) {
            if(!cautare.empty()) {
                cleardevice();
                cautare.pop_back();
                x -= 12;
                outtextxy(textwidth("Find word: "), 0, sir);
            }
        }
    }
    if(active_page == 0) active_page = 1;
    else active_page = 0;
    setactivepage(active_page);
    cleardevice();
    drawToolbar();
    sepLine();
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setbkcolor(c_bk);
    setcolor(c_text);
    if(!cautare.empty()) {
        cnt = 0;
        int hau = 0;
        aparitii.erase(aparitii.begin(), aparitii.end());
        while(text.find(cautare, hau) != string::npos) {
            aparitii.push_back((int) text.find(cautare, hau));
            hau = aparitii[cnt] + 1;
            cnt++;
        }
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
                }
                else setbkcolor(c_bk);
            }
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
        scroll_oriz();
        scroll_vert();
        setcolor(c_text);
        setbkcolor(c_bk);
        contor_linie_coloana();
        setvisualpage(active_page);
        text_cautat = true;
        cautatt = cautare;
    }
}
void lipire() {
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
    ctrl_v(control_c, pozitie_i, pozitie);
    doar_text();
}
void selectare_pozitii(bool & cct) {
    while(!ismouseclick(WM_LBUTTONUP));
    clearmouseclick(WM_LBUTTONUP);
    cct = true;
    if(!text.empty()) {
        string cautare;
        string inlocuire;
        int cnt_ent = 0;
        int act = true;
        int j = initwindow(800, 100, "Select", (getmaxwidth() - 800) / 2, (getmaxheight() - 100) / 2, false, false);
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        setbkcolor(c_bk);
        setcolor(c_text);
        floodfill(0, 0, c_bk);
        while(act) {
            setcolor(MAGENTA);
            outtextxy(0, 0, "Starting position: ");
            outtextxy(0, 41, "End position: ");
            setcolor(c_text);
            c = getch();
            char * sir = & cautare[0], * sir1 = & inlocuire[0];
            if(c == 13 || c == 27) {
                cnt_ent++;
                if(cnt_ent > 1) {
                    act = false;
                    closegraph(j);
                    setcurrentwindow(mainWindowHandle);
                }
            }
            else if(c >= '0' && c <= '9') {
                cleardevice();
                if(cnt_ent == 0) {
                    cautare.push_back(c);
                }
                else inlocuire.push_back(c);
                outtextxy(textwidth("Starting position: "), 0, sir);
                outtextxy(textwidth("End position: "), 41, sir1);
            }
            else if(c == 8) {
                if(cnt_ent == 0) {
                    if(!cautare.empty()) {
                        cleardevice();
                        cautare.pop_back();
                        outtextxy(textwidth("Starting position: "), 0, sir);
                    }
                }
                else {
                    if(!inlocuire.empty()) {
                        cleardevice();
                        inlocuire.pop_back();
                        outtextxy(textwidth("Starting position: "), 0, sir);
                        outtextxy(textwidth("End position: "), 41, sir1);
                    }
                }
            }
        }
        if(active_page == 0) active_page = 1;
        else active_page = 0;
        setactivepage(active_page);
        cleardevice();
        drawToolbar();
        sepLine();
        settextstyle(BOLD_FONT, HORIZ_DIR, 2);
        setbkcolor(c_bk);
        setcolor(c_text);
        int aux1 = 0;
        if(!cautare.empty() && !inlocuire.empty()) {
            for(int i = 0; i < cautare.size(); i++) aux1 = aux1 * 10 + cautare[i] - 48;
            pozitie_i = min((int) text.size(), aux1);
            aux1 = 0;
            for(int i = 0; i < inlocuire.size(); i++) aux1 = aux1 * 10 + inlocuire[i] - 48;
            pozitie = min((int) text.size(), aux1);
        }
        else if(!cautare.empty()) {
            for(int i = 0; i < cautare.size(); i++) aux1 = aux1 * 10 + cautare[i] - 48;
            pozitie_i = min((int) text.size(), aux1);
            pozitie = 0;
        }
        else if(!inlocuire.empty()) {
            for(int i = 0; i < inlocuire.size(); i++) aux1 = aux1 * 10 + inlocuire[i] - 48;
            pozitie = min((int) text.size(), aux1);
            pozitie_i = 0;
        }
        else pozitie_i = pozitie;
        x_caret_i = pozitii[pozitie_i].first;
        y_caret_i = pozitii[pozitie_i].second;
        x_caret = pozitii[pozitie].first;
        y_caret = pozitii[pozitie].second;
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
        if(pozitie_i < pozitie && !text.empty()) {
            if(x + 36 == (getmaxx() - 20) / 36 * 36 && wrap_mode == true) {
                x = 0;
                y += 21;
            }
            aux[1] = 0;
            x = 0;
            y = 65;
            for(int i = 0; i < text.size(); i++) {
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
        }
        else if(!text.empty()) {
            aux[1] = 0;
            x = 0;
            y = 65;
            for(int i = 0; i < text.size(); i++) {
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
        if(cautare.empty()) doar_text();
        contor_linie_coloana();
        scroll_oriz();
        scroll_vert();
        setvisualpage(active_page);
        doar_text();
    }
    else {
        doar_text();
        contor_linie_coloana();
        scroll_oriz();
        scroll_vert();
        setvisualpage(active_page);
    }
}
void inlocuire(bool & cct) {
    cct = true;
    while(!ismouseclick(WM_LBUTTONUP));
    clearmouseclick(WM_LBUTTONUP);
    string cautare;
    string inlocuire;
    int cnt_ent = 0;
    int act = true;
    int j = initwindow(800, 100, "Replace", (getmaxwidth() - 800) / 2, (getmaxheight() - 100) / 2, false, false);
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setbkcolor(c_bk);
    setcolor(c_text);
    floodfill(0, 0, c_bk);
    while(act) {
        setcolor(MAGENTA);
        outtextxy(0, 0, "Find word: ");
        outtextxy(0, 41, "Replace word: ");
        setcolor(c_text);
        c = getch();
        char * sir = & cautare[0], * sir1 = & inlocuire[0];
        if(c == 13 || c == 27) {
            cnt_ent++;
            if(cnt_ent > 1) {
                act = false;
                closegraph(j);
                setcurrentwindow(mainWindowHandle);
            }
        }
        else if((c >= '0' && c <= '9' || c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == ' ' || strchr(caractere, c)) && c != 0) {
            cleardevice();
            if(cnt_ent == 0) {
                cautare.push_back(c);
            }
            else inlocuire.push_back(c);
            outtextxy(textwidth("Find word: "), 0, sir);
            outtextxy(textwidth("Replace word: "), 41, sir1);
        }
        else if(c == 8) {
            if(cnt_ent == 0) {
                if(!cautare.empty()) {
                    cleardevice();
                    cautare.pop_back();
                    outtextxy(textwidth("Find word: "), 0, sir);
                }
            }
            else {
                if(!inlocuire.empty()) {
                    cleardevice();
                    inlocuire.pop_back();
                    outtextxy(textwidth("Find word: "), 0, sir);
                    outtextxy(textwidth("Replace word: "), 41, sir1);
                }
            }
        }
    }
    if(active_page == 0) active_page = 1;
    else active_page = 0;
    setactivepage(active_page);
    cleardevice();
    drawToolbar();
    sepLine();
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setbkcolor(c_bk);
    setcolor(c_text);
    if(!cautare.empty()) {
        cct = true;
        replaceAll(text, cautare, inlocuire);
        pozitie = text.size();
    }
    x = 0;
    y = 65;
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
    echilibrare_pozitii();
    dim_max_x = 0;
    dim_max_y = 65;
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
        if(text[i] == 10) {
            y = y + textheight(aux);
            x = 0;
        }
        else {
            pozitii[i].first = x;
            pozitii[i].second = y;
            aux[0] = text[i];
            if(x >= poz_min_x && x <= poz_max_x && y >= poz_min_y && y <= poz_max_y) outtextxy(x - poz_min_x + 12, y - poz_min_y + 65, aux);
            x = x + 12;
        }
        pozitii[i].first = x;
        pozitii[i].second = y;
    }
    if(pozitie != 0) {
        x_caret = pozitii[pozitie - 1].first;
        y_caret = pozitii[pozitie - 1].second;
    }
    else {
        x_caret = 0;
        y_caret = 65;
    }
    contor_linie_coloana();
    doar_text();
    contor_linie_coloana();
    scroll_oriz();
    scroll_vert();
    setvisualpage(active_page);
    setcolor(c_text);
    line(x_caret + 12, y_caret, x_caret + 12, 21 + y_caret);
}
void select_all() {
    if(active_page == 0) active_page = 1;
    else active_page = 0;
    setactivepage(active_page);
    cleardevice();
    drawToolbar();
    sepLine();
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setcolor(c_text);
    setbkcolor(c_selectat);
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
    setcolor(c_text);
    text_selectat = true;
    setbkcolor(c_bk);
    scroll_oriz();
    scroll_vert();
    setvisualpage(active_page);
    pozitie_i = 0;
    pozitie = text.size();
    echilibrare_caret();
    contor_linie_coloana();
}
