#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

struct Bullet {
    RectangleShape shape;
    int vel = 5.f;
    bool direct;


    Bullet(Vector2f position, bool direction) {
        this->shape.setPosition(position);
        this->shape.setSize(Vector2f(10,4));
        this->shape.setFillColor(Color::Yellow);
        this->direct=direct;
    }

    Vector2f update() {
        if(direct == 1) vel=vel*(-1);

        this->shape.move(vel,0);
        return shape.getPosition();
    }
};


