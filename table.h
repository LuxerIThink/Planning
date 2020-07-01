#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
#include "card.h";

class Table
{
    int xcen, ycen, xc, yc;
    std::vector<Card*>table;
public:
    Table();
    Table(const int &, const int &, const int &, const int &);
    void AddCard(Card*);
    void RemoveCard(const int &i);
    void RemoveAllCards();
    void CenterPosition();
    void SetCenterPosition(const int &, const int &, const int &, const int &);
    Card* ShowCard(const int &);
    int GetSize();
    int Compare();
    int Compare(Card *);
    bool findColor(const char &);
};

#endif // TABLE_H
