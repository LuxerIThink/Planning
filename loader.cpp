#include "loader.h"

Loader::Loader()
{

}

void Loader::loadDeck()
{
    this->add_path("NormalCards", "textures\\NormalCards.png");
    this->add_path("InclinedCards", "textures\\InclinedCards.png");
    this->add_path("LeftCard", "textures\\LeftCard.png");
    this->add_path("NormalCard", "textures\\NormalCard.png");
    this->add_path("InvertedCard", "textures\\InvertedCard.png");
    this->add_path("RightCard", "textures\\RightCard.png");
}

void Loader::add_path(const std::string &name, const std::string &path)
{
    paths.emplace(name, path);
}

int Loader::getsize()
{
    return paths.size();
}

std::map<std::string, std::string> Loader::get_all()
{
    return paths;
}
