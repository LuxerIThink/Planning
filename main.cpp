#include "loader.h"
#include "card.h"
#include "deck.h"
#include "table.h"

#include <iostream>
#include <memory>
#include <vector>
#include <random>
#include <algorithm>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Planowanie");
    std::srand(unsigned(std::time(0)));
    sf::Clock clock;
    sf::Time time;

    Loader loader;
    loader.loadDeck();

    std::map<std::string, std::string>paths=loader.get_all();
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

    Deck normalDeck, inclinedDeck, invertedDeck, leftDeck, rightDeck;
    std::vector<std::unique_ptr<sf::Sprite>>normalCards = normalDeck.generate_deck(textures, 49, 73, "NormalCards", true);
    std::vector<std::unique_ptr<sf::Sprite>>inclinedCards = inclinedDeck.generate_deck(textures, 83, 38, "InclinedCards", true);
    std::vector<std::unique_ptr<sf::Sprite>>invertedCards = invertedDeck.generate_one_deck(textures, "InvertedCard", 13);
    std::vector<std::unique_ptr<sf::Sprite>>leftCards = leftDeck.generate_one_deck(textures, "LeftCard", 13);
    std::vector<std::unique_ptr<sf::Sprite>>rightCards = rightDeck.generate_one_deck(textures, "RightCard", 13);
    std::random_shuffle(normalCards.begin(), normalCards.end());

    Table *playerTable = new Table(410, 560, 53, 0);
    Table *leftTable = new Table(210, 300, -36, 36);
    Table *invertedTable = new Table(880, 23, 53, 0);
    Table *rightTable = new Table(950, 300, -36, 36);
    Table *playerHand = new Table(640, 660, 53, 0);
    Table *leftHand = new Table;
    Table *invertedHand = new Table;
    Table *rightHand = new Table;
    Table *opTable = new Table(150, 360, 53, 0);
    Table *mainTable  = new Table(640, 290, 53, 0);

    int card_amount=13;

    for(int i=0; i<card_amount; i++)
    {
        leftHand->AddCard(dynamic_cast<Card*>(normalCards[i].get()));
        invertedHand->AddCard(dynamic_cast<Card*>(normalCards[i+card_amount].get()));
        rightHand->AddCard(dynamic_cast<Card*>(normalCards[i+card_amount*2].get()));
        playerHand->AddCard(dynamic_cast<Card*>(normalCards[i+card_amount*3].get()));
        leftTable->AddCard(dynamic_cast<Card*>(leftCards[i].get()));
        invertedTable->AddCard(dynamic_cast<Card*>(invertedCards[i].get()));
        rightTable->AddCard(dynamic_cast<Card*>(rightCards[i].get()));
        for(int j=0; j<52; j++)
        {
            if(dynamic_cast<Card*>(inclinedCards[j].get())->getColor()==playerHand->ShowCard(i)->getColor() && dynamic_cast<Card*>(inclinedCards[j].get())->getName()==playerHand->ShowCard(i)->getName())
            {
                 playerTable->AddCard(dynamic_cast<Card*>(inclinedCards[j].get()));
                 //std::cerr << j << std::endl;
            }
        }
    }

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
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                for (int i=0; i<playerHand->GetSize(); i++)
                {
                    if(mouse_pos.x >= playerHand->ShowCard(i)->getGlobalBounds().left && mouse_pos.x <= playerHand->ShowCard(i)->getGlobalBounds().left+playerHand->ShowCard(i)->getGlobalBounds().width && mouse_pos.y >= playerHand->ShowCard(i)->getGlobalBounds().top && mouse_pos.y <= playerHand->ShowCard(i)->getGlobalBounds().top+playerHand->ShowCard(i)->getGlobalBounds().height)
                    {
                        int z;
                        //std::cerr << "click" << std::endl;
                        mainTable->AddCard(playerHand->ShowCard(i));
                        //std::cerr << playerHand->GetSize() << std::endl;
                        playerHand->RemoveCard(i);
                        playerHand->CenterPosition();
                        playerTable->RemoveCard(i);
                        playerTable->CenterPosition();
                        //std::cerr << playerHand->GetSize() << std::endl;
                        z = rand()%leftHand->GetSize();
                        mainTable->AddCard(leftHand->ShowCard(z));
                        leftHand->RemoveCard(z);
                        leftTable->RemoveCard(z);
                        leftTable->CenterPosition();
                        z = rand()%invertedHand->GetSize();
                        mainTable->AddCard(invertedHand->ShowCard(z));
                        invertedHand->RemoveCard(z);
                        invertedTable->RemoveCard(z);
                        invertedTable->CenterPosition();
                        z = rand()%rightTable->GetSize();
                        mainTable->AddCard(rightHand->ShowCard(z));
                        rightHand->RemoveCard(z);
                        rightTable->RemoveCard(z);
                        rightTable->CenterPosition();
                        //std::cerr << "click" << std::endl;
                    }
                }
            }
        }
        window.clear(sf::Color::White);

        //sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

        for(int i=0; i<rightTable->GetSize(); i++)
        {
            window.draw(*rightTable->ShowCard(i));
        }
        for(int i=0; i<leftTable->GetSize(); i++)
        {
            window.draw(*leftTable->ShowCard(i));
        }
        for(int i=0; i<invertedTable->GetSize(); i++)
        {
            window.draw(*invertedTable->ShowCard(i));
        }
        for(int i=0; i<playerTable->GetSize(); i++)
        {
            window.draw(*playerTable->ShowCard(i));
        }
        for(int i=0; i<playerHand->GetSize(); i++)
        {
            window.draw(*playerHand->ShowCard(i));
        }
        for(int i=0; i<mainTable->GetSize(); i++)
        {
            window.draw(*mainTable->ShowCard(i));
        }

        window.display();
        time = clock.getElapsedTime();
    }
    delete [] playerTable;
    delete [] leftTable;
    delete [] invertedTable;
    delete [] rightTable;
    delete [] playerHand;
    delete [] leftHand;
    delete [] invertedHand;
    delete [] rightHand;
    delete [] opTable;
    delete [] mainTable;
    return 0;
}
