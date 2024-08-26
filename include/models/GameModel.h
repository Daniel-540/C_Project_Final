#ifndef MODEL_GAME_H_ // header guard to prevent multiple inclusions of the same header file
#define MODEL_GAME_H_

#include "../observer.h" // include header file for the Observable class
#include "./Alien.h"
#include "./Bullet.h"
#include "./Player.h"
#include "./PowerUp.h"
#include <vector>
#include <string>

class Bot;

class GameModel : public Observable {
private:
    std::vector<Alien> aliens;
    std::vector<Bullet> bullets;
    std::vector<Bullet> alienBullets;
    std::vector<PowerUp> powerUps;
    Player player;
    Bot* bot;
    int alienMoveDelay = 5;  // Delay between alien moves (can adjust for difficulty)
    int alienMoveCounter = 0; // Counter to manage movement speed
    int alienShootDelay = 20; // Delay between alien shots (can adjust for difficulty)
    int alienShootCounter = 0; // Counter to manage shooting speed
    int bulletMoveDelay = 6;
    int bulletMoveCounter = 0;
    int powerUpMoveDelay = 5;
    int powerUpMoveCounter = 0;
    int dir = 1; // 1 means moving right, -1 means moving left
    int width;
    int height;
    int level = 1;
    std::string msg;
    bool gameOver = false;
    bool gamePaused = false;
    void move_aliens();
    void alien_shoot();
    void powerUpMove();
    void spawnAliens(int rows);

public:
    GameModel();

    int getGameWidth();
    int getGameHeight();
    int getLevel();
    void setLevel(int newLevel);
    void setAlienShootDelay(int delay);
    void setBulletMoveDelay(int delay);
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

    std::string getMsg();
    void setMsg(std::string newMsg);

    int getDir();

    bool isGameOver();
    void setGameOver();
    bool isGamePaused();
    void setGamePaused(bool paused);

    //following functions only for testing
     void addAlien(const Alien& alien) {
        aliens.push_back(alien);
    }

    void addAlienBullet(const Bullet& bullet) {
        alienBullets.push_back(bullet);
    }

    void addPowerUp(const PowerUp& powerUp) {
        powerUps.push_back(powerUp);
    }

    void clearAliens() {
        aliens.clear();
    }
};

#endif // end of header file
