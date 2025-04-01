#include "game.h"
//#include "SDL.h"
#include <iostream>
int score = 0;
Game::Game(std::size_t grid_width, std::size_t grid_height)
    : pipe1(400.0f), pipe2(625.0f)
{
    running = false;   
}

void Game::Run(Controller const &controller, Renderer &renderer, double MsPerFrame){
    running = true;
    unsigned int frame_start;
    unsigned int frame_end;
    unsigned int frame_duration;
    int frame_count = 0;
    

    while(running) {
        //frame_start = SDL_GetTicks();
        controller.HandleInput(running, bird);
        Update();
        renderer.Render(bird, pipe1, pipe2);
        //frame_end = SDL_GetTicks();

        frame_count++;
        frame_duration = frame_end - frame_start;
        if (frame_duration < MsPerFrame) {
            //SDL_Delay(MsPerFrame - frame_duration);
        }
    }

}


void Game::Update() {
    //std::cout << "Test" << std::endl;
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