#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include <map>
#include "windows.h"
#include "Text.h"
#include "Tile.h"
#include "Board.h"

int main() {
    // First, WelcomeWindow Section

    // Load Windows
    WelcomeWindow welcomeWindow;
    int framerate = 60;
    welcomeWindow.setFramerateLimit(framerate);
    welcomeWindow.setKeyRepeatEnabled(false);

    // Load LeaderBoard for collecting data
    LeaderBoard leaderBoard;
    leaderBoard.setFramerateLimit(framerate);
    LeaderboardTitleText leaderboardTitleText;
    leaderBoard.getWinnersFromTxt();
    LeaderBoardContent leaderBoardContent(leaderBoard);
    leaderBoard.close();

    // Load texts
    WelcomeScreenText welcomeScreenText;
    WelcomeScreenText* wSTptr = &welcomeScreenText;
    EnterYourNameText enterYourNameText;
    EnterYourNameText* eYNTptr = &enterYourNameText;
    UserTypedNameText userTypedNameText;
    UserTypedNameText* uTNTptr = &userTypedNameText;

    std::vector<BaseText*> welcomeTextVect {};
    welcomeTextVect.push_back(wSTptr);
    welcomeTextVect.push_back(eYNTptr);
    welcomeTextVect.push_back(uTNTptr);

    bool openGame = false;

    // WelcomeWindow Loop, then never come back once we get into the game
    while (welcomeWindow.isOpen()) {
        // Events
        sf::Event event;
        while (welcomeWindow.pollEvent(event)) {
            // These two events to close Welcome Window
            if (event.type == sf::Event::Closed) {
                welcomeWindow.close();
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                welcomeWindow.close();
            }
            // Now work on receiving alphabetic key inputs
            if (event.type == sf::Event::TextEntered) {
                // Here is the case if enter is pressed
                if (event.text.unicode == 13) {
                    if (userTypedNameText.getName() != "|") {
                        openGame = true;
                        welcomeWindow.close();
                    }

                    // Eventually, add opening of game window here and leaderboard functionality by sending name
                    // to leaderboard.txt
                    // To save memory space, consider destroying these objects here since they're no longer used
                    // ... but make sure to keep user typed name for leader board
                }
                // Backspace pressed here
                if (event.text.unicode == 8) {
                    userTypedNameText.removeLetter();
                }
                // Otherwise, change our string by updating it when letters are pressed
                if (65 <= event.text.unicode  && event.text.unicode <= 90 ||
                97 <= event.text.unicode && event.text.unicode <= 122) {
                    char myLetter =  static_cast<char>(event.text.unicode);
                    userTypedNameText.updateName(myLetter);
                }
                // Otherwise, do nothing
            }
        }
        // WelcomeWindow Display Gang
        welcomeWindow.clear(sf::Color(0,0,255,255));
        for (auto& i : welcomeTextVect) {
            welcomeWindow.draw(*i);
        }
        welcomeWindow.display();
    }

    // LeaderBoard Collects Name
    leaderBoard.setTempName(userTypedNameText.getName());

    // Next, GameWindow Time!
    std::random_device rd;
    std::mt19937 mt{rd()};
    if (openGame) {
        // GameWindow and Board Initialization
        GameWindow gameWindow;
        gameWindow.setFramerateLimit(framerate);
        gameWindow.setKeyRepeatEnabled(false);
        bool first_click = true;
        Board board;
        board.PlaceTiles();
        board.PlaceMines(mt);
        board.FillTileNeighbors();
        board.UpdateNearbyMineCount();
        // Load all textures
        std::map<std::string, sf::Texture> textureMap;
        sf::Texture hidden;
        hidden.loadFromFile("files/images/tile_hidden.png");
        textureMap.emplace("Tile_Hidden", hidden);
        sf::Texture revealed;
        revealed.loadFromFile("files/images/tile_revealed.png");
        textureMap.emplace("Tile_Revealed", revealed);
        sf::Texture flag;
        flag.loadFromFile("files/images/flag.png");
        textureMap.emplace("Flag", flag);
        sf::Texture mine;
        mine.loadFromFile("files/images/mine.png");
        textureMap.emplace("Mine", mine);
            // Nearby Mine Number Loading
        sf::Texture num1;
        num1.loadFromFile("files/images/number_1.png");
        textureMap.emplace("1", num1);
        sf::Texture num2;
        num2.loadFromFile("files/images/number_2.png");
        textureMap.emplace("2", num2);
        sf::Texture num3;
        num3.loadFromFile("files/images/number_3.png");
        textureMap.emplace("3", num3);
        sf::Texture num4;
        num4.loadFromFile("files/images/number_4.png");
        textureMap.emplace("4", num4);
        sf::Texture num5;
        num5.loadFromFile("files/images/number_5.png");
        textureMap.emplace("5", num5);
        sf::Texture num6;
        num6.loadFromFile("files/images/number_6.png");
        textureMap.emplace("6", num6);
        sf::Texture num7;
        num7.loadFromFile("files/images/number_7.png");
        textureMap.emplace("7", num7);
        sf::Texture num8;
        num8.loadFromFile("files/images/number_8.png");
        textureMap.emplace("8", num8);
            // Button Textures
                // Happy Face Button
        sf::Texture happyFaceTex;
        happyFaceTex.loadFromFile("files/images/face_happy.png");
        textureMap.emplace("Face_Happy", happyFaceTex);
        sf::Texture loseFaceTex;
        loseFaceTex.loadFromFile("files/images/face_lose.png");
        textureMap.emplace("Face_Lose", loseFaceTex);
        sf::Texture winFaceTex;
        winFaceTex.loadFromFile("files/images/face_win.png");
        textureMap.emplace("Face_Win", winFaceTex);
                // Debug Button
        sf::Texture debugTex;
        debugTex.loadFromFile("files/images/debug.png");
        textureMap.emplace("Debug", debugTex);
                // Pause Button
        sf::Texture pauseTex;
        pauseTex.loadFromFile("files/images/pause.png");
        textureMap.emplace("Paused", pauseTex);
        sf::Texture playTex;
        playTex.loadFromFile("files/images/play.png");
        textureMap.emplace("Play", playTex);
                // Leaderboard Button
        sf::Texture leaderboardTex;
        leaderboardTex.loadFromFile("files/images/leaderboard.png");
        textureMap.emplace("LeaderboardButton", leaderboardTex);
            // Counter Texture Loading
        sf::Texture counterTex;
        textureMap.emplace("Counter", counterTex);
        sf::Texture tensTex;
        textureMap.emplace("Tens", tensTex);
        sf::Texture onesTex;
        textureMap.emplace("Ones", onesTex);
            // Timer Texture Loading
        sf::Texture minTens;
        textureMap.emplace("minTens", minTens);
        sf::Texture minOnes;
        textureMap.emplace("minOnes", minOnes);
        sf::Texture secTens;
        textureMap.emplace("secTens", secTens);
        sf::Texture secOnes;
        textureMap.emplace("secOnes", secOnes);

        // Button Initialization
        HappyFace happyFace;
        Debug debug;
        Pause pause;
        LeaderboardButton leaderboardButton;
        bool leaderboardOpen = false;
        bool pausedStateBeforeLeaderboard = false;

        // Counter Initialization
        Counter counter;

        // Timer
        auto start_time = std::chrono::high_resolution_clock::now();
        auto end_time = std::chrono::high_resolution_clock::now();
        auto paused_time = end_time - start_time;
        long long min = std::chrono::duration_cast<std::chrono::minutes>(end_time - start_time).count();
        long long sec = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

        while (gameWindow.isOpen()) {
            gameWindow.clear(sf::Color(245,245,245,255));
            board.DisplayHiddenStatus(gameWindow, textureMap);
            board.setFlagImage(gameWindow, textureMap);
            board.setMineImage(gameWindow, textureMap);
            board.setNumberImage(gameWindow, textureMap);
            board.setHappyFaceImage(gameWindow, textureMap, happyFace);
            board.setDebugImage(gameWindow, textureMap, debug);
            counter.setFlagCounter(board.getFlagCount(), board.IntMineCount());
            board.setCounterImage(gameWindow, textureMap, counter);
            board.setDebuggedMineImage(gameWindow, textureMap);
            board.setPauseImage(gameWindow, textureMap, pause);
            board.setPausedMineImage(gameWindow, textureMap);
            board.setLeaderboardButtonImage(gameWindow,textureMap, leaderboardButton);
            board.setTimerImage(gameWindow, textureMap, min, sec);
            board.GameOver();

            sf::Mouse mouse;
            sf::Event event;
            bool reset = false;
            if (first_click) {
                reset = true;
                leaderBoard.setCollectedTimeBoolFalse();
            }
            while (gameWindow.pollEvent(event)) {
                // These two events to close Welcome Window
                if (leaderboardOpen == false) {
                    if (event.type == sf::Event::Closed) {
                        gameWindow.close();
                    }
                    if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                        gameWindow.close();
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.type == sf::Event::MouseButtonPressed) {
                        sf::Vector2<int> position = mouse.getPosition(gameWindow);
                        sf::Vector2<float> floatPosition;
                        floatPosition.x = position.x;
                        floatPosition.y = position.y;
                        if (leaderboardButton.getGlobalBounds().contains(floatPosition)) {
                            leaderboardOpen = true;
                            leaderBoard.clearWinnersAsterisk();
                            leaderBoard.updateWinnersInTxt();
                            leaderBoard.getWinnersFromTxt();
                            leaderBoardContent.updateContent(leaderBoard);
                        }
                        if (board.getPauseStatus() == false) {
                            pausedStateBeforeLeaderboard = false;
                            board.LeftClickTile(floatPosition, first_click);
                            board.LeftClickDebugToggle(floatPosition, debug);
                        }
                        if (pause.getGlobalBounds().contains(floatPosition)) {
                            board.LeftClickPauseToggle(floatPosition, pause);
                            pausedStateBeforeLeaderboard = true;
                        }
                        reset = board.LeftClickResetButton(floatPosition, happyFace, mt, first_click);
                        board.CheckGameWin();
                        board.GameWon();
                        if (first_click == false && !(board.getGameWon() or board.getGameOver())) {
                            board.setTimerStart();
                        }
                    }
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && event.type == sf::Event::MouseButtonPressed) {
                        sf::Vector2<int> position = mouse.getPosition(gameWindow);
                        sf::Vector2<float> floatPosition;
                        floatPosition.x = position.x;
                        floatPosition.y = position.y;
                        if (board.getPauseStatus() == false) {
                            board.RightClickTile(floatPosition);
                        }
                    }
                }
            }
            gameWindow.display();

            // Timer Logic
            if (first_click) {
                end_time = start_time;
                min = std::chrono::duration_cast<std::chrono::minutes>(end_time - start_time).count();
                sec = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
            }
            if (!(board.getGameOver() or board.getGameWon()) and board.getTimerStart() and !board.getPauseStatus()) {
                end_time = std::chrono::high_resolution_clock::now() + paused_time;
                min = std::chrono::duration_cast<std::chrono::minutes>(end_time - start_time).count();
                sec = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
            }
            if (board.getGameOver() or board.getGameWon() or reset) {
                board.unsetTimerStart();
                if (board.getGameWon() && !leaderBoard.getCollectedTimeBool()) {
                    leaderBoard.setCollectedTimeBoolTrue();
                    min = std::chrono::duration_cast<std::chrono::minutes>(end_time - start_time).count();
                    sec = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
                    leaderBoard.setMinute(min);
                    leaderBoard.setSecond(sec);
                    leaderBoard.makeLogName();
                    leaderBoard.clearWinnersAsterisk();
                    leaderBoard.insertLogName();
                    leaderBoard.updateWinnersInTxt();
                    leaderBoardContent.updateContent(leaderBoard);
                    leaderboardOpen = true;
                }
                end_time = std::chrono::high_resolution_clock::now();
                start_time = std::chrono::high_resolution_clock::now();
                paused_time = end_time - start_time;
            }
            if (board.getPauseStatus() == true) {
                auto time_c = std::chrono::high_resolution_clock::now();
                end_time = time_c + (end_time - start_time);
                start_time = time_c;
                paused_time = end_time - start_time;
            }

            // Leaderboard Window Activity
            if (leaderboardOpen) {
                if (!leaderBoard.isOpen()) {
                    if (pausedStateBeforeLeaderboard == false) {
                        board.setPauseStatus();
                    }
                    leaderBoard.reOpen();
                }
                leaderBoard.requestFocus();

                sf::Event leaderboardEvent;
                while (leaderBoard.pollEvent(leaderboardEvent)) {
                    if (leaderboardEvent.type == sf::Event::Closed) {
                        leaderboardOpen = false;
                        if (pausedStateBeforeLeaderboard == false) {
                            board.unsetPauseStatus();
                        }
                        else {
                            board.setPauseStatus();
                        }
                        leaderBoard.close();
                    }
                    if ((leaderboardEvent.type == sf::Event::KeyPressed) && (leaderboardEvent.key.code == sf::Keyboard::Escape)) {
                        leaderboardOpen = false;
                        if (pausedStateBeforeLeaderboard == false) {
                            board.unsetPauseStatus();
                        }
                        else {
                            board.setPauseStatus();
                        }
                        leaderBoard.close();
                    }
                }
                leaderBoard.clear(sf::Color(0,0,255,255));
                leaderBoard.draw(leaderboardTitleText);
                leaderBoard.draw(leaderBoardContent);
                leaderBoard.display();
            }
            else {
                if (leaderBoard.isOpen()) {
                    leaderBoard.close();
                }
            }
        }
    }

    return 0;
}
