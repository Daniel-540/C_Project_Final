#include "../../include/models/Bot.h"
#include "../../include/models/Player.h"
#include "../../include/models/GameModel.h"
#include <algorithm> // Include the <algorithm> header for std::min_element.

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

// Main logic for the bot's decision-making during the game.
void Bot::play() {
    auto player = model->getPlayer(); // Get the current player object from the game model.

    // Check if there are bullets in the same lane as the player.
    if (checkBullets(player.getX())) {
        // Check if dodging right is possible.
        if (checkBullets(player.getX() + 1) || (player.getX() + 1 >= model->getGameWidth())) {
            // Check if dodging left is possible.
            if (checkBullets(player.getX() - 1) || player.getX() - 1 <= 0) {
                model->setMsg("[Bot]: couldn't dodge"); // Set message indicating no possible dodge.
            } else {
                model->setMsg("[Bot]: dodging left"); // Set message indicating dodging left.
                model->movePlayerLeft();
                //player.setX(player.getX() - 1); // Move player left.
            }
        } else {
            model->setMsg("[Bot]: dodging right"); // Set message indicating dodging right.
            model->movePlayerRight(); 
            //model->getPlayer().setX(model->getPlayer().getX() + 1); // Move player right.
        }
    } else {
        // Decide whether to shoot or aim at aliens or power-ups.
        if (shootCounter >= 5) {
            model->shoot(); // Make the player shoot.
            shootCounter = 0; // Reset the shoot counter.
        } else {
            // Find the nearest alien by comparing Y positions (vertical distance).
            auto nearestAlien = std::min_element(model->getAliens().begin(), model->getAliens().end(),
                [](const Alien& a, const Alien& b) {
                    return a.getY() > b.getY(); // Compare by Y position.
                });
            int alienPositionX = nearestAlien->getX(); // X position of the nearest alien.
            int alienPositionY = nearestAlien->getY(); // Y position of the nearest alien.
            int direction; // Direction to aim at.

            // Check if there are any power-ups.
            if (model->getPowerUps().size() > 0) {
                // Find the nearest power-up.
                auto nearestPowerUp = std::min_element(model->getPowerUps().begin(), model->getPowerUps().end(),
                    [](const PowerUp& a, const PowerUp& b) {
                        return a.getY() > b.getY(); // Compare by Y position.
                    });
                // Decide if chasing a power-up is better than targeting an alien.
                if (player.getY() - nearestAlien->getY() > 5 && (player.getY() - nearestPowerUp->getY() <= (int)(std::abs(player.getX() - nearestPowerUp->getX()) / 4))) {
                    direction = nearestPowerUp->getX(); // Aim at the power-up.
                } else {
                    // Calculate aiming direction towards the alien.
                    direction = alienPositionX + ((int)(static_cast<float>(player.getY() - alienPositionY) / 5.0)) * model->getDir();
                }
            } else {
                // Calculate aiming direction towards the alien if no power-ups are present.
                direction = alienPositionX + ((int)(static_cast<float>(player.getY() - alienPositionY) / 5.0)) * model->getDir();
            }
            model->setMsg("[Bot] aiming at: " + std::to_string(direction)); // Set aiming message.

            // Adjust player's position towards the calculated direction, avoiding bullets.
            if (direction < model->getPlayer().getX() && !checkBullets(player.getX() - 1)) {
                model->movePlayerLeft(); // Move player left.
            } else if (direction > model->getPlayer().getX() && !checkBullets(player.getX() + 1)) {
                model->movePlayerRight();  // Move player right.
            }
        }
        shootCounter++; // Increment the shoot counter.
    }
}

// Method to check if there are any alien bullets in the specified lane.
bool Bot::checkBullets(int laneToCheck) {
    // Iterate through all alien bullets to check their position.
    for (auto alienBullet : model->getAlienBullets()) {
        if (alienBullet.getY() > model->getPlayer().getY() - 3) { // Check if bullet is near the player.
            if (laneToCheck == alienBullet.getX()) { // Check if the bullet is in the same lane.
                return true; // Bullet found in the lane, return true.
            }
        }
    }
    return false; // No bullet found in the lane, return false.
}
