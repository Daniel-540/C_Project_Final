#ifndef PLAYER_H_
#define PLAYER_H_

class Player {
private:
    int x, y, height, lives, score = 0; // player's coordinates and height
public:
    Player(int x, int y, int startLives); // constructor that takes in initial x and y coordinates of player
    bool isAlive();
    int getX() const;
    int getY() const;
    int getLives();
    int getScore();
    void setX(int a);
    void setY(int a);
    void setLives(int newLives);
    void setScore(int newScore);
};

#endif