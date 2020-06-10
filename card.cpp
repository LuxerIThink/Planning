#include "card.h"

Card::Card()
{

}

Card::Card(short val)
{
    default_val=val;
}

Card::Card(short val, char n, char c)
{
    default_val=val;
    name=n;
    color=c;
}

Card::Card(std::string txt_name, std::map<std::string, sf::Texture>&txt)
{
    load_textures(txt_name, txt);
}

Card::Card(short val, std::string txt_name, std::map<std::string, sf::Texture>&txt)
{
    default_val=val;
    load_textures(txt_name, txt);
}

Card::Card(short val, std::string txt_name, std::map<std::string, sf::Texture> &txt, int x, int y, int xx, int yy)
{
    default_val=val;
    load_texture(txt_name, txt, x, y, xx, yy);
}

Card::Card(short val, char n, char c, std::string txt_name, std::map<std::string, sf::Texture>&txt)
{
    default_val=val;
    name=n;
    color=c;
    load_textures(txt_name, txt);
}

Card::Card(short val, char n, char c, std::string txt_name, std::map<std::string, sf::Texture> &txt, int x, int y, int xx, int yy)
{
    default_val=val;
    name=n;
    color=c;
    load_texture(txt_name, txt, x, y, xx, yy);
}

void Card::load_textures(std::string txt_name, std::map<std::string, sf::Texture> &txt)
{
    for(auto &i : txt)
    {
        if(txt_name==i.first)
        {
            this->setTexture(i.second);
        }
    }
}

void Card::load_texture(std::string txt_name, std::map<std::string, sf::Texture> &txt, int x, int y, int xx, int yy)
{
    for(auto &i : txt)
    {
        if(txt_name==i.first)
        {
            this->setTexture(i.second);
            this->setTextureRect({x,y,xx,yy});
        }
    }
}
