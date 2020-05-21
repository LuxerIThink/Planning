#include "deck.h"

std::vector<Card>Deck::shuffle_deck(std::vector<Card> &temp)
{
    std::random_device rd;
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(temp), std::end(temp), rng);
    return temp;
}

Deck::Deck()
{

}

std::vector<Card>Deck::generate_deck(std::map<std::string, sf::Texture>*txt)
{
    std::vector<Card>temp;
    Card s2S((short)6, '2', '2', "s2S", txt);
    temp.emplace_back(s2S);
    return temp;
}
