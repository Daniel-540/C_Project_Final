#include "../../include/models/Bot.h"
#include "../../include/models/Player.h"

Bot::Bot(GameModel* model) : model(model) {}

void Bot::toggle() {enabled = !enabled;}

bool Bot::isEnabled() {return enabled;}

void Bot::play() {
    auto player = model->getPlayer();
    if (checkBullets(player.getX())) {
        if (checkBullets(player.getX()+1) || (player.getX()+1 >= model->getGameWidth())) {
            if (checkBullets(player.getX()-1) || player.getX()-1 <= 0) {
                model->setMsg("[Bot]: couldnt dodge");
            } else {
                model->setMsg("[Bot]: dodging left");
                player.setX(player.getX()-1);
            }

        } else {
            model->setMsg("[Bot]: dodging right");
            model->getPlayer().setX(model->getPlayer().getX()+1);
        }
    } else {
        if (shootCounter >= 5) {
            model->shoot();
            shootCounter = 0;
        } else {
            auto nearestAlien = std::min_element(model->getAliens().begin(), model->getAliens().end(),
                                        [](const Alien& a, const Alien& b) {
                                            return a.getY() > b.getY();
                                        });
            int alienPositionX = nearestAlien->getX();
            int alienPositionY = nearestAlien->getY();
            int direction;
            
            if (model->getPowerUps().size() > 0) {
                auto nearestPowerUp = std::min_element(model->getPowerUps().begin(), model->getPowerUps().end(),
                                        [](const PowerUp& a, const PowerUp& b) {
                                            return a.getY() > b.getY();
                                        });
                if (player.getY() - nearestAlien->getY() > 5 && (player.getY() - nearestPowerUp->getY() <= (int)(std::abs(player.getX() - nearestPowerUp->getX())/4))) {
                    direction = nearestPowerUp->getX();
                } else {
                    direction = alienPositionX+((int)(static_cast<float>(player.getY()-alienPositionY)/5.0))*model->getDir();
                }
            } else {
                direction = alienPositionX+((int)(static_cast<float>(player.getY()-alienPositionY)/5.0))*model->getDir();
            }
            model->setMsg("[Bot] aiming at: "+std::to_string(direction));

            if (direction < model->getPlayer().getX() && !checkBullets(player.getX()-1)) {
                model->getPlayer().setX(model->getPlayer().getX()-1);
            } else if (direction > model->getPlayer().getX() && !checkBullets(player.getX()+1)) {
                model->getPlayer().setX(model->getPlayer().getX()+1);
            }
        }
        shootCounter++;
    }
    
}

bool Bot::checkBullets(int laneToCheck) {
    for (auto alienBullet : model->getAlienBullets()) {
        if(alienBullet.getY() > model->getPlayer().getY()-3) {
            if(laneToCheck == alienBullet.getX()) {
                return true;
            }
        }
    }
    return false;
}