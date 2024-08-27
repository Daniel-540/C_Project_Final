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
    void tryDodging(Player &player);
    int calcSensibleDirection(
        Player player, 
        std::vector<Alien>::const_iterator nearestAlien, 
        int alienPositionX, 
        int alienPositionY
    );

    void movePlayer(int direction, Player player);

public:
    Bot(GameModel* model);
    void toggle();
    bool isEnabled();
    void play();
};

#endif