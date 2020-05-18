#ifndef COUNTERBOX_H
#define COUNTERBOX_H
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class CounterBox :public sf::Sprite
{
    int value;
    std::string text;
public:
    CounterBox();
    void increase();
    void decrease();
    void reset();
};

#endif // COUNTERBOX_H
