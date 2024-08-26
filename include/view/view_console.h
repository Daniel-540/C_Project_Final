#pragma once  // #pragma once directive added to avoid multiple inclusions of header files

#include "../observer.h"  // Include Observer header file
#include "../models/GameModel.h"  // Include GameModel header file
#include <ncurses.h>
#include <string>

class ConsoleView : public Observer  // Inheriting from Observer class
{
    GameModel* model;  // Pointer variable of GameModel class

public:
    ConsoleView(GameModel* model);  // Constructor of ConsoleView class

    virtual ~ConsoleView();  // Virtual destructor of ConsoleView class

    void update();  // Function to update the screen

    void drawPlayer(int y, int x);  // Function to draw the player

    void drawBullet(int y, int x);

    void drawAlien(int y, int x);

    void drawLives(int lives);

    void drawScore(int score);

    void drawLevel(int level);

    void drawPowerUp(int y, int x);

    void printMessage(int y, int x, std::string msg);

private:
    // Textures
    char wallTexture = 'X';  // Wall texture character

    void setup_view();  // Function to set up the view
};
