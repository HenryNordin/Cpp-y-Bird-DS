#include <nds.h>

#include "renderer.h"
#include "game.h"
#include "controller.h"

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------
	const int screen_width{256};
    const int screen_height{192};
    const int FPS{60};
    const double MsPerFrame{1000/FPS};

    Renderer renderer(screen_width, screen_height);
    Controller controller;
    // Height, Width
    Game game(screen_width, screen_height);
    game.Run(controller, renderer, MsPerFrame);

	return 0;
}
