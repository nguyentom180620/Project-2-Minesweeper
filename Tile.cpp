#include "Tile.h"

Tile::Tile() {
    hidden_status = true;
    flag_status = false;
    has_mine = false;
    tileVect.x = 0;
    tileVect.y = 0;
}

bool Tile::getHiddenStatus() {
    return hidden_status;
}

bool Tile::getFlagStatus() {
    return flag_status;
}

bool Tile::getMineStatus() {
    return has_mine;
}

int Tile::getNumOfMines() {
    return num_of_mines_nearby;
}

std::vector<Tile*> Tile::getNeighbors() {
    return neighbors;
}

void Tile::setRevealed() {
    hidden_status = false;
}

void Tile::setHidden() {
    hidden_status = true;
}

void Tile::recursiveReveal() {
    if (this->getNumOfMines() != 0) {
        this->setRevealed();
        if (this->getFlagStatus() == true) {
            this->setHidden();
        }
    }
    else {
        this->setRevealed();
        if (this->getFlagStatus() == true) {
            this->setHidden();
        }
        for (auto& i : this->getNeighbors()) {
            if (i->getHiddenStatus() == true && this->getFlagStatus() == false) {
                i->recursiveReveal();
            }
        }
    }
}

void Tile::setFlag() {
    flag_status = true;
}

void Tile::unsetFlag() {
    flag_status = false;
}

void Tile::setMine() {
    has_mine = true;
}

void Tile::unsetMine() {
    has_mine = false;
}

void Tile::updateNearbyMineCount() {
    if (this->getNumOfMines() != 0) {
        num_of_mines_nearby = 0;
    }
    for (auto& i : neighbors) {
        if (i->getMineStatus() == true) {
            num_of_mines_nearby += 1;
        }
    }
}

void Tile::setLocation(int x, int y) {
    tileVect.x = x;
    tileVect.y = y;
}

void Tile::addNeighbor(Tile* neighborTile) {
    neighbors.push_back(neighborTile);
}


int Tile::get_x_value() {
    return tileVect.x;
}

int Tile::get_y_value() {
    return tileVect.y;
}

sf::Vector2<float> Tile::getTileVect() {
    return tileVect;
}