#ifndef ALIEN_H_
#define ALIEN_H_

class Alien {
private:
    int x, y, scoreForKill;
    bool alive = true;
public:
    Alien(int startY, int startX, int scoreForKill);
    int getX() const;
    int getY() const;
    int getScoreForKill() const;
    bool isAlive() const;
    void destroy();
    void move(int dx, int dy);
};

#endif