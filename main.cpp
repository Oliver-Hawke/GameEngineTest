#include <SDL2/SDL.h>

//(struct is just a public-by-default class)
//player is now an object
struct Player
{
    float x;
    float y;
    int width;
    int height;
    float speed;
};


int main() {
    //initialize the window maker.
    SDL_Init(SDL_INIT_VIDEO);

    //SDL's window maker tool
    SDL_Window* window = SDL_CreateWindow(
        "Game Attempt From Scratch",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        //width
        1920,
        //height
        1080,
        SDL_WINDOW_SHOWN
    );
    
    //Make your renderer pointer (basically a paint brush that is a pain to control)
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED
    );

    //create your player (rectangle for now) properties
    //ORIGINAL VARIABLE KEPT HERE FOR MEMORIES 
    //(I would not do this in a job but i feel for my learning it is important to see what I'm replacing)
    // float xpos = 100.0f;
    // float ypos = 100.0f;
    // int PWidth = 80; // Player Width
    // int PHeight = 80; //Player Height
    // float PSpeed = 300.0f; //Player Speed
    
    //Player Rectangle Object
    Player player = {100.0f, 100.0f, 80, 80, 300.0f};
    int PRVal = 0; //Player Red Value
    int PGVal = 255; //Player Green Value
    int PBVal = 0; //Player Blue Value

    //a big ball of wibbly wobbly... TIMEY WHIMEY... Stuff 
    Uint32 lastTime = SDL_GetTicks();


    //create the while loop
    bool running = true;
    SDL_Event event;


    //MAIN UPDATE LOOP
    while (running) {
        //People assume that time is a strict progression of cause to effect but actually it's more like
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        //IS WINDOW OPEN? IF NO THEN SHUT DOWN
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }          
        }

        //INPUTS
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        
        if (keys[SDL_SCANCODE_W]) {
            player.y -= player.speed * deltaTime;
        }

        if (keys[SDL_SCANCODE_S]) {
            player.y += player.speed * deltaTime;
        }

        if (keys[SDL_SCANCODE_A]) {
            player.x -= player.speed * deltaTime;
        }

        if (keys[SDL_SCANCODE_D]) {
            player.x += player.speed * deltaTime;
        }  

        //select colour
        SDL_SetRenderDrawColor(renderer, 37, 150, 190, 255);
        
        //paint background
        SDL_RenderClear(renderer);

        
        //Rectangle objects
        SDL_Rect playerRect = {(int)player.x,(int)player.y, player.width, player.height};

        //select colour
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        //paint the rectangle
        SDL_RenderFillRect(renderer, &playerRect);


        
        
        
        
        //present the frame
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}