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
    char dnames[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A'};
    char dcolors[4] = {'s', 'h', 'd', 'c'};
public:
    Deck();
    void addCard(Card*);
    void removeCard(Card*);
    Card* getRandomCard();
    std::vector<Card*>generate_deck(std::map<std::string, sf::Texture>&txt, int ,int, std::string, bool);
    std::vector<Card*>generate_one_deck(std::map<std::string, sf::Texture>&txt, std::string, int);
    std::vector<Card*>shuffle_deck(std::vector<Card*>&);
};

#endif // DECK_H
