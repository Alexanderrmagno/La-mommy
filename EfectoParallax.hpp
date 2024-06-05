#ifndef EfectoParallax_hpp
#define EfectoParallax_hpp

#include <SFML/Graphics.hpp>

using namespace sf;

class Background
{
public:
    Sprite skySprite;
    Sprite shadowSprite;
    Sprite pyramidSprite;
    Sprite desertSprite;
    Sprite trainSprite;
    Sprite barraVidaSprite;

    Background(Texture &skyTexture, Texture &shadowTexture, Texture &pyramidTexture, Texture &desertTexture, Texture &trainTexture, Texture &barraVidaTexture);

    void move(float shadowSpeed, float pyramidSpeed, float desertSpeed, float trainSpeed);
    void draw(RenderWindow &window);
};

#endif
