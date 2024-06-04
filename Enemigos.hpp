#ifndef Enemigos_hpp
#define Enemigos_hpp

#include <SFML/Graphics.hpp>
#include "Jugador.hpp"

using namespace sf;

class Enemy
{
public:
    std::vector<Texture> textures;
    Sprite sprite;
    float speed;
    int direction;
    float attackDistance;
    int frame;
    float timeSinceLastFrame;
    float frameInterval;
    int playerLife;
    Texture &gameOverTexture;
    bool gameOver;
    Clock attackClock;
    Time attackCooldown;

    Enemy(const std::vector<Texture> &enemyTextures, float x, float y, float speed, float frameInterval, Texture &gameOverTexture);

    void update(float deltaTime, Player &player);
    void move();
    void animate(float deltaTime);
    bool isNearPlayer(const Sprite &player);
    void attack(Player &player);
    void checkGameOver(RenderWindow &window);
};

#endif