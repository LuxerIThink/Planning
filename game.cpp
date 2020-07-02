#include "game.h"

Game::Game()
{
    setStartOptions();
    loadTextures();
    loadFonts();
    setTablesPosition();
    addObjectsToDraw();
    mainCycle();
}

Game::~Game()
{
}

void Game::render()
{
    window.clear(sf::Color::White);

    for(auto &j : drawable_objects)
    {
        for(int i=0; i<j->GetSize(); i++)
        {
            window.draw(*j->ShowCard(i));
        }
    }
    window.display();
}

void Game::mainCycle()
{
    while (window.isOpen())
    {
        close();
        mainLoop();
        render();
    }
}

void Game::mainLoop()
{
    switch(step)
    {
    case 0:
        if(mainLoopStep0()==true){break;}
    case 1:
        if(mainLoopStep1()==true){break;}
    case 2:
        if(mainLoopStep2()==true){break;}
    case 3:
        if(mainLoopStep3()==true){break;}
    }
}

bool Game::mainLoopStep0()
{
    if(op_table.GetSize()>0){op_table.RemoveAllCards();}
    std::random_shuffle(normal_cards.begin(), normal_cards.end());
    op_table.AddCard(dynamic_cast<Card*>(normal_cards[normal_cards.size()-1].get()));
    random_player++;
    if(random_player>=3){random_player=0;}
    player=random_player;
    step=1;
    return true;
}

bool Game::mainLoopStep1()
{
    std::random_shuffle(normal_cards.begin(), normal_cards.end());
    for(int i=0; i<card_amount; i++)
    {
        left_hand.AddCard(dynamic_cast<Card*>(normal_cards[i].get()));
        inverted_hand.AddCard(dynamic_cast<Card*>(normal_cards[i+card_amount].get()));
        right_hand.AddCard(dynamic_cast<Card*>(normal_cards[i+card_amount*2].get()));
        player_hand.AddCard(dynamic_cast<Card*>(normal_cards[i+card_amount*3].get()));
        left_table.AddCard(dynamic_cast<Card*>(left_cards[i].get()));
        inverted_table.AddCard(dynamic_cast<Card*>(inverted_cards[i].get()));
        right_table.AddCard(dynamic_cast<Card*>(right_cards[i].get()));
        for(int j=0; j<52; j++)
        {
            if(dynamic_cast<Card*>(inclined_cards[j].get())->getColor()==player_hand.ShowCard(i)->getColor() &&
                    dynamic_cast<Card*>(inclined_cards[j].get())->getName()==player_hand.ShowCard(i)->getName())
            {
                player_table.AddCard(dynamic_cast<Card*>(inclined_cards[j].get()));
            }
        }
    }
    step=2;
    return true;
}

bool Game::mainLoopStep2()
{
    if(playerLoopStart()==true){return true;}
    switch(player)
    {
        case 0:
            if(playerLoopPlayer0()==true){break;}
        case 1:
            if(playerLoopPlayer1()==true){break;}
        case 2:
            if(playerLoopPlayer2()==true){break;}
        case 3:
            if(playerLoopPlayer3()==true){break;}
    }
    return true;
}

bool Game::mainLoopStep3()
{
    int what_player;
    if(op_table.GetSize()>0){what_player=main_table.Compare(op_table.ShowCard(0));}
    else{what_player=main_table.Compare();}
    p[what_player]++;
    for(int i=0; i<main_table.GetSize(); i++){dynamic_cast<Card*>(main_table.ShowCard(0))->setValueDefault();}
    main_table.RemoveAllCards();
    std::cerr << p[0] << p[1] << p[2] << p[3] << std::endl;
    player=what_player;
    if(player_hand.GetSize()==0 && left_hand.GetSize()==0 && right_hand.GetSize()==0 &&
            inverted_hand.GetSize()==0 &&
            main_table.GetSize()==0)
    {
        if(one_card>=3){return 1;}
        else if(card_amount>1){card_amount--;}
        else{one_card++;}
        step=0;
    }
    else{step=2;}
    return true;
}

bool Game::playerLoopStart()
{
    if(main_table.GetSize()>=4)
    {
        step=3;
        return true;
    }
}

bool Game::playerLoopPlayer0()
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        for(int i=0; i<player_hand.GetSize(); i++)
        {
            if(mouse_pos.x >= player_hand.ShowCard(i)->getGlobalBounds().left &&
               mouse_pos.x <= player_hand.ShowCard(i)->getGlobalBounds().left+player_hand.ShowCard(i)->getGlobalBounds().width &&
               mouse_pos.y >= player_hand.ShowCard(i)->getGlobalBounds().top &&
               mouse_pos.y <= player_hand.ShowCard(i)->getGlobalBounds().top+player_hand.ShowCard(i)->getGlobalBounds().height)
            {
                if((main_table.GetSize()>0 && (dynamic_cast<Card*>(player_hand.ShowCard(i))->getColor()==dynamic_cast<Card*>(main_table.ShowCard(0))->getColor() ||
                    player_hand.findColor(dynamic_cast<Card*>(main_table.ShowCard(0))->getColor())==false)) || main_table.GetSize()==0)
                {
                    main_table.AddCard(player_hand.ShowCard(i));
                    dynamic_cast<Card*>(main_table.ShowCard(main_table.GetSize()-1))->setPlayer(0);
                    player_hand.RemoveCard(i);
                    player_hand.CenterPosition();
                    player_table.RemoveCard(i);
                    player_table.CenterPosition();
                    player=1;
                }
            }
        }
    }
    return true;
}

bool Game::playerLoopPlayer1()
{
    int z;
    while(true)
    {
        z = rand()%left_table.GetSize();
        if((main_table.GetSize()>0 && (dynamic_cast<Card*>(left_table.ShowCard(z))->getColor()==dynamic_cast<Card*>(main_table.ShowCard(0))->getColor() ||
            left_table.findColor(dynamic_cast<Card*>(main_table.ShowCard(0))->getColor())==false)) || main_table.GetSize()==0)
        {
            break;
        }
    }
    main_table.AddCard(left_hand.ShowCard(z));
    dynamic_cast<Card*>(main_table.ShowCard(main_table.GetSize()-1))->setPlayer(1);
    left_hand.RemoveCard(z);
    left_table.RemoveCard(z);
    left_table.CenterPosition();
    player=2;
    return true;
}

bool Game::playerLoopPlayer2()
{
    int z;
    while(true)
    {
        z = rand()%inverted_table.GetSize();
        if((main_table.GetSize()>0 && (dynamic_cast<Card*>(inverted_table.ShowCard(z))->getColor()==dynamic_cast<Card*>(main_table.ShowCard(0))->getColor() ||
            inverted_table.findColor(dynamic_cast<Card*>(main_table.ShowCard(0))->getColor())==false)) || main_table.GetSize()==0)
        {
            break;
        }
    }
    main_table.AddCard(inverted_hand.ShowCard(z));
    dynamic_cast<Card*>(main_table.ShowCard(main_table.GetSize()-1))->setPlayer(2);
    inverted_hand.RemoveCard(z);
    inverted_table.RemoveCard(z);
    inverted_table.CenterPosition();
    player=3;
    return true;
}

bool Game::playerLoopPlayer3()
{
    int z;
    while(true)
    {
        z = rand()%right_table.GetSize();
        if((main_table.GetSize()>0 && (dynamic_cast<Card*>(right_table.ShowCard(z))->getColor()==dynamic_cast<Card*>(main_table.ShowCard(0))->getColor() ||
           right_table.findColor(dynamic_cast<Card*>(main_table.ShowCard(0))->getColor())==false)) || main_table.GetSize()==0)
        {
            break;
        }
    }
    main_table.AddCard(right_hand.ShowCard(z));
    dynamic_cast<Card*>(main_table.ShowCard(main_table.GetSize()-1))->setPlayer(3);
    right_hand.RemoveCard(z);
    right_table.RemoveCard(z);
    right_table.CenterPosition();
    player=0;
    return true;
}

bool Game::playerLoopPlayerEnd()
{
    player=0;
    return true;
}

void Game::close()
{
    while (window.pollEvent(event)){if (event.type == sf::Event::Closed){window.close();}}
}

void Game::loadTextures()
{
    std::map<std::string, std::string>txt_paths;
    txt_paths.emplace("NormalCards", "textures\\NormalCards.png");
    txt_paths.emplace("InclinedCards", "textures\\InclinedCards.png");
    txt_paths.emplace("LeftCard", "textures\\LeftCard.png");
    txt_paths.emplace("NormalCard", "textures\\NormalCard.png");
    txt_paths.emplace("InvertedCard", "textures\\InvertedCard.png");
    txt_paths.emplace("RightCard", "textures\\RightCard.png");
    for(auto &i : txt_paths)
    {
        sf::Texture temp_texture;
        if(!temp_texture.loadFromFile(i.second))
        {std::cerr << "Path " << i.second << " don't exist" << std::endl; window.close();}
        textures.emplace(i.first, temp_texture);
    }
    normal_cards = generateDeck(textures, 49, 73, "NormalCards", true);
    inclined_cards = generateDeck(textures, 83, 38, "InclinedCards", true);
    inverted_cards = generateDeckOne(textures, "InvertedCard", 13);
    left_cards = generateDeckOne(textures, "LeftCard", 13);
    right_cards = generateDeckOne(textures, "RightCard", 13);
}

void Game::loadFonts()
{
    std::map<std::string, std::string>font_paths;
    font_paths.emplace("Fyodor", "fonts\\Fyodor.ttf");
    for(auto &i : font_paths)
    {
        sf::Font temp_font;
        if(!temp_font.loadFromFile(i.second))
        {std::cerr << "Path " << i.second << " don't exist" << std::endl; window.close();}
        fonts.emplace(i.first, temp_font);
    }
}

void Game::setTablesPosition()
{
    player_table.SetCenterPosition(410, 560, 53, 0);
    left_table.SetCenterPosition(210, 300, -36, 36);
    inverted_table.SetCenterPosition(880, 23, 53, 0);
    right_table.SetCenterPosition(950, 300, -36, 36);
    player_hand.SetCenterPosition(640, 660, 53, 0);
    op_table.SetCenterPosition(150, 260, 53, 0);
    main_table.SetCenterPosition(640, 290, 53, 0);
}

void Game::addObjectsToDraw()
{
    drawable_objects.emplace_back(&right_table);
    drawable_objects.emplace_back(&left_table);
    drawable_objects.emplace_back(&inverted_table);
    drawable_objects.emplace_back(&player_table);
    drawable_objects.emplace_back(&player_hand);
    drawable_objects.emplace_back(&main_table);
    drawable_objects.emplace_back(&op_table);
}

void Game::setStartOptions()
{
    window.create(sf::VideoMode(1280, 720), "Planowanie");
    std::srand(unsigned(std::time(0)));
    random_player=rand()%4;
    player=random_player;
    for(auto &i : p){i=0;}
    card_amount=13;
    step=1;
    one_card=0;
}

std::vector<std::unique_ptr<sf::Sprite>> Game::generateDeckOne(const std::map<std::string, sf::Texture> &txt, const std::string &txt_name,const int &amount)
{
    std::vector<std::unique_ptr<sf::Sprite>>temp;
    for(int i=0; i<amount; i++){temp.emplace_back(std::make_unique<Card>(txt_name, txt));}
    return temp;
}

std::vector<std::unique_ptr<sf::Sprite>> Game::generateDeck(const std::map<std::string, sf::Texture>&txt, const int &xval, const int &yval, const std::string &txt_name, const bool &count)
{
    const char dnames[13] = {'2', '3', '4', '5', '6', '7', '8', '9', '0', 'J', 'Q', 'K', 'A'};
    const char dcolors[4] = {'s', 'h', 'd', 'c'};
    int x=0, y=0;
    short val;
    std::vector<std::unique_ptr<sf::Sprite>>temp;
    if(count==true)
    {
        for(auto &c : dcolors)
        {
            val=2;
            for(auto &n : dnames)
            {
                temp.emplace_back(std::make_unique<Card>(val, n, c, txt_name, txt, x, y, xval, yval));
                val++;
                x+=xval;
            }
            x=0;
            y+=yval;
        }
        return temp;
    }
    else
    {
        for(auto &c : dcolors)
        {
            val=0;
            for(auto &n : dnames)
            {
                temp.emplace_back(std::make_unique<Card>(val, n, c, txt_name, txt, x, y, xval, yval));
                x+=xval;
            }
            x=0;
            y+=yval;
        }
        return temp;
    }
}
