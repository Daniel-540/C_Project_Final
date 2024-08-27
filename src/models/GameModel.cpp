#include "../../include/models/GameModel.h"
#include "../../include/models/Bot.h"
#include <ncurses.h>
#include <stdlib.h>
#include <algorithm> 
#include <vector>
#include <string>
#include <cmath>

// Constructor for the GameModel class, initializing game parameters.
GameModel::GameModel() : width(40), height(24), player(20, 22, 3), bot(new Bot(this)) {
    spawnAliens(1); // Spawn the initial set of aliens.
}

// Getters for different game entities.
std::vector<Bullet>& GameModel::getBullets() { return bullets; }  // Return the list of player bullets.
std::vector<Bullet>& GameModel::getAlienBullets() { return alienBullets; } // Return the list of alien bullets.
std::vector<Alien>& GameModel::getAliens() { return aliens; }  // Return the list of aliens.
std::vector<PowerUp>& GameModel::getPowerUps() { return powerUps; } // Return the list of power-ups.

// Getters for game dimensions.
int GameModel::getGameWidth() { return width; }  // Return the game width.
int GameModel::getGameHeight() { return height; }  // Return the game height.

// Getter for the player object.
Player& GameModel::getPlayer() { return player; }  // Return a reference to the player object.

// Getters and setters for the current game level.
int GameModel::getLevel() { return level; }  // Return the current game level.
void GameModel::setLevel(int newLevel) { level = newLevel; }  // Set the current game level.

// Setters for delays related to alien shooting and bullet movement.
void GameModel::setAlienShootDelay(int delay) { alienShootDelay = delay; }  // Set the delay between alien shots.
void GameModel::setBulletMoveDelay(int delay) { bulletMoveDelay = delay; }  // Set the delay between bullet movements.

// Methods to manage the paused state of the game.
bool GameModel::isGamePaused() { return gamePaused; }  // Return whether the game is paused.
void GameModel::setGamePaused(bool paused) { gamePaused = paused; }  // Set the game paused state.

// Methods for handling game messages.
std::string GameModel::getMsg() { return msg; }  // Return the current game message.
void GameModel::setMsg(std::string newMsg) { msg = newMsg; }  // Set a new game message.

// Get the current direction of alien movement.
int GameModel::getDir() { return dir; }  // Return the direction in which aliens are moving.

void GameModel::movePlayerLeft() {
    player.setX(player.getX() - 1);
    preventMovingOffScreen();
   
}

void GameModel::movePlayerRight() {
    player.setX(player.getX() + 1);
    preventMovingOffScreen();
   
}

void GameModel::playerShoot() {
    shoot(); 
    
}

void GameModel::continueGame() {
    setGamePaused(false);
}

void GameModel::toggleBot() {
    bot->toggle();
}

// Prevent the player from moving off-screen.
void GameModel::preventMovingOffScreen() {
    if (player.getX() < 1) player.setX(1);  // Left boundary check.
    if (player.getX() > width - 2) player.setX(width - 2);  // Right boundary check.
}

// Update the positions of bullets and remove off-screen bullets.
void GameModel::update_bullets(std::vector<Bullet>& bulletArr) {
    for (int i = 0; i < bulletArr.size(); i++) {
        bulletArr[i].move(bulletArr[i].getVelocityY());  // Move each bullet based on its velocity.
        if (bulletArr[i].isOffScreen(height)) {  // Check if the bullet is off-screen.
            bulletArr.erase(bulletArr.begin() + i);  // Remove off-screen bullets.
            i--;  // Adjust the index after erasing an element.
        }
    }
}

// Simulate a single step in the game.
void GameModel::simulate_game_step() {
    if (!gameOver) {
        if (aliens.size() == 0) {
            // Prepare for the next level if all aliens are destroyed.
            setMsg("");  // Clear messages.
            setGamePaused(true);  // Pause the game.
            bullets.clear();  // Clear player bullets.
            alienBullets.clear();  // Clear alien bullets.
            powerUps.clear();  // Clear power-ups.
            newLevel();  // Start a new level.
        }

        if (!gamePaused) {
            // Only update game entities if the game is not paused.
            update_bullets(bullets);  // Update player bullets.
            
            alienMoveCounter++;
            if (alienMoveCounter > alienMoveDelay) {
                move_aliens();  // Move aliens after a delay.
                alienMoveCounter = 0;
            }

            alienShootCounter++;
            if (alienShootCounter > alienShootDelay) {
                alien_shoot();  // Aliens shoot after a delay.
                alienShootCounter = 0;
            }

            powerUpMoveCounter++;
            if (powerUpMoveCounter > powerUpMoveDelay) {
                powerUpMove();  // Move power-ups after a delay.
                powerUpMoveCounter = 0;
            }

            bulletMoveCounter++;
            if (bulletMoveCounter > bulletMoveDelay) {
                update_bullets(alienBullets);  // Update alien bullets after a delay.
                bulletMoveCounter = 0;
            }

            check_collisions();  // Check for collisions between game entities.
        }
    }

    notifyUpdate();  // Notify the game view about the updates.
}

// Check for collisions between bullets, aliens, the player, and power-ups.
void GameModel::check_collisions() {
    // Check for collisions between player bullets and aliens.
    for (auto &bullet : bullets) {  // Use non-const reference
        for (int i = 0; i < aliens.size(); i++) {
            auto &alien = aliens[i];  // Use non-const reference to the alien
            if (bullet.getX() == alien.getX() && bullet.getY() == alien.getY()) {
                player.setScore(player.getScore() + alien.getScoreForKill());  // Increase score.
                
                // 15% chance to spawn a power-up.
                if (rand() % 100 < 15) {
                    powerUps.emplace_back(alien.getX(), alien.getY());
                }
                
                bullet.setY(-1);  // Mark bullet as off-screen after collision.
                aliens.erase(aliens.begin() + i);  // Remove the alien.
                break;  // Stop checking further aliens for this bullet.
            }
        }
    }

    // Check for collisions between alien bullets and the player.
    for (auto &alienBullet : alienBullets) {  // Use non-const reference
        if (alienBullet.getX() == player.getX() && alienBullet.getY() == player.getY()) {
            player.setLives(player.getLives() - 1);  // Decrease player lives.
            
            // End game if player is out of lives.
            if (!player.isAlive()) {
                setGameOver();
            }
            
            alienBullet.setY(height + 1);  // Mark alien bullet as off-screen.
        }
    }

    // Check for collisions between aliens and the player.
    for (auto &alien : aliens) {  // Use non-const reference
        if (alien.getY() == player.getY()) {
            setGameOver();  // End game if any alien reaches the player's row.
        }
    }

    // Check for collisions between power-ups and the player.
    for (int i = 0; i < powerUps.size(); i++) {
        auto &powerUp = powerUps[i];  // Use non-const reference to the power-up
        if (powerUp.getX() == player.getX() && powerUp.getY() == player.getY()) {
            powerUps.erase(powerUps.begin() + i);  // Remove the power-up after collection.
            player.setLives(player.getLives() + 1);  // Increase player lives.
        }
    }
}


// Method to handle player shooting.
void GameModel::shoot() {
    bullets.emplace_back(player.getY(), player.getX(), -1);  // Add a new bullet moving upwards.
}

// Method to move all aliens either sideways or down if they reach screen edge.
void GameModel::move_aliens() {
    bool needToMoveDown = false;

    // Check if any alien is at the screen edge.
    for (auto &alien : aliens) {
        if ((dir == 1 && alien.getX() >= width - 2) || (dir == -1 && alien.getX() <= 1)) {
            needToMoveDown = true;
            break;
        }
    }

    // Move aliens either sideways or down based on the flag.
    for (auto &alien : aliens) {
        if (needToMoveDown) {
            alien.move(0, 1); // Move down.
            if (alien.getY() > height) {
                setGameOver();
                break;
            }
        } else {
            alien.move(dir, 0); // Move sideways.
        }
    }

    if (needToMoveDown) {
        dir *= -1; // Reverse direction.
    }
}

// Aliens randomly shoot bullets.
void GameModel::alien_shoot() {
    // 10% chance for each alien to shoot.
    for (auto &alien : aliens) {
        if (rand() % 100 < 10) {
            alienBullets.emplace_back(alien.getY() + 1, alien.getX(), 1);  // Add a new bullet moving downwards.
        }
    }
}

// Move power-ups down the screen.
void GameModel::powerUpMove() {
    for (int i = 0; i < powerUps.size(); i++) {
        powerUps[i].move();  // Move each power-up.
        if (powerUps[i].isOffScreen(height)) {
            powerUps.erase(powerUps.begin() + i);  // Remove power-ups that are off-screen.
            i--;  // Adjust the index after erasing an element.
        }
    }
}

// Check if the game is over.
bool GameModel::isGameOver() {
    return gameOver;
}

// Set the game state to over.
void GameModel::setGameOver() {
    gameOver = true;
}

// Spawn aliens at the start of the game or new level.
void GameModel::spawnAliens(int rows) {
    int cols = 8;  // Number of columns of aliens.
    int startX = 2;  // Starting X position for the first alien.
    int startY = 2;  // Starting Y position for the first alien.
    int spacingX = 4;  // Horizontal spacing between aliens.
    int spacingY = 2;  // Vertical spacing between aliens.
    int score = level * (100 / alienShootDelay);  // Calculate the score for killing an alien.

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            aliens.emplace_back(startY + r * spacingY, startX + c * spacingX, score);  // Place an alien in the grid.
        }
    }
}

// Set up the game for a new level.
void GameModel::newLevel() {
    setLevel(level + 1);  // Increase the level.
    setAlienShootDelay(std::max(21 - level, 1));  // Decrease alien shoot delay.
    setBulletMoveDelay(std::max(7 - level, 4));  // Decrease bullet move delay.
    spawnAliens(std::min(level, 4));  // Spawn a number of rows of aliens based on the level.
}
