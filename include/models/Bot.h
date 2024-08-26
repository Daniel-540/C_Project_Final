#ifndef BOT_H_
#define BOT_H_

#include "./GameModel.h"

class Bot {
    GameModel* model;
private:
    bool enabled = false;
    bool checkBullets(int laneToCheck);
    int shootCounter = 0;
public:
    Bot(GameModel* model);
    void toggle();
    bool isEnabled();
    void play();
};

#endif