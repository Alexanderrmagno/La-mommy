#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // Incluye la biblioteca de audio
#include <vector>
#include <iostream>
#include <cmath> // Para abs
#include "MainMenu.hpp"
#include "bullet .hpp"
using namespace std;
using namespace sf;

class Enemy {
public:
    Sprite sprite;
    float speed;
    int direction; // 1 para derecha, -1 para izquierda
    float attackDistance; // Distancia para atacar al jugador
    int frame; // Para manejar la animación de los sprites
    vector<Texture> textures;
    float timeSinceLastFrame; // Tiempo transcurrido desde el último cambio de fotograma
    float frameInterval; // Intervalo de tiempo entre cambios de fotograma

    Enemy(const vector<Texture>& enemyTextures, float x, float y, float speed, float frameInterval)
        : textures(enemyTextures), speed(speed), direction(1), attackDistance(50.0f), frame(0),
          timeSinceLastFrame(0.0f), frameInterval(frameInterval) {
        sprite.setTexture(textures[frame]);
        sprite.setPosition(x, y);
    }

    void update(float deltaTime) {
        move();
        animate(deltaTime);
    }

    void move() {
        sprite.move(speed * direction, 0);
        if (sprite.getPosition().x < 0 || sprite.getPosition().x + sprite.getGlobalBounds().width > 600) {
            direction *= -1;
        }
    }

    void animate(float deltaTime) {
        timeSinceLastFrame += deltaTime;
        if (timeSinceLastFrame >= frameInterval) {
            frame = (frame + 1) % textures.size();
            sprite.setTexture(textures[frame]);
            timeSinceLastFrame = 0.0f;
        }
    }

    bool isNearPlayer(const Sprite& player) {
        return abs(sprite.getPosition().x - player.getPosition().x) < attackDistance;
    }

    void attack(const Sprite& player) {
        if (isNearPlayer(player)) {
            cout << "Enemy attacks the player!" << endl;
        }
    }

};

int main() {
    // Crear una ventana SFML
    RenderWindow window(VideoMode(600, 600), "La Mommy: la venganza de anubis");
    window.setFramerateLimit(60);

    // Crear el menú principal
    MainMenu menu(window.getSize().x, window.getSize().y);

    // Configurar la imagen de fondo del menú
    Texture menuBackgroundTexture;
    if (!menuBackgroundTexture.loadFromFile("fondos/alterno.png")) {
        return -1; // Error cargando la imagen de fondo del menú
    }
    menu.setBackground(menuBackgroundTexture);

    // Configurar los textos de las opciones del menú
    menu.setOptionText(0, "Jugar");
    menu.setOptionText(1, "Salir del juego");

    // Bucle principal del menú
    while (window.isOpen()) {
        // Procesar eventos
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
                        // Opción "Jugar" seleccionada
                        goto game_loop;
                    } else if (selectedItem == 1) {
                        // Opción "Terminar" seleccionada
                        window.close();
                    }
                }
            }
        }

        // Dibujar el menú principal
        window.clear();
        menu.draw(window);
        window.display();
    }

game_loop:
    // Cargar texturas
    Texture skyTexture, shadowTexture, pyramidTexture, desertTexture, trainTexture, characterTexture;
    if (!skyTexture.loadFromFile("fondos/fondosky.png") ||
        !shadowTexture.loadFromFile("fondos/Sombras.png") ||
        !pyramidTexture.loadFromFile("fondos/primamid-pixilart.png") ||
        !desertTexture.loadFromFile("fondos/Vias del tren.png") ||
        !trainTexture.loadFromFile("fondos/gohancomoquedolamoto.png") ||
        !characterTexture.loadFromFile("fondos/Izquierda.png")) {
        return -1; // Error cargando las imágenes
    }

    // Texturas del enemigo
    Texture enemyTexture1, enemyTexture2;
    if (!enemyTexture1.loadFromFile("fondos/Momia1-1.png") || !enemyTexture2.loadFromFile("fondos/Momia1-2.png")) {
        return -1; // Error cargando las imágenes del enemigo
    }
    vector<Texture> enemyTextures = {enemyTexture1, enemyTexture2};

    // Configurar las texturas repetidas si es necesario
    skyTexture.setRepeated(true);
    shadowTexture.setRepeated(true);
    pyramidTexture.setRepeated(true);
    desertTexture.setRepeated(true);

    // Crear sprites
    Sprite skySprite(skyTexture);
    Sprite shadowSprite(shadowTexture);
    Sprite pyramidSprite(pyramidTexture);
    Sprite desertSprite(desertTexture);
    Sprite trainSprite(trainTexture);
    Sprite characterSprite(characterTexture);

    // Crear el enemigo con un intervalo de fotograma de 0.5 segundos (ajusta según sea necesario)
    Enemy enemy(enemyTextures, 100, 335, 2.0f, 0.5f);

    // Configurar las escalas y rectángulos de textura si es necesario
    characterSprite.setScale(0.7, 0.7);
    desertSprite.setScale(2, 2);
    desertSprite.setTextureRect(IntRect(0, 0, 120000, 600));
    shadowSprite.setTextureRect(IntRect(0, 0, 120000, 600));
    pyramidSprite.setTextureRect(IntRect(0, 0, 120000, 600));

    // Configurar las posiciones iniciales
    skySprite.setPosition(0, 0);
    shadowSprite.setPosition(0, 20);
    pyramidSprite.setPosition(0, -100);
    desertSprite.setPosition(0, 0);
    trainSprite.setPosition(0, -100);
    characterSprite.setPosition(300, 335); // Centro de la pantalla, 100 arriba del suelo (ubicación del tren)

    // Configurar las velocidades de desplazamiento
    float shadowSpeed = 2.f;
    float pyramidSpeed = 5.f;
    float desertSpeed = 10.f;
    float characterSpeed = 3.f;

    // Gravedad
    float gravity = 0.f;
    float velocityY = 0.f;
    float groundLevel = 335; // Nivel del tren
    bool pisando = 0;
    bool direction = 1;

    // Reloj para medir el tiempo transcurrido
    Clock clock;

    // Cargar y reproducir música

    // Bucle principal del juego
    while (window.isOpen()) {

        // Calcular el tiempo transcurrido desde la última iteración
        float deltaTime = clock.restart().asSeconds();

        if(characterSprite.getGlobalBounds().top < groundLevel) {

        }
        if (characterSprite.getGlobalBounds().getPosition().y < groundLevel) {
            pisando = 0;
        } else {
            pisando = 1;
        }

        // Procesar eventos
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::W && (pisando == 1)) {
                    cout << "salto" << endl;
                    velocityY = -15.f;
                    gravity = 1.f;
                }
            }
        }

        // Mover el personaje con WASD
        velocityY += gravity;

        if (Keyboard::isKeyPressed(Keyboard::A)) {
            characterSprite.setScale(0.7, 0.7);
            characterSprite.move(-characterSpeed, 0);
            direction = 1;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            characterSprite.setScale(-0.7, 0.7);
            characterSprite.move(characterSpeed, 0);
            direction = 0;
        }
        cout << direction;

        // Aplicar gravedad
        characterSprite.move(0, velocityY);

        // Verificar colisión con el suelo
        if (characterSprite.getGlobalBounds().getPosition().y > groundLevel) {
            characterSprite.move(0, -velocityY);
            gravity = 0;
        }
        // Verificar si el personaje se sale de la pantalla
        if (characterSprite.getGlobalBounds().getPosition().x < 0) {
            characterSprite.setPosition(600, 335); // Reposicionar en el lado opuesto
        }
        if (characterSprite.getGlobalBounds().getPosition().x > 600) {
            characterSprite.setPosition(50, 335); // Reposicionar en el lado opuesto
        }

        cout << direction;

        //Disparar
        if (Keyboard::isKeyPressed(Keyboard::E))
        {
            Bullet gun(Vector2f(characterSprite.getGlobalBounds().getPosition().x, (characterSprite.getGlobalBounds().getPosition().y- 10)), direction);
            cout << "bullet";
            gun.drawTo(window);
        }

        // Actualizar el enemigo
        enemy.update(deltaTime);
        enemy.attack(characterSprite);

        cout << direction;

        // Actualizar las posiciones del escenario
        shadowSprite.move(-shadowSpeed, 0);
        pyramidSprite.move(-pyramidSpeed, 0);
        desertSprite.move(-desertSpeed, 0);

        // Limpiar la ventana
        window.clear();

        // Dibujar los sprites en orden
        window.draw(skySprite);
        window.draw(shadowSprite);
        window.draw(pyramidSprite);
        window.draw(desertSprite);
        window.draw(trainSprite);
        window.draw(characterSprite);
        window.draw(enemy.sprite); // Dibujar el enemigo

        // Mostrar lo dibujado en la ventana
        window.display();
    }

    return 0;
}


