#include "../../include/controller/controller_console.h"

ConsoleController::ConsoleController(GameModel* model) {
	this->model = model;
};

wchar_t ConsoleController::getInput() {
    wchar_t ch = getch();
    wchar_t newCh;
    if (ch == KEY_LEFT) {newCh = 'L';} 
    else if (ch == KEY_RIGHT) {newCh = 'R';}
    else if (ch == ' ') {newCh = ' ';}
    else if (ch == 'q') {newCh = 'q';}
    else if (ch == 'c') {newCh = 'C';}
    else if (ch == 'b') {newCh = 'B';}
    model->control_player(newCh);
    return newCh; // Removed the duplicate return statement
}


