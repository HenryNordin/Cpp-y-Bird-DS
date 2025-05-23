#include "bird.h"
#include "renderer.h"
#include <string>
#include <iostream>

#include <nds.h>

#include "bird_spritesheet.h"



#include <chrono>
#include <thread>

Bird::Bird() {
    x = 128;
    y = 0;
    alive = true;
    collided = false;

    // Load sprite graphics into VRAM
    spriteGfx = oamAllocateGfx(&oamMain, SpriteSize_32x16, SpriteColorFormat_16Color);
    dmaCopy(bird_spritesheetTiles, &spriteGfx[0], bird_spritesheetTilesLen);
    //dmaCopy(bird_spritesheetPal, &SPRITE_PALETTE[0], bird_spritesheetPalLen);
    dmaCopy(bird_spritesheetPal, &SPRITE_PALETTE[0], 32);
}

bool Bird::GetAlive(){
    //return true; // so never dies
    return alive; //- OBS!! TEMP off
}

void Bird::SetCollided(){
    collided = true;
    //collided = false;
}

void Bird::RoofCollision(){
    if (y <= 0)
    {
        y = 0;
        velocity = 0;
    }
}

void Bird::GroundCollision(){
    if (y >= 155)
    {
        y = 155;
        velocity = 0;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        alive = false; //- OBS!! TEMP off
        
        //sprite_path = "assets/images/bird_sprite_2.png"; - placeholder
    }
}

void Bird::Fly(){
    if (!collided || invincible) {
        velocity = -3.5;
    }
}

void Bird::Fall(){
    velocity += gravity;
    y += velocity;
    if (velocity > 3.5) {
        velocity = 3.5;
    }


    if (y >= 100 && !gameStarted) {
        Fly();
    }
}

void Bird::Update(){
    if (alive) {
        Fall();
    }
    GroundCollision();
    RoofCollision();
}

void Bird::DrawYourself(Renderer &renderer){
    tileOffset = 0;

    if (velocity > -2) {
        tileOffset = 256; // skip the first sprite (32x16 = 512 bytes for 256-color)
    }
    //iprintf("Birdsprite: %d\n", (int)bird_spritesheetPalLen);

    oamSet(&oamMain, 
        0,  // Sprite ID
        x,y,// Position 
        1,  // Priority 
        0,  // Palette index
        SpriteSize_32x16, 
        SpriteColorFormat_16Color,
        (u16*)((u8*)spriteGfx + tileOffset), -1, false, false, false, false, false);

}

float Bird::GetX(){
    return x;
}

float Bird::GetY(){
    return y;
}

void Bird::Reset(){
    y = 0;
    alive = true;
    collided = false;
    gameStarted = false;
}

bool Bird::GetStarted(){
    return gameStarted;
//
}

void Bird::SetStarted(bool start){
    gameStarted = start;
//
}