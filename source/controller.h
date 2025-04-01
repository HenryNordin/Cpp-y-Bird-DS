#ifndef CONTROLLER_H
#define CONTROLLER_H

//#include "SDL.h"
#include "bird.h"

class Controller {
    public:
        Controller();
        void HandleInput(bool &running, Bird &bird) const;
    private:
};

#endif