#ifndef POWERUP_H_
#define POWERUP_H_


class PowerUp {
private:
    int x, y;

public:
    PowerUp(int startX, int startY);
    int getX() const;
    int getY() const;
    bool isOffScreen(int height);
    void move();
};


#endif