#include "Enemigos.hpp"
#include <iostream>

Enemy::Enemy(const vector<Texture>& enemyTextures, float x, float y, float speed, float frameInterval, Texture& gameOverTex)
    : textures(enemyTextures), speed(speed), direction(1), attackDistance(50.0f), frame(0),
      timeSinceLastFrame(0.0f), frameInterval(frameInterval), playerLife(15), gameOverTexture(gameOverTex) {
    sprite.setTexture(textures[frame]);
    sprite.setPosition(x, y);
    gameOverSprite.setTexture(gameOverTexture);
    gameOverSprite.setPosition(100, 100); // Ajustar según sea necesario
}

void Enemy::update(float deltaTime, Sprite& player, Texture& playerHurtTexture) {
    move();
    animate(deltaTime);
    attack(player, playerHurtTexture);
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

void Enemy::attack(Sprite& player, Texture& playerHurtTexture) {
    if (isNearPlayer(player) && playerLife > 0) {
        playerLife -= 1;
        player.setTexture(playerHurtTexture);
        cout << "Player life: " << playerLife << endl;
    }
}

void Enemy::checkGameOver(RenderWindow& window) {
    if (playerLife <= 0) {
        window.clear();
        window.draw(gameOverSprite);
        window.display();
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
            }
        }
    }
}
