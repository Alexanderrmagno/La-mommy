#include "Enemigos.hpp"
#include "Jugador.hpp"
#include <iostream>

Enemy::Enemy(const std::vector<Texture> &enemyTextures, float x, float y, float speed, float frameInterval, Texture &gameOverTexture, Texture &playerHurtTexture, bool alive)
    : textures(enemyTextures), speed(speed), direction(1), attackDistance(50.0f), frame(0),
      timeSinceLastFrame(0.0f), frameInterval(frameInterval), playerLife(15), gameOverTexture(gameOverTexture), playerHurtTexture(playerHurtTexture), gameOver(false)
{
    sprite.setTexture(textures[frame]);
    sprite.setPosition(x, y);
    attackCooldown = seconds(1); // Tiempo de enfriamiento de 1 segundo
}

void Enemy::update(float deltaTime, Player &player)
{
    if (alive)
    {
    move();
    animate(deltaTime);
    if (attackClock.getElapsedTime() >= attackCooldown)
    {
        attack(player);
    }
    player.resetTexture(); // Verifica si es momento de resetear la textura del jugador
    }
}

void Enemy::move()
{
    if (alive)
    {
    sprite.move(speed * direction, 0);
    if (sprite.getPosition().x < 0 || sprite.getPosition().x + sprite.getGlobalBounds().width > 600)
    {
        direction *= -1;
    }
    }
}

void Enemy::animate(float deltaTime)
{
    if (alive)
    {
    timeSinceLastFrame += deltaTime;
    if (timeSinceLastFrame >= frameInterval)
    {
        frame = (frame + 1) % textures.size();
        sprite.setTexture(textures[frame]);
        timeSinceLastFrame = 0.0f;
    }
    }
}

bool Enemy::isNearPlayer(const Sprite &player)
{
    if (alive)
    {
    return abs(sprite.getPosition().x - player.getPosition().x) < attackDistance;
    }
}

void Enemy::attack(Player &player)
{
 if (alive)
    {
    if (isNearPlayer(player.sprite))
    {
        playerLife -= 1;
        std::cout << "Enemy attacks the player! Player life: " << playerLife << std::endl;
        player.sprite.setTexture(playerHurtTexture); // Cambia la textura del jugador a la textura de daño
        player.hurtClock.restart();                  // Reinicia el reloj de herido
        attackClock.restart();                       // Reinicia el reloj de ataque
    }
    }
}

void Enemy::checkGameOver(RenderWindow &window)
{
    if (alive)
    {
    if (playerLife <= 0)
    {
        gameOver = true;
        Sprite gameOverSprite(gameOverTexture);
        gameOverSprite.setPosition(100, 150); // Ajusta la posición según sea necesario
        window.clear();
        window.draw(gameOverSprite);
        window.display();
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }
        }
    }
    }
}

