#include "Enemigos.hpp"
#include <iostream>

Enemy::Enemy(const vector<Texture>& enemyTextures, float x, float y, float speed, float frameInterval)
    : textures(enemyTextures), speed(speed), direction(1), attackDistance(50.0f), frame(0),
      timeSinceLastFrame(0.0f), frameInterval(frameInterval) {
    sprite.setTexture(textures[frame]);
    sprite.setPosition(x, y);
}

void Enemy::update(float deltaTime) {
    move();
    animate(deltaTime);
}

void Enemy::move() {
    sprite.move(speed * direction, 0);
    if (sprite.getPosition().x < 0 || sprite.getPosition().x + sprite.getGlobalBounds().width > 600) {
        direction *= -1;
    }
}

void Enemy::animate(float deltaTime) {
    timeSinceLastFrame += deltaTime;
    if (timeSinceLastFrame >= frameInterval) {
        frame = (frame + 1) % textures.size();
        sprite.setTexture(textures[frame]);
        timeSinceLastFrame = 0.0f;
    }
}

bool Enemy::isNearPlayer(const Sprite& player) {
    return abs(sprite.getPosition().x - player.getPosition().x) < attackDistance;
}

void Enemy::attack(const Sprite& player) {
    if (isNearPlayer(player)) {
        cout << "Enemy attacks the player!" << endl;
    }
}
