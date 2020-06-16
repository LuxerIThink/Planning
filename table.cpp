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


