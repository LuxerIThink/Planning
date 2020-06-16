#include "card.h"

Card::Card(const short &val, const char &n, const char &c)
{
    default_val=val;
    name=n;
    color=c;
}

Card::Card(const std::string &txt_name, const std::map<std::string, sf::Texture> &txt)
{
    load_textures(txt_name, txt);
}

Card::Card(const short &val, const std::string &txt_name, const std::map<std::string, sf::Texture> &txt, const int &x, const int &y, const int &xx, const int &yy)
{
    default_val=val;
    load_texture(txt_name, txt, x, y, xx, yy);
}

Card::Card(const short &val, const char &n, const char &c, const std::string &txt_name, const std::map<std::string, sf::Texture> &txt, const int &x, const int &y, const int &xx, const int &yy)
{
    default_val=val;
    name=n;
    color=c;
    load_texture(txt_name, txt, x, y, xx, yy);
}

char Card::getName()
{
    return name;
}

char Card::getColor()
{
    return color;
}

void Card::load_textures(const std::string &txt_name, const std::map<std::string, sf::Texture> &txt)
{
    for(auto &i : txt)
    {
        if(txt_name==i.first)
        {
            this->setTexture(i.second);
        }
    }
}

void Card::load_texture(const std::string &txt_name, const std::map<std::string, sf::Texture> &txt, const int &x, const int &y, const int &xx, const int &yy)
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
