#ifndef BULLET_H_
#define BULLET_H_

class Bullet {
private:
    int x, y;
    int velocityY;
public:
    Bullet(int y, int x, int velocityY);
    int getX() const;
    int getY() const;
    void setY(int newY);
    bool isOffScreen();
    void move(int velocity);
};

#endif