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
    sf::Time time, timer;

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
    Table *opTable = new Table(150, 260, 53, 0);
    Table *mainTable  = new Table(640, 290, 53, 0);

    int random_player=rand()%4;
    int player=random_player;
    int p[4]={0,0,0,0};
    int card_amount=13;
    int distribution=card_amount;
    int step=1;

    while (window.isOpen())
    {
        //std::cerr << step << std::endl;
        clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        switch(step)
        {
        case 0:
            if(opTable->GetSize()>0)
            {
                opTable->RemoveAllCards();
            }
            std::random_shuffle(normalCards.begin(), normalCards.end());
            opTable->AddCard(dynamic_cast<Card*>(normalCards[normalCards.size()-1].get()));
            random_player++;
            if(random_player>=3)
            {
                random_player=0;
            }
            player=random_player;
            step=1;
            break;
        case 1:
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
                    }
                }
            }
            step=2;
            break;
        case 2:
            if(mainTable->GetSize()>=4)
            {
                step=3;
                break;
            }
            int z;
            switch(player)
            {
            case 0:
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    for(int i=0; i<playerHand->GetSize(); i++)
                    {
                        if(mouse_pos.x >= playerHand->ShowCard(i)->getGlobalBounds().left && mouse_pos.x <= playerHand->ShowCard(i)->getGlobalBounds().left+playerHand->ShowCard(i)->getGlobalBounds().width && mouse_pos.y >= playerHand->ShowCard(i)->getGlobalBounds().top && mouse_pos.y <= playerHand->ShowCard(i)->getGlobalBounds().top+playerHand->ShowCard(i)->getGlobalBounds().height)
                        {
                            if((mainTable->GetSize()>0 && (dynamic_cast<Card*>(playerHand->ShowCard(i))->getColor()==dynamic_cast<Card*>(mainTable->ShowCard(0))->getColor() || playerHand->findColor(dynamic_cast<Card*>(mainTable->ShowCard(0))->getColor())==false)) || mainTable->GetSize()==0)
                            {
                                mainTable->AddCard(playerHand->ShowCard(i));
                                dynamic_cast<Card*>(mainTable->ShowCard(mainTable->GetSize()-1))->setPlayer(0);
                                playerHand->RemoveCard(i);
                                playerHand->CenterPosition();
                                playerTable->RemoveCard(i);
                                playerTable->CenterPosition();
                                player=1;
                                clock.restart();
                            }
                            else
                            {
                            }
                        }
                    }
                }
                break;
            case 1:
                if(clock.getElapsedTime().asMicroseconds() > 20)
                {
                    clock.restart();
                    while(true)
                    {
                        z = rand()%leftTable->GetSize();
                        if((mainTable->GetSize()>0 && (dynamic_cast<Card*>(leftTable->ShowCard(z))->getColor()==dynamic_cast<Card*>(mainTable->ShowCard(0))->getColor() || leftTable->findColor(dynamic_cast<Card*>(mainTable->ShowCard(0))->getColor())==false)) || mainTable->GetSize()==0)
                        {
                            break;
                        }
                    }
                    mainTable->AddCard(leftHand->ShowCard(z));
                    dynamic_cast<Card*>(mainTable->ShowCard(mainTable->GetSize()-1))->setPlayer(1);
                    leftHand->RemoveCard(z);
                    leftTable->RemoveCard(z);
                    leftTable->CenterPosition();
                    player=2;
                    clock.restart();
                }
                break;
            case 2:
                if(clock.getElapsedTime().asMicroseconds() > 20)
                {
                    while(true)
                    {
                        z = rand()%invertedTable->GetSize();
                        if((mainTable->GetSize()>0 && (dynamic_cast<Card*>(invertedTable->ShowCard(z))->getColor()==dynamic_cast<Card*>(mainTable->ShowCard(0))->getColor() || invertedTable->findColor(dynamic_cast<Card*>(mainTable->ShowCard(0))->getColor())==false)) || mainTable->GetSize()==0)
                        {
                            break;
                        }
                    }
                    mainTable->AddCard(invertedHand->ShowCard(z));
                    dynamic_cast<Card*>(mainTable->ShowCard(mainTable->GetSize()-1))->setPlayer(2);
                    invertedHand->RemoveCard(z);
                    invertedTable->RemoveCard(z);
                    invertedTable->CenterPosition();
                    player=3;
                    clock.restart();
                }
                break;
            case 3:
                if(clock.getElapsedTime().asMicroseconds() > 20)
                {
                    while(true)
                    {
                        z = rand()%rightTable->GetSize();
                        if((mainTable->GetSize()>0 && (dynamic_cast<Card*>(rightTable->ShowCard(z))->getColor()==dynamic_cast<Card*>(mainTable->ShowCard(0))->getColor() || rightTable->findColor(dynamic_cast<Card*>(mainTable->ShowCard(0))->getColor())==false)) || mainTable->GetSize()==0)
                        {
                            break;
                        }
                    }
                    mainTable->AddCard(rightHand->ShowCard(z));
                    dynamic_cast<Card*>(mainTable->ShowCard(mainTable->GetSize()-1))->setPlayer(3);
                    rightHand->RemoveCard(z);
                    rightTable->RemoveCard(z);
                    rightTable->CenterPosition();
                    player=0;
                    clock.restart();
                }
                break;
            default:
                player=0;
                break;
            }
            break;
        case 3:
            if(clock.getElapsedTime().asMicroseconds() > 20)
            {
                int what_player;
                if(opTable->GetSize()>0)
                {
                    what_player=mainTable->Compare(opTable->ShowCard(0));
                }
                else
                {
                    what_player=mainTable->Compare();
                }
                p[what_player]++;
                for(int i=0; i<mainTable->GetSize(); i++)
                {
                    dynamic_cast<Card*>(mainTable->ShowCard(0))->set_def_value();
                }
                mainTable->RemoveAllCards();
                std::cerr << p[0] << p[1] << p[2] << p[3] << std::endl;
                player=what_player;
                clock.restart();
                if(playerHand->GetSize()==0 && leftHand->GetSize()==0 && rightHand->GetSize()==0 && invertedHand->GetSize()==0 && mainTable->GetSize()==0)
                {
                    if(card_amount>1)
                    {
                        card_amount--;
                    }
                    step=0;
                }
                else
                {
                    step=2;
                    distribution--;
                }
            }
            break;
        }
        window.clear(sf::Color::White);

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
        for(int i=0; i<opTable->GetSize(); i++)
        {
            window.draw(*opTable->ShowCard(i));
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
