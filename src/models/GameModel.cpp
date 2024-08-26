#include "../../include/models/GameModel.h"
#include <ncurses.h>
#include <stdlib.h>
#include <algorithm> 
#include <vector>

GameModel::GameModel(): width(40), height(24), player(width / 2, 22, 3) {
    int rows = 3;
    int cols = 8;
    int startX = 2;
    int startY = 2;
    int spacingX = 4;
    int spacingY = 2;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            aliens.emplace_back(startY + r * spacingY, startX + c * spacingX, 30);
        }
    }
}

const std::vector<Bullet>& GameModel::getBullets() const { return bullets; }
const std::vector<Bullet>& GameModel::getAlienBullets() const { return alienBullets; }
const std::vector<Alien>& GameModel::getAliens() const { return aliens; }
const std::vector<PowerUp>& GameModel::getPowerUps() const { return powerUps; }

int GameModel::getGameWidth() { 
    return width; 
}

int GameModel::getGameHeight() { 
    return height; 
}

Player& GameModel::getPlayer() { 
    return player; 
}

int GameModel::getLevel() {return level;}
void GameModel::setLevel(int newLevel) {level = newLevel;}

void GameModel::control_player(wchar_t ch)
{
    if (ch == KEY_LEFT) {
        player.setX(player.getX() - 1);
    } else if (ch == KEY_RIGHT) {
        player.setX(player.getX() + 1);
    } else if (ch == ' ') { // Space bar as shooting key
        shoot(); 
    }

    // Prevent the player from moving off-screen
    if (player.getX() < 1) player.setX(1);
    if (player.getX() > width - 2) player.setX(width - 2);
}


void GameModel::update_bullets(std::vector<Bullet>& bulletArr) {
    for (auto &bullet : bulletArr) {
        bullet.move(bullet.getVelocityY());
    }
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i].isOffScreen(height)) {
            bullets.erase(bullets.begin()+i);
        }
    }
}

void GameModel::simulate_game_step() {
    if(!gameOver) {
        if(aliens.size() == 0) {
            newLevel()
        }
        
        // Update player bullets
        update_bullets(bullets);
        
        // Move aliens after a certain delay
        alienMoveCounter++;
        if (alienMoveCounter >= alienMoveDelay) {
            move_aliens();
            alienMoveCounter = 0;
        }

        // Aliens shoot after a certain delay
        alienShootCounter++;
        if (alienShootCounter >= alienShootDelay) {
            alien_shoot();
            alienShootCounter = 0;
        }

        powerUpMoveCounter++;
        if (powerUpMoveCounter >= powerUpMoveDelay) {
            powerUpMove();
            powerUpMoveCounter = 0;
        }

        // Update alien bullets
        update_bullets(alienBullets);

        // Check collisions
        check_collisions();

        // Notify view of updates
    }

    notifyUpdate();
}

void GameModel::check_collisions() {
    for (auto &bullet : bullets) {
        for (int i = 0; i < aliens.size(); i++) {
            auto alien = aliens[i];
            if (bullet.getX() == alien.getX() && bullet.getY() == alien.getY()) {
                player.setScore(player.getScore()+alien.getScoreForKill());
                if (rand() % 100 < 20) {
                    powerUps.emplace_back(alien.getX(), alien.getY(), 1);
                }
                // Remove bullet after collision
                bullet.setY(-1); // Mark bullet as off-screen
                aliens.erase(aliens.begin()+i);
            }
        }
    }

    for (auto &alienBullet : alienBullets) {
        if (alienBullet.getX() == player.getX() && alienBullet.getY() == player.getY()) {
            player.setLives(player.getLives()-1);
            if (!player.isAlive()) {
                setGameOver();
            }
            alienBullet.setY(height+1);
        }
    }

    for (auto &alien : aliens) {
        if (alien.getY() == player.getY()) {
            setGameOver();
        }
    }

    for (int i = 0; i < powerUps.size(); i++) {
        if (powerUps[i].getX() == player.getX() && powerUps[i].getY() == player.getY()) {
            powerUps.erase(powerUps.begin()+i);
            player.setLives(player.getLives()+2);
        }
    }
}

void GameModel::shoot() { bullets.emplace_back(player.getY(), player.getX(), -1); }

void GameModel::move_aliens() {
    bool needToMoveDown = false;

    // Check if any alien is at the screen edge
    for (auto &alien : aliens) {
        if ((dir == 1 && alien.getX() >= width - 2) || (dir == -1 && alien.getX() <= 1)) {
            needToMoveDown = true;
            break;
        }
    }

    // Move aliens sideways or down
    for (auto &alien : aliens) {
        if (needToMoveDown) {
            alien.move(0, 1); // Move down
            if (alien.getY() > height) { //Check if any alien hits bottom border
                setGameOver();
                break;
            }
        } else {
            alien.move(dir, 0); // Move sideways
        }
    }

    // Change direction after moving down
    if (needToMoveDown) {
        dir *= -1;
    }
}

void GameModel::alien_shoot() {
    // Randomly select aliens to shoot
    for (auto &alien : aliens) {
        if (rand() % 100 < 10) { // 10% chance per alien to shoot
            alienBullets.emplace_back(alien.getY() + 1, alien.getX(), 1);
        }
    }
}

void GameModel::powerUpMove() {
    for (int i = 0; i < powerUps.size(); i++) {
        powerUps[i].move();
        if (powerUps[i].isOffScreen(height)) {
            powerUps.erase(powerUps.begin()+i);
        }
    }
}

bool GameModel::isGameOver() {
    return gameOver;
}

void GameModel::setGameOver() {
    gameOver = true;
}
