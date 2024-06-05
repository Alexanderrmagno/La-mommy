#ifndef Enemigos_hpp
#define Enemigos_hpp

#include <SFML/Graphics.hpp>
#include "Jugador.hpp"

using namespace sf;

class Enemy
{
public:
    std::vector<Texture> textures;
    bool alive;
    Sprite sprite;
    float speed;
    int direction;
    float attackDistance;
    int frame;
    float timeSinceLastFrame;
    float frameInterval;
    int playerLife;
    Texture &gameOverTexture;
    Texture &playerHurtTexture;  // Añadido
    bool gameOver;
    Clock attackClock;
    Time attackCooldown;

    Enemy(const std::vector<Texture> &enemyTextures, float x, float y, float speed, float frameInterval, Texture &gameOverTexture, Texture &playerHurtTexture, bool alive);

    void update(float deltaTime, Player &player);
    void move();
    void animate(float deltaTime);
    bool isNearPlayer(const Sprite &player);
    void attack(Player &player);
    void checkGameOver(RenderWindow &window);
};

#endif
