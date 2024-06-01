#ifndef Mainmenu_hpp
#define Mainmenu_hpp

#include <SFML/Graphics.hpp>
#include <vector>

class MainMenu {
public:
    MainMenu(float width, float height);
    ~MainMenu() = default;

    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menu;
};

#endif