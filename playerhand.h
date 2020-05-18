#ifndef PLAYERHAND_H
#define PLAYERHAND_H
#include "card.h"

#include <iostream>
#include <vector>

class PlayerHand
{
    std::vector<Card>cardsInHand;
public:
    PlayerHand();
    void addCard(Card *);
    void removeCard(Card*);
    void resetHand();
    void centerCards();
    Card* getRandomCard();
};

#endif // PLAYERHAND_H
