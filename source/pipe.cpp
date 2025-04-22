#include "pipe.h"
//#include "SDL.h"
//#include "SDL_image.h"
#include <string>
#include <iostream>
#include <random>

#include "pipe_sprite.h"
#include "bird_spritesheet.h"


Pipe::Pipe(float x_start, bool initial_in) {
    x = x_start;
    upper_y = UpperYGenerator();
    lower_y = upper_y + pipe_gap;
    offscreen = false;
    initial = initial_in;

    spriteGfx = oamAllocateGfx(&oamMain, SpriteSize_32x64, SpriteColorFormat_16Color);  // Use 16Color format
    dmaCopy(pipe_spriteTiles, spriteGfx, pipe_spriteTilesLen);
    dmaCopy(pipe_spritePal, &SPRITE_PALETTE[16], 32);
}

void Pipe::Update(){
    MoveLeft();
}

void Pipe::DrawYourself(Renderer &renderer, int baseId){
    iprintf("sprite: %d\n", (int)pipe_spritePalLen);
    iprintf("X: %d, Upp_Y: %d, Low_Y: %d\n", (int)x, (int)upper_y, (int)lower_y);

    int tileOffset;
    iprintf("spriteGfx: %d\n", (int)spriteGfx);
    oamSet(&oamMain, baseId, x, upper_y, 0, 1, SpriteSize_32x64, SpriteColorFormat_16Color,
        (u16*)((u8*)spriteGfx), -1, false, false, false, false, false);
    
    if (baseId == 3){
        tileOffset = 1024;
        //x = 0;
        
    } else {
        tileOffset = 2048;
        //x = 64;
    }
    oamSet(&oamMain, baseId + 1, x, lower_y, 0, 1, SpriteSize_32x64, SpriteColorFormat_16Color,
         (u16*)((u8*)spriteGfx + tileOffset), -1, false, false, false, false, false);
}

void Pipe::MoveLeft(){
    if (offscreen == false) {
        x -= 3.0f;
    }
    if (x <= -32.0f){
        offscreen = true;
        x = 256.0f;
        //upper_y = UpperYGenerator();
        lower_y = upper_y + pipe_gap;
    }

    if (x == 256.0f){
        offscreen = false;
    }
}

float Pipe::UpperYGenerator(){
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, (192 - 2 * 32 - pipe_gap));

    int rng = dis(gen) - 0.0f;
    iprintf("RNG: %d\n", (int)rng);
    return rng;
}

bool Pipe::CollideWithBird(Bird bird){
    // Top
    if ((x < bird.GetX() + 32) && (x + 64 > bird.GetX()) && (upper_y < bird.GetY() + 32)
            && (upper_y + 256 > bird.GetY())) {
        return true;
    }
    // Bottom
    if ((x < bird.GetX() + 32) && (x + 64 > bird.GetX()) && (lower_y < bird.GetY() + 32)
            && (lower_y + 256 > bird.GetY())) {
        return true;
    }
    return false;
}