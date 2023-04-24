// بسم الله الرحمن الرحيم

#include <SDL.h>

int main(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif
    int counter = 2;

    while(counter > 0){


        // Create window with SDL_Renderer graphics context
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_POPUP_MENU);
        SDL_Window* window = SDL_CreateWindow("Dikr", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 90, window_flags);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr)
        {
            SDL_Log("Error creating SDL_Renderer!");
            return 0;
        }
        SDL_Event event;
        bool running = true;
        while(running){
            while(SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT) {
                    running = false;
                }
                if (SDL_MOUSEBUTTONDOWN == event.type && SDL_BUTTON_LEFT == event.button.button){
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

        SDL_Delay(3000);

    }
    SDL_Quit();
    return 0;
}