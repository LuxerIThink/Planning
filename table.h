#ifndef TABLE_H
#define TABLE_H

#include "card.h"

#include "Card.h"

class Table
{
    std::vector<Card>cardsInTable;
public:
    Table();
    void centerCards();
    void addCard(Card);
    void removeCard(Card);
    void resetCards();
    void compare();
    void addTPoint();
};

#endif // TABLE_H
