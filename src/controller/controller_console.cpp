#include "../../include/controller/controller_console.h"
#include "../../include/models/Bot.h"

ConsoleController::ConsoleController(GameModel* model, bool isBotEnabled) {
	this->model = model;
    this->isBotEnabled = isBotEnabled;
    this->bot = new Bot(model);
};

wchar_t ConsoleController::getInput() {
    wchar_t ch = getch();
    wchar_t newCh;
    if (ch == 'b') {model->toggleBot(); this->isBotEnabled = !this->isBotEnabled;}
    if (!isBotEnabled) {
        if (ch == KEY_LEFT) {model->movePlayerLeft();} 
        else if (ch == KEY_RIGHT) {model->movePlayerRight();}
        else if (ch == ' ') {model->playerShoot();}
        else if (ch == 'q') {newCh = 'q';}
        else if (ch == 'c') {model->continueGame();}
        //model->control_player(newCh);
    } else {
        if (ch == KEY_LEFT) {bot->play();} 
        else if (ch == KEY_RIGHT) {bot->play();}
        else if (ch == ' ') {bot->play();}
        else if (ch == 'q') {newCh = 'q';}
        else if (ch == 'c') {model->continueGame();}
    }
    return newCh; 
}


