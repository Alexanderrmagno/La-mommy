#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainMenu.hpp"
#include "Enemigos.hpp"
#include "Jugador.hpp"
#include "bullet .hpp"
#include "EfectoParallax.hpp"
#include <vector>

using namespace sf;
using namespace std;

vector<Bullet> bullets;

enum GameState
{
    MAIN_MENU,
    GAME_RUNNING,
    GAME_OVER
};

int main()
{
    SoundBuffer buffer;
    if (!buffer.loadFromFile("Fondos/anani.wav"))
    {
        // Error handling...
    }
    Sound sound;
    sound.setBuffer(buffer);
    sound.play();

    RenderWindow window(VideoMode(600, 600), "La Mommy: la venganza de anubis");
    window.setFramerateLimit(60);

    MainMenu menu(window.getSize().x, window.getSize().y);

    Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("fondos/neoPortada.png"))
    {
        return -1;
    }
    menu.setBackground(menuBackgroundTexture);

    menu.setOptionText(0, "Jugar");
    menu.setOptionText(1, "Salir del juego");

    GameState state = MAIN_MENU;

    // Cargar texturas del juego
    Texture skyTexture, shadowTexture, pyramidTexture, desertTexture, trainTexture, characterTexture, playerHurtTexture, gameOverTexture;
    if (!skyTexture.loadFromFile("fondos/fondosky.png") ||
        !shadowTexture.loadFromFile("fondos/Sombras.png") ||
        !pyramidTexture.loadFromFile("fondos/primamid-pixilart.png") ||
        !desertTexture.loadFromFile("fondos/Vias del tren.png") ||
        !trainTexture.loadFromFile("fondos/gohancomoquedolamoto.png") ||
        !characterTexture.loadFromFile("fondos/Izquierda.png") ||
        !playerHurtTexture.loadFromFile("fondos/JugadorHerido.png") ||
        !gameOverTexture.loadFromFile("fondos/GameOver.png"))
    {
        return -1;
    }

    // Cargar texturas de la barra de vida
    vector<Texture> barraVidaTextures(16);
    for (int i = 0; i <= 15; i++)
    {
        if (!barraVidaTextures[i].loadFromFile("fondos/BarraVida" + to_string(i) + ".png"))
        {
            return -1;
        }
    }

    Texture enemyTexture1, enemyTexture2;
    if (!enemyTexture1.loadFromFile("fondos/Anubis1.png") || !enemyTexture2.loadFromFile("fondos/Anubis1.png"))
    {
        return -1;
    }
    vector<Texture> enemyTextures = {enemyTexture1, enemyTexture2};

    skyTexture.setRepeated(true);
    shadowTexture.setRepeated(true);
    pyramidTexture.setRepeated(true);
    desertTexture.setRepeated(true);

    // Ajuste de fondo y elementos
    Background background(skyTexture, shadowTexture, pyramidTexture, desertTexture, trainTexture, barraVidaTextures[15]);

    // Coordenadas verticales del tren
    float trainYPosition = 335.0f;

    // Ajustar la posición vertical del jugador y del enemigo
    Player player(characterTexture, 300, trainYPosition, 3.f, trainYPosition);
    Enemy enemy1(enemyTextures, 60, 250, 2.0f, 0.5f, gameOverTexture, playerHurtTexture, barraVidaTextures, 5);

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
            sound.stop();
            player.handleInput();
            player.applyGravity();
            player.checkBounds(600);

            enemy1.update(deltaTime, player);
            enemy1.checkGameOver(window);

            background.move(0.5f, 1.f, 2.f, 0.0f);

            background.draw(window);
            window.draw(player.sprite);
            window.draw(enemy1.barraVidaSprite); // Dibuja la barra de vida

            if (Keyboard::isKeyPressed(Keyboard::E))
            {
                float xPlayer = player.sprite.getPosition().x;
                float yPlayer = player.sprite.getPosition().y + 20;
                Bullet gun(Vector2f(xPlayer, yPlayer), player.direction);
                bullets.push_back(gun);
                int c = 0;
                for (auto &r : bullets)
                {
                    r.update(player);
                    if (r.shape.getGlobalBounds().getPosition().x == enemy1.sprite.getGlobalBounds().getPosition().x ||
                        r.shape.getGlobalBounds().getPosition().y == enemy1.sprite.getGlobalBounds().getPosition().y)
                    {
                        c = c + r.daño;
                        r.hit = 1;

                        cout << "hit, vida de anubis: " << c << endl;
                    }

                    r.drawTo(window);
                    if (r.shape.getGlobalBounds().getPosition().x == 600 || r.shape.getGlobalBounds().getPosition().x == 0)
                    {
                        r.vel = 0;
                    }
                    while (c <= enemy1.vida) window.draw(enemy1.sprite);
                }
            }
        }

        window.display();
    }

    return 0;
}
