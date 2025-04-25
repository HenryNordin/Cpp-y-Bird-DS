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


Pipe::Pipe(float x_init, bool initial_in) {
    x_start = x_init - 10;
    x = x_start;
    upper_y = UpperYGenerator();

    lower_y = upper_y + pipe_gap;
    offscreen = false;
    initial = initial_in;

    // if (!initial){
    //     score + 1;
    // }

    spriteGfx = oamAllocateGfx(&oamMain, SpriteSize_32x64, SpriteColorFormat_16Color);  // Use 16Color format
    dmaCopy(pipe_spriteTiles, spriteGfx, pipe_spriteTilesLen);
    dmaCopy(pipe_spritePal, &SPRITE_PALETTE[16], 32);

    // Random seed
    srand(time(NULL)); // or any seed value
}

void Pipe::Update(){
    MoveLeft();
}

void Pipe::DrawYourself(int baseId){
    //iprintf("sprite: %d\n", (int)pipe_spritePalLen);
    //iprintf("X: %d, Upp_Y: %d, Low_Y: %d\n", (int)x, (int)upper_y, (int)lower_y);

    bool Invisible = false;

    int tileOffset;
    if (baseId == 4){
        tileOffset = 1024;
        //x = 0;
        
    } else {
        tileOffset = 2048;
        //x = 64;
    }

    // Renders if the pipes are onscreen
    if (x >= -32 && x <= 255) {
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
    } else {
        oamSet(&oamMain, 
            baseId,     // Sprite ID 
            x, upper_y, // Position
            2,          // Priority
            1,          // Palette index
            SpriteSize_32x64, 
            SpriteColorFormat_16Color,
            (u16*)((u8*)spriteGfx + tileOffset), -1, false, true, false, false, false);

        // Extends above - tileoffset 512 (to only draw middle part of pipe)
        oamSet(&oamMain, 
            baseId + 2,
            x, upper_y-64,
            2, 
            1, 
            SpriteSize_32x64, 
            SpriteColorFormat_16Color,
            (u16*)((u8*)spriteGfx + 768), -1, false, true, false, false, false);
    
        // Bottom pipe
        oamSet(&oamMain, 
            baseId + 1, 
            x, lower_y, 
            2, 
            1, 
            SpriteSize_32x64, 
            SpriteColorFormat_16Color,
            (u16*)((u8*)spriteGfx), -1, false, true, false, false, false);

    }
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

    // Score Increase
    if (x == 128){
        int val = GetScore();
        SetScore(val+1);
    }
    if (x == 0){
        int val = GetScore();
        SetScore(val+1);
    }

    if (x == 256.0f){
        offscreen = false;
    }
}

float Pipe::UpperYGenerator(){
    int min = -21;
    int max = 38;
    float rng = ((float)rand() / (float)RAND_MAX) * (max - min) + min;
    return (float)rng;
}

bool Pipe::CollideWithBird(Bird bird){
    // // Upper
    // if ((x < bird.GetX() + 16) && (x + 32 > bird.GetX()) && (0 < bird.GetY() + 16)
    //         && (upper_y + 64 > bird.GetY())) {
    //     //iprintf("2-OKAYYYY\n");
    //     return true;
    // }

    // //iprintf("X: %d, Upp_Y: %d, Low_Y: %d\n", (int)x, (int)upper_y, (int)lower_y);
    // // Lower
    // if ((x < bird.GetX() + 16) && (x + 32 > bird.GetX()) && (upper_y + pipe_gap < bird.GetY() + 16)
    //         && (upper_y + 64 + pipe_gap > bird.GetY())) {
    //     //iprintf("4-YESSSSSSSSSSSSS\n");
    //     return true;
    // }
    return false;
}

void Pipe::Reset(){    
    oamUpdate(&oamMain);
    offscreen = false;
    x = x_start;
    score = 0;
}

int Pipe::GetScore(){

    return score;
}

void Pipe::SetScore(int value){
    score = value;
}