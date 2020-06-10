#include "loader.h"
#include "card.h"
#include "deck.h"
#include "playertable.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    std::srand(unsigned(std::time(0)));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Planowanie");
    sf::Clock clock;
    sf::Time time;

    Loader temp_paths;
    temp_paths.loadDeck();

    Playertable playertable;

    std::map<std::string, std::string>paths;
    paths=temp_paths.get_all();
    std::map<std::string, sf::Texture>textures;
    for(auto &i : paths)
    {
        sf::Texture temp_texture;
        if(!temp_texture.loadFromFile(i.second))
        {
            return 1;
        }
        textures.emplace(i.first, temp_texture);
    }
    Deck newdeck;
    std::vector<Card*>deck = newdeck.generate_deck(textures, 83, 38, "InclinedCards", true);
    deck = newdeck.shuffle_deck(deck);
    std::vector<Card*>tdeck = newdeck.generate_one_deck(textures, "InvertedCard", 13);
    for(int i=0; i<13; i++)
    {
        playertable.AddCard(deck[i]);
    }
    playertable.CenterPosition(640, 640, 27, 0);
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
        window.clear(sf::Color::White);
        for(int i=0; i<13; i++)
        {
            window.draw(*deck[i]);
        }
        window.draw(*tdeck[5]);
        window.display();
        time = clock.getElapsedTime();
    }
    return 0;
}
