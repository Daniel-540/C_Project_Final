#ifndef MODEL_GAME_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_GAME_H_

#include "../observer.h" // include header file for the Observable class
#include "./Alien.h"
#include "./Bullet.h"
#include "./Player.h"
#include "./PowerUp.h"
#include <vector>


class GameModel : public Observable {
private:
    std::vector<Alien> aliens;
    std::vector<Bullet> bullets;
    std::vector<Bullet> alienBullets;
    std::vector<PowerUp> powerUps;
    Player player;
    int alienMoveDelay = 5;  // Delay between alien moves (can adjust for difficulty)
    int alienMoveCounter = 0; // Counter to manage movement speed
    int alienShootDelay = 20; // Delay between alien shots (can adjust for difficulty)
    int alienShootCounter = 0; // Counter to manage shooting speed
    int powerUpMoveDelay = 2;
    int powerUpMoveCounter = 0;
    int dir = 1; // 1 means moving right, -1 means moving left
    int width = 40;
    int height = 24;
    int level = 1;
    bool gameOver = false;
    void move_aliens();
    void alien_shoot();
    void powerUpMove();

public:
    GameModel();

    int getGameWidth();
    int getGameHeight();
    int getLevel();
    void setLevel(int newLevel);
    void newLevel();
    Player& getPlayer();

    void simulate_game_step();
    void control_player(wchar_t ch);
    void update_bullets(std::vector<Bullet>& bulletArr);
    void check_collisions();
    void shoot(); // Specify velocityY to make bullets move upwards
    const std::vector<Bullet>& getBullets() const;
    const std::vector<Bullet>& getAlienBullets() const;
    const std::vector<Alien>& getAliens() const;
    const std::vector<PowerUp>& getPowerUps() const;

    bool isGameOver();
    void setGameOver();
};

#endif // end of header file
