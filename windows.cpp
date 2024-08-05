#include "windows.h"

// Helper Functions
namespace window_helpers {
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

    int getGameHeight() {
        return getConfigY() * 32 + 100;;
    }

    int getGameWidth() {
        return getConfigX() * 32;
    }
}

using namespace window_helpers;

// WelcomeWindow Functions
WelcomeWindow::WelcomeWindow() {
    // Get config data, then make our window!
    int welcomeWidth = getWelcomeWidth();
    int welcomeHeight = getWelcomeHeight();

    this->create(sf::VideoMode(welcomeWidth,welcomeHeight), "Minesweeper", sf::Style::Close);
}

// GameWindow Functions
GameWindow::GameWindow() {
    int gameWidth = getGameWidth();
    int gameHeight = getGameHeight();

    this->create(sf::VideoMode(gameWidth, gameHeight), "Minesweeper", sf::Style::Close);
}

// LeaderBoard Functions
LeaderBoard::LeaderBoard() {
    temp_name = "";
    temp_min = 0;
    temp_sec = 0;
    collected_time = false;
    log_name = "";

    int leaderboardWidth = getConfigX() * 16;
    int leaderboardHeight = getConfigY() * 16 + 50;

    this->create(sf::VideoMode(leaderboardWidth, leaderboardHeight), "Minesweeper", sf::Style::Close);
}

void LeaderBoard::reOpen() {
    int leaderboardWidth = getConfigX() * 16;
    int leaderboardHeight = getConfigY() * 16 + 50;
    this->create(sf::VideoMode(leaderboardWidth, leaderboardHeight), "Minesweeper", sf::Style::Close);
}

void LeaderBoard::setTempName(std::string name) {
    temp_name = name;
}

void LeaderBoard::setMinute(int min) {
    temp_min = min;
}

void LeaderBoard::setSecond(int sec) {
    temp_sec = sec;
}

void LeaderBoard::setCollectedTimeBoolTrue() {
    collected_time = true;
}

void LeaderBoard::setCollectedTimeBoolFalse() {
    collected_time = false;
}

bool LeaderBoard::getCollectedTimeBool() {
    return collected_time;
}

void LeaderBoard::makeLogName() {
    std::string min_part;
    if ((temp_min / 10) < 1) {
        min_part = '0' + std::to_string(temp_min % 60);
    }
    else {
        min_part = std::to_string(temp_min % 60);
    }
    std::string sec_part;
    if ((temp_sec / 10) < 1) {
        sec_part = '0' + std::to_string(temp_sec % 60);
    }
    else {
        sec_part = std::to_string(temp_sec % 60);
    }

    log_name = min_part + ':' + sec_part + ',' + ' ' + temp_name;
    log_name.pop_back();
    log_name += '*';
}

void LeaderBoard::clearWinnersAsterisk() {
    for (auto& i : winners) {
        if (i.find('*') != std::string::npos) {
            i.pop_back();
        }
    }
}

void LeaderBoard::insertLogName() {
    std::string log_min_sub = log_name.substr(0, 2);
    std::string  log_sec_sub = log_name.substr(3, 2);
    int log_min_ten = stoi(log_min_sub.substr(0, 1));
    int log_min_one = stoi(log_min_sub.substr(1,1));
    int log_sec = stoi(log_sec_sub);

    for (int i = 0; i < winners.size(); i++) {
        std::string winner_min_sub = winners[i].substr(0, 2);
        std::string winner_sec_sub = winners[i].substr(3, 2);
        int winner_min_ten = stoi(winner_min_sub.substr(0,1));
        int winner_min_one = stoi(winner_min_sub.substr(1,1));
        int winner_sec = stoi(winner_sec_sub);

        if (log_min_ten < winner_min_ten) {
            winners.insert(winners.begin() + i, log_name);
            break;
        }
        else if (log_min_one < winner_min_one) {
            winners.insert(winners.begin() + i, log_name);
            break;
        }
        else if (log_sec < winner_sec) {
            winners.insert(winners.begin() + i, log_name);
            break;
        }
        else {
            if (i == winners.size() - 1) {
                winners.push_back(log_name);
                break;
            }
        }
    }

    if (winners.size() > 5) {
        winners.pop_back();
    }

    if (winners.empty()) {
        winners.push_back(log_name);
    }
}

void LeaderBoard::printWinners() {
    for (auto& i : winners) {
        std::cout << i << std::endl;
    }
}

void LeaderBoard::getWinnersFromTxt() {
    if (!winners.empty()) {
        winners.clear();
    }
    std::ifstream file;
    std::string read;
    file.open("files/leaderboard.txt");
    if (!file) {
        throw std::runtime_error("leaderboard.txt failed to open");
    }
    while (std::getline(file, read)) {
        winners.push_back(read);
    }
    file.close();
}

void LeaderBoard::updateWinnersInTxt() {
    std::ofstream file;
    file.open("files/leaderboard.txt");
    if (!file) {
        throw std::runtime_error("leaderboard.txt failed to open");
    }
    for (auto& i : winners) {
        if (i == winners[4]) {
            file << i;
        }
        else {
            file << i << std::endl;
        }
    }
    file.close();
}

std::string LeaderBoard::getLogName() {
    return log_name;
}

std::vector<std::string> LeaderBoard::getWinners() {
    return winners;
}