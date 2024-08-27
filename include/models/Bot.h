#ifndef BOT_H_
#define BOT_H_

#include "./GameModel.h"

class Bot {
    GameModel* model;
private:
    bool enabled = false;
    bool checkBullets(int laneToCheck);
    int checkPowerUps();
    int searchForBulletFreeLane(int lane);
    int checkDirection(int lane, int dir);
    int shootCounter = 0;
public:
    Bot(GameModel* model);
    void toggle();
    bool isEnabled();
    void play();
};

#endif