#include <SFML/Graphics.hpp>
#include "Heroe.hpp"
#include <vector>
using namespace sf;

int main() {
    
    // Crear una ventana SFML
    sf::RenderWindow window(sf::VideoMode(800, 800), "Parallax Effect");

    // Cargar texturas
    Texture skyTexture, shadowTexture, pyramidTexture, desertTexture;
    if (!skyTexture.loadFromFile("fondonoche.png") ||
        !shadowTexture.loadFromFile("Sombras.png") ||
        !pyramidTexture.loadFromFile("piramid-pixilart.png") ||
        !desertTexture.loadFromFile("Vias del tren.png")){ //||
        //!trainTexture.loadFromFile("train.png")) 
        
        return -1; // Error cargando las imágenes
    }

    // Crear sprites
    Sprite skySprite(skyTexture);
    Sprite shadowSprite(shadowTexture);
    Sprite pyramidSprite(pyramidTexture);
    Sprite desertSprite(desertTexture);
    Sprite trainSprite(trainTexture);

    // Configurar las posiciones iniciales
    skySprite.setPosition(0, 0);
    shadowSprite.setPosition(0, 300);
    pyramidSprite.setPosition(0, 200);
    desertSprite.setPosition(0, 400);
    //trainSprite.setPosition(100, 450);

    // Configurar las velocidades de desplazamiento
    float skySpeed = 0.0f;
    float shadowSpeed = 0.1f;
    float pyramidSpeed = 0.2f;
    float desertSpeed = 0.5f;
    //float trainSpeed = 0.5f;

    // Bucle principal
    while (window.isOpen()) {
        // Procesar eventos
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Actualizar las posiciones de los sprites
        shadowSprite.move(-shadowSpeed, 0);
        pyramidSprite.move(-pyramidSpeed, 0);
        desertSprite.move(-desertSpeed, 0);
        //trainSprite.move(-trainSpeed, 0);

        // Resetear las posiciones si salen de la pantalla
        if (shadowSprite.getPosition().x <= -shadowTexture.getSize().x)
            shadowSprite.setPosition(0, 300);
        if (pyramidSprite.getPosition().x <= -pyramidTexture.getSize().x)
            pyramidSprite.setPosition(0, 200);
        if (desertSprite.getPosition().x <= -desertTexture.getSize().x)
            desertSprite.setPosition(0, 400);
        /*if (trainSprite.getPosition().x <= -trainTexture.getSize().x)
            trainSprite.setPosition(0, 450);
*/
        // Limpiar la ventana
        window.clear();

        // Dibujar los sprites en orden
        window.draw(skySprite);
        window.draw(shadowSprite);
        window.draw(pyramidSprite);
        window.draw(desertSprite);
        //window.draw(trainSprite);

        // Mostrar lo dibujado en la ventana
        window.display();
    }
    return bazinga();
}