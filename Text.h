#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "windows.h"
#include <SFML/Graphics.hpp>

class BaseText : public sf::Text {
public:
    // only here to make BaseText an Abstract Base Class
    // Tried with Destructor, but got errors for undefined reference
    virtual void nothing() = 0;
};

class WelcomeScreenText : public BaseText {
    sf::Font font;
public:
    WelcomeScreenText();
    void nothing() {};
};

class EnterYourNameText : public BaseText {
    sf::Font font;
public:
    EnterYourNameText();
    void nothing() {};
};

class UserTypedNameText : public BaseText {
    sf::Font font;
    std::string _name;
public:
    UserTypedNameText();
    std::string getName();
    void setName(std::string newName);
    void updateName(char& myChar);
    void removeLetter();
    void nothing() {};
};

class LeaderboardTitleText : public BaseText {
    sf::Font font;
public:
    LeaderboardTitleText();
    void nothing() {};
};

class LeaderBoardContent : public BaseText {
    sf::Font font;
public:
    LeaderBoardContent(LeaderBoard& leaderBoard);
    void updateContent(LeaderBoard& leaderBoard);
    void nothing() {};
};