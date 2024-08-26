#include "../../include/models/PowerUp.h"

PowerUp::PowerUp(int startX, int startY) : x(startX), y(startY) {}

int PowerUp::getX() const {
    return x;
}

int PowerUp::getY() const {
    return y;
}

bool PowerUp::isOffScreen(int height) {
    return (y < 1 || y > height);
}

void PowerUp::move() {
    y = y + 1;
}