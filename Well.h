#pragma once
#include <SFML/Graphics.hpp>

#include "Tetromino.h"
class Well {
private:
    sf::RenderWindow& window;
    int Height = 20;
    int width = 10;
    sf::RectangleShape well[20][10];

public:
    // constructor
    Well(sf::RenderWindow& window) : window(window) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                well[i][j] = sf::RectangleShape();
                well[i][j].setPosition(sf::Vector2f(j * 50.0f, i * 50.0f));
                well[i][j].setSize(sf::Vector2f(50.0f, 50.0f));
                well[i][j].setFillColor(sf::Color::White);
                // well[i][j].setFillColor(sf::Color(0x0A0A0AFF));

                well[i][j].setOutlineColor(sf::Color::Black);
                well[i][j].setOutlineThickness(3);
            }
        }
    }
    // to draw well

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 10; ++j) {
                window.draw(well[i][j]);
            }
        }
    }
};