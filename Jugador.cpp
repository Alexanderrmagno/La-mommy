#include "Jugador.hpp"
#include "bullet .hpp"
#include <iostream>

Player::Player(Texture &texture, float x, float y, float speed, float groundLevel)
    : originalTexture(texture), speed(speed), groundLevel(groundLevel), velocityY(0.f), gravity(0.f), pisando(false), hurtDuration(seconds(0.5f))
{
    sprite.setTexture(originalTexture);
    sprite.setPosition(x, y);
    sprite.setScale(0.7, 0.7);
}

void Player::handleInput()
{
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        sprite.setScale(0.7, 0.7);
        sprite.move(-speed, 0);
        direction = 0; // izquierda
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        sprite.setScale(-0.7, 0.7);
        sprite.move(speed, 0);
        direction = 1; // derecha
    }
    if (Keyboard::isKeyPressed(Keyboard::W) && pisando)
    {
        velocityY = -20.f;
        gravity = 1.f;
    }
}

void Player::applyGravity()
{
    velocityY += gravity;
    sprite.move(0, velocityY);

    if (sprite.getPosition().y >= groundLevel)
    {
        sprite.setPosition(sprite.getPosition().x, groundLevel);
        pisando = true;
        gravity = 0;
    }
    else
    {
        pisando = false;
    }
}

void Player::checkBounds(float windowWidth)
{
    if (sprite.getPosition().x < 0)
    {
        sprite.setPosition(windowWidth, sprite.getPosition().y);
    }
    if (sprite.getPosition().x > windowWidth)
    {
        sprite.setPosition(0, sprite.getPosition().y);
    }
}

void Player::resetTexture()
{
    if (hurtClock.getElapsedTime() >= hurtDuration)
    {
        sprite.setTexture(originalTexture);
    }
}