#ifndef BOTHAND_H
#define BOTHAND_H
#include <card.h>

class BotHand
{
    std::vector<Card>cardsInHand;
public:
    BotHand();
    void chooseCard();
    void addCard(Card *);
    void removeCard(Card*);
    void resetHand();
    void centerCards();
    Card* getRandomCard();
};

#endif // BOTHAND_H
