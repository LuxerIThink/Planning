#include "deck.h"

Deck::Deck()
{

}

std::vector<std::unique_ptr<sf::Sprite>> Deck::generate_deck(const std::map<std::string, sf::Texture>&txt, const int &xval, const int &yval, const std::string &txt_name, const bool &count)
{
    char dnames[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A'};
    char dcolors[4] = {'s', 'h', 'd', 'c'};
    int x=0, y=0;
    short val;
    std::vector<std::unique_ptr<sf::Sprite>>temp;
    if(count==true)
    {
        for(auto &c : dcolors)
        {
            val=2;
            for(auto &n : dnames)
            {
                temp.emplace_back(std::make_unique<Card>(val, n, c, txt_name, txt, x, y, xval, yval));
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
                temp.emplace_back(std::make_unique<Card>(val, n, c, txt_name, txt, x, y, xval, yval));
                x+=xval;
            }
            x=0;
            y+=yval;
        }
        return temp;
    }
}

std::vector<std::unique_ptr<sf::Sprite>> Deck::generate_one_deck(const std::map<std::string, sf::Texture> &txt, const std::string &txt_name,const int &amount)
{
    std::vector<std::unique_ptr<sf::Sprite>>temp;
    for(int i=0; i<amount; i++)
    {
        temp.emplace_back(std::make_unique<Card>(txt_name, txt));
    }
    return temp;
}
