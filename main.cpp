// بسم الله الرحمن الرحيم

#include <SDL.h>
#include <SDL_ttf.h>

long unsigned int cooldown = 3000;

int main(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    if(TTF_Init() == -1){
        printf("Error: %s\n", TTF_GetError());
        return -1;
    }

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif
    int counter = 2;

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto screen_width = DM.w;
    auto screen_height = DM.h;

    int window_width = 200;
    int window_height = 75;

    while(counter > 0){


        // Create window with SDL_Renderer graphics context
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_POPUP_MENU);
        SDL_Window* window = SDL_CreateWindow("Dikr", screen_width - window_width, screen_height * 2 / 8, window_width, window_height, window_flags);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr)
        {
            SDL_Log("Error creating SDL_Renderer!");
            return 0;
        }

        bool running = true;

        SDL_Event event;
        while(running){
            while(SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT) {
                    running = false;
                }
                if (SDL_MOUSEBUTTONDOWN == event.type){
                    running = false;    
                }
            }
            

            SDL_SetRenderDrawColor(renderer,0,0,0,0);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
        counter--;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        if(counter > 0){
            SDL_Delay(cooldown);
        }

    }
    SDL_Quit();
    return 0;
}