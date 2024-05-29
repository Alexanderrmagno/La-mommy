#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
using namespace std;
using namespace sf;

int main()
{
    // Crear una ventana SFML
    RenderWindow window(VideoMode(600, 600), "Parallax Effect");
    window.setFramerateLimit(60);

    // Cargar texturas
    Texture skyTexture, shadowTexture, pyramidTexture, desertTexture, trainTexture, characterTexture;
    if (!skyTexture.loadFromFile("fondos/fondosky.png") ||
        !shadowTexture.loadFromFile("fondos/Sombras.png") ||
        !pyramidTexture.loadFromFile("fondos/primamid-pixilart.png") ||
        !desertTexture.loadFromFile("fondos/Vias del tren.png") ||
        !trainTexture.loadFromFile("fondos/gohancomoquedolamoto.png") ||
        !characterTexture.loadFromFile("fondos/Izquierda.png"))
    {
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

    // Bucle principal
    while (window.isOpen())
    {
        if(characterSprite.getGlobalBounds().getPosition().y < groundLevel){
            pisando = 0;
        }else{
            pisando = 1;
        }
        // Procesar eventos
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::W && (pisando== 1))
                {
                    cout << "salto" << endl;
                    velocityY = -15.f;
                    gravity = 1.f;
                }
            }
        }

        // Mover el personaje con WASD
        velocityY += gravity;

        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            characterSprite.setScale(0.7, 0.7);
            characterSprite.move(-characterSpeed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
                characterSprite.setScale(-0.7, 0.7);
            characterSprite.move(characterSpeed, 0);
        }

        // Aplicar gravedad
        characterSprite.move(0, velocityY);

        // Verificar colisión con el suelo
        if (characterSprite.getGlobalBounds().getPosition().y > groundLevel)
        {
            characterSprite.move(0, -velocityY);
            gravity = 0;
        }
        // Verificar si el personaje se sale de la pantalla
        if (characterSprite.getGlobalBounds().getPosition().x < 0)
        {
            characterSprite.setPosition(600, 335); // Reposicionar en el lado opuesto
        }
        if (characterSprite.getGlobalBounds().getPosition().x > 600 )
        {
            characterSprite.setPosition(50, 335); // Reposicionar en el lado opuesto
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