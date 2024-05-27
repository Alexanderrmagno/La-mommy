#include <SFML/Graphics.hpp>
#include "Heroe.hpp"
#include <vector>
using namespace sf;

int main() {
    
    // Crear una ventana SFML
    RenderWindow window(sf::VideoMode(600, 600), "Parallax Effect");

    // Cargar texturas
    Texture skyTexture, shadowTexture, pyramidTexture, desertTexture;
    if (!skyTexture.loadFromFile("fondos/fondosky.png") ||
        !shadowTexture.loadFromFile("fondos/Sombras.png") ||
        !pyramidTexture.loadFromFile("fondos/primamid-pixilart.png") ||
        !desertTexture.loadFromFile("fondos/Vias del tren.png")){ //||
        //!trainTexture.loadFromFile("train.png")) 
        
        return -1; // Error cargando las imágenes
    }
   
    // skyTexture.setRepeated(true);
    // shadowTexture.setRepeated(true);
    // pyramidTexture.setRepeated(true);
    // desertTexture.setRepeated(true);
    // Crear sprites
    Sprite skySprite(skyTexture);
    Sprite shadowSprite(shadowTexture);
    Sprite pyramidSprite(pyramidTexture);
    Sprite desertSprite(desertTexture);
    desertSprite.setScale(2,2);
    desertSprite.setTextureRect(IntRect(0,0,1200,600));
    
    //Sprite trainSprite(trainTexture);

    // Configurar las posiciones iniciales
    skySprite.setPosition(0, 0);
    shadowSprite.setPosition(0, 20);
    pyramidSprite.setPosition(0, 0);
    desertSprite.setPosition(0, 0);
    //trainSprite.setPosition(100, 450);

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

        // shadowSprite.move(-shadowSpeed, 0);
        // pyramidSprite.move(-pyramidSpeed, 0);
        // desertSprite.move(-desertSpeed, 0);
        //trainSprite.move(-trainSpeed, 0);

        // Resetear las posiciones si salen de la pantalla
        // if (shadowSprite.getPosition().x <= -shadowTexture.getSize().x)
        //     shadowSprite.setPosition(0, 300);
        // if (pyramidSprite.getPosition().x <= -pyramidTexture.getSize().x)
        //     pyramidSprite.setPosition(0, 200);
        // if (desertSprite.getPosition().x <= -desertTexture.getSize().x)
        //     desertSprite.setPosition(0, 400);
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
    return 0;
}