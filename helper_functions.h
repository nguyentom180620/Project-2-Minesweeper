#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

// README This file holds a collections of helper functions, but this file is not to be included in other files
// as I don't know how to properly do that yet, although it seems namespace is useful to use

// Helper Functions
int getConfigX() {
    std::string temp_config_x;
    std::ifstream configFile("files/config.cfg");
    if (!configFile.is_open()) {
        std::cout << "Oh no! Config file didn't open :(" << std::endl;
    }
    std::getline(configFile, temp_config_x);
    return std::stoi(temp_config_x);
}

int getConfigY() {
    std::string temp_config_y;
    std::ifstream configFile("files/config.cfg");
    if (!configFile.is_open()) {
        std::cout << "Oh no! Config file didn't open :(" << std::endl;
    }
    configFile.ignore(100, '\n');
    std::getline(configFile, temp_config_y);
    return std::stoi(temp_config_y);
}

int getWelcomeHeight() {
    return getConfigY() * 32 + 100;;
}

int getWelcomeWidth() {
    return getConfigX() * 32;
}

void setText(sf::Text& text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2<float> (x, y));
}
