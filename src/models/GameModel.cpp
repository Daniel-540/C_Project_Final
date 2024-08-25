#include "include/models/GameModel.h"
#include <ncurses.h>
#include <stdlib.h>
#include <algorithm> 


GameModel::GameModel(): width(40), height(24), player(width / 2, height - 2, 3) {
    int rows = 3;
    int cols = 8;
    int startX = 2;
    int startY = 2;
    int spacingX = 4;
    int spacingY = 2;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            aliens.emplace_back(startY + r * spacingY, startX + c * spacingX, 20);
        }
    }
}

const std::vector<Bullet>& GameModel::getBullets() const { return bullets; }
const std::vector<Bullet>& GameModel::getAlienBullets() const { return alienBullets; }
const std::vector<Alien>& GameModel::getAliens() const { return aliens; }

int GameModel::getGameWidth() { 
    return width; 
}

int GameModel::getGameHeight() { 
    return height; 
}

Player& GameModel::getPlayer() { 
    return player; 
}

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


void GameModel::update_bullets() {
    for (auto &bullet : bullets) {
        bullet.move(-1);
    }
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](Bullet &b) { return b.isOffScreen(); }), bullets.end());
}

void GameModel::simulate_game_step() {
    // Update player bullets
    update_bullets();
    
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

    // Update alien bullets
    for (auto &bullet : alienBullets) {
        bullet.move(1);
    }
    alienBullets.erase(std::remove_if(alienBullets.begin(), alienBullets.end(),
        [](Bullet &b) { return b.isOffScreen(); }), alienBullets.end());

    for (auto &alien : aliens) {
        if (alien.getY() > height) {
            toggleGameOver();
        }
    }
    // Check collisions
    check_collisions();

    // Notify view of updates
    notifyUpdate();
}

void GameModel::check_collisions() {
    for (auto &bullet : bullets) {
        for (auto &alien : aliens) {
            if (alien.isAlive() && bullet.getX() == alien.getX() && bullet.getY() == alien.getY()) {
                alien.destroy();
                player.setScore(player.getScore()+alien.getScoreForKill());
                // Remove bullet after collision
                bullet.setY(-1); // Mark bullet as off-screen
            }
        }
    }
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](Bullet &b) { return b.isOffScreen(); }), bullets.end());

    for (auto &alienBullet : alienBullets) {
        if (alienBullet.getX() == player.getX() && alienBullet.getY() == player.getY()) {
            player.setLives(player.getLives()-1);
            if (!player.isAlive()) {
                toggleGameOver();
            }
            alienBullet.setY(-1);
        }
    }

    for (auto &alien : aliens) {
        if (alien.getX() == player.getX() && alien.getY() == player.getY()) {
            toggleGameOver();
        }
    }
}

void GameModel::shoot() { bullets.emplace_back(player.getY(), player.getX(), -1); }

void GameModel::move_aliens() {
    bool needToMoveDown = false;

    // Check if any alien is at the screen edge
    for (auto &alien : aliens) {
        if (alien.isAlive()) {
            if ((dir == 1 && alien.getX() >= width - 2) || (dir == -1 && alien.getX() <= 1)) {
                needToMoveDown = true;
                break;
            }
        }
    }

    // Move aliens sideways or down
    for (auto &alien : aliens) {
        if (alien.isAlive()) {
            if (needToMoveDown) {
                alien.move(0, 1); // Move down
            } else {
                alien.move(dir, 0); // Move sideways
            }
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
        if (alien.isAlive() && rand() % 100 < 10) { // 10% chance per alien to shoot
            alienBullets.emplace_back(alien.getY() + 1, alien.getX(), 1);
        }
    }
}

bool GameModel::isGameOver() {
    return gameOver;
}

void GameModel::toggleGameOver() {
    gameOver = !gameOver;
}
