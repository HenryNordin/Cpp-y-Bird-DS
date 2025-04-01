#ifndef RENDERER_H
#define RENDERER_H

//#include "SDL.h"
#include "bird.h"
#include "pipe.h"

class Renderer {
    public:
        Renderer(int ScreenWidth, int ScreenHeight);
        ~Renderer();
        void Render(Bird &bird, Pipe &pipe_1, Pipe &pipe_2);

    private:
        //SDL_Window *sdl_window;
        //SDL_Renderer *sdl_renderer;

        void DrawBackground();
            //SDL_Renderer* renderer);
        void DrawGround();
            //SDL_Renderer* renderer);

        void Update();

};

#endif