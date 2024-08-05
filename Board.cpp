#include "Board.h"

namespace helper_functions {
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

    int getMineCount() {
        std::string temp_mine_count;
        std::ifstream configFile("files/config.cfg");
        if (!configFile.is_open()) {
            std::cout << "Oh no! Config file didn't open :(" << std::endl;
        }
        configFile.ignore(100, '\n');
        configFile.ignore(100, '\n');
        std::getline(configFile, temp_mine_count);
        return std::stoi(temp_mine_count);
    }
}
using namespace helper_functions;

HappyFace::HappyFace() {
    position.x = (getConfigX()/2.0f * 32) - 32;
    position.y = 32 * (getConfigY() + 0.5f);
}

sf::Vector2<float> HappyFace::getPositionVect() {
    return position;
}

Counter::Counter() {
    flag_counter = 0;
}

void Counter::setFlagCounter(int flags, int num_mines) {
    flag_counter = num_mines - flags;
}

int Counter::getFlagCounter() {
    return flag_counter;
}

Debug::Debug() {
    position.x = (getConfigX()*32) - 304;
    position.y = 32 * (getConfigY() + 0.5f);
}

sf::Vector2<float> Debug::getPositionVect() {
    return position;
}

Pause::Pause() {
    position.x = (getConfigX()*32) - 240;
    position.y = 32 * (getConfigY() + 0.5f);
}

sf::Vector2<float> Pause::getPositionVect() {
    return position;
}

LeaderboardButton::LeaderboardButton() {
    position.x = (getConfigX()*32) - 176;
    position.y = 32 * (getConfigY() + 0.5f);
}

sf::Vector2<float> LeaderboardButton::getPositionVect() {
    return position;
}

Board::Board() {
    num_in_row = getConfigX();
    num_in_col = getConfigY();
    mine_count = getMineCount();
    flag_count = getMineCount();
    timer_start = false;
    paused = false;
    debugMode = false;
    gameOver = false;
    gameWon = false;
    for (int i = 0; i < num_in_col; i++) {
        std::vector<Tile> myTileRow {};
        for (int j = 0; j < num_in_row; j++) {
            Tile tempTile;
            tempTile.setLocation(j*32, i*32);
            myTileRow.push_back(tempTile);
        }
        myTiles.push_back(myTileRow);
    }
}

int Board::getNumRow() {
    return num_in_row;
}

int Board::getNumCol() {
    return num_in_col;
}

int Board::getFlagCount() {
    int flag_count = 0;
    for (auto&i : myTiles) {
        for (auto& j : i) {
            if (j.getFlagStatus() == true) {
                flag_count++;
            }
        }
    }
    return flag_count;
}

bool Board::getPauseStatus() {
    return paused;
}

void Board::setPauseStatus() {
    paused = true;
}

void Board::unsetPauseStatus() {
    paused = false;
}

bool Board::getGameWon() {
    return gameWon;
}

bool Board::getGameOver() {
    return gameOver;
}

bool Board::getTimerStart() {
    return timer_start;
}

void Board::setTimerStart() {
    timer_start = true;
}

void Board::unsetTimerStart() {
    timer_start = false;
}

std::vector<std::vector<Tile>> Board::getMyTiles() {
    return myTiles;
}

void Board::setTempTexture(sf::Texture& texture) {
    tempTexture = texture;
}

void Board::DisplayHiddenStatus(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map) {
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (j.getHiddenStatus()) {
                j.setTexture(map["Tile_Hidden"]);
            }
            else {
                j.setTexture(map["Tile_Revealed"]);
            }
            gameWindow.draw(j);
        }
    }
}

void Board::setFlagImage(sf::RenderWindow& gameWindow, std::map<std::string, sf::Texture>& map) {
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (j.getFlagStatus()) {
                sf::Sprite flagTile;
                flagTile.setTexture(map["Flag"]);
                flagTile.setPosition(j.getTileVect());
                gameWindow.draw(flagTile);
            }
        }
    }
}

void Board::setMineImage(sf::RenderWindow &gameWindow, std::map<std::string, sf::Texture>& map) {
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (j.getMineStatus() && gameOver) {
                sf::Sprite mineTile;
                mineTile.setTexture(map["Mine"]);
                mineTile.setPosition(j.getTileVect());
                gameWindow.draw(mineTile);
            }
        }
    }
}

void Board::setNumberImage(sf::RenderWindow &gameWindow, std::map<std::string, sf::Texture>& map) {
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (j.getNumOfMines() != 0 && j.getHiddenStatus() == false && j.getMineStatus() == false) {
                sf::Sprite numTile;
                numTile.setTexture(map[std::to_string(j.getNumOfMines())]);
                numTile.setPosition(j.getTileVect());
                gameWindow.draw(numTile);
            }
        }
    }
}

void Board::setHappyFaceImage(sf::RenderWindow &gameWindow, std::map<std::string, sf::Texture>& map,
                              HappyFace& happyFace) {
    if (gameOver) {
        happyFace.setTexture(map["Face_Lose"]);
    }
    else if (gameWon) {
        happyFace.setTexture(map["Face_Win"]);
    }
    else {
        happyFace.setTexture(map["Face_Happy"]);
    }
    happyFace.setPosition(happyFace.getPositionVect());
    gameWindow.draw(happyFace);
}

void Board::setCounterImage(sf::RenderWindow &gameWindow, std::map<std::string, sf::Texture> &map, Counter &counter) {
    // Check if negative
    if (counter.getFlagCounter() < 0) {
        map["Counter"].loadFromFile("files/images/digits.png", sf::IntRect(210, 0, 21, 32));
    }
    else {
        map["Counter"].loadFromFile("files/images/digits.png", sf::IntRect(0, 0, 21, 32));
    }
    counter.setTexture(map["Counter"]);
    counter.setPosition(sf::Vector2<float> (12, 32*(getConfigY() + 0.5f) + 16));

    int counter_tens;
    int counter_ones;

    if (counter.getFlagCounter() < 0) {
        counter_tens = (-1 * counter.getFlagCounter()) / 10;
        counter_ones = (-1 * counter.getFlagCounter()) % 10;
    }
    else {
        counter_tens = counter.getFlagCounter() / 10;
        counter_ones = counter.getFlagCounter() % 10;
    }

    sf::Sprite tens;
    map["Tens"].loadFromFile("files/images/digits.png", sf::IntRect(counter_tens*21, 0, 21, 32));
    tens.setTexture(map["Tens"]);
    tens.setPosition(sf::Vector2<float> (33, 32*(getConfigY() + 0.5f) + 16));
    sf::Sprite ones;
    map["Ones"].loadFromFile("files/images/digits.png", sf::IntRect(counter_ones*21, 0, 21, 32));
    ones.setTexture(map["Ones"]);
    ones.setPosition(sf::Vector2<float> (54, 32*(getConfigY() + 0.5f) + 16));

    gameWindow.draw(counter);
    gameWindow.draw(tens);
    gameWindow.draw(ones);
}

void Board::setDebugImage(sf::RenderWindow &gameWindow, std::map<std::string, sf::Texture> &map, Debug &debug) {
    debug.setTexture(map["Debug"]);
    debug.setPosition(debug.getPositionVect());
    gameWindow.draw(debug);
}

void Board::setDebuggedMineImage(sf::RenderWindow &gameWindow, std::map<std::string, sf::Texture> &map) {
    if (debugMode) {
        for (auto& i : myTiles) {
            for (auto& j : i) {
                if (j.getMineStatus() == true) {
                    sf::Sprite mineTile;
                    mineTile.setTexture(map["Mine"]);
                    mineTile.setPosition(j.getTileVect());
                    gameWindow.draw(mineTile);
                }
            }
        }
    }
}

void Board::setPauseImage(sf::RenderWindow &gameWindow, std::map<std::string, sf::Texture> &map, Pause &pause) {
    if (paused == false) {
        pause.setTexture(map["Paused"]);
    }
    else {
        pause.setTexture(map["Play"]);
    }
    pause.setPosition(pause.getPositionVect());
    gameWindow.draw(pause);
}

void Board::setPausedMineImage(sf::RenderWindow &gameWindow, std::map<std::string, sf::Texture> &map) {
    if (paused == true) {
        for (auto&i : myTiles) {
            for (auto&j : i) {
                sf::Sprite pausedMine;
                pausedMine.setTexture(map["Tile_Revealed"]);
                pausedMine.setPosition(j.getTileVect());
                gameWindow.draw(pausedMine);
            }
        }
    }
}

void Board::setLeaderboardButtonImage(sf::RenderWindow &gameWindow, std::map<std::string, sf::Texture> &map,
                                      LeaderboardButton &leaderboardButton) {
    leaderboardButton.setTexture(map["LeaderboardButton"]);
    leaderboardButton.setPosition(leaderboardButton.getPositionVect());
    gameWindow.draw(leaderboardButton);
}

void Board::setTimerImage(sf::RenderWindow &gameWindow, std::map<std::string, sf::Texture> &map, long long min,
                          long long sec) {
    int minTens = (min / 10) % 6;
    int minOnes = min % 10;
    int secTens = (sec / 10) % 6;
    int secOnes = sec % 10;

    sf::Sprite minTenSprite;
    map["minTens"].loadFromFile("files/images/digits.png", sf::IntRect(minTens*21, 0, 21, 32));
    minTenSprite.setTexture(map["minTens"]);
    minTenSprite.setPosition(sf::Vector2<float> (getConfigX()*32 - 97, 32*(getConfigY() + 0.5f) + 16));
    sf::Sprite minOneSprite;
    map["minOnes"].loadFromFile("files/images/digits.png", sf::IntRect(minOnes*21, 0, 21, 32));
    minOneSprite.setTexture(map["minOnes"]);
    minOneSprite.setPosition(sf::Vector2<float> (getConfigX()*32 - 76, 32*(getConfigY() + 0.5f) + 16));
    sf::Sprite secTenSprite;
    map["secTens"].loadFromFile("files/images/digits.png", sf::IntRect(secTens*21, 0, 21, 32));
    secTenSprite.setTexture(map["secTens"]);
    secTenSprite.setPosition(sf::Vector2<float> (getConfigX()*32 - 54, 32*(getConfigY() + 0.5f) + 16));
    sf::Sprite secOnesSprite;
    map["secOnes"].loadFromFile("files/images/digits.png", sf::IntRect(secOnes*21, 0, 21, 32));
    secOnesSprite.setTexture(map["secOnes"]);
    secOnesSprite.setPosition(sf::Vector2<float> (getConfigX()*32 - 33, 32*(getConfigY() + 0.5f) + 16));

    gameWindow.draw(minTenSprite);
    gameWindow.draw(minOneSprite);
    gameWindow.draw(secTenSprite);
    gameWindow.draw(secOnesSprite);
}

void Board::FillTileNeighbors() {
    for (auto& i : myTiles) {
        for (auto& j : i) {
            int j_x_origin = j.get_x_value();
            int j_y_origin = j.get_y_value();
            sf::Vector2<float> vect1(j_x_origin, j_y_origin - 32);
            sf::Vector2<float> vect2(j_x_origin + 32, j_y_origin - 32);
            sf::Vector2<float> vect3(j_x_origin + 32, j_y_origin);
            sf::Vector2<float> vect4 (j_x_origin + 32, j_y_origin + 32);
            sf::Vector2<float> vect5(j_x_origin, j_y_origin + 32);
            sf::Vector2<float> vect6(j_x_origin - 32, j_y_origin + 32);
            sf::Vector2<float> vect7(j_x_origin - 32, j_y_origin);
            sf::Vector2<float> vect8(j_x_origin - 32, j_y_origin - 32);
            std::vector<sf::Vector2<float>> neighborVectors;
            neighborVectors.push_back(vect1);
            neighborVectors.push_back(vect2);
            neighborVectors.push_back(vect3);
            neighborVectors.push_back(vect4);
            neighborVectors.push_back(vect5);
            neighborVectors.push_back(vect6);
            neighborVectors.push_back(vect7);
            neighborVectors.push_back(vect8);
            for (auto& k : myTiles) {
                for (auto& l : k) {
                    for (auto& m : neighborVectors) {
                        if (l.getPosition() == m) {
                            Tile* tempPtr = &l;
                            j.addNeighbor(tempPtr);
                        }
                    }
                }
            }
        }
    }
}

void Board::UpdateNearbyMineCount() {
    for (auto& i : myTiles) {
        for (auto& j : i) {
            j.updateNearbyMineCount();
        }
    }
}

void Board::PlaceMines(std::mt19937& mt) {
    int count_for_mines_placed = 0;
    std::srand((unsigned)std::time(0));
    while (count_for_mines_placed < mine_count) {
        for (auto &i: myTiles) {
            for (auto &j: i) {
                if (count_for_mines_placed == mine_count) {
                    break;
                }
                int random2 = ((rand()%6)+1) * 10;
                int random3 = ((rand()%6)+1) * 10;
                int randomCheck = random2 + random3;
                std::uniform_int_distribution<int> dist(0, randomCheck);
                int random = dist(mt);

                if (random > 80) {
                    j.setMine();
                    count_for_mines_placed++;
                }
            }
            if (count_for_mines_placed == mine_count) {
                break;
            }
        }
    }
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (((rand()%6)+1) < 4) {
                continue;
            }
            if (j.getMineStatus() == false && j.getHiddenStatus() == true && this->IntMineCount() < mine_count) {
                j.setMine();
                j.updateNearbyMineCount();
                for (auto&k : j.getNeighbors()) {
                    k->updateNearbyMineCount();
                }
            }
            else if (j.getMineStatus() == true && this->IntMineCount() > mine_count) {
                j.unsetMine();
                j.updateNearbyMineCount();
                for (auto&k : j.getNeighbors()) {
                    k->updateNearbyMineCount();
                }
            }
        }
    }
}

bool Board::MoveMine(Tile& oldTile, sf::Vector2<float>& mouse_pos) {
    // Fix this to get proper 50 mines set
    // Fixed! Hideous though
    int num_mines_to_replace = 0;
    for (auto& i : oldTile.getNeighbors()) {
        if (i->getMineStatus() == true) {
            num_mines_to_replace++;
            i->unsetMine();
        }
    }
    oldTile.unsetMine();
    oldTile.updateNearbyMineCount();
    for (auto&i : oldTile.getNeighbors()) {
        i->updateNearbyMineCount();
    }
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (j.getMineStatus() == false && j.getHiddenStatus() == true && num_mines_to_replace > 0
            && !j.getGlobalBounds().contains(mouse_pos)) {
                j.setMine();
                j.updateNearbyMineCount();
                for (auto&k : j.getNeighbors()) {
                    k->updateNearbyMineCount();
                }
                num_mines_to_replace--;
            }
        }
    }
    this->UpdateNearbyMineCount();
    this->MineCount();
    std::srand((unsigned)time(0));
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (((rand()%6)+1) < 4) {
                continue;
            }
            if (j.getMineStatus() == false && j.getHiddenStatus() == true && this->IntMineCount() < mine_count
                                                                             && !j.getGlobalBounds().contains(mouse_pos)) {
                j.setMine();
                j.updateNearbyMineCount();
                for (auto&k : j.getNeighbors()) {
                    k->updateNearbyMineCount();
                }
            }
            else if (j.getMineStatus() == true && this->IntMineCount() > mine_count && !j.getGlobalBounds().contains(mouse_pos)) {
                j.unsetMine();
                j.updateNearbyMineCount();
                for (auto&k : j.getNeighbors()) {
                    k->updateNearbyMineCount();
                }
            }
        }
    }
    this->UpdateNearbyMineCount();
    this->MineCount();
    oldTile.recursiveReveal();
    return false;
}

void Board::MineCount() {
    int mine_count = 0;
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (j.getMineStatus() == true) {
                mine_count++;
            }
        }
    }
}

int Board::IntMineCount() {
    int mine_count = 0;
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (j.getMineStatus() == true) {
                mine_count++;
            }
        }
    }
    return mine_count;
}

void Board::PlaceTiles() {
    for (auto& i : myTiles) {
        for (auto& j : i) {
            j.setPosition(j.getTileVect());
        }
    }
}

void Board::LeftClickDebugToggle(sf::Vector2<float> &mouse_pos, Debug &debug) {
    if (debug.getGlobalBounds().contains(mouse_pos)) {
        debugMode = !debugMode;
    }
}

void Board::LeftClickPauseToggle(sf::Vector2<float> &mouse_pos, Pause &pause) {
    if (pause.getGlobalBounds().contains(mouse_pos)) {
        paused = !paused;
    }
}

bool Board::LeftClickResetButton(sf::Vector2<float> &mouse_pos, HappyFace& happyFace, std::mt19937& mt, bool& first_click) {
    if (happyFace.getGlobalBounds().contains(mouse_pos)) {
        gameOver = false;
        gameWon = false;
        paused = false;
        timer_start = false;

        for (auto& i : myTiles) {
            for (auto& j : i) {
                if (j.getHiddenStatus() == false) {
                    j.setHidden();
                }
                if (j.getFlagStatus() == true) {
                    j.unsetFlag();
                }
                if (j.getMineStatus() == true) {
                    j.unsetMine();
                }
            }
        }
        this->PlaceMines(mt);
        first_click = true;
        this->UpdateNearbyMineCount();
        return true;
    }
    return false;
}

void Board::LeftClickTile(sf::Vector2<float>& mouse_pos, bool& first_click) {
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (j.getGlobalBounds().contains(mouse_pos)) {
                if (j.getFlagStatus() == false) {
                    if (first_click == true) {
                        // Move Mine
                        first_click = this->MoveMine(j, mouse_pos);
                    }
                    if (j.getMineStatus() == true) {
                        gameOver = true;
                    }
                    else if (j.getFlagStatus() == false && j.getHiddenStatus() == true && !gameOver) {
                        // Here, add recursive reveal!
                        j.recursiveReveal();
                    }
                }
            }
        }
    }
}

void Board::RightClickTile(sf::Vector2<float> &mouse_pos) {
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (j.getGlobalBounds().contains(mouse_pos)) {
                if (j.getFlagStatus() == true && !gameWon && !gameOver) {
                    j.unsetFlag();
                }
                else if (j.getHiddenStatus() == true && !gameOver) {
                    j.setFlag();
                }
            }
        }
    }
}

void Board::GameOver() {
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (j.getMineStatus() == true && gameOver) {
                j.setRevealed();
            }
        }
    }
}

void Board::CheckGameWin() {
    int non_mine_tiles = num_in_row * num_in_col - mine_count;
    int check_count = 0;
    for (auto& i : myTiles) {
        for (auto& j : i) {
            if (j.getMineStatus() == false && j.getHiddenStatus() == false) {
                check_count++;
            }
        }
    }
    if (check_count == non_mine_tiles) {
        gameWon = true;
    }
}

void Board::GameWon() {
    if (gameWon) {
        for (auto& i : myTiles) {
            for (auto& j : i) {
                if (j.getMineStatus() == true) {
                    j.setFlag();
                }
            }
        }
    }
}