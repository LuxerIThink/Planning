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

Card::Card(short val, std::string txt_name, std::map<std::string, sf::Texture>*txt)
{
    default_val=val;
    load_texture(txt_name, txt);
}

Card::Card(short val, char n, char c, std::string txt_name, std::map<std::string, sf::Texture>*txt)
{
    default_val=val;
    name=n;
    color=c;
    load_texture(txt_name, txt);
}

void Card::load_texture(std::string txt_name, std::map<std::string, sf::Texture> *txt)
{
    for(auto &i : *txt)
    {
        if(txt_name==i.first)
        {
            this->setTexture(i.second);
        }
    }
}
