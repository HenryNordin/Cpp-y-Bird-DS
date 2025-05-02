#include "game.h"
#include <iostream>

#include "savemanager.h"

SaveManager saveManager;
SaveData data;

int score = 0;
Game::Game(std::size_t grid_width, std::size_t grid_height)
    : pipe1(384.0f, true), pipe2(528.0f, false)
{
    running = false;   
    score = 0;
    data = saveManager.Load();
    highScore = data.highscore; // Load saved highscore
}

void Game::Run(Controller const &controller, Renderer &renderer, double MsPerFrame){
    running = true;
    //unsigned int frame_start;
    //unsigned int frame_end;
    //unsigned int frame_duration;
    int frame_count = 0;

    while(running) {
        consoleClear();
        //iprintf("X: %d, Y: %d\n", (int)bird.GetX(), (int)bird.GetY());
        iprintf("\n\n\n         High Score: %d\n", highScore);
        iprintf("            Score: %d", score);

        if (!bird.GetStarted()){
            iprintf("\n\n\n   Touch or press A to play!");
        }

        controller.HandleInput(running, bird, highScore);
        Update();
        renderer.Render(bird, pipe1, pipe2);
        //pipe1.PointUp();
        frame_count++;
    }
}


void Game::Update() {
    if (bird.GetAlive() == false){
        //iprintf("Dead");
        //running = false;
        Reset();
    } else {
        bird.Update();
        if (bird.GetStarted()){
            pipe1.Update(); 
            pipe2.Update();

            score = pipe1.GetScore();
            //score = pipe2.GetScore();
            
        }
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


void Game::Reset(){
    bird.Reset();
    pipe1.Reset(); 
    pipe2.Reset();

    if (score > highScore) {
        highScore = score;
        data.highscore = highScore;
        saveManager.Save(data);
    }
}

int Game::GetScore() const { return score;}