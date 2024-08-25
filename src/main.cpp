#include <ncurses.h>
#include <stdlib.h>
#include <iostream>

#include "models/GameModel.h"
#include "view/view_console.h"
#include "controller/controller_console.h"

int main() {
    GameModel* simplegame = new GameModel();
    ConsoleView* view = new ConsoleView(simplegame);
    ConsoleController* controller = new ConsoleController(simplegame);
    wchar_t ch = '\0';
    while(ch != 'q' && !simplegame->isGameOver()) {
        ch = controller->getInput();
        simplegame->simulate_game_step();
    }
    delete simplegame;
    delete view;
    return 0;
}