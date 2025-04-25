#ifndef GAME_H
#define GAME_H

//#include "SDL.h"

#include "controller.h"
#include "renderer.h"
#include "bird.h"
#include "pipe.h"


class Game {
    public:
        Game(std::size_t grid_width, std::size_t grid_height);
        void Run(Controller const &controller, Renderer &renderer, double MsPerFrame);
        int GetScore() const;

    private:
        bool running;
        int score;
        int highScore;
        Bird bird;
        Pipe pipe1;
        Pipe pipe2;
        void Update();
        void Reset();
        void CollisionDetection(Bird& bird, Pipe pipe1, Pipe pipe2);

};

#endif