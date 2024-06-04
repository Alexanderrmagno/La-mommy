#ifndef Jugador_hpp
#define Jugador_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

class Player {
public:
    Sprite sprite;
    float speed;
    float gravity;
    float velocityY;
    float groundLevel;
    bool pisando;
    bool direction;

    Player(Texture& texture, float x, float y, float speed, float groundLevel);
    void handleInput();
    void applyGravity();
    void updatePosition();
    void checkBounds(float screenWidth);
};

#endif 
