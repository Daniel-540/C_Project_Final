#include "../../include/controller/controller_console.h"

ConsoleController::ConsoleController(GameModel* model) {
	this->model = model;
};

// !!! NEEDS REWORK: Anweisungen an Model sollen allgemein sein, es soll nicht die Eingabe weitergeleitet werden,
// damit Model und Controller unabhängig voneinander sind. !!!
wchar_t ConsoleController::getInput() {
    wchar_t ch = getch();
    wchar_t newCh;
    if (ch == KEY_LEFT) {model->movePlayerLeft();} 
    else if (ch == KEY_RIGHT) {model->movePlayerRight();}
    else if (ch == ' ') {model->playerShoot();}
    else if (ch == 'q') {newCh = 'q';}
    else if (ch == 'c') {model->continueGame();}
    else if (ch == 'b') {model->toggleBot();}
    //model->control_player(newCh);
    return newCh; 
}


