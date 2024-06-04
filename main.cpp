#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainMenu.hpp"
#include "Enemigos.hpp"
#include "Jugador.hpp"
#include "EfectoParallax.hpp"

using namespace sf;
using namespace std;

enum GameState
{
    MAIN_MENU,
    GAME_RUNNING,
    GAME_OVER
};

int main()
{
    RenderWindow window(VideoMode(600, 600), "La Mommy: la venganza de anubis");
    window.setFramerateLimit(60);

    MainMenu menu(window.getSize().x, window.getSize().y);

    Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("fondos/alterno.png"))
    {
        return -1;
    }
    menu.setBackground(menuBackgroundTexture);

    menu.setOptionText(0, "Jugar");
    menu.setOptionText(1, "Salir del juego");

    GameState state = MAIN_MENU;

    // Cargar texturas del juego
    Texture skyTexture, shadowTexture, pyramidTexture, desertTexture, trainTexture, characterTexture, playerHurtTexture, gameOverTexture, barraVidaTexture;
    if (!skyTexture.loadFromFile("fondos/fondosky.png") ||
        !shadowTexture.loadFromFile("fondos/Sombras.png") ||
        !pyramidTexture.loadFromFile("fondos/primamid-pixilart.png") ||
        !desertTexture.loadFromFile("fondos/Vias del tren.png") ||
        !trainTexture.loadFromFile("fondos/gohancomoquedolamoto.png") ||
        !characterTexture.loadFromFile("fondos/Izquierda.png") ||
        !playerHurtTexture.loadFromFile("fondos/JugadorHerido.png") ||
        !gameOverTexture.loadFromFile("fondos/GameOver.png") ||
        !barraVidaTexture.loadFromFile("fondos/BarraVida.png"))
    {
        return -1;
    }

    Texture enemyTexture1, enemyTexture2;
    if (!enemyTexture1.loadFromFile("fondos/Momia1-1.png") || !enemyTexture2.loadFromFile("fondos/Momia1-2.png"))
    {
        return -1;
    }
    vector<Texture> enemyTextures = {enemyTexture1, enemyTexture2};

    skyTexture.setRepeated(true);
    shadowTexture.setRepeated(true);
    pyramidTexture.setRepeated(true);
    desertTexture.setRepeated(true);

    Background background(skyTexture, shadowTexture, pyramidTexture, desertTexture, trainTexture, barraVidaTexture);
    Player player(characterTexture, 300, 335, 3.f, 335);
    Enemy enemy1(enemyTextures, 100, 335, 2.0f, 0.5f, gameOverTexture, playerHurtTexture);
    Enemy enemy2(enemyTextures, 200, 335, 2.0f, 0.5f, gameOverTexture, playerHurtTexture);

    Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (state == MAIN_MENU)
            {
                if (event.type == Event::KeyPressed)
                {
                    if (event.key.code == Keyboard::Up)
                    {
                        menu.moveUp();
                    }
                    if (event.key.code == Keyboard::Down)
                    {
                        menu.moveDown();
                    }
                    if (event.key.code == Keyboard::Return)
                    {
                        int selectedItem = menu.getPressedItem();
                        if (selectedItem == 0)
                        {
                            state = GAME_RUNNING;
                        }
                        else if (selectedItem == 1)
                        {
                            window.close();
                        }
                    }
                }
            }
        }

        window.clear();

        if (state == MAIN_MENU)
        {
            menu.draw(window);
        }
        else if (state == GAME_RUNNING)
        {
            SoundBuffer buffer;
            if (!buffer.loadFromFile("Fondos/anani.wav"))
            {
                // Error handling...
            }
            Sound sound;
            sound.setBuffer(buffer);
            sound.play();
            player.handleInput();
            player.applyGravity();
            player.checkBounds(600);

            enemy1.update(deltaTime, player);
            enemy2.update(deltaTime, player);
            enemy1.checkGameOver(window);

            background.move(2.f, 5.f, 10.f);

            background.draw(window);
            window.draw(player.sprite);
            window.draw(enemy1.sprite);
            window.draw(enemy2.sprite);
        }

        window.display();
    }

    return 0;
}
