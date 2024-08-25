#include "../../include/models/Player.h"

Player::Player(int x, int y, int startLives) : x(x), y(y), lives(startLives) {} 

bool Player::isAlive() {
    return lives > 0;
}

int Player::getX() const { 
    return x;
}

int Player::getY() const { 
    return y;
}

int Player::getLives() {
    return lives;
}

int Player::getScore() {
    return score;
}

void Player::setX(int a) {
    x = a;
}

void Player::setY(int a) {
    y = a;
}

void Player::setLives(int newLives) {
    lives = newLives;
}

void Player::setScore(int newScore) {
    score = newScore;
}
