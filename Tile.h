#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Tile : public sf::Sprite {
    bool hidden_status;
    bool flag_status;
    bool has_mine;
    int num_of_mines_nearby;
    sf::Vector2<float> tileVect;
    std::vector<Tile*> neighbors {};
public:
    Tile();
    bool getHiddenStatus();
    bool getFlagStatus();
    bool getMineStatus();
    int getNumOfMines();
    std::vector<Tile*> getNeighbors();
    void setRevealed();
    void setHidden();
    void recursiveReveal();
    void setFlag();
    void unsetFlag();
    void setMine();
    void unsetMine();
    void updateNearbyMineCount();
    void setLocation(int x, int y);
    void addNeighbor(Tile* neighborTile);
    int get_x_value();
    int get_y_value();
    sf::Vector2<float> getTileVect();
};
