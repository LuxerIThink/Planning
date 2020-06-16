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
    bool can_be_selected=false;
    bool is_playable=false;
public:
    Card(const short &,const char &,const char &);
    Card(const std::string &, const std::map<std::string, sf::Texture> &);
    Card(const short &, const std::string &, const std::map<std::string, sf::Texture> &, const int &, const int &, const int &, const int &);
    Card(const short &, const char &, const char &, const std::string &, const std::map<std::string, sf::Texture> &, const int &, const int &, const int &, const int &);
    char getName();
    char getColor();
    void reload_val();
    void set_val(short &);
    void load_textures(const std::string &, const std::map<std::string, sf::Texture> &);
    void load_texture(const std::string &, const std::map<std::string, sf::Texture> &, const int &, const int &, const int &, const int &);
};

#endif // CARD_H
