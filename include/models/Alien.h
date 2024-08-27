#ifndef ALIEN_H_
#define ALIEN_H_

class Alien {
private:
    int x, y, scoreForKill;
public:
    Alien(int startY, int startX, int scoreForKill);
    int getX() const;
    int getY() const;
    int getScoreForKill() const;
    void move(int dx, int dy);
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
};

#endif