#ifndef Enemigos_hpp
#define Enemigos_hpp

#include <SFML/Graphics.hpp>
#include "Jugador.hpp"
#include <vector>

using namespace sf;

class Enemy {
public:
    std::vector<Texture> textures;
    std::vector<Texture> barraVidaTextures; // Añadido
    Sprite sprite;
    Sprite barraVidaSprite; // Añadido
    float speed;
    int direction;
    float attackDistance;
    int frame;
    float timeSinceLastFrame;
    float frameInterval;
    int playerLife;
    Texture& gameOverTexture;
    Texture& playerHurtTexture;
    bool gameOver;
    Clock attackClock;
    Time attackCooldown;

    Enemy(const std::vector<Texture>& enemyTextures, float x, float y, float speed, float frameInterval, Texture& gameOverTexture, Texture& playerHurtTexture, const std::vector<Texture>& barraVidaTextures); // Modificado

    void update(float deltaTime, Player& player);
    void move();
    void animate(float deltaTime);
    bool isNearPlayer(const Sprite& player);
    void attack(Player& player);
    void checkGameOver(RenderWindow& window);
    void updateBarraVida(); // Añadido
};

#endif

