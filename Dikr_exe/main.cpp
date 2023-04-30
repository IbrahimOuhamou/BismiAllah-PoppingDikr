// بسم الله الرحمن الرحيم

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>


unsigned int cooldown = 3;

// "/usr/share/fonts/truetype/ubuntu/UbuntuMono-RI.ttf"

std::string DikrList[5] = {"Bismi Allah", "Allah Akbar", "Alhamdo li Allah", "Astaghfiro Allah", "La ilaha illa Allah"};


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

    short int border = 5;
    SDL_Rect BismiAllahRect = SDL_Rect{border, border, window_width - (2 * border), window_height - (2 * border)};
    
    TTF_Font * Mono = TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/UbuntuMono-BI.ttf", 67);
    SDL_Color dikr_color = SDL_Color{0, 0, 0};
    
    srand(time(NULL));

    while(counter > 0){


        // Create window with SDL_Renderer graphics context
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_POPUP_MENU);
        SDL_Window* window = SDL_CreateWindow("Dikr", screen_width - window_width, screen_height * 1 / 8, window_width, window_height, window_flags);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr)
        {
            SDL_Log("Error creating SDL_Renderer!");
            return 0;
        }

        SDL_Surface * Surface_Dikr = TTF_RenderUTF8_Solid(Mono, DikrList[rand() % 5].c_str(), dikr_color);
        SDL_Texture * Dikr = SDL_CreateTextureFromSurface(renderer, Surface_Dikr);
        SDL_Rect Dikr_rect = SDL_Rect{border * 2, border * 2, window_width - (border * 4), window_height - (border * 4)};

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
            
            //Clear background
            SDL_SetRenderDrawColor(renderer,255,255,0,0);
            SDL_RenderClear(renderer);

            //Draw inner box
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &BismiAllahRect);
            SDL_RenderFillRect(renderer, &BismiAllahRect);
            
            //Draw Dikr
            SDL_RenderCopy(renderer, Dikr, NULL, &Dikr_rect);

            SDL_RenderPresent(renderer);
        }
        counter--;

        SDL_FreeSurface(Surface_Dikr);
        SDL_DestroyTexture(Dikr);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        if(counter > 0){
            SDL_Delay(cooldown * 1000);
        }

    }

    SDL_Quit();
    return 0;
}