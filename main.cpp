#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;

int main() {
    // Crear una ventana SFML
    RenderWindow window(sf::VideoMode(600, 600), "Parallax Effect");

    // Cargar texturas
    Texture skyTexture, shadowTexture, pyramidTexture, desertTexture, trainTexture, characterTexture;
    if (!skyTexture.loadFromFile("fondos/fondosky.png") ||
        !shadowTexture.loadFromFile("fondos/Sombras.png") ||
        !pyramidTexture.loadFromFile("fondos/primamid-pixilart.png") ||
        !desertTexture.loadFromFile("fondos/Vias del tren.png") ||
        !trainTexture.loadFromFile("fondos/gohancomoquedolamoto.png") ||
        !characterTexture.loadFromFile("fondos/boptoronja.png")) {
        return -1; // Error cargando las imágenes
    }

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

    // Configurar las escalas y rectángulos de textura si es necesario
    characterSprite.setScale(0.7, 0.7);
    desertSprite.setScale(2, 2);
    desertSprite.setTextureRect(IntRect(0, 0, 120000, 600));
    shadowSprite.setTextureRect(IntRect(0, 0, 120000, 600));
    pyramidSprite.setTextureRect(IntRect(0, 0, 120000, 600));

    // Configurar las posiciones iniciales
    skySprite.setPosition(0, 0);
    shadowSprite.setPosition(0, 20);
    pyramidSprite.setPosition(0, 0);
    desertSprite.setPosition(0, 0);
    trainSprite.setPosition(0, -100);
    characterSprite.setPosition(300, 330); // Centro de la pantalla, 100 arriba del suelo (ubicación del tren)

    // Configurar las velocidades de desplazamiento
    float shadowSpeed = 0.1f;
    float pyramidSpeed = 0.2f;
    float desertSpeed = 0.5f;

    float characterSpeed = 0.05f;

    // Bucle principal
    while (window.isOpen()) {
        // Procesar eventos
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Movimiento del personaje con WASD
        if (Keyboard::isKeyPressed(Keyboard::W))
            characterSprite.move(0, -characterSpeed);
        if (Keyboard::isKeyPressed(Keyboard::S))
            characterSprite.move(0, characterSpeed);
        if (Keyboard::isKeyPressed(Keyboard::A))
            characterSprite.move(-characterSpeed, 0);
        if (Keyboard::isKeyPressed(Keyboard::D))
            characterSprite.move(characterSpeed, 0);

        // Verificar si el personaje se sale de la pantalla
        if (characterSprite.getPosition().x < 0 || characterSprite.getPosition().x > window.getSize().x ||
            characterSprite.getPosition().y < 0 || characterSprite.getPosition().y > window.getSize().y) {
            characterSprite.setPosition(300, 330); // Reposicionar en el origen
        }



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

        // Mostrar lo dibujado en la ventana
        window.display();
    }
       return 0;
}