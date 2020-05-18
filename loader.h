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
    void add_path(std::string, std::string);
    int getsize();
    std::string get_name(int);
    std::string get_path(int);
    std::string get_path(std::string);
    std::map<std::string, std::string>get_all();
};

#endif // LOADER_H
