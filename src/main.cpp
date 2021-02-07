#include <game_application.h>



int main() {
    //create game:
    auto game = GameApplication();
    //run game loop:
    game.gameRunLoop();
    return 0;
}

    