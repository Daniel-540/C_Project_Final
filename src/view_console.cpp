#include "view_console.h"
#include <ncurses.h>
#include <stdlib.h>

ConsoleView::ConsoleView(GameModel* model) {
    setup_view();
    this->model = model;
    this->model->addObserver(this);
}

ConsoleView::~ConsoleView() {
    endwin();
}

void ConsoleView::update() {
    erase();
    refresh();

    // Draw walls
    for (int i = 0; i < model->getGameWidth(); i++) {
        mvaddch(0, i, wallTexture);
    }
    for (int i = 0; i < model->getGameHeight(); i++) {
        mvaddch(i, 0, wallTexture);
        mvaddch(i, model->getGameWidth() - 1, wallTexture);
    }

    // Draw player
    drawPlayer(model->getPlayer().getY(), model->getPlayer().getX());

    // Draw bullets
    for (const auto &bullet : model->getBullets()) {
        drawBullet(bullet.getY(), bullet.getX());
    }

    // Draw alien bullets
    for (const auto &bullet : model->getAlienBullets()) {
        drawBullet(bullet.getY(), bullet.getX());
    }

    // Draw aliens
    for (const auto &alien : model->getAliens()) {
        if (alien.isAlive()) {
            drawAlien(alien.getY(), alien.getX());
        }
    }

    refresh();  // Ensure the screen is updated with the latest draw calls
}

void ConsoleView::setup_view() {
    // Init ncurses
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(30);
}

void ConsoleView::drawPlayer(int y, int x) {
    mvaddch(y-1, x, 'P');
}