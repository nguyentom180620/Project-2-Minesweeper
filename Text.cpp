#include "Text.h"

// Helper Functions
namespace text_helpers {
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

    void setText(sf::Text &text, float x, float y) {
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
                       textRect.top + textRect.height / 2.0f);
        text.setPosition(sf::Vector2<float>(x, y));
    }
}

using namespace text_helpers;

// WelcomeScreenText Functions
WelcomeScreenText::WelcomeScreenText() {
    // Load and set font and other characteristics
    if (!font.loadFromFile("files/font.ttf")) {
        std::cout << "Fonts didn't load! D:" << std::endl;
    }
    this->setFont(font);
    this->setCharacterSize(24);
    this->setString("WELCOME TO MINESWEEPER!");
    this->setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Set text position too
    int welcomeWidth = getWelcomeWidth();
    int welcomeHeight = getWelcomeHeight();
    float welcomeScreenText_x = welcomeWidth / 2.0f;
    float welcomeScreenText_y = welcomeHeight / 2.0f - 150;
    setText(*this, welcomeScreenText_x, welcomeScreenText_y);
}

// EnterYourNameText Functions
EnterYourNameText::EnterYourNameText() {
    if (!font.loadFromFile("files/font.ttf")) {
        std::cout << "Fonts didn't load! D:" << std::endl;
    }
    this->setFont(font);
    this->setCharacterSize(20);
    this->setString("Enter your name:");
    this->setStyle(sf::Text::Bold);

    int EnterWidth = getWelcomeWidth();
    int EnterHeight = getWelcomeHeight();
    float EnterText_x = EnterWidth / 2.0f;
    float EnterText_y = EnterHeight / 2.0f - 75;
    setText(*this, EnterText_x, EnterText_y);
}

// UserTypedNameText Functions
UserTypedNameText::UserTypedNameText() {
    this->_name = "|";

    if (!font.loadFromFile("files/font.ttf")) {
        std::cout << "Fonts didn't load! D:" << std::endl;
    }
    this->setFont(font);
    this->setCharacterSize(20);
    this->setStyle(sf::Text::Bold);
    this->setFillColor(sf::Color(255, 235, 59, 255));

    int UserWidth = getWelcomeWidth();
    int UserHeight = getWelcomeHeight();
    float UserTypedName_x = UserWidth / 2.0f;
    float UserTypedName_y = UserHeight / 2.0f - 45;
    setText(*this, UserTypedName_x, UserTypedName_y);

    // Now set string, which will be the cursor character |
    this->setString(_name);
}

std::string UserTypedNameText::getName() {
    return _name;
}

void UserTypedNameText::removeLetter() {
    // for backspace gang
    int len = this->getName().size() / sizeof(this->getName().at(0));
    if (len > 1) {
        std::string myName = this->getName();
        std::string myNewName = myName.substr(0, len - 2);
        myNewName += '|';
        this->setName(myNewName);
        this->setString(myNewName);

        int UserWidth = getWelcomeWidth();
        int UserHeight = getWelcomeHeight();
        float UserTypedName_x = UserWidth / 2.0f;
        float UserTypedName_y = UserHeight / 2.0f - 45;
        this->setOrigin(UserTypedName_x, UserTypedName_y);
        setText(*this, UserTypedName_x, UserTypedName_y);
    }
}

void UserTypedNameText::setName(std::string newName) {
    this->_name = newName;
}

void UserTypedNameText::updateName(char& myChar) {
    // Do magic here
    char charCheck;
    std::string myName = this->getName();
    int len = this->getName().size() / sizeof(this->getName().at(0));
    if (len < 11) {
        std::string myNewName = myName.substr(0, len - 1);

        if (myName.length() == 1) {
            charCheck = std::toupper(myChar);
        }
        else {
            charCheck = std::tolower(myChar);
        }

        myNewName += charCheck;
        myNewName += '|';
        this->setName(myNewName);
        this->setString(this->getName());

        int UserWidth = getWelcomeWidth();
        int UserHeight = getWelcomeHeight();
        float UserTypedName_x = UserWidth / 2.0f;
        float UserTypedName_y = UserHeight / 2.0f - 45;
        this->setOrigin(UserTypedName_x, UserTypedName_y);
        setText(*this, UserTypedName_x, UserTypedName_y);
    }
}

LeaderboardTitleText::LeaderboardTitleText() {
    if (!font.loadFromFile("files/font.ttf")) {
        std::cout << "Fonts didn't load! D:" << std::endl;
    }
    this->setFont(font);
    this->setCharacterSize(20);
    this->setString("LEADERBOARD");
    this->setStyle(sf::Text::Bold | sf::Text::Underlined);
    int leaderboardWidth = getConfigX() * 16;
    int leaderboardHeight = getConfigY() * 16 + 50;
    float leaderboardTitleText_x = leaderboardWidth / 2.0f;
    float leaderboardTitleText_y = leaderboardHeight / 2.0f - 120;
    setText(*this, leaderboardTitleText_x, leaderboardTitleText_y);
}

LeaderBoardContent::LeaderBoardContent(LeaderBoard& leaderBoard) {
    // Make mega string
    std::string content;
    for (int i = 0; i < leaderBoard.getWinners().size(); i++) {
        content += std::to_string(i+1) + '.' + '\t';
        content += leaderBoard.getWinners()[i].substr(0, 5) + '\t';
        if (i == leaderBoard.getWinners().size() - 1) {
            content += leaderBoard.getWinners()[i].substr(7);
        }
        else {
            content += leaderBoard.getWinners()[i].substr(7) + "\n\n";
        }
    }

    if (!font.loadFromFile("files/font.ttf")) {
        std::cout << "Fonts didn't load! D:" << std::endl;
    }
    this->setFont(font);
    this->setCharacterSize(18);
    this->setString(content);
    this->setStyle(sf::Text::Bold);
    int leaderboardWidth = getConfigX() * 16;
    int leaderboardHeight = getConfigY() * 16 + 50;
    float leaderboardContent_x = leaderboardWidth / 2.0f;
    float leaderboardContent_y = leaderboardHeight / 2.0f + 20;
    setText(*this, leaderboardContent_x, leaderboardContent_y);
}

void LeaderBoardContent::updateContent(LeaderBoard& leaderBoard) {
    // Make mega string
    std::string content;
    for (int i = 0; i < leaderBoard.getWinners().size(); i++) {
        content += std::to_string(i+1) + '.' + '\t';
        content += leaderBoard.getWinners()[i].substr(0, 5) + '\t';
        if (i == leaderBoard.getWinners().size() - 1) {
            content += leaderBoard.getWinners()[i].substr(7);
        }
        else {
            content += leaderBoard.getWinners()[i].substr(7) + "\n\n";
        }
    }

    this->setString(content);
}