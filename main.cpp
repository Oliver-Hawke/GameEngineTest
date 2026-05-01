#include <SDL2/SDL.h>

struct Player {
    float x;
    float y;
    int width;
    int height;
    float speed;
};

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Game Testing",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1920,
        1080,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    Player player = {100.0f, 100.0f, 80, 80, 300.0f};

    Uint32 lastTime = SDL_GetTicks();

    bool running = true;
    SDL_Event event;

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        const Uint8* keys = SDL_GetKeyboardState(NULL);

        float moveX = 0.0f;
        float moveY = 0.0f;

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

        player.x += moveX * player.speed * deltaTime;
        player.y += moveY * player.speed * deltaTime;

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        SDL_Rect playerRect = {
            (int)player.x,
            (int)player.y,
            player.width,
            player.height
        };

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &playerRect);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}