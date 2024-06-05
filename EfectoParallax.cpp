#include "EfectoParallax.hpp"

Background::Background(Texture &skyTexture, Texture &shadowTexture, Texture &pyramidTexture, Texture &desertTexture, Texture &trainTexture, Texture &barraVidaTexture)
{
    skySprite.setTexture(skyTexture);
    barraVidaSprite.setTexture(barraVidaTexture);
    shadowSprite.setTexture(shadowTexture);
    pyramidSprite.setTexture(pyramidTexture);
    desertSprite.setTexture(desertTexture);
    trainSprite.setTexture(trainTexture);

    desertSprite.setScale(2,2);

    skySprite.setPosition(0, 0);
    barraVidaSprite.setPosition(0, 0);
    shadowSprite.setPosition(0, 20);
    pyramidSprite.setPosition(0, -100);
    desertSprite.setPosition(0, 0);  
    trainSprite.setPosition(0, -100);  

    skySprite.setTextureRect(IntRect(0, 0, 120000, 600));
    shadowSprite.setTextureRect(IntRect(0, 0, 120000, 600));
    pyramidSprite.setTextureRect(IntRect(0, 0, 120000, 600));
    desertSprite.setTextureRect(IntRect(0, 0, 120000, 600));
    trainSprite.setTextureRect(IntRect(0, 0, 120000, 600));
}

void Background::move(float shadowSpeed, float pyramidSpeed, float desertSpeed, float)
{
    shadowSprite.move(-shadowSpeed, 0);
    pyramidSprite.move(-pyramidSpeed, 0);
    desertSprite.move(-desertSpeed, 0);

    if (shadowSprite.getPosition().x <= -120000) {
        shadowSprite.setPosition(0, shadowSprite.getPosition().y);
    }
    if (pyramidSprite.getPosition().x <= -120000) {
        pyramidSprite.setPosition(0, pyramidSprite.getPosition().y);
    }
    if (desertSprite.getPosition().x <= -120000) {
        desertSprite.setPosition(0, desertSprite.getPosition().y);
    }
}

void Background::draw(RenderWindow &window)
{
    window.draw(skySprite);
    window.draw(barraVidaSprite);
    window.draw(shadowSprite);
    window.draw(pyramidSprite);
    window.draw(desertSprite);
    window.draw(trainSprite);
}
