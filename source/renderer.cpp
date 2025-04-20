#include "renderer.h"
#include "tilemap.h"
#include <iostream>
#include <nds.h>

Renderer::Renderer(int screen_width, int screen_height) {
    // //Code
    


    // // Initialize SDL
    // if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    //     std::cerr << "SDL could not initialize.\n";
    //     std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    // }

    // // Create Window
    // sdl_window = SDL_CreateWindow("Cpp-y Bird", 0,
    //                             0, screen_width,
    //                             screen_height, SDL_WINDOW_SHOWN);

    // if (nullptr == sdl_window) {
    //     std::cerr << "Window could not be created.\n";
    //     std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    // }

    // // Create renderer
    // sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    // if (nullptr == sdl_renderer) {
    //     std::cerr << "Renderer could not be created.\n";
    //     std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    // }


    BGCTRL[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_COLOR_256 | BG_32x32;
    dmaCopy(tilemapTiles,(void *)CHAR_BASE_BLOCK(1),tilemapTilesLen);
	dmaCopy(tilemapMap,(void *)SCREEN_BASE_BLOCK(0),tilemapMapLen);
	dmaCopy(tilemapPal,BG_PALETTE,tilemapPalLen);
}

Renderer::~Renderer() {
    // SDL_DestroyWindow(sdl_window);
    // SDL_Quit();
}


void Renderer::Render(Bird &bird, Pipe &pipe_1, Pipe &pipe_2){
    // // Clear screen
    // SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    // SDL_RenderClear(sdl_renderer);

    // DrawBackground(sdl_renderer);
    bird.DrawYourself(*this);
    // pipe_1.DrawYourself(sdl_renderer);
    // pipe_2.DrawYourself(sdl_renderer);

    // DrawGround(sdl_renderer);

    // // Update Screen
    // SDL_RenderPresent(sdl_renderer);


    swiWaitForVBlank();
    oamUpdate(&oamMain);
}


void Renderer::DrawBackground(){
    //SDL_Renderer* renderer) {
    // SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    // SDL_RenderClear(renderer);
}

void Renderer::DrawGround(){
    // //SDL_Renderer* renderer) {
    // int windowWidth, windowHeight;
    // SDL_GetWindowSize(sdl_window, &windowWidth, &windowHeight);

    // // Grass
    // SDL_SetRenderDrawColor(renderer, 16, 151, 0, 255);
    // SDL_Rect grassRect = {0, 480, windowWidth, windowHeight / 5};
    // SDL_RenderFillRect(renderer, &grassRect);

    // // Ground
    // SDL_SetRenderDrawColor(renderer, 117, 101, 80, 255);
    // SDL_Rect groundRect = {0, 490, windowWidth, windowHeight / 5};
    // SDL_RenderFillRect(renderer, &groundRect);

    // // Border lines
    // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    // for (int y : {480, 490}) {
    //     SDL_Rect borderRect = {0, y, windowWidth, 1};
    //     SDL_RenderFillRect(renderer, &borderRect);
    // }
}