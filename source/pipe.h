#ifndef PIPE_H
#define PIPE_H

#include <string>
#include "bird.h"

class Pipe {
    public:
        Pipe(float x_start, bool initial);
        void Update();
        void DrawYourself(int baseId);
        bool CollideWithBird(Bird bird);
        void Reset();

        int GetScore();
        
        void SetScore(int value);

    private:
        float x, upper_y, lower_y, x_start;
        const float pipe_gap = 128;
        void MoveLeft();
        float UpperYGenerator();

        bool offscreen;
        bool initial;
        u16* spriteGfx;

        int score = 0;
};

#endif