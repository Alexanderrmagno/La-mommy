#ifndef EfectoParallax_hpp
#define EfectoParallax_hpp

#include <SFML/Graphics.hpp>

using namespace sf;

class Background {
public:
    Sprite skySprite;
    Sprite barraVidaSprite; // Cambiado el nombre a barraVidaSprite para ser consistente
    Sprite shadowSprite;
    Sprite pyramidSprite;
    Sprite desertSprite;
    Sprite trainSprite;

    Background(Texture& skyTexture, Texture& shadowTexture, Texture& pyramidTexture, Texture& desertTexture, Texture& trainTexture, Texture& barraVidaTexture);

    void move(float shadowSpeed, float pyramidSpeed, float desertSpeed);
    void draw(RenderWindow& window);
};

#endif
