#include "renderer.h"
#include "tilemap.h"
#include "foreground.h"
#include <iostream>
#include <nds.h>

Renderer::Renderer(int screen_width, int screen_height) {
    // Top Screen background
    BGCTRL[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_COLOR_256 | BG_32x32 | BG_PRIORITY(3);
    dmaCopy(tilemapTiles,(void *)CHAR_BASE_BLOCK(1),tilemapTilesLen);
	dmaCopy(tilemapMap,(void *)SCREEN_BASE_BLOCK(0),tilemapMapLen);
	dmaCopy(tilemapPal,BG_PALETTE,tilemapPalLen);


    // Foreground (layer 1) setup
//     BGCTRL[1] = BG_TILE_BASE(2) | BG_MAP_BASE(1) | BG_COLOR_256 | BG_32x32 | BG_PRIORITY(2); // Priority 2 (Above sprites)
//     dmaCopy(foregroundTiles, (void *)CHAR_BASE_BLOCK(2), foregroundTilesLen);
//     dmaCopy(foregroundMap, (void *)SCREEN_BASE_BLOCK(1), foregroundMapLen);
//     dmaCopy(foregroundPal, BG_PALETTE, foregroundPalLen);
}

Renderer::~Renderer() {
}


void Renderer::Render(Bird &bird, Pipe &pipe_1, Pipe &pipe_2){
    // DrawBackground(sdl_renderer);
    bird.DrawYourself(*this);
    pipe_1.DrawYourself(*this, 1);
    pipe_2.DrawYourself(*this, 3);

    // DrawGround(sdl_renderer);

    // // Update Screen
    // SDL_RenderPresent(sdl_renderer);


    swiWaitForVBlank();
    oamUpdate(&oamMain);
}


void Renderer::DrawBackground(){

}

void Renderer::DrawGround(){

}