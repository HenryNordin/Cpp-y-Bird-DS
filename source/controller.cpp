#include "controller.h"
#include <nds.h>

#include <iostream>
#include "bird.h"

Controller::Controller() {}

void Controller::HandleInput(bool &running, Bird &bird, int &highScore) const {
    scanKeys();
    u32 keys = keysHeld();  // Get currently held buttons
    touchPosition touch;     // Create touchPosition struct
    touchRead(&touch);       // Read touch input


    // Score reset
    bool allHeld = (keys & (KEY_X | KEY_B | KEY_L | KEY_R)) == 
                   (KEY_X | KEY_B | KEY_L | KEY_R);
    if (allHeld) {
        consoleClear();
        iprintf("\n\n\n      You want to reset\n   your current highscore?!\n\n");
        iprintf("    Well.. then continue \n  holding and now press SELECT!");
        if (keys & KEY_SELECT) {
            consoleClear();
            iprintf("\n\n\n         SCORE RESET!!\n\n");
            highScore = 0;
        }
    }

    // Bird controlls
    if ((keys & KEY_A) || (keys & KEY_TOUCH)) {  
        bird.Fly();  // Make the bird fly when "A" is pressed
        bird.SetStarted(true);
    }

    if (keys & KEY_START) {  
        running = false;  // Allow exiting the game with START
    }
}