#ifndef MODEL_GAME_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_GAME_H_

#include "observer.h" // include header file for the Observable class

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

class GameModel : public Observable {
private:
    std::vector<Alien> aliens;
    std::vector<Bullet> bullets;
    std::vector<Bullet> alienBullets;
    Player player;
    int alienMoveDelay = 5;  // Delay between alien moves (can adjust for difficulty)
    int alienMoveCounter = 0; // Counter to manage movement speed
    int alienShootDelay = 20; // Delay between alien shots (can adjust for difficulty)
    int alienShootCounter = 0; // Counter to manage shooting speed
    int dir = 1; // 1 means moving right, -1 means moving left
    int width = 40;
    int height = 24;
    bool gameOver = false;
    void move_aliens();
    void alien_shoot();

public:
    GameModel();

    int getGameWidth();
    int getGameHeight();
    Player& getPlayer();

    void simulate_game_step();
    void control_player(wchar_t ch);
    void update_bullets();
    void check_collisions();
    void shoot(); // Specify velocityY to make bullets move upwards
    const std::vector<Bullet>& getBullets() const;
    const std::vector<Bullet>& getAlienBullets() const;
    const std::vector<Alien>& getAliens() const;

    bool isGameOver();
    void toggleGameOver();
};

#endif // end of header file
