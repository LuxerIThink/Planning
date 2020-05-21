#include "loader.h"
#include "card.h"
#include "deck.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Planowanie");
    sf::Clock clock;
    sf::Time time;
    Loader temp_paths;
    temp_paths.loadDeck();
    std::map<std::string, std::string>paths=temp_paths.get_all();
    std::map<std::string, sf::Texture>*textures = new std::map<std::string, sf::Texture>;
    for(auto &i : paths)
    {
        sf::Texture temp_texture;
        if(!temp_texture.loadFromFile(i.second))
        {
            return 1;
        }
        textures->emplace(i.first, temp_texture);
    }
    Deck newdeck;
    std::vector<Card>deck=newdeck.generate_deck(textures);
    while (window.isOpen())
    {
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear(sf::Color::Blue);
        window.draw(deck[0]);
        window.display();
        time = clock.getElapsedTime();
    }
    delete textures;
    return 0;
}
