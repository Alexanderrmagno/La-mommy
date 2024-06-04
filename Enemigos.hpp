#ifndef Enemigos_hpp
#define Enemigos_hpp


#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath> // Para abs

using namespace std;
using namespace sf;

class Enemy {
public:
    Sprite sprite;
    float speed;
    int direction; // 1 para derecha, -1 para izquierda
    float attackDistance; // Distancia para atacar al jugador
    int frame; // Para manejar la animación de los sprites
    vector<Texture> textures;
    float timeSinceLastFrame; // Tiempo transcurrido desde el último cambio de fotograma
    float frameInterval; // Intervalo de tiempo entre cambios de fotograma
    int playerLife; // Vida del jugador
    Texture gameOverTexture;
    Sprite gameOverSprite;

    Enemy(const vector<Texture>& enemyTextures, float x, float y, float speed, float frameInterval, Texture& gameOverTex);
    void update(float deltaTime, Sprite& player, Texture& playerHurtTexture);
    void move();
    void animate(float deltaTime);
    bool isNearPlayer(const Sprite& player);
    void attack(Sprite& player, Texture& playerHurtTexture);
    void checkGameOver(RenderWindow& window);
};

#endif