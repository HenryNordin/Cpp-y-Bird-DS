#include "bird.h"
//#include "SDL.h"
//#include "SDL_image.h"
#include <string>
#include <iostream>

Bird::Bird() {
    x = 175;
    y = 0;
    alive = true;
    collided = false;
    //sprite = nullptr;
    sprite_path = "assets/images/bird_sprite_1.png";
}

bool Bird::GetAlive(){
    return alive;
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
    if (y >= 450)
    {
        y = 450;
        velocity = 0;
        alive = false;
        sprite_path = "assets/images/bird_sprite_2.png";
    }
}

void Bird::Fly(){
    if (!collided || invincible) {
        velocity = -10.0;
        if (velocity < -2) {
            sprite_path = "assets/images/bird_sprite_3.png";
        }
    }
}

void Bird::Fall(){
    velocity += gravity;
    y += velocity;
    if (velocity > 7) {
        velocity = 7;
    }
    if (velocity > 2) {
        sprite_path = "assets/images/bird_sprite_2.png";
    }
    //std::cout << "x: " << x << " y: "<<y<< " velocity: "<< velocity << std::endl;
}

void Bird::Update(){
    if (alive) {
        Fall();
    }
    GroundCollision();
    RoofCollision();
}

void Bird::DrawYourself( ){
    //SDL_Renderer* renderer) {
    // // Try to load the texture
    // sprite = IMG_LoadTexture(renderer, sprite_path.c_str());

    // // If failed it draws a red square
    // if (sprite == nullptr) {
    //     std::cerr << "Error loading texture: " << IMG_GetError() << std::endl;
    //     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //     SDL_Rect squareRect = { static_cast<int>(x), static_cast<int>(y), 32, 32 };
    //     SDL_RenderFillRect(renderer, &squareRect); 
    //     return;
    // }

    // // Get the texture dimensions
    // int textureWidth, textureHeight;
    // SDL_QueryTexture(sprite, nullptr, nullptr, &textureWidth, &textureHeight);
    // SDL_Rect srcRect = { 0, 0, textureWidth, textureHeight };
    // SDL_Rect destRect = { static_cast<int>(x), static_cast<int>(y), 32, 32 }; // Positioning the bird

    // SDL_RenderCopy(renderer, sprite, &srcRect, &destRect);
    // SDL_DestroyTexture(sprite);
}

float Bird::GetX(){
    return x;
}

float Bird::GetY(){
    return y;
}