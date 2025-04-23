#include "renderer.h"
#include "background.h"
#include "foreground.h"
#include <iostream>
#include <nds.h>

Renderer::Renderer(int screen_width, int screen_height) {
    // Top Screen background
    // Sky background
    int background = bgInit(1, BgType_Text8bpp, BgSize_T_256x256, 2, 3);  // mapBase 2, tileBase 3
    REG_BG1CNT = (REG_BG1CNT & ~0x3) | BG_PRIORITY(3);
    dmaCopy(backgroundTiles, bgGetGfxPtr(background), backgroundTilesLen);
    dmaCopy(backgroundMap,   bgGetMapPtr(background), backgroundMapLen);
 
    // Ground
    int bgForeground = bgInit(0, BgType_Text8bpp, BgSize_T_256x256, 0, 1); // mapBase 0, tileBase 1
    REG_BG0CNT = (REG_BG0CNT & ~0x3) | BG_PRIORITY(1);   // Highest priority
    dmaCopy(foregroundTiles, bgGetGfxPtr(bgForeground), foregroundTilesLen);
    dmaCopy(foregroundMap,   bgGetMapPtr(bgForeground), foregroundMapLen);
 
    // Set shared background palette
    dmaCopy(foregroundPal, BG_PALETTE, foregroundPalLen); 
}

Renderer::~Renderer() {
}


void Renderer::Render(Bird &bird, Pipe &pipe_1, Pipe &pipe_2){
    bird.DrawYourself(*this);
    pipe_1.DrawYourself(1);
    pipe_2.DrawYourself(4);
    swiWaitForVBlank();
    oamUpdate(&oamMain);
}


void Renderer::DrawBackground(){

}

void Renderer::DrawGround(){

}