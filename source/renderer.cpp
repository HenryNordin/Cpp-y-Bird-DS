#include "renderer.h"
#include "background.h"
#include "foreground.h"
#include <iostream>
#include <nds.h>

Renderer::Renderer(int screen_width, int screen_height) {
    // // Top Screen background
    // BGCTRL[0] = BG_TILE_BASE(1) | BG_MAP_BASE(0) | BG_COLOR_256 | BG_32x32 | BG_PRIORITY(3);
    // dmaCopy(backgroundTiles,(void *)CHAR_BASE_BLOCK(1),backgroundTilesLen);
	// dmaCopy(backgroundMap,(void *)SCREEN_BASE_BLOCK(0),backgroundMapLen);
	// dmaCopy(backgroundPal,BG_PALETTE,backgroundPalLen);


    // // Foreground (layer 1) setup
    // BGCTRL[1] = BG_TILE_BASE(2) | BG_MAP_BASE(1) | BG_COLOR_256 | BG_32x32 | BG_PRIORITY(2); // Priority 2 (Above sprites)
    // dmaCopy(foregroundTiles, (void *)CHAR_BASE_BLOCK(2), foregroundTilesLen);
    // dmaCopy(foregroundMap, (void *)SCREEN_BASE_BLOCK(1), foregroundMapLen);
    // dmaCopy(foregroundPal, BG_PALETTE, foregroundPalLen);

     // --- Init BG1: Sky (behind) ---
     int background = bgInit(1, BgType_Text8bpp, BgSize_T_256x256, 2, 3);  // mapBase 2, tileBase 3
     REG_BG1CNT = (REG_BG1CNT & ~0x3) | BG_PRIORITY(3);
     dmaCopy(backgroundTiles, bgGetGfxPtr(background), backgroundTilesLen);
     dmaCopy(backgroundMap,   bgGetMapPtr(background), backgroundMapLen);
 
     // --- Init BG0: Ground (in front) ---
     int bgForeground = bgInit(0, BgType_Text8bpp, BgSize_T_256x256, 0, 1); // mapBase 0, tileBase 1
     REG_BG0CNT = (REG_BG0CNT & ~0x3) | BG_PRIORITY(1);   // Highest priority
     dmaCopy(foregroundTiles, bgGetGfxPtr(bgForeground), foregroundTilesLen);
     dmaCopy(foregroundMap,   bgGetMapPtr(bgForeground), foregroundMapLen);
 
     // --- Set background palette (shared) ---
     dmaCopy(foregroundPal, BG_PALETTE, foregroundPalLen); 

}

Renderer::~Renderer() {
}


void Renderer::Render(Bird &bird, Pipe &pipe_1, Pipe &pipe_2){
    // DrawBackground(sdl_renderer);
    bird.DrawYourself(*this);
    pipe_1.DrawYourself(*this, 1);
    pipe_2.DrawYourself(*this, 4);

    // DrawGround(sdl_renderer);

    swiWaitForVBlank();
    oamUpdate(&oamMain);
}


void Renderer::DrawBackground(){

}

void Renderer::DrawGround(){

}