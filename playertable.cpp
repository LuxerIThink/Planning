#include "playertable.h"

Playertable::Playertable()
{

}

void Playertable::AddCard(Card *card)
{
    playertable.emplace_back(card);
}

void Playertable::CenterPosition(int xcen,int ycen,int x,int y)
{
    xcen-=x*playertable.size();
    ycen-=y*playertable.size();
    for(auto &el : playertable)
    {
        el->setPosition(xcen,ycen);
        xcen+=x*2;
        ycen+=y;
        //std::cerr << x << std::endl;
    }
}
