#ifndef SNAKE_H
#define SNAKE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "SDL.h"
#include "SDL_ttf.h"

#if 0
//fullscreen
#define WINDOW_WIDTH    1920
#define WINDOW_HEIGHT   1080
#define GRID_X  (WINDOW_WIDTH / 2 - GRID_DIM / 2)
#else
//window
#define WINDOW_WIDTH    960
#define WINDOW_HEIGHT   800
#define GRID_X  0

#endif

#define GRID_SIZE   20
#define GRID_DIM    WINDOW_HEIGHT

#define GRID_Y  (WINDOW_HEIGHT / 2 - GRID_DIM / 2)

#define TARGET_FRAME_FPS   15
#define TARGET_FRAME_DURATION   (1000/TARGET_FRAME_FPS)


enum {
    SNAKE_UP,
    SNAKE_DOWN,
    SNAKE_LEFT,
    SNAKE_RIGHT,
};

typedef struct Snake{
    int x;
    int y;
    int dir;
    struct Snake *next;
}Snake;

typedef struct Apple{
    int x;
    int y;
}Apple;

typedef struct State
{
    bool quit;
    bool pause;
    bool game_over;
    bool restart;
}State;

extern Snake *head;
extern Snake *tail;
extern Apple apple;
extern int score;


void init_snake();
void increase_snake();
void render_grid(SDL_Renderer *renderer, int x, int y);
void render_snake(SDL_Renderer *renderer, int x, int y, bool is_over);
void move_snake();
void gen_apple();
void detect_apple();
void render_apple(SDL_Renderer *renderer, int x, int y);
bool detect_crash();
void reset_snake();
void render_score(SDL_Renderer *renderer, SDL_Texture *texture, TTF_Font *font , int x, int y);
void render_gameover(SDL_Renderer *renderer,SDL_Texture *texture,TTF_Font *font);

#endif

