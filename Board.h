#pragma once
#include <fstream>
#include <random>
#include <ctime>
#include <map>
#include "Tile.h"

// Buttons
class HappyFace : public sf::Sprite {
    sf::Vector2<float> position;
public:
    HappyFace();
    sf::Vector2<float> getPositionVect();
};

class Counter : public sf::Sprite {
    int flag_counter;
public:
    Counter();
    void setFlagCounter(int flags, int num_mines);
    int getFlagCounter();
};

class Debug : public sf::Sprite {
    sf::Vector2<float> position;
public:
    Debug();
    sf::Vector2<float> getPositionVect();
};

class Pause : public sf::Sprite {
    sf::Vector2<float> position;
public:
    Pause();
    sf::Vector2<float> getPositionVect();
};

class LeaderboardButton : public sf::Sprite {
    sf::Vector2<float> position;
public:
    LeaderboardButton();
    sf::Vector2<float> getPositionVect();
};

// Board
class Board {
    std::vector<std::vector<Tile>> myTiles {};
    int num_in_row;
    int num_in_col;
    int mine_count;
    int flag_count;
    bool timer_start;
    bool paused;
    bool debugMode;
    bool gameOver;
    bool gameWon;
    sf::Texture tempTexture;
public:
    Board();
    int getNumRow();
    int getNumCol();
    int getFlagCount();
    bool getPauseStatus();
    void setPauseStatus();
    void unsetPauseStatus();
    bool getGameWon();
    bool getGameOver();
    bool getTimerStart();
    void setTimerStart();
    void unsetTimerStart();
    std::vector<std::vector<Tile>> getMyTiles();
    void DisplayHiddenStatus(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map);
    void setFlagImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map);
    void setMineImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map);
    void setNumberImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map);
    void setHappyFaceImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map, HappyFace& happyFace);
    void setCounterImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map, Counter& counter);
    void setDebugImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map, Debug& debug);
    void setDebuggedMineImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map);
    void setPauseImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map, Pause& pause);
    void setPausedMineImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map);
    void setLeaderboardButtonImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map, LeaderboardButton& leaderboardButton);
    void setTimerImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map, long long min, long long sec);
    void FillTileNeighbors();
    void UpdateNearbyMineCount();
    void PlaceMines(std::mt19937& mt);
    bool MoveMine(Tile& oldTile, sf::Vector2<float>& mouse_pos);
    void MineCount();
    int IntMineCount();
    void PlaceTiles();
    void setTempTexture(sf::Texture& texture);
    void LeftClickDebugToggle(sf::Vector2<float>& mouse_pos, Debug& debug);
    void LeftClickPauseToggle(sf::Vector2<float>& mouse_pos, Pause& pause);
    bool LeftClickResetButton (sf::Vector2<float>& mouse_pos, HappyFace& happyFace, std::mt19937& mt, bool& first_click);
    void LeftClickTile(sf::Vector2<float>& mouse_pos, bool& first_click);
    void RightClickTile(sf::Vector2<float>& mouse_pos);
    void GameOver();
    void CheckGameWin();
    void GameWon();
};