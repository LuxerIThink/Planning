#ifndef DECK_H
#define DECK_H
#include "card.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

class Deck
{
public:
    Deck();
    Deck(const std::map<std::string, sf::Texture> &, const int &, const int &, const std::string &, const bool &);
    Deck(const std::map<std::string, sf::Texture> &, const std::string &, const int &);
    std::vector<std::unique_ptr<sf::Sprite>>generate_deck(const std::map<std::string, sf::Texture> &, const int &, const int &, const std::string &, const bool &);
    std::vector<std::unique_ptr<sf::Sprite>>generate_one_deck(const std::map<std::string, sf::Texture> &, const std::string &, const int &);
};

#endif // DECK_H
