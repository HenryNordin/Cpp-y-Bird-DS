#include "bird.h"
#include "renderer.h"
#include <string>
#include <iostream>

#include <nds.h>

#include "bird_spritesheet.h"

Bird::Bird() {
    x = 128;
    y = 0;
    alive = true;
    collided = false;

    // Load sprite graphics into VRAM
    spriteGfx = oamAllocateGfx(&oamMain, SpriteSize_32x16, SpriteColorFormat_256Color);  // Use 16Color format
    dmaCopy(bird_spritesheetTiles, spriteGfx, bird_spritesheetTilesLen);
    dmaCopy(bird_spritesheetPal, SPRITE_PALETTE, bird_spritesheetPalLen);
}

bool Bird::GetAlive(){
    return true; // so never dies
    //return alive; - OBS!! TEMP off
}

void Bird::SetCollided(){
    collided = true;
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
        //alive = false; - OBS!! TEMP off
        
        //sprite_path = "assets/images/bird_sprite_2.png"; - placeholder
    }
}

void Bird::Fly(){
    if (!collided || invincible) {
        velocity = -6.0;
        if (velocity < -2) {
            //sprite_path = "assets/images/bird_sprite_3.png"; -  placeholder
        }
    }
}

void Bird::Fall(){
    velocity += gravity;
    y += velocity;
    if (velocity > 3.5) {
        velocity = 3.5;
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
    int tileOffset = 0;

    if (velocity > -2) {
        tileOffset = 512; // skip the first sprite (32x16 = 512 bytes for 256-color)
    }

    oamSet(&oamMain, 0, x, y, 0, 0, SpriteSize_32x16, SpriteColorFormat_256Color,
        (u16*)((u8*)spriteGfx + tileOffset), -1, false, false, false, false, false);

}

float Bird::GetX(){
    return x;
}

float Bird::GetY(){
    return y;
}