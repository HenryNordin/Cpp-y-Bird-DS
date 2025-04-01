#include "pipe.h"
//#include "SDL.h"
//#include "SDL_image.h"
#include <string>
#include <iostream>
#include <random>

Pipe::Pipe(float x_start) {
    x = x_start;
    upper_y = UpperYGenerator();
    lower_y = upper_y + pipe_gap;
    offscreen = false;
}

void Pipe::Update(){
    MoveLeft();
}

void Pipe::DrawYourself(){
    //SDL_Renderer* renderer){
    // sprite_path = "assets/images/pipe_sprite.png";
    // sprite = IMG_LoadTexture(renderer, sprite_path.c_str());

    // int textureWidth, textureHeight;
    // SDL_QueryTexture(sprite, nullptr, nullptr, &textureWidth, &textureHeight);
    // SDL_Rect srcRect1 = { 0, 0, textureWidth, textureHeight };
    // SDL_Rect destRect1 = { static_cast<int>(x), static_cast<int>(upper_y), 64, 256 };
    // SDL_RenderCopy(renderer, sprite, &srcRect1, &destRect1);

    // SDL_QueryTexture(sprite, nullptr, nullptr, &textureWidth, &textureHeight);
    // SDL_Rect srcRect2 = { 0, 0, textureWidth, textureHeight };
    // SDL_Rect destRect2 = { static_cast<int>(x), static_cast<int>(lower_y), 64, 256 };

    // SDL_RenderCopy(renderer, sprite, &srcRect2, &destRect2);
    // SDL_DestroyTexture(sprite);
}

void Pipe::MoveLeft(){
    if (offscreen == false) {
        x -= 4.0f;
    }
    if (x <= -64.0f){
        offscreen = true;
        x = 400.0f;
        upper_y = UpperYGenerator();
        lower_y = upper_y + pipe_gap;
    }

    if (x == 400.0f){
        offscreen = false;
    }
}

float Pipe::UpperYGenerator(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, (600 - 2 * 32 - pipe_gap));

    return dis(gen) - 100.0f;
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