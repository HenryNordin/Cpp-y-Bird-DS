#include "controller.h"
//#include "SDL.h"
#include <iostream>
#include "bird.h"

Controller::Controller() {
    //Code
}

void Controller::HandleInput(bool &running, Bird &bird) const {
    // SDL_Event e;
    // // Calls for bird to fly when buttons pressed
    // while (SDL_PollEvent(&e)) {
    // if (e.type == SDL_QUIT) {
    //     running = false;
    // } else if (e.type == SDL_KEYDOWN) {
    // switch (e.key.keysym.sym) {
    //     case SDLK_UP:
    //     case SDLK_SPACE:
    //         bird.Fly();
    //         break;
    //     }
    // }
    // }
}