#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include <map>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "card.h"
#include "table.h"

class Game
{
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Time time;

    std::vector<std::unique_ptr<sf::Sprite>>normal_cards, inclined_cards,
    inverted_cards, left_cards, right_cards;

    Table player_table, left_table, inverted_table, right_table, player_hand,
    left_hand, inverted_hand, right_hand, op_table, main_table;

    short random_player, player, turn_points[4], points[4], need_points[4],
    card_amount, step, one_card, choose;
    std::vector<Table*>drawable_objects;
    sf::Event event;

    std::map<std::string, sf::Texture>textures;
    std::map<std::string, sf::Font>fonts;

    std::map<std::string, sf::Text>texts, choose_texts;
    std::map<std::string, sf::RectangleShape>shapes, choose_shapes;

    std::vector<sf::RectangleShape>diamonds;

    bool render_choose, left_click, op_card;

public:
    Game();
    ~Game();
    void render();
    void mainCycle();
    void mainLoop();
    bool mainLoopStep0();
    bool mainLoopStep1();
    bool mainLoopStep2();
    bool mainLoopStep3();
    bool mainLoopStep4();
    bool playerLoopChoose0();
    bool playerLoopChoose1();
    bool playerLoopChoose2();
    bool playerLoopChoose3();
    bool playerLoopStart();
    bool playerLoopPlayer0();
    bool playerLoopPlayer1();
    bool playerLoopPlayer2();
    bool playerLoopPlayer3();
    bool playerLoopPlayerEnd();
    void close();

    void loadTextures();
    void loadFonts();
    void setTablesPosition();
    void addObjectsToDraw();
    void setStartOptions();
    void setTexts();
    void setShapes();

    void RefreshCounter();
    void RefreshTurnPoints();
    void RefreshPoints();
    void DiamondsCenterPosition(const int &, const int &, const int &, const int &, const int &);

    sf::Text generateText(const std::string &, const std::string &, const sf::Color &, const int &, const int &, const int &, const float &scalex=1, const float &scaley=1, const float &rotation=0);
    sf::RectangleShape generateRectrangle(const int &, const int &, const int &, const int &, const sf::Color &, const float &rotation=0);

    std::vector<std::unique_ptr<sf::Sprite>>generateDeck(const std::map<std::string, sf::Texture> &, const int &, const int &, const std::string &, const bool &);
    std::vector<std::unique_ptr<sf::Sprite>>generateDeckOne(const std::map<std::string, sf::Texture> &, const std::string &, const int &);
};

#endif // GAME_H
