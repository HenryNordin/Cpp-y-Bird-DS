#ifndef PIPE_H
#define PIPE_H

#include <string>
//#include "SDL.h"
#include "bird.h"

class Pipe {
    public:
        Pipe(float x_start, bool initial);
        void Update();
        void DrawYourself(Renderer &renderer, int baseId);
        //SDL_Renderer* renderer);
        bool CollideWithBird(Bird bird);
    private:
        float x, upper_y, lower_y, x_start;
        const float pipe_gap = 380;
        void MoveLeft();
        float UpperYGenerator();

        bool offscreen;
        //std::string sprite_path;
        //SDL_Texture* sprite;
        bool initial;
        u16* spriteGfx;
};

#endif