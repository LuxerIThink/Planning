#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include <map>

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

    short random_player, player, p[4], card_amount, step, one_card;
    std::vector<Table*>drawable_objects;
    sf::Event event;

    std::map<std::string, sf::Texture>textures;
    std::map<std::string, sf::Font>fonts;


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
    std::vector<std::unique_ptr<sf::Sprite>>generateDeck(const std::map<std::string, sf::Texture> &, const int &, const int &, const std::string &, const bool &);
    std::vector<std::unique_ptr<sf::Sprite>>generateDeckOne(const std::map<std::string, sf::Texture> &, const std::string &, const int &);
};

#endif // GAME_H
