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

    Enemy(const vector<Texture>& enemyTextures, float x, float y, float speed, float frameInterval);
    void update(float deltaTime);
    void move();
    void animate(float deltaTime);
    bool isNearPlayer(const Sprite& player);
    void attack(const Sprite& player);
};








#endif