//بسم الله الرحمن الحيم

#include <SDL.h>
//#include <SDL_ttf.h>

const char* Dikr_list[][3] = {"بسم الله", "سبحن الله", "الله أكبر"};

int cooldown_time = 3;
int cooldown_time_debug = 3;
int show_counter = 2; // for debugging
bool always_show = false; // for debugging
int screen_width = 0, screen_heigth = 0;
int window_width = 250, window_height = 60;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

void init();
void pop_dikr();
void clean_up();
void cooldown();

int main(){

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0){
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

/*    if(TTF_Init() == -1){
        printf("Error: %s\n", TTF_GetError());
        return -1;
    }
*/
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    init();

    while(show_counter > 0){
        pop_dikr();
        
        show_counter--;
        
        clean_up();

        SDL_Delay(cooldown_time_debug * 1000);
    }


    SDL_Quit();
}

void init(){
    //get screen resolution
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    screen_heigth = DM.h;
    screen_width = DM.w;
}

void pop_dikr(){
    window = SDL_CreateWindow("Dikr", screen_width - window_width, screen_heigth * 3 / 10, window_width, window_height, SDL_WINDOW_POPUP_MENU);
    renderer = SDL_CreateRenderer(window, -1, 0);

    if(renderer == nullptr){
        SDL_Log("Error creating SDL_Renderer!");
    }



    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
    
    bool running = true;

    SDL_Event w_event;
    while(running){
        while(SDL_PollEvent(&w_event)){
            if(w_event.type == SDL_QUIT || w_event.type == SDL_MOUSEBUTTONDOWN){
                running = false;
            }
        }
    }
}

void clean_up(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void cooldown(){
    int waited_time = 0;
    while(waited_time < cooldown_time){
        SDL_Delay(60 * 1000);
        waited_time++;
    }
}
