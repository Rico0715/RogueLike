#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Game::Game()
    : window(sf::VideoMode(1920, 1080), "SFML Character and Monster Test"),
    character1("Arthur", 10000, 70, 50, 100, 10, 1.9f, { Spell("Fireball", 50, 30), Spell("Lightning", 40, 20), Spell("Heal", -30, 25) }, "C:/Users/aymer/Pictures/assets/PixelWarriorsByAndrox/warblue.png"),
    gameState(GameState::Playing),
    isMousePressed(false) // Initialisation de la variable à false
{
    if (!font.loadFromFile("C:/Users/aymer/Source/Repos/RogueLike/Kanit-Black.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    character1.setPosition(100, 100);

    resetGame();
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (gameState == GameState::Playing) {
            update();
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (gameState == GameState::GameOver && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            resetGame();
            gameState = GameState::Playing;
        }

        if (gameState == GameState::Playing) {
            if (event.type == sf::Event::KeyPressed)
                handlePlayerInput(event.key.code, true);
            else if (event.type == sf::Event::KeyReleased)
                handlePlayerInput(event.key.code, false);
            else if (event.type == sf::Event::MouseButtonPressed)
                handleMouseInput(event.mouseButton.button, true);
            else if (event.type == sf::Event::MouseButtonReleased)
                handleMouseInput(event.mouseButton.button, false);
        }
    }
}

void Game::update() {
    // Handle character input
    character1.handleInput(window);

    // Handle shooting if mouse is pressed
    handleShooting();

    // Update projectiles
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        it->update();
        bool projectileErased = false;
        for (auto& monster : monsters) {
            if (monster.isAlive() && it->getBounds().intersects(monster.getBounds())) {
                std::cout << "Monster hit!" << std::endl;
                monster.receiveDamage(10); // Assuming damage is 10, adjust as needed
                it = projectiles.erase(it); // Remove the projectile after collision
                projectileErased = true;
                break; // Break out of the inner loop to avoid modifying the iterator twice
            }
        }
        if (!projectileErased) {
            ++it;
        }
    }

    // Check collision between character and monsters
    for (auto& monster : monsters) {
        if (monster.isAlive() && character1.getBounds().intersects(monster.getBounds())) {
            std::cout << "Character collided with monster!" << std::endl;
            int damage = monster.getAttackDamage(); // Example: Get monster's attack damage
            character1.receiveDamage(damage); // Character receives damage from monster

            if (!character1.isAlive()) {
                gameState = GameState::GameOver;
            }
        }
    }

    // Vérifiez la collision entre le personnage et les bonus
    for (auto it = bonuses.begin(); it != bonuses.end();) {
        if (character1.getBounds().intersects(it->getBounds())) {
            character1.applyBonus(*it);
            it = bonuses.erase(it); // Supprimez le bonus après l'application
        }
        else {
            ++it;
        }
    }

    // Move monsters towards the character
    sf::Vector2f characterPosition = character1.getPosition();
    float deltaTime = 0.1f; // Simulated delta time for movement (replace with actual delta time)
    for (auto& monster : monsters) {
        if (monster.isAlive()) {
            monster.moveTowards(characterPosition, deltaTime);
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    if (gameState == GameState::Playing) {
        // Dessiner le personnage
        character1.draw(window);

        // Dessiner les projectiles
        for (auto& projectile : projectiles) {
            projectile.draw(window);
        }

        // Dessiner les monstres
        for (auto& monster : monsters) {
            if (monster.isAlive()) {
                monster.draw(window);
            }
        }

        // Dessiner les bonus
        for (auto& bonus : bonuses) {
            bonus.draw(window);
        }

        // Afficher le pourcentage des HP du personnage
        sf::Text hpText;
        hpText.setFont(font);
        hpText.setCharacterSize(20);
        hpText.setFillColor(sf::Color::Green);
        hpText.setString("HP: " + std::to_string(character1.getHealthPoints()) + " / " + std::to_string(character1.getMaxHealthPoints())
            + " (" + std::to_string(static_cast<int>(character1.getHealthPercentage())) + "%)");
        hpText.setPosition(20, 20); // Position à ajuster selon votre interface

        window.draw(hpText);

        // Afficher la vitesse d'attaque du personnage
        sf::Text attackSpeedText;
        attackSpeedText.setFont(font);
        attackSpeedText.setCharacterSize(20);
        attackSpeedText.setFillColor(sf::Color::Yellow);
        attackSpeedText.setString("Attack Speed: " + std::to_string(character1.getAttackSpeed()));
        attackSpeedText.setPosition(20, 50); // Position à ajuster selon votre interface

        window.draw(attackSpeedText);

        sf::Text attackDamageText;
        attackDamageText.setFont(font);
        attackDamageText.setCharacterSize(20);
        attackDamageText.setFillColor(sf::Color::Red);
        attackDamageText.setString("Attack Damage: " + std::to_string(character1.getAttackDamage()));
        attackDamageText.setPosition(20, 70); // Position à ajuster selon votre interface

        window.draw(attackDamageText);
    }
    else if (gameState == GameState::GameOver) {
        drawGameOverScreen();
    }

    window.display();
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    // Handle keyboard input if needed
}

void Game::handleMouseInput(sf::Mouse::Button button, bool isPressed) {
    if (button == sf::Mouse::Left && gameState == GameState::Playing) {
        isMousePressed = isPressed; // Met à jour l'état du clic de la souris
    }
}

void Game::handleShooting() {
    // Check if mouse is pressed and shoot continuously
    if (isMousePressed && shootClock.getElapsedTime().asSeconds() >= 1.0f / character1.getAttackSpeed()) {
        character1.shoot(projectiles, "C:/Users/aymer/Pictures/assets/PixelWarriorsByAndrox/projectilev1.png", window);
        shootClock.restart();
    }
}

void Game::resetGame() {
    character1.setPosition(100, 100);
    character1.resetHealth();
    projectiles.clear();

    monsters.clear();
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < 5; ++i) {
        Monstre monster("Goblin", 100, 15, 1.0f, "C:/Users/aymer/Pictures/assets/PixelWarriorsByAndrox/warriorRed.png");
        monster.setPosition(rand() % 1920, rand() % 1080); // Random position on the map
        monsters.push_back(monster);
    }

    bonuses.clear();
    generateBonuses();
}

void Game::drawGameOverScreen() {
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(1920 / 2.f - gameOverText.getLocalBounds().width / 2.f, 300);

    sf::Text restartText;
    restartText.setFont(font);
    restartText.setString("Click to Restart");
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);
    restartText.setPosition(1920 / 2.f - restartText.getLocalBounds().width / 2.f, 400);

    window.draw(gameOverText);
    window.draw(restartText);
}

void Game::generateBonuses() {
    // Exemple de génération d'un bonus de type AttackSpeed avec une valeur aléatoire entre 1 et 5
    sf::Vector2f position(rand() % 1920, rand() % 1080); // Position aléatoire
    float attackSpeedValue = static_cast<float>((rand() % 5) + 1); // Valeur aléatoire entre 1 et 5
    bonuses.push_back(Bonus(BonusType::AttackSpeed, attackSpeedValue, position)); // Bonus de vitesse d'attaque avec une valeur aléatoire

    // Vous pouvez également ajouter d'autres bonus si nécessaire
    for (int i = 0; i < 4; ++i) { // 4 autres bonus
        BonusType type = static_cast<BonusType>(rand() % 2); // Deux types de bonus restants: Speed et AttackDamage
        float value = static_cast<float>((rand() % 5) + 1); // Valeur aléatoire entre 1 et 5
        sf::Vector2f position(rand() % 1920, rand() % 1080); // Position aléatoire
        bonuses.push_back(Bonus(type, value, position));
    }
}
