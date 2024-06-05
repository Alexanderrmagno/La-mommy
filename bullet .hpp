#include "Jugador.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

class Bullet
{
public:
    RectangleShape shape;
    int vel = 5.f;
    bool direct;

    Bullet(Vector2f position, bool direction)
    {
        this->shape.setPosition(position);
        this->shape.setSize(Vector2f(3, 5));
        this->shape.setFillColor(Color::Yellow);
        this->direct = direction;
    }

    void update(Player &player)
    {
        if (direct == 1)
        {
            this->shape.move(vel, 0);
        }
        if (direct == 0)
        {
            this->shape.move(-vel, 0);
        }
    }

    void drawTo(RenderWindow &window)
    {
        window.draw(this->shape);
    }
};
