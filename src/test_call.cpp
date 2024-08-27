#define BOOST_TEST_MODULE GameModelTest
#include <boost/test/included/unit_test.hpp>
#include "../include/models/GameModel.h"

BOOST_AUTO_TEST_SUITE(GameModelSuite)

BOOST_AUTO_TEST_CASE(InitializationTest)
{
    GameModel game;
    BOOST_CHECK_EQUAL(game.getLevel(), 1);
    BOOST_CHECK_EQUAL(game.getPlayer().getLives(), 3);
    BOOST_CHECK_EQUAL(game.getPlayer().getX(), 20);
    BOOST_CHECK_EQUAL(game.getPlayer().getY(), 22);
    BOOST_CHECK_EQUAL(game.getGameWidth(), 40);
    BOOST_CHECK_EQUAL(game.getGameHeight(), 24);
    BOOST_CHECK_EQUAL(game.getAliens().size(), 8);
}

BOOST_AUTO_TEST_CASE(PlayerMovementTest)
{
    GameModel game;
    int initialX = game.getPlayer().getX();
    game.movePlayerLeft();
    BOOST_CHECK_EQUAL(game.getPlayer().getX(), initialX - 1);
    game.movePlayerRight();
    game.movePlayerRight();
    BOOST_CHECK_EQUAL(game.getPlayer().getX(), initialX + 1);
}

BOOST_AUTO_TEST_CASE(BulletShootingTest)
{
    GameModel game;
    game.playerShoot();
    BOOST_CHECK_EQUAL(game.getBullets().size(), 1); // Check if a bullet was added.
    BOOST_CHECK_EQUAL(game.getBullets()[0].getX(), game.getPlayer().getX());
    BOOST_CHECK_EQUAL(game.getBullets()[0].getY(), game.getPlayer().getY()); // Should be just above the player.
}

BOOST_AUTO_TEST_CASE(AlienCollisionTest)
{
    GameModel game;
    game.getPlayer().setX(3);
    game.getPlayer().setY(4);
    game.getAliens().emplace_back(3, 3, 5); // Add an alien directly above the player.
    game.playerShoot();
    game.simulate_game_step();
    game.simulate_game_step();
    //game.getBullets()[0].setY(3); // Move the bullet to collide with the alien.
    
    //game.check_collisions();
    BOOST_CHECK_EQUAL(game.getBullets().size(), 0); // Bullet should be removed.
    BOOST_CHECK_EQUAL(game.getAliens().size(), 8); // one Alien should be removed.
    BOOST_CHECK_EQUAL(game.getPlayer().getScore(), 5); 
} 

BOOST_AUTO_TEST_CASE(PowerUpCollisionTest)
{
    GameModel game;
    game.getPlayer().setX(5);
    game.getPlayer().setY(5);
    game.getPowerUps().emplace_back(5, 5); // Place a power-up on the player.
    
    game.check_collisions();
    BOOST_CHECK_EQUAL(game.getPowerUps().size(), 0); // Power-up should be removed.
    BOOST_CHECK_EQUAL(game.getPlayer().getLives(), 4); // Player should gain a life.
} 

BOOST_AUTO_TEST_CASE(GameOverTest)
{
    GameModel game;
    game.getPlayer().setLives(1);
    game.getAliens().emplace_back(24, 38, 5); // Place an alien near the bottom of the screen.
    
for (int i= 0; i < 100; i++) {
    game.simulate_game_step();
}
    BOOST_CHECK(game.isGameOver());
} 

BOOST_AUTO_TEST_SUITE_END()
