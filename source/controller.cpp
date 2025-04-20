#include "controller.h"
//#include "SDL.h"
#include <nds.h>

#include <iostream>
#include "bird.h"

Controller::Controller() {
    //Code
}

void Controller::HandleInput(bool &running, Bird &bird) const {
    scanKeys();
    u16 keys = keysHeld();  // Get currently held buttons

    if (keys & KEY_A) {  
        bird.Fly();  // Make the bird fly when "A" is pressed
    }

    if (keys & KEY_START) {  
        running = false;  // Allow exiting the game with START
    }
}