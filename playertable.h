#ifndef PLAYERTABLE_H
#define PLAYERTABLE_H

#include <iostream>
#include <vector>
#include "card.h";

class Playertable
{
    std::vector<Card*>playertable;
public:
    Playertable();
    void AddCard(Card*);
    void CenterPosition(int, int, int, int);
};

#endif // PLAYERTABLE_H
