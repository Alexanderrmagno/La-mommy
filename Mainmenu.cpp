#include "MainMenu.hpp"

MainMenu::MainMenu(float width, float height) {
    if (!font.loadFromFile("Fonts/")) {
        // Manejar error
    }

    sf::Text playText;
    playText.setFont(font);
    playText.setFillColor(sf::Color::Red);
    playText.setString("Jugar");
    playText.setPosition(sf::Vector2f(width / 2 - 50, height / 2 - 50));
    menu.push_back(playText);

    sf::Text exitText;
    exitText.setFont(font);
    exitText.setFillColor(sf::Color::White);
    exitText.setString("Terminar");
    exitText.setPosition(sf::Vector2f(width / 2 - 50, height / 2 + 50));
    menu.push_back(exitText);

    selectedItemIndex = 0;
}

void MainMenu::draw(sf::RenderWindow &window) {
    if (backgroundSprite.getTexture()) {
        window.draw(backgroundSprite);
    }
    for (auto &item : menu) {
        window.draw(item);
    }
}

void MainMenu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void MainMenu::moveDown() {
    if (selectedItemIndex + 1 < menu.size()) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void MainMenu::setOptionText(int index, const std::string& text) {
    if (index >= 0 && index < menu.size()) {
        menu[index].setString(text);
    }
}

void MainMenu::setBackground(const sf::Texture &texture) {
    backgroundSprite.setTexture(texture);
}

