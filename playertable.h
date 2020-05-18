#ifndef PLAYERTABLE_H
#define PLAYERTABLE_H
#include "card.h"
#include <iostream>
#include <vector>

class PlayerTable
{
    std::vector<Card>AngelDeck;
    std::vector<Card>cardsInPTable;
public:
    PlayerTable();
    void addCard(Card *);
    void removeCard(Card*);
    void resetHand();
    void centerCards();
    void checkPlayerCards();
    Card* getRandomCard();
    std::vector<Card>make_deck(std::map<std::string, sf::Texture>*);
};

#endif // PLAYERTABLE_H
