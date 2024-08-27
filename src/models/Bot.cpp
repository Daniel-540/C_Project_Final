#include "../../include/models/Bot.h"
#include "../../include/models/Player.h"
#include "../../include/models/GameModel.h"
#include <algorithm>

// Constructor for the Bot class, initializing with a reference to the game model.
Bot::Bot(GameModel* model) : model(model) {}

// Method to toggle the bot's enabled state (on or off).
void Bot::toggle() {
    enabled = !enabled; // Toggle the enabled state of the bot.
}

// Method to check if the bot is enabled.
bool Bot::isEnabled() {
    return enabled; // Return the current state of the bot (enabled or disabled).
}

void Bot::play() {
    auto player = model->getPlayer(); 
    auto nearestAlien = std::min_element(model->getAliens().begin(), model->getAliens().end(),
                                [](const Alien& a, const Alien& b) {
                                    return a.getY() > b.getY();
                                });
    int alienPositionX = nearestAlien->getX();
    int alienPositionY = nearestAlien->getY();
    int direction;
    if (checkBullets(model->getPlayer().getX())) {
        direction = searchForBulletFreeLane(model->getPlayer().getX());
    } else {
        int powerUpDir = checkPowerUps();
        if (powerUpDir >= 0) {
            direction = powerUpDir;
        } else {
            direction = alienPositionX+((int)(static_cast<float>(player.getY()-alienPositionY)/5.0))*model->getDir();
        }
    }
    model->setMsg("[Bot] aiming at: "+std::to_string(direction));

    if (direction < model->getPlayer().getX() && !checkBullets(player.getX()-1)) {
        model->movePlayerLeft();
    } else if (direction > model->getPlayer().getX() && !checkBullets(player.getX()+1)) {
         model->movePlayerRight();
    }

    if (shootCounter >= 0) {
        model->shoot();
        shootCounter = 0;
    }
    shootCounter++;

    
}

// Method to check if there are any alien bullets in the specified lane.
bool Bot::checkBullets(int laneToCheck) {
    // Iterate through all alien bullets to check their position.
    for (auto alienBullet : model->getAlienBullets()) {
        if(alienBullet.getY() > model->getPlayer().getY()-2 && alienBullet.getY() <= model->getPlayer().getY()) {
            if(laneToCheck == alienBullet.getX()) {
                return true;
            }
        }
    }
    return false;
}

int Bot::searchForBulletFreeLane(int lane) {
    if (checkBullets(lane)) {
        int right = checkDirection(lane, 1);
        int left = checkDirection(lane, -1);
        if (right > model->getGameWidth()-2) {
            return left;
        }
        if (left < 1) {
            return right;
        }
        if (right - lane > lane - left) {
            return left;
        }
        return right;
    }
    return lane;
}

int Bot::checkDirection(int lane, int dir) {
    if (checkBullets(lane)) {
        return checkDirection(lane+dir, dir);
    }
    return lane;
}

int Bot::checkPowerUps() {
    if (model->getPowerUps().size() > 0 && model->getPowerUps()[0].getY() <= model->getPlayer().getY()) {
        auto nearestPowerUp = model->getPowerUps()[0];
        for (auto powerUp : model->getPowerUps()) {
            if (powerUp.getY() <= model->getPlayer().getY()) {
                if (powerUp.getY() > nearestPowerUp.getY()) {
                    nearestPowerUp = powerUp;
                }
            }
        }
        if (model->getPlayer().getY() - nearestPowerUp.getY() <= std::max((int)(std::abs(model->getPlayer().getX() - nearestPowerUp.getX())/4), 5)) {
            return nearestPowerUp.getX();
        }
        return -1;
    }
    return -1;
}