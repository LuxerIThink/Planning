#include "deck.h"

std::vector<Card*>Deck::shuffle_deck(std::vector<Card*> &temp)
{
    std::random_shuffle(temp.begin(), temp.end());
    return temp;
}

Deck::Deck()
{

}

std::vector<Card*>Deck::generate_deck(std::map<std::string, sf::Texture>&txt, int xval, int yval, std::string txt_name, bool count)
{
    std::vector<Card*>temp;
    int x=0, y=0;
    short val;
    if(count==true)
    {
        for(auto &c : dcolors)
        {
            val=2;
            for(auto &n : dnames)
            {
                Card *tempcard = new Card(val, n, c, txt_name, txt, x, y, xval, yval);
                temp.emplace_back(tempcard);
                val++;
                x+=xval;
            }
            x=0;
            y+=yval;
        }
        return temp;
    }
    else
    {
        for(auto &c : dcolors)
        {
            val=0;
            for(auto &n : dnames)
            {
                Card *tempcard = new Card(val, n, c, txt_name, txt, x, y, xval, yval);
                temp.emplace_back(tempcard);
                x+=xval;
            }
            x=0;
            y+=yval;
        }
        return temp;
    }
}

std::vector<Card *> Deck::generate_one_deck(std::map<std::string, sf::Texture> &txt, std::string txt_name, int amount)
{
    std::vector<Card*>temp;
    for(int i=0; i<amount; i++)
    {
        Card *tempcard = new Card(txt_name, txt);
        temp.emplace_back(tempcard);
    }
    return temp;
}
