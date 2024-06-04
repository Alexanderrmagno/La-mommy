#include "Jugador.hpp"

Player::Player(Texture& texture, float x, float y, float speed, float groundLevel)
    : speed(speed), gravity(0.f), velocityY(0.f), groundLevel(groundLevel), pisando(0), direction(1) {
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(0.7, 0.7);
}

void Player::handleInput() {
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        sprite.setScale(0.7, 0.7);
        sprite.move(-speed, 0);
        direction = 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        sprite.setScale(-0.7, 0.7);
        sprite.move(speed, 0);
        direction = 0;
    }
    if (Keyboard::isKeyPressed(Keyboard::W) && pisando) {
        std::cout << "salto" << std::endl;
        velocityY = -15.f;
        gravity = 1.f;
    }
}

void Player::applyGravity() {
    velocityY += gravity;
    sprite.move(0, velocityY);
    if (sprite.getPosition().y > groundLevel) {
        sprite.setPosition(sprite.getPosition().x, groundLevel);
        gravity = 0;
        velocityY = 0;
        pisando = 1;
    } else {
        pisando = 0;
    }
}

void Player::updatePosition() {
    sprite.move(0, velocityY);
}

void Player::checkBounds(float screenWidth) {
    if (sprite.getPosition().x < 0) {
        sprite.setPosition(screenWidth, sprite.getPosition().y);
    }
    if (sprite.getPosition().x > screenWidth) {
        sprite.setPosition(0, sprite.getPosition().y);
    }
}
