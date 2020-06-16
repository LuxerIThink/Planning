#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <map>

class Loader
{
    std::map<std::string, std::string>paths;
public:
    Loader();
    void loadDeck();
    int getsize();
    void add_path(const std::string &,const std::string &);
    std::map<std::string, std::string>get_all();
};

#endif // LOADER_H
