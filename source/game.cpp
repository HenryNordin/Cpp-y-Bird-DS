#include "game.h"
#include <iostream>
int score = 0;
Game::Game(std::size_t grid_width, std::size_t grid_height)
    : pipe1(512.0f, true), pipe2(656.0f, false)
{
    running = false;   
}

void Game::Run(Controller const &controller, Renderer &renderer, double MsPerFrame){
    running = true;
    //unsigned int frame_start;
    //unsigned int frame_end;
    //unsigned int frame_duration;
    int frame_count = 0;

    while(running) {
        consoleClear();
        iprintf("X: %d, Y: %d\n", (int)bird.GetX(), (int)bird.GetY());

        controller.HandleInput(running, bird);
        Update();
        renderer.Render(bird, pipe1, pipe2);

        frame_count++;
    }
}


void Game::Update() {
    bird.Update();
    pipe1.Update(); 
    pipe2.Update();

    if (bird.GetAlive() == false){
        running = false;
    }
    CollisionDetection(bird, pipe1, pipe2);
}

void Game::CollisionDetection(Bird& bird, Pipe pipe1, Pipe pipe2) {
    bool collided = false;
    collided = pipe1.CollideWithBird(bird) || pipe2.CollideWithBird(bird);
    if (collided) {
        bird.SetCollided();
    }
}

int Game::GetScore() const { return score;}