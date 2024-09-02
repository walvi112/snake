#include "snake.h"

int main(int argc, char* argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *tex_score = NULL;
    SDL_Texture *tex_msg = NULL;

    SDL_Event event;
    State state = {false, false, false, false};
    uint32_t frame_start, frame_end, frame_duration;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    {
        fprintf(stderr, "ERROR: SDL_INIT_VIDEO");
    }

    window = SDL_CreateWindow(
        "Snake",
        SDL_WINDOWPOS_UNDEFINED ,
        SDL_WINDOWPOS_UNDEFINED ,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    if (window == NULL)
    {
        fprintf(stderr, "ERROR: Window ");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL)
    {
        fprintf(stderr, "ERROR: Renderer");
    }

    if (TTF_Init() < 0)
    {
        fprintf(stderr, "ERROR: TTF INIT");
    }

    TTF_Font * font = TTF_OpenFont("PixelGameFont.ttf", 20);
    if (font == NULL)
    {
        fprintf(stderr, "ERROR: Font");
    }

    TTF_Font * msg_font = TTF_OpenFont("PixelGameFont.ttf", 50);
    if (msg_font == NULL)
    {
        fprintf(stderr, "ERROR: Msg Font");
    }

    srand(time(0));
    init_snake();
    increase_snake();
    gen_apple();
    bool button_pressed = false;
    while(!state.quit)
    {
        frame_start = SDL_GetTicks();
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    state.quit = true;
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_KEYDOWN:
                    if (!button_pressed)
                    {            
                        button_pressed = true;            
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_ESCAPE:
                                state.quit = true;
                                break;
                            case SDLK_w:
                                if (head->dir != SNAKE_UP && head->dir != SNAKE_DOWN)
                                    head->dir = SNAKE_UP;
                                break;
                            case SDLK_UP:
                                if (head->dir != SNAKE_UP && head->dir != SNAKE_DOWN)
                                    head->dir = SNAKE_UP;
                                break; 
                            case SDLK_s:
                                if (head->dir != SNAKE_UP && head->dir != SNAKE_DOWN)
                                    head->dir = SNAKE_DOWN;
                                break;
                            case SDLK_DOWN:
                                if (head->dir != SNAKE_UP && head->dir != SNAKE_DOWN)
                                    head->dir = SNAKE_DOWN;
                                break;
                            case SDLK_a:
                                if (head->dir != SNAKE_LEFT && head->dir != SNAKE_RIGHT)
                                    head->dir = SNAKE_LEFT;
                                break;
                            case SDLK_LEFT:
                                if (head->dir != SNAKE_LEFT && head->dir != SNAKE_RIGHT)
                                    head->dir = SNAKE_LEFT;
                                break;
                            case SDLK_d:
                                if (head->dir != SNAKE_LEFT && head->dir != SNAKE_RIGHT)
                                    head->dir = SNAKE_RIGHT; 
                                break;
                            case SDLK_RIGHT:
                                if (head->dir != SNAKE_LEFT && head->dir != SNAKE_RIGHT)
                                    head->dir = SNAKE_RIGHT; 
                                break;
                            case SDLK_SPACE:
                                {
                                    state.pause = state.pause ^ true;  
                                    if (state.game_over)
                                    {
                                        state.game_over = false;
                                        state.restart = true;
                                    }
                                }
                                break;
                        }
                    }
            }
        }
        button_pressed = false;
        SDL_RenderClear(renderer);
        //Render loop
        if (state.restart)
        {
            state.restart = false;
            reset_snake();
        }
        if (!state.pause)
        {
            move_snake();
            detect_apple();
            state.game_over = detect_crash();
        }

        
        render_grid(renderer, GRID_X, GRID_Y);
        render_apple(renderer, GRID_X, GRID_Y);
        render_snake(renderer, GRID_X, GRID_Y, state.game_over);
        render_score(renderer, tex_score, font, GRID_X, GRID_Y);
        if (state.game_over)
        {   
            state.pause = true;
            render_gameover(renderer, tex_msg, msg_font);
        }
        //Render loop end
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderPresent(renderer);


        frame_end = SDL_GetTicks();
        frame_duration = frame_end - frame_start;
        if (frame_duration < TARGET_FRAME_DURATION)
        {
            SDL_Delay(TARGET_FRAME_DURATION - frame_duration);
        }
        
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);	
    TTF_CloseFont(font);
    TTF_CloseFont(msg_font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}