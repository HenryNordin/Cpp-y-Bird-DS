#include "controller.h"
#include <nds.h>

#include <iostream>
#include "bird.h"

Controller::Controller() {}

void Controller::HandleInput(bool &running, Bird &bird) const {
    scanKeys();
    u16 keys = keysHeld();  // Get currently held buttons
    
    touchPosition touch;     // Create touchPosition struct
    touchRead(&touch);       // Read touch input
    u16 keysDownNow = keysDown();

    if ((keys & KEY_A) || (keys & KEY_TOUCH)) {  
        bird.Fly();  // Make the bird fly when "A" is pressed
        bird.SetStarted(true);
    }

    if (keys & KEY_START) {  
        running = false;  // Allow exiting the game with START
    }
}