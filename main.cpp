#include <iostream>
#include <SDL3/SDL.h>

bool running = true;

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    
    SDL_Window *window = SDL_CreateWindow("676767 What is this diddy blud doing on that calculator, is he bloody epstein", 1024, 768, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, "");

    while(running)
    {
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_EVENT_QUIT)
            {
                running = false;
                break;
            }
            else if(e.type == SDL_EVENT_KEY_DOWN)
            {
                if(e.key.key == SDLK_ESCAPE)
                {
                    running = false;
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    return 0;
}