#include "../../include/controller/controller_console.h"
#include "../../include/models/Bot.h"

ConsoleController::ConsoleController(GameModel* model, bool isBotEnabled) {
	this->model = model;
    this->isBotEnabled = isBotEnabled;
    this->bot = new Bot(model);
};


/* The functionality of the controller and the model is now separated, 
so the handling of input is independent of the model functions. 
This way, one could also accept other inputs via the controller 
and would only need to configure which input calls which function of 
the model, without having to change the model. */
wchar_t ConsoleController::getInput() {
    wchar_t ch = getch();
    wchar_t newCh;
    if (!isGamePaused()) {
        if (ch == 'b') {model->toggleBot(); this->isBotEnabled = !this->isBotEnabled;}
        if (!isBotEnabled) {
            if (ch == KEY_LEFT) {model->movePlayerLeft();} 
            else if (ch == KEY_RIGHT) {model->movePlayerRight();}
            else if (ch == ' ') {model->playerShoot();}
        } else {
            bot->play();
        }
    }
    if (ch == 'q') {newCh = 'q';}
    else if (ch == 'c') {model->continueGame();}

    return newCh; 
}

bool ConsoleController::isGamePaused() { return model->isGamePaused(); }  // Return whether the game is paused.


