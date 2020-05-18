#ifndef DECK_H
#define DECK_H
#include "card.h"

#include <iostream>
#include <vector>

class Deck
{
    std::vector<Card>*deck;
public:
    Deck();
    void addCard(Card*);
    void removeCard(Card*);
    Card* getRandomCard();
    std::vector<Card>generate_deck(std::map<std::string, sf::Texture>*);
    std::vector<Card>shuffle_deck(std::vector<Card>&);
};

#endif // DECK_H
