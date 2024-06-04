#include "EfectoParallax.hpp"

Background::Background(Texture& skyTexture, Texture& shadowTexture, Texture& pyramidTexture, Texture& desertTexture, Texture& trainTexture) {
    skySprite.setTexture(skyTexture);
    shadowSprite.setTexture(shadowTexture);
    pyramidSprite.setTexture(pyramidTexture);
    desertSprite.setTexture(desertTexture);
    trainSprite.setTexture(trainTexture);

    skySprite.setPosition(0, 0);
    shadowSprite.setPosition(0, 20);
    pyramidSprite.setPosition(0, -100);
    desertSprite.setPosition(0, 0);
    trainSprite.setPosition(0, -100);
    
    shadowSprite.setTextureRect(IntRect(0, 0, 120000, 600));
    pyramidSprite.setTextureRect(IntRect(0, 0, 120000, 600));
    desertSprite.setTextureRect(IntRect(0, 0, 120000, 600));
}

void Background::move(float shadowSpeed, float pyramidSpeed, float desertSpeed) {
    shadowSprite.move(-shadowSpeed, 0);
    pyramidSprite.move(-pyramidSpeed, 0);
    desertSprite.move(-desertSpeed, 0);
}

void Background::draw(RenderWindow& window) {
    window.draw(skySprite);
    window.draw(shadowSprite);
    window.draw(pyramidSprite);
    window.draw(desertSprite);
    window.draw(trainSprite);
}