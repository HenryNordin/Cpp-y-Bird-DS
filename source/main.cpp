#include <nds.h>

#include "renderer.h"
#include "game.h"
#include "controller.h"

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------
    // Top Screen
    videoSetMode(MODE_0_2D | DISPLAY_BG0_ACTIVE);
    // map bank A for backgrounds
	vramSetBankA(VRAM_A_MAIN_BG);
    // map bank B for sprites
    vramSetBankB(VRAM_B_MAIN_SPRITE);
    // map bank c for foreground
    //vramSetBankC(VRAM_C_MAIN_BG);

    // Initialize oam
    oamInit(&oamMain, SpriteMapping_1D_32, false);

    // Bottom Screen
    videoSetModeSub(MODE_0_2D);
    vramSetBankH(VRAM_H_SUB_BG);
    consoleDemoInit(); // Console debug output
    BG_PALETTE_SUB[0] = RGB15(13, 7, 6);
    

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
