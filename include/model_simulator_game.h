#ifndef MODEL_GAME_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_GAME_H_

#include "observer.h" // include header file for the Observable class

class Player {
public:
    Player(int x, int y); // constructor that takes in initial x and y coordinates of player
    int getX();
    int getY();
    void setX(int a);
    void setY(int a);
private:
    int x, y, height; // player's coordinates and height
};

class Bullet {
    int x, y;
    int velocityY;
public:
    Bullet(int y, int x, int velocityY) : x(x), y(y), velocityY(velocityY) {}
    void move(int velocity) { y = y + velocity; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setY(int newY) { y = newY; }
    bool isOffScreen() const { return y < 1; }
};

class Alien {
    int x, y;
    bool alive = true;
public:
    Alien(int startY, int startX) : y(startY), x(startX) {}
    void move(int dx, int dy) { x += dx; y += dy; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool isAlive() const { return alive; }
    void destroy() { alive = false; }
};

class GameModel : public Observable {
    std::vector<Alien> aliens;
    std::vector<Bullet> bullets;
    std::vector<Bullet> alienBullets;
    int alienMoveDelay = 5;  // Delay between alien moves (can adjust for difficulty)
    int alienMoveCounter = 0; // Counter to manage movement speed
    int alienShootDelay = 20; // Delay between alien shots (can adjust for difficulty)
    int alienShootCounter = 0; // Counter to manage shooting speed
    int dir = 1; // 1 means moving right, -1 means moving left

public:
    GameModel();

    int getGameWidth();
    int getGameHeight();
    Player& getPlayer();

    void simulate_game_step();
    void control_player(wchar_t ch);
    void update_bullets();
    void check_collisions();
    void shoot() { bullets.emplace_back(player.getY(), player.getX(), -1); } // Specify velocityY to make bullets move upwards
    const std::vector<Bullet>& getBullets() const;
    const std::vector<Bullet>& getAlienBullets() const;
    const std::vector<Alien>& getAliens() const;

private:
    int width = 40;
    int height = 24;
    Player player;
    void move_aliens();
    void alien_shoot();
};

#endif // end of header file
