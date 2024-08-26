#include "../../include/models/PowerUp.h"

PowerUp::PowerUp(int startX, int startY, int velocityY) : x(startX), y(startY), velocityY(velocityY) {}

int PowerUp::getX() const {
    return x;
}

int PowerUp::getY() const {
    return y;
}

int PowerUp::getVelocityY() const {
    return velocityY;
}

bool PowerUp::isOffScreen(int height) {
    return (y < 1 || y > height);
}

void PowerUp::move() {
    y = y + velocityY;
}