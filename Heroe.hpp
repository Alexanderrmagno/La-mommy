#ifndef Heroe_hpp
#define Heroe_hpp

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int bazinga() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Movimiento de personaje con WASD");

    // Cargar la textura del personaje
    sf::Texture texture;
    if (!texture.loadFromFile("character.png")) {
        std::cerr << "Error al cargar la imagen character.png" << std::endl;
        return -1;
    }

    // Crear el sprite y asignarle la textura
    sf::Sprite character(texture);
    character.setPosition(400.f, 400.f); // Posición inicial del personaje en el centro

    // Dimensiones del cuadrado
    const float speed = 200.f; // Velocidad de movimiento en píxeles por segundo

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Calcular el tiempo transcurrido desde el último frame
        float deltaTime = clock.restart().asSeconds();

        // Movimiento del personaje
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement.y -= speed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement.y += speed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.x -= speed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.x += speed * deltaTime;
        }

        character.move(movement);

        window.clear();
        window.draw(character);
        window.display();
    }

    return 0;
}







#endif