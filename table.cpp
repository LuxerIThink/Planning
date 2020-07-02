#include "table.h"

Table::Table()
{

}

Table::Table(const int &xcenter, const int &ycenter, const int &xcard, const int &ycard)
{
    this->SetCenterPosition(xcenter, ycenter, xcard, ycard);
}

void Table::AddCard(Card *card)
{
    table.emplace_back(card);
    this->CenterPosition();
}

void Table::RemoveCard(const int &i)
{
    table.erase(table.begin()+i);
}

void Table::RemoveAllCards()
{
    //std::cerr << "Cleared" << std::endl;
    table.clear();
    //std::cerr << "Cleared" << std::endl;
}

void Table::CenterPosition()
{
    int xo=xcen-xc*table.size()/2;
    int yo=ycen-yc*table.size()/2;
    for(auto &el : table)
    {
        el->setPosition(xo,yo);
        xo=xo+xc;
        yo=yo+yc;
        //std::cerr << xo << std::endl;
    }
}

void Table::SetCenterPosition(const int &xcenter, const int &ycenter, const int &xcard, const int &ycard)
{
    xcen=xcenter;
    ycen=ycenter;
    xc=xcard;
    yc=ycard;
}

Card *Table::ShowCard(const int &x)
{
    return table[x];
}

int Table::GetSize()
{
    return table.size();
}

int Table::Compare()
{
    table[0]->setValueDefault();
    for(int i=1; i<4; i++)
    {
        if(table[i]->getColor()!=table[0]->getColor())
        {
            table[i]->setValueDefault();
        }
        else
        {
            table[i]->setValueDefault();
        }
    }
    int z=0, tempvalue=0;
    for(int i=0; i<4; i++)
    {
        //std::cout << table[i]->getValue() << std::endl;
        if(table[i]->getValue() > tempvalue)
        {
            z=i;
            tempvalue=table[i]->getValue();
        }
    }
    return table[z]->getPlayer();
}

int Table::Compare(Card *opCard)
{
    table[0]->setValueDefault();
    for(int i=1; i<4; i++)
    {
        if(table[i]->getColor()==opCard->getColor())
        {
            table[i]->addValue(14);
        }
        else if(table[i]->getColor()==table[0]->getColor())
        {
            table[i]->setValueZero();
        }
        else
        {
            table[i]->setValueDefault();
        }
    }
    int z=0, tempvalue=0;
    for(int i=0; i<4; i++)
    {
        //std::cout << table[i]->getValue() << std::endl;
        if(table[i]->getValue() > tempvalue)
        {
            z=i;
            tempvalue=table[i]->getValue();
        }
    }
    return table[z]->getPlayer();
}

bool Table::findColor(const char &color)
{
    for(auto &x : table)
    {
        if(x->getColor() == color)
        {
            return true;
        }
    }
    return false;
}


