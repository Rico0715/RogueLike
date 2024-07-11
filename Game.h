#ifndef GAME_H
#define GAME_H

#include "Personnage.h"
#include "Monstre.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void handleMouseInput(sf::Mouse::Button button, bool isPressed);
    void resetGame();
    void drawGameOverScreen();
    void handleShooting(); // Nouvelle m�thode pour g�rer le tir continu


    sf::RenderWindow window;
    sf::Font font;
    Personnage character1;
    std::vector<Monstre> monsters;
    std::vector<Projectile> projectiles;

    enum class GameState {
        Playing,
        GameOver
    };

    GameState gameState;
    bool isMousePressed; // Variable pour suivre l'�tat du clic de la souris
    sf::Clock shootClock; // Horloge pour contr�ler la cadence de tir
};

#endif
