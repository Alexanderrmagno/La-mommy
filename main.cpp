#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainMenu.hpp"
#include "bullet .hpp"
#include "Enemigos.hpp"
#include "Player.hpp"
#include "Background.hpp"

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
    Texture skyTexture, shadowTexture, pyramidTexture, desertTexture, trainTexture, characterTexture;
    if (!skyTexture.loadFromFile("fondos/fondosky.png") ||
        !shadowTexture.loadFromFile("fondos/Sombras.png") ||
        !pyramidTexture.loadFromFile("fondos/primamid-pixilart.png") ||
        !desertTexture.loadFromFile("fondos/Vias del tren.png") ||
        !trainTexture.loadFromFile("fondos/gohancomoquedolamoto.png") ||
        !characterTexture.loadFromFile("fond



