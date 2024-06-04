#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainMenu.hpp"
#include "bullet .hpp"
#include "Enemigos.hpp"
#include "Jugador.hpp"
#include "EfectoParallax.hpp"

using namespace sf;
using namespace std;

int main() {
    RenderWindow window(VideoMode(600, 600), "La Mommy: la venganza de anubis");
    window.setFramerateLimit(60);

    MainMenu menu(window.getSize().x, window.getSize().y);

    Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("fondos/alterno.png")) {
        return -1;
    }
    menu.setBackground(menuBackgroundTexture);

    menu.setOptionText(0, "Jugar");
    menu.setOptionText(1, "Salir del juego");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    menu.moveUp();
                }
                if (event.key.code == Keyboard::Down) {
                    menu.moveDown();
                }
                if (event.key.code == Keyboard::Return) {
                    int selectedItem = menu.getPressedItem();
                    if (selectedItem == 0) {
                        goto game_loop;
                    } else if (selectedItem == 1) {
                        window.close();
                    }
                }
            }
        }
        window.clear();
        menu.draw(window);
        window.display();
    }

game_loop:
    Texture skyTexture, shadowTexture, pyramidTexture, desertTexture, trainTexture, characterTexture, playerHurtTexture, gameOverTexture, BarraVidaTexture;
    if (!skyTexture.loadFromFile("fondos/fondosky.png") ||
        !shadowTexture.loadFromFile("fondos/Sombras.png") ||
        !pyramidTexture.loadFromFile("fondos/primamid-pixilart.png") ||
        !desertTexture.loadFromFile("fondos/Vias del tren.png") ||
        !trainTexture.loadFromFile("fondos/gohancomoquedolamoto.png") ||
        !characterTexture.loadFromFile("fondos/Izquierda.png") ||
        !playerHurtTexture.loadFromFile("fondos/JugadorHerido.png") ||
        !gameOverTexture.loadFromFile("fondos/GameOver.png") ||
        !BarraVidaTexture.loadFromFile("fondos/BarraVida.png")) { // Asegúrate de tener la imagen de la barra de vida
        return -1;
    }

    Texture enemyTexture1, enemyTexture2;
    if (!enemyTexture1.loadFromFile("fondos/Momia1-1.png") || !enemyTexture2.loadFromFile("fondos/Momia1-2.png")) {
        return -1;
    }
    vector<Texture> enemyTextures = {enemyTexture1, enemyTexture2};

    skyTexture.setRepeated(true);
    shadowTexture.setRepeated(true);
    pyramidTexture.setRepeated(true);
    desertTexture.setRepeated(true);

    Background background(skyTexture, shadowTexture, pyramidTexture, desertTexture, trainTexture, BarraVidaTexture);
    Player player(characterTexture, 300, 335, 3.f, 335);
    Enemy enemy(enemyTextures, 100, 335, 2.0f, 0.5f, gameOverTexture);

    Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        player.handleInput();
        player.applyGravity();
        player.checkBounds(600);

        enemy.update(deltaTime, player.sprite, playerHurtTexture);
        enemy.checkGameOver(window);

        background.move(2.f, 5.f, 10.f);

        window.clear();
        background.draw(window);
        window.draw(player.sprite);
        window.draw(enemy.sprite);
        window.display();
    }

    return 0;
}