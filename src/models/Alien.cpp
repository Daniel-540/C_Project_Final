#include "../../include/models/Alien.h"

Alien::Alien(int startY, int startX, int scoreForKill) : y(startY), x(startX), scoreForKill(scoreForKill) {}

int Alien::getX() const {
    return x;
}

int Alien::getY() const {
    return y;
}

int Alien::getScoreForKill() const {
    return scoreForKill;
}

bool Alien::isAlive() const { return alive; }

void Alien::destroy() { alive = false; }

void Alien::move(int dx, int dy) { x += dx; y += dy; }