// بسم الله الرحمن الرحيم

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>

unsigned int cooldown = 3;

// "/usr/share/fonts/truetype/ubuntu/UbuntuMono-RI.ttf"
// "/home/ibrahimo/Downloads/Noto_Sans_Arabic/NotoSansArabic-VariableFont_wdth,wght.ttf"

std::string DikrList[5] = {"Bismi Allah", "Allah Akbar", "Alhamdo li Allah", "Astaghfiro Allah", "La ilaha illa Allah"};
std::vector<const char*> ArDikrVec = {"سبحن الله", "الله أكبر"};

int chosenDikr = 0;

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

    int show_counter = 2;

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto screen_width = DM.w;
    auto screen_height = DM.h;

    int window_width = 200;
    int window_height = 75;

    short int border = 5;
    SDL_Rect BismiAllahRect = SDL_Rect{border, border, window_width - (2 * border), window_height - (2 * border)};
    
    TTF_Font * Mono = TTF_OpenFont("/home/ibrahimo/Downloads/Noto_Sans_Arabic/NotoSansArabic-VariableFont_wdth,wght.ttf", 67);
    SDL_Color dikr_color = SDL_Color{0, 0, 0};

/*    TTF_SetDirection(HB_DIRECTION_RTL);
    TTF_SetScript(HB_SCRIPT_ARABIC);
*/

    srand(time(NULL));


    //
    while(show_counter > 0){
        chosenDikr = rand() % ArDikrVec.size();

        // Create window with SDL_Renderer graphics context
        SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_POPUP_MENU);
        SDL_Window* window = SDL_CreateWindow("Dikr", screen_width - window_width, screen_height * 1 / 8, window_width, window_height, window_flags);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr)
        {
            SDL_Log("Error creating SDL_Renderer!");
            return 0;
        }

        //convert unicode to multibyte "https://stackoverflow.com/questions/73275395/how-do-i-join-up-arabic-glyphs-with-sdl-ttf-v2-20"
/*        int wstr_len = (int)wcslen(ArDikrVec[chosenDikr]);
        int num_chars = WideCharToMultiByte(CP_UTF8, 0, ArDikrVec[chosenDikr], wstr_len, NULL, 0, NULL, NULL);
        char* strTo = (char*)malloc((num_chars + 1) * sizeof(char));
        if (strTo)
        {
            WideCharToMultiByte(CP_UTF8, 0, ArDikrVec[chosenDikr], wstr_len, strTo, num_chars, NULL, NULL);
            strTo[num_chars] = '\0';
        }
*/
        SDL_Surface * Surface_Dikr = TTF_RenderUTF8_Blended(Mono, ArDikrVec[chosenDikr], dikr_color);
        SDL_Texture * DikrTexture = SDL_CreateTextureFromSurface(renderer, Surface_Dikr);
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
            SDL_SetRenderDrawColor(renderer,0,255,0,0);
            SDL_RenderClear(renderer);

            //Draw inner box
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderDrawRect(renderer, &BismiAllahRect);
            SDL_RenderFillRect(renderer, &BismiAllahRect);
            
            //Draw Dikr
            SDL_RenderCopy(renderer, DikrTexture, NULL, &Dikr_rect);

            SDL_RenderPresent(renderer);
        }
        show_counter--;

        SDL_FreeSurface(Surface_Dikr);
        SDL_DestroyTexture(DikrTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        if(show_counter > 0){
            SDL_Delay(cooldown * 1000);
        }

    
    }
    SDL_Quit();
    return 0;
    }