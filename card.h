#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <algorithm>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Card :public sf::Sprite
{
    char name;
    char color;
    std::string texture_name;
    short default_val=0;
    short actual_val=0;
    short player;
public:
    Card(const short &,const char &,const char &);
    Card(const std::string &, const std::map<std::string, sf::Texture> &);
    Card(const short &, const std::string &, const std::map<std::string, sf::Texture> &, const int &, const int &, const int &, const int &);
    Card(const short &, const char &, const char &, const std::string &, const std::map<std::string, sf::Texture> &, const int &, const int &, const int &, const int &);
    char getName();
    char getColor();
    short getValue();
    short getDefaultValue();
    short getPlayer();
    void setValue(short &);
    void setValueZero();
    void setValueDefault();
    void setPlayer(const short &);
    void reloadValue();
    void addValue(const short &);
    void setCenterPosition();
    void loadTextures(const std::string &, const std::map<std::string, sf::Texture> &);
    void loadTexture(const std::string &, const std::map<std::string, sf::Texture> &, const int &, const int &, const int &, const int &);
};

#endif // CARD_H
