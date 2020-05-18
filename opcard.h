#ifndef OPCARD_H
#define OPCARD_H
#include "card.h"
#include <vector>

class OpCard :private Card
{

public:
    OpCard(Card*);
    void setPosition(Card);
    void zerovalues(std::vector<Card>*);
    void resetvalues(std::vector<Card>*);
};

#endif // OPCARD_H
