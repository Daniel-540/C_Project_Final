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
                model->setMsg("Error");
            } else {
                model->setMsg("dodging left");
                player.setX(player.getX()-1);
            }

        } else {
            model->setMsg("dodging right");
            model->getPlayer().setX(model->getPlayer().getX()+1);
        }
    } else {
        if (shootCounter >= 2) {
            model->shoot();
            shootCounter = 0;
        } else {
            int alienPositionX = model->getAliens()[0].getX();
            int alienPositionY = model->getAliens()[0].getY();
            int direction = alienPositionX;
            if (model->getPlayer().getY()-alienPositionY >= 20) {
                direction+=4*model->getDir();
            } else if (model->getPlayer().getY()-alienPositionY >= 15) {
                direction+=3*model->getDir();
            } else if (model->getPlayer().getY()-alienPositionY >= 10) {
                direction+=2*model->getDir();
            } else if (model->getPlayer().getY()-alienPositionY >= 5) {
                direction+=1*model->getDir();
            }

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