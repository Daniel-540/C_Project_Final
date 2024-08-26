#define BOOST_TEST_MODULE GameModelTest
#include <boost/test/included/unit_test.hpp>

#include "../include/models/GameModel.h"
#include "../include/models/Bullet.h"
#include "../include/models/Alien.h"
#include "../include/models/Player.h"
#include "../include/models/PowerUp.h"

BOOST_AUTO_TEST_SUITE(GameModelTestSuite)

// Test to check the initial state of the game
BOOST_AUTO_TEST_CASE(TestGameInitialization) {
    GameModel game;
    
    // Verify initial game state
    BOOST_CHECK_EQUAL(game.getGameWidth(), 40);      // Check game width
    BOOST_CHECK_EQUAL(game.getGameHeight(), 24);     // Check game height
    BOOST_CHECK_EQUAL(game.getLevel(), 1);           // Check initial level
    BOOST_CHECK_EQUAL(game.isGamePaused(), false);   // Game should not be paused initially
    BOOST_CHECK_EQUAL(game.isGameOver(), false);     // Game should not be over initially

    // Check if player is correctly initialized
    BOOST_CHECK_EQUAL(game.getPlayer().getLives(), 3);  // Player starts with 3 lives
    BOOST_CHECK_EQUAL(game.getPlayer().getX(), 20);     // Player starts at the center (x position)
    BOOST_CHECK_EQUAL(game.getPlayer().getY(), 22);     // Player's y position

    // Check if aliens are spawned
    BOOST_CHECK_GT(game.getAliens().size(), 0);  // There should be aliens at the start
}

// Test to check player movement functionality
BOOST_AUTO_TEST_CASE(TestPlayerMovement) {
    GameModel game;

    // Move player left
    game.control_player('L');
    BOOST_CHECK_EQUAL(game.getPlayer().getX(), 19);

    // Move player right twice
    game.control_player('R');
    game.control_player('R');
    BOOST_CHECK_EQUAL(game.getPlayer().getX(), 21);

    // Ensure player doesn't move off-screen
    game.getPlayer().setX(1);
    game.control_player('L');  // Attempt to move left at screen edge
    BOOST_CHECK_EQUAL(game.getPlayer().getX(), 1);  // Player should remain at 1
}

// Test to check player shooting functionality
BOOST_AUTO_TEST_CASE(TestPlayerShooting) {
    GameModel game;

    // Test shooting
    int initialBulletCount = game.getBullets().size();
    game.control_player(' ');  // Space key to shoot
    BOOST_CHECK_EQUAL(game.getBullets().size(), initialBulletCount + 1);  // One bullet should be added

    // Check properties of the bullet
    Bullet bullet = game.getBullets().back();
    BOOST_CHECK_EQUAL(bullet.getX(), game.getPlayer().getX());
    BOOST_CHECK_EQUAL(bullet.getY(), game.getPlayer().getY());
    BOOST_CHECK_EQUAL(bullet.getVelocityY(), -1);  // Bullet should move upwards
}

// Test to check alien movement indirectly through game simulation
BOOST_AUTO_TEST_CASE(TestAlienMovement) {
    GameModel game;

    // Capture initial positions of aliens
    std::vector<Alien> initialAliens = game.getAliens();

    // Simulate game steps to move aliens
    for (int i = 0; i < 10; ++i) {
        game.simulate_game_step();  // This will move aliens
    }
    
    // Capture new positions of aliens
    std::vector<Alien> movedAliens = game.getAliens();

    // Check if at least one alien has moved
    bool alienMoved = false;
    for (size_t i = 0; i < initialAliens.size(); ++i) {
        if (initialAliens[i].getX() != movedAliens[i].getX() || initialAliens[i].getY() != movedAliens[i].getY()) {
            alienMoved = true;
            break;
        }
    }
    BOOST_CHECK(alienMoved);  // Assert that aliens moved
}

// Test to check collision detection logic
BOOST_AUTO_TEST_CASE(TestCollisionDetection) {
    GameModel game;

    // Assuming there's a public method to add an alien for testing:
    Alien alien(22, game.getPlayer().getX(), 100);

    // Hypothetical method to add an alien:
    game.addAlien(alien); 

    // Player shoots
    game.control_player(' ');  // Player shoots
    game.simulate_game_step();  // Update game to move bullet

    // Simulate another step to allow collision
    game.simulate_game_step();

    // Check if alien is destroyed and bullet is removed
    BOOST_CHECK_EQUAL(game.getAliens().size(), 0);  // Alien should be destroyed
    BOOST_CHECK_EQUAL(game.getBullets().size(), 0);  // Bullet should be gone

    // Check if player score is updated
    BOOST_CHECK_EQUAL(game.getPlayer().getScore(), alien.getScoreForKill());
}


// Test to check game over condition when the player is hit
BOOST_AUTO_TEST_CASE(TestGameOverCondition) {
    GameModel game;

    // Reduce player lives to 1
    game.getPlayer().setLives(1);

    // Assuming there's a public method to add an alien bullet:
    Bullet alienBullet(game.getPlayer().getY(), game.getPlayer().getX(), 1);

    // Hypothetical method to add an alien bullet:
    game.addAlienBullet(alienBullet);

    game.simulate_game_step();  // Update game to process bullet

    // Check if game is over
    BOOST_CHECK_EQUAL(game.isGameOver(), true);
}

// Test to check power-up collection by the player
BOOST_AUTO_TEST_CASE(TestPowerUpCollection) {
    GameModel game;

    // Place a power-up directly in front of the player
    PowerUp powerUp(game.getPlayer().getY(), game.getPlayer().getX());

    // Hypothetical method to add a power-up:
    game.addPowerUp(powerUp);  // Implement this in GameModel

    // Simulate game step to check for collision
    game.simulate_game_step();

    // Check if power-up is collected and player lives increased
    BOOST_CHECK_EQUAL(game.getPowerUps().size(), 0);  // Power-up should be collected
    BOOST_CHECK_EQUAL(game.getPlayer().getLives(), 4);  // Player should have one extra life
}

// Test to check new level initialization
BOOST_AUTO_TEST_CASE(TestNewLevelInitialization) {
    GameModel game;
    int initialLevel = game.getLevel();

    // Assuming a method to clear aliens or trigger new level exists:
    game.clearAliens(); 

    game.simulate_game_step();  // Simulate game step to trigger new level

    // Check if new level is initialized correctly
    BOOST_CHECK_EQUAL(game.getLevel(), initialLevel + 1);  // Level should be increased
    BOOST_CHECK_GT(game.getAliens().size(), 0);  // New aliens should be spawned
    BOOST_CHECK(game.isGamePaused());  // Game should be paused for new level setup
}

BOOST_AUTO_TEST_SUITE_END()
