#include "../../include/controller/controller_console.h"

ConsoleController::ConsoleController(GameModel* model) {
	this->model = model;
};

// !!! NEEDS REWORK: Anweisungen an Model sollen allgemein sein, es soll nicht die Eingabe weitergeleitet werden,
// damit Model und Controller unabhängig voneinander sind.
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


