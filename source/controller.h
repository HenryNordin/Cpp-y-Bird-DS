#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "bird.h"

class Controller {
    public:
        Controller();
        void HandleInput(bool &running, Bird &bird, int &highScore) const;
    private:
};

#endif