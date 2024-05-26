#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    // Crear una ventana SFML
    sf::RenderWindow window(sf::VideoMode(800, 800), "Parallax Effect");

    // Cargar texturas
    sf::Texture skyTexture, shadowTexture, pyramidTexture, desertTexture, trainTexture;
    if (!skyTexture.loadFromFile("sky.png") ||
        !shadowTexture.loadFromFile("shadow.png") ||
        !pyramidTexture.loadFromFile("pyramid.png") ||
        !desertTexture.loadFromFile("desert.png") ||
        !trainTexture.loadFromFile("train.png")) {
        return -1; // Error cargando las imágenes
    }

    // Crear sprites
    sf::Sprite skySprite(skyTexture);
    sf::Sprite shadowSprite(shadowTexture);
    sf::Sprite pyramidSprite(pyramidTexture);
    sf::Sprite desertSprite(desertTexture);
    sf::Sprite trainSprite(trainTexture);

    // Configurar las posiciones iniciales
    skySprite.setPosition(0, 0);
    shadowSprite.setPosition(0, 300);
    pyramidSprite.setPosition(0, 200);
    desertSprite.setPosition(0, 400);
    trainSprite.setPosition(100, 450);

    // Configurar las velocidades de desplazamiento
    float skySpeed = 0.0f;
    float shadowSpeed = 0.1f;
    float pyramidSpeed = 0.2f;
    float desertSpeed = 0.5f;
    float trainSpeed = 0.5f;

    // Bucle principal
    while (window.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualizar las posiciones de los sprites
        shadowSprite.move(-shadowSpeed, 0);
        pyramidSprite.move(-pyramidSpeed, 0);
        desertSprite.move(-desertSpeed, 0);
        trainSprite.move(-trainSpeed, 0);

        // Resetear las posiciones si salen de la pantalla
        if (shadowSprite.getPosition().x <= -shadowTexture.getSize().x)
            shadowSprite.setPosition(0, 300);
        if (pyramidSprite.getPosition().x <= -pyramidTexture.getSize().x)
            pyramidSprite.setPosition(0, 200);
        if (desertSprite.getPosition().x <= -desertTexture.getSize().x)
            desertSprite.setPosition(0, 400);
        if (trainSprite.getPosition().x <= -trainTexture.getSize().x)
            trainSprite.setPosition(0, 450);

        // Limpiar la ventana
        window.clear();

        // Dibujar los sprites en orden
        window.draw(skySprite);
        window.draw(shadowSprite);
        window.draw(pyramidSprite);
        window.draw(desertSprite);
        window.draw(trainSprite);

        // Mostrar lo dibujado en la ventana
        window.display();
    }

    return 0;
}