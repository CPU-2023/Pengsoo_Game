#pragma warning(disable:4996)
#include <mysql.h>
#include <errno.h>

#define MAX_STRING 70
#define MAP_WIDTH 18
#define MAP_HEIGHT 100

#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

void show_title();
int draw_menu();
int show_maplist();
void show_rank();
void setUser();
void gLoop(int);
void gameOver();
void gameClear();
void drawMap(int* x, int* y);
void move(int* x, int* y, int _x, int _y, int* key, int* playing);
void drawUI(int* x, int* y, int* key);
void drawTime(double time, double stime);
void maze_key();
void gamerule();