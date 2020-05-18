#ifndef TEXTBOX_H
#define TEXTBOX_H
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class TextBox :public sf::Sprite
{
    std::string text;
public:
    TextBox();
    void setText();
    void reloadText();
};

#endif // TEXTBOX_H
