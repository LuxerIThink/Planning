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
    Card();
    Card(short);
    Card(short, char, char);
    Card(std::string, std::map<std::string, sf::Texture>&);
    Card(short, std::string, std::map<std::string, sf::Texture>&);
    Card(short, std::string, std::map<std::string, sf::Texture>&, int, int, int, int);
    Card(short, char, char, std::string, std::map<std::string, sf::Texture>&);
    Card(short, char, char, std::string, std::map<std::string, sf::Texture>&, int, int, int, int);
    void reload_val();
    void set_val(short &);
    void load_textures(std::string, std::map<std::string, sf::Texture>&);
    void load_texture(std::string, std::map<std::string, sf::Texture>&, int, int, int, int);
};

#endif // CARD_H
