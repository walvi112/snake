#include "snake.h"


Snake *head;
Snake *tail;
Apple apple;
int score = 0;


void render_grid(SDL_Renderer *renderer, int x, int y)
{
#if 0
    SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 0xFF);
    int cell_size = GRID_DIM / GRID_SIZE;
    SDL_Rect cell = {x, y, cell_size, cell_size};

    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            cell.x = x + i * cell_size;
            cell.y = y + j * cell_size;
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
#else
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Rect outline = {x, y, GRID_DIM, GRID_DIM};
    SDL_RenderDrawRect(renderer, &outline);
#endif
}

void render_snake(SDL_Renderer *renderer, int x, int y, bool is_over)
{
    Snake *track = head->next;
    int seg_size = GRID_DIM / GRID_SIZE;
    SDL_Rect seg;
    seg.w = seg_size;
    seg.h = seg_size;

    //render head
    if (is_over)
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    else
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
    seg.x = x + head->x * seg_size;
    seg.y = y + head->y * seg_size;
    if((head->x >= 0) && (head->x < GRID_SIZE) && (head->y  >= 0) && (head->y < GRID_SIZE))
        SDL_RenderFillRect(renderer, &seg);
    
    //render body
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    while (track != NULL)
    {
        seg.x = x + track->x * seg_size;
        seg.y = y + track->y * seg_size;
        if((track->x >= 0) && (track->x < GRID_SIZE) && (track->y  >= 0) && (track->y < GRID_SIZE))
            SDL_RenderFillRect(renderer, &seg);
        track = track->next;
    }
    
}

void init_snake()
{
    Snake *new = malloc(sizeof(Snake));
    new->x = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
    new->y = rand() % (GRID_SIZE / 2) + (GRID_SIZE / 4);
    new->dir = SNAKE_UP;
    new->next = NULL;

    head = new;
    tail = new;
}

void increase_snake()
{
    Snake *new = malloc(sizeof(Snake));
    switch (tail->dir)
    {
        case SNAKE_UP:
                {
                    new->x = tail->x ;
                    new->y = tail->y + 1;
                }
                break;
        case SNAKE_DOWN:
                {
                    new->x = tail->x ;
                    new->y = tail->y - 1;
                }  
                break;      
        case SNAKE_LEFT:
                {
                    new->x = tail->x + 1;
                    new->y = tail->y;
                }  
                break;
        case SNAKE_RIGHT:
                {
                    new->x = tail->x - 1;
                    new->y = tail->y;
                }  
                break;
    }
    new->dir = tail->dir;
    new->next = NULL;
    tail->next = new;

    tail = new;
}

void move_snake()
{    
    int prev_x = head->x;
    int prev_y = head->y;
    int prev_dir = head->dir;
    switch (head->dir)
    {
        case SNAKE_UP:
            head->y -= 1;
            break;
        case SNAKE_DOWN:
            head->y += 1;
            break;
        case SNAKE_LEFT:
            head->x -= 1;
            break;
        case SNAKE_RIGHT:
            head->x += 1;
            break;
    }

    head->x = (head->x + GRID_SIZE) % GRID_SIZE;
    head->y = (head->y + GRID_SIZE) % GRID_SIZE;

    if (head->next != NULL)
    {
        Snake *track = head->next;
        while(track != NULL)
        {
            int temp_x = track->x;
            int temp_y = track->y;
            int temp_dir = track->dir;

            track->x = prev_x;
            track->y = prev_y;
            track->dir = prev_dir;

            prev_x = temp_x;
            prev_y = temp_y;
            prev_dir = temp_dir;

            track = track->next;                    
        }
    }

}

void gen_apple()
{
    bool in_snake = false;
    do
    {
        apple.x = rand() % GRID_SIZE;
        apple.y = rand() % GRID_SIZE;
        in_snake = false;

        Snake *seg = head;
        while(seg != NULL)
        {
            if((apple.x == seg->x) && (apple.y == seg->y))
            {
                in_snake = true;
            }
            seg = seg->next;
        }
    
    }
    while (in_snake);
    
}

void render_apple(SDL_Renderer *renderer, int x, int y)
{
    int apple_size = GRID_DIM / GRID_SIZE;
    SDL_Rect rect = {
        x + apple.x * apple_size,
        y + apple.y * apple_size,
        apple_size,
        apple_size
    };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
}

void detect_apple()
{
    if (head->x == apple.x && head->y == apple.y)
    {
        gen_apple();
        score += 1;
        increase_snake();
    }
}

bool detect_crash()
{
    #if 0
    if ((head->x < 0) || (head->y < 0) || (head->x >= GRID_SIZE || (head->y >= GRID_SIZE)))
    {
        reset_snake();
    }
    #endif

    if (head->next != NULL)
    {
        Snake *track = head->next;
        while (track != NULL)
        {
            if ((track->x == head->x) && (track->y == head->y))
            {
                return true;
                break;
            }
            track = track->next;
        }
        
    }
    return false;
}
void reset_snake()
{
    Snake *temp = head;
    Snake *track = head;
    while (track != NULL)
    {
        temp = track->next;
        free(track);
        track = temp;
    }
    printf("Score: %d\n", score);
    score = 0;
    init_snake();
    increase_snake();
    gen_apple();
}

void render_score(SDL_Renderer *renderer, SDL_Texture *texture, TTF_Font* font , int x, int y)
{   
    int w,h;
    char score_str[15];
    snprintf(score_str, 15, "Score : %d", score);

    SDL_Color font_color = { 255, 255, 255, 255};
    SDL_Surface * surface = TTF_RenderText_Solid(font, score_str, font_color);

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        fprintf(stderr, "ERROR: Font Texture");
    }
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    SDL_Rect text_rect = {x + GRID_DIM + 10, y + 10, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);
    
}

void render_gameover(SDL_Renderer *renderer,SDL_Texture *texture,TTF_Font *font)
{
    int w,h;
    SDL_Color font_color = { 0xFF, 0xFF, 0xFF, 0xFF};
    SDL_Surface * surface = TTF_RenderText_Solid_Wrapped(font, "          GAME OVER   \nPress SPACE to restart", font_color, 800);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        fprintf(stderr, "ERROR: Font Texture");
        printf(SDL_GetError());
    }
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);

    SDL_Rect text_rect = {(WINDOW_WIDTH - w) / 2, (WINDOW_HEIGHT - h) / 2, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &text_rect);
}

