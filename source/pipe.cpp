#include "pipe.h"
//#include "SDL.h"
//#include "SDL_image.h"
#include <string>
#include <iostream>
#include <random>


#include <stdlib.h>  // rng
#include <time.h>    // seed


#include "pipe_sprite.h"
#include "bird_spritesheet.h"


Pipe::Pipe(float x_start, bool initial_in) {
    x = x_start;
    upper_y = UpperYGenerator();
    //lowest -21.0f
    //highest 38.0f
    //UpperYGenerator();
    lower_y = upper_y + pipe_gap;
    offscreen = false;
    initial = initial_in;

    spriteGfx = oamAllocateGfx(&oamMain, SpriteSize_32x64, SpriteColorFormat_16Color);  // Use 16Color format
    dmaCopy(pipe_spriteTiles, spriteGfx, pipe_spriteTilesLen);
    dmaCopy(pipe_spritePal, &SPRITE_PALETTE[16], 32);

    // Random seed
    srand(time(NULL)); // or any seed value
}

void Pipe::Update(){
    MoveLeft();
}

void Pipe::DrawYourself(Renderer &renderer, int baseId){
    //iprintf("sprite: %d\n", (int)pipe_spritePalLen);
    //iprintf("X: %d, Upp_Y: %d, Low_Y: %d\n", (int)x, (int)upper_y, (int)lower_y);

    

    int tileOffset;
    if (baseId == 4){
        tileOffset = 1024;
        //x = 0;
        
    } else {
        tileOffset = 2048;
        //x = 64;
    }

    // Top pipe(s)
    oamSet(&oamMain, 
        baseId,     // Sprite ID 
        x, upper_y, // Position
        2,          // Priority
        1,          // Palette index
        SpriteSize_32x64, 
        SpriteColorFormat_16Color,
        (u16*)((u8*)spriteGfx + tileOffset), -1, false, false, false, false, false);

    // Extends above - tileoffset 512 (to only draw middle part of pipe)
    oamSet(&oamMain, 
        baseId + 2,
        x, upper_y-64,
        2, 
        1, 
        SpriteSize_32x64, 
        SpriteColorFormat_16Color,
            (u16*)((u8*)spriteGfx + 768), -1, false, false, false, false, false);
    
    // Bottom pipe
    oamSet(&oamMain, 
        baseId + 1, 
        x, lower_y, 
        2, 
        1, 
        SpriteSize_32x64, 
        SpriteColorFormat_16Color,
         (u16*)((u8*)spriteGfx), -1, false, false, false, false, false);
}

void Pipe::MoveLeft(){
    if (offscreen == false) {
        x -= 2.0f;
    }
    if (x <= -32.0f){
        offscreen = true;
        x = 256.0f;
        upper_y = UpperYGenerator();
        lower_y = upper_y + pipe_gap;
    }

    if (x == 256.0f){
        offscreen = false;
    }
}

float Pipe::UpperYGenerator(){
    // Make sure srand() is called once, maybe in main()
    // srand(time(NULL));  <-- Call this only ONCE

    int min = -21;
    int max = 38;

    float rng = ((float)rand() / (float)RAND_MAX) * (max - min) + min;


    //iprintf("RNG: %f\n", rng);
    return (float)rng;
}

bool Pipe::CollideWithBird(Bird bird){
    // Top
    if ((x < bird.GetX() + 16) && (x + 32 > bird.GetX()) && (upper_y < bird.GetY() + 16)
            && (upper_y + 64 > bird.GetY())) {
        iprintf("BOOM\n");
        return true;
    }
    // // Bottom
    // if ((x < bird.GetX() + 32) && (x + 64 > bird.GetX()) && (lower_y < bird.GetY() + 32)
    //         && (lower_y + 256 > bird.GetY())) {
    //     return true;
    // }
    return false;
}