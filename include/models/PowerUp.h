#ifndef POWERUP_H_
#define POWERUP_H_


class PowerUp {
private:
    int x, y, velocityY;

public:
    PowerUp(int startX, int startY, int velocityY);
    int getX() const;
    int getY() const;
    int getVelocityY() const;
    bool isOffScreen(int height);
    void move();
};


#endif