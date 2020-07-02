#include "card.h"

Card::Card(const short &val, const char &n, const char &c)
{
    default_val=val;
    name=n;
    color=c;
}

Card::Card(const std::string &txt_name, const std::map<std::string, sf::Texture> &txt)
{
    loadTextures(txt_name, txt);
}

Card::Card(const short &val, const std::string &txt_name, const std::map<std::string, sf::Texture> &txt, const int &x, const int &y, const int &xx, const int &yy)
{
    default_val=val;
    loadTexture(txt_name, txt, x, y, xx, yy);
}

Card::Card(const short &val, const char &n, const char &c, const std::string &txt_name, const std::map<std::string, sf::Texture> &txt, const int &x, const int &y, const int &xx, const int &yy)
{
    default_val=val;
    name=n;
    color=c;
    loadTexture(txt_name, txt, x, y, xx, yy);
}

char Card::getName()
{
    return name;
}

char Card::getColor()
{
    return color;
}

void Card::setValue(short &val)
{
    actual_val=val;
}

void Card::setValueZero()
{
    actual_val=0;
}

void Card::setValueDefault()
{
    actual_val=default_val;
}

void Card::addValue(const short &val)
{
    actual_val=default_val+val;
}

short Card::getValue()
{
    return actual_val;
}

void Card::setPlayer(const short &val)
{
    player=val;
}

short Card::getPlayer()
{
    return player;
}

void Card::loadTextures(const std::string &txt_name, const std::map<std::string, sf::Texture> &txt)
{
    for(auto &i : txt){if(txt_name==i.first){this->setTexture(i.second);}}
}

void Card::loadTexture(const std::string &txt_name, const std::map<std::string, sf::Texture> &txt, const int &x, const int &y, const int &xx, const int &yy)
{
    for(auto &i : txt)
    {
        if(txt_name==i.first)
        {
            this->setTexture(i.second);
            this->setTextureRect({x,y,xx,yy});
        }
    }
    float tempx=round(this->getLocalBounds().width/2);
    float tempy=round(this->getLocalBounds().height/2);
    this->setOrigin(tempx, tempy);
}

