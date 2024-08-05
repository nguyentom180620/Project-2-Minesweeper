#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

class WelcomeWindow : public sf::RenderWindow {
public:
    WelcomeWindow();
};

class GameWindow : public sf::RenderWindow {
public:
    GameWindow();
};

class LeaderBoard : public sf::RenderWindow {
    std::vector<std::string> winners {};
    std::string temp_name;
    int temp_min;
    int temp_sec;
    bool collected_time;
    std::string log_name;
public:
    LeaderBoard();
    void setTempName(std::string name);
    void setMinute(int min);
    void setSecond(int sec);
    void setCollectedTimeBoolTrue();
    void setCollectedTimeBoolFalse();
    bool getCollectedTimeBool();
    void makeLogName();
    void clearWinnersAsterisk();
    void insertLogName();
    void printWinners();
    void getWinnersFromTxt();
    void updateWinnersInTxt();
    void reOpen();
    std::string getLogName();
    std::vector<std::string> getWinners();
};