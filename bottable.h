#ifndef BOTTABLE_H
#define BOTTABLE_H
#include "card.h"

class BotTable
{
    std::vector<Card>cardsInBTable;
public:
    BotTable();
    void addCard(Card *);
    void removeCard(Card*);
    void resetHand();
    void centerCards();
    void checkPlayerCards();
};

#endif // BOTTABLE_H
