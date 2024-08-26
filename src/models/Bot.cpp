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
        model->setMsg("");
        if (shootCounter >= 5) {
            model->shoot();
            shootCounter = 0;
        } else {
            int direction = model->getAliens()[0].getX();
            if (direction < model->getPlayer().getX() && !checkBullets(player.getX()-1)) {
                model->getPlayer().setX(model->getPlayer().getX()-1);
            } else if (!checkBullets(player.getX()+1)) {
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