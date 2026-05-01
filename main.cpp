#include <SDL2/SDL.h>

//player object struct (struct = class that is public by default)
struct Player {
    float x;
    float y;
    int width;
    int height;
    float speed;

    float velocityX;
    float velocityY;

    float acceleration;
    float friction;
};

int main() {
    //start window maker
    SDL_Init(SDL_INIT_VIDEO);
    
    //start window
    SDL_Window* window = SDL_CreateWindow(
        "Game Testing",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1920,
        1080,
        SDL_WINDOW_SHOWN
    );

    //create renderer with pointer (renderer = paint brush)
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    Player player = {100.0f, 100.0f, 80, 80, 300.0f, 0.0f, 0.0f, 3000.0f, 2.0f};

    //A BIG BALL OF WIBBLY WOBBLY... TIMEY WIMEY... STUFF
    Uint32 lastTime = SDL_GetTicks();

    bool running = true;
    SDL_Event event;

    while (running) {
        //fps logic with deltaTime method to stop the player from moving based on frames, and start moving based on time
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;
        
        //if window quits, quit program
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        //better than sdl key events to monitor multiple keys at once (diagonal movement)
        const Uint8* keys = SDL_GetKeyboardState(NULL);

        //movement floats to make movement speed more manipulatable
        float moveX = 0.0f;
        float moveY = 0.0f;

        //setup wasd
        if (keys[SDL_SCANCODE_W]) {
            moveY -= 1.0f;
        }

        if (keys[SDL_SCANCODE_S]) {
            moveY += 1.0f;
        }

        if (keys[SDL_SCANCODE_A]) {
            moveX -= 1.0f;
        }

        if (keys[SDL_SCANCODE_D]) {
            moveX += 1.0f;
        }

        if (moveX != 0.0f && moveY != 0.0f) {
            moveX *= 0.7071f;
            moveY *= 0.7071f;
        }

        //movement speed physics logic (everything needs time!!!)

        //add acceleration
        player.velocityX += moveX * player.acceleration * deltaTime;
        player.velocityY += moveY * player.acceleration * deltaTime;

        //subtract friction
        player.velocityX -= player.velocityX * player.friction * deltaTime;
        player.velocityY -= player.velocityY * player.friction * deltaTime;

        //cap speed
        if (player.velocityX > player.speed) {
            player.velocityX = player.speed;
        }

        if (player.velocityX < -player.speed) {
            player.velocityX = -player.speed;
        }

        if (player.velocityY > player.speed) {
            player.velocityY = player.speed;
        }

        if (player.velocityY < -player.speed) {
            player.velocityY = -player.speed;
        }
       
        //log for collider (BEFORE MOVEMENT IS APPLIED!)
        float oldX = player.x;
        float oldY = player.y;

        //apply movement
        player.x += player.velocityX * deltaTime;
        player.y += player.velocityY * deltaTime;



        //add boundaries
        if (player.x < 0) {
            player.x = 0;
        }

        if (player.y < 0) {
            player.y = 0;
        }

        if (player.x + player.width > 1920) {
            player.x = 1920 - player.width;
        }

        if (player.y + player.height > 1080) {
            player.y = 1080 - player.height;
        }




        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        //ENTITIES

        //PLAYER
        SDL_Rect playerRect = {
            (int)player.x,
            (int)player.y,
            player.width,
            player.height
        };

        //OBSTACLE
        SDL_Rect obstacle ={400, 400, 100, 100};

        //collider
        bool isColliding = SDL_HasIntersection(&playerRect, &obstacle);
        
        if (isColliding){
            player.x = oldX;
            player.y = oldY;

            player.velocityX = 0.0f;
            player.velocityY = 0.0f;
          
            playerRect = {
                (int)player.x,
                (int)player.y,
                player.width,
                player.height
            };
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &playerRect);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &obstacle);

        } else{
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderFillRect(renderer, &playerRect);
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_RenderFillRect(renderer, &obstacle);
        }
        
        


        
        


        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}