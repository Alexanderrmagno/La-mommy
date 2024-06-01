#ifndef Mainmenu_HPP
#define Mainmenu_HPP

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

    void setOptionText(int index, const std::string& text);
    void setBackground(const sf::Texture &texture);

private:
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menu;
    sf::Sprite backgroundSprite;
};

#endif // MAINMENU_HPP
