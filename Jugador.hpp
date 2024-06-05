#ifndef Jugador_hpp
#define Jugador_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

class Player
{
public:
    Sprite sprite;
    Texture originalTexture;
    float speed;
    float groundLevel;
    float velocityY;
    float gravity;
    bool pisando;
    bool direction;
    Clock hurtClock;   // Reloj para manejar el tiempo de la textura de herido
    Time hurtDuration; // Duración durante la cual se muestra la textura de herido

    Player(Texture &texture, float x, float y, float speed, float groundLevel);

    void handleInput();
    void applyGravity();
    void checkBounds(float windowWidth);
    void resetTexture(); // Método para resetear la textura del jugador
};

#endif
