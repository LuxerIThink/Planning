#include "loader.h"

Loader::Loader()
{

}

void Loader::loadDeck()
{
    this->add_path("s2S", "textures\\cards\\simple\\S\\2S.png");
    this->add_path("s3S", "textures\\cards\\simple\\S\\3S.png");
}

void Loader::add_path(std::string name, std::string path)
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
