#pragma once
#include <conio.h>
#include <graphics.h>
#include <unistd.h>
#include <winbgim.h>
#include <chrono>
#include <cstdint>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int c_bk = WHITE, c_text = BLACK, c_selectat = LIGHTBLUE, c_text_aux = GREEN;
bool wrap_wrap = false;
string text, text_binar, text_aux;
bool wrap_mode = false;
bool fereastra_deschisa = false;
vector<pair<int, int>> pozitii;
vector<int> y_max_coloana;
string cautatt;
bool text_selectat = false;
int mainWindowHandle = 0;
time_t now = time(0);
bool text_cautat = false;
bool inchidere_fereastra = false;
int dif_x = 0, dif_y = 0;
int x_caret_i = 0, y_caret_i = 0, pozitie_i = 0, x_caret = 0, y_caret = 65, pozitie = 0;
int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
int active_page = 0;
char c, caractere[] = "`~!@#$%^:&*()-_+={}[\\]|–?/>.<,'\"''țșăîâ";
int x = 0, y = 65, cnt = 0;
int lungime_scroll_vert, pozitie_scroll_vert;
int lungime_scroll_oriz, pozitie_scroll_oriz;
bool mouse_click_vert = false, mouse_click_oriz = false;
int fereastra_fisier, fereastra_editati, fereastra_tema, fereastra_culoare, fereastra_dimensiune, fereastra_wrap;
bool ctrlPressed = false;
bool func_caut = false;
bool hex_view = false;
int dim_x = 0, dim_y = 0, dim_max_x = 0, dim_max_y = 65, poz_min_x = 0, poz_min_y = 65, poz_max_x, poz_max_y;
char aux[3];
vector<int> aparitii;

struct nod {
  string text;
  vector<pair<int, int>> pozitii;
  int x_caret = 0, y_caret = 0, x_caret_i = 0, y_caret_i = 0, pozitie = 0, pozitie_i = 0;
  nod *urm, *ant;
} *undo = NULL, *redo = NULL, *undo1 = NULL;

struct nod1 {
  string text;
} control_c, control_x;
