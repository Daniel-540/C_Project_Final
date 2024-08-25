#include "../../include/models/Bullet.h"

Bullet::Bullet(int y, int x, int velocityY) : x(x), y(y), velocityY(velocityY) {}

int Bullet::getX() const {
    return x;
}

int Bullet::getY() const {
    return y;
}

int Bullet::getVelocityY() const {
    return velocityY;
}

void Bullet::setY(int newY) {
    y = newY;
}

bool Bullet::isOffScreen() {
    return y < 1;
}

void Bullet::move(int velocity) { 
    y = y + velocity; 
}
