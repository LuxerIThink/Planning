#include "game.h"

Game::Game()
{
    setStartOptions();
    loadTextures();
    loadFonts();
    setTexts();
    setShapes();
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
    for(auto &j : shapes){window.draw(j.second);}
    for(auto &j : texts){window.draw(j.second);}
    if(render_choose==true)
    {
        for(auto &j : choose_shapes){window.draw(j.second);}
        for(auto &j : choose_texts){window.draw(j.second);}
    }
    if(op_card==true)
    {
        window.draw(diamonds[4]);
    }
    for(int i=0; i<4; i++)
    {
        if(main_table.GetSize()>=i+1)
        {
            window.draw(diamonds[i]);
        }
    }

    //mainLoopTest();
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
    case 4:
        if(mainLoopStep4()==true){break;}
    }
}

bool Game::mainLoopStep0()
{
    if(op_table.GetSize()>0){op_table.RemoveAllCards();}
    step=1;
    return true;
}

bool Game::mainLoopStep1()
{
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
        if(op_card==true)
        {
            op_table.AddCard(dynamic_cast<Card*>(normal_cards[normal_cards.size()-1].get()));
        }
    }
    step=2;
    render_choose=true;
    return true;
}

bool Game::mainLoopStep2()
{
    if(choose>=4){step=3; clock.restart(); return true;}
    switch(player)
    {
        case 0:
            if(playerLoopChoose0()==true){break;}
        case 1:
            if(playerLoopChoose1()==true){break;}
        case 2:
            if(playerLoopChoose2()==true){break;}
        case 3:
            if(playerLoopChoose3()==true){break;}
    }
    return true;
}

bool Game::mainLoopStep3()
{
    time = clock.getElapsedTime();
    if(playerLoopStart()==true){clock.restart(); return true;}
    switch(player)
    {
        case 0:
            if(playerLoopPlayer0()==true){break;}
        case 1:
            if(time.asMilliseconds()>=600){if(playerLoopPlayer1()==true){break;}}
        case 2:
            if(time.asMilliseconds()>=600){if(playerLoopPlayer2()==true){break;}}
        case 3:
            if(time.asMilliseconds()>=600){if(playerLoopPlayer3()==true){break;}}
    }
    return true;
}

bool Game::mainLoopStep4()
{
    time = clock.getElapsedTime();
    if(time.asMilliseconds()>=2000)
    {
    int what_player;
    if(op_table.GetSize()>0){what_player=main_table.Compare(op_table.ShowCard(0));}
    else{what_player=main_table.Compare();}
    turn_points[what_player]++;
    for(int i=0; i<main_table.GetSize(); i++){dynamic_cast<Card*>(main_table.ShowCard(0))->setValueDefault();}
    main_table.RemoveAllCards();
    player=what_player;
    //std::cerr << turn_points[0] << turn_points[1] << turn_points[2] << turn_points[3] << std::endl;
    if(player_hand.GetSize()==0 && left_hand.GetSize()==0 && right_hand.GetSize()==0 &&
            inverted_hand.GetSize()==0 && main_table.GetSize()==0)
    {
        for(int i=0; i<4; i++)
        {
            if(turn_points[i]==need_points[i])
            {
                points[i]+=turn_points[i]+10;
            }
        }
        if(one_card>=3){return 1;}
        else if(card_amount>1){card_amount--;}
        else{one_card++;}
        RefreshPoints();
        for(auto &i : turn_points){i=0;}
        for(auto &i : need_points){i=0;}
        left_click=false;
        RefreshTurnPoints();
        RefreshCounter();
        choose=0;
        random_player++;
        if(random_player>=3){random_player=0;}
        player=random_player;
        op_card=true;
        std::random_shuffle(normal_cards.begin(), normal_cards.end());
        step=0;
    }
    else{RefreshTurnPoints(); step=3;}
    return true;
    }
}

bool Game::playerLoopChoose0()
{
    if (left_click==true)
    {
        left_click=false;
        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        for(auto &el : choose_shapes)
        {
            if(mouse_pos.x >= el.second.getGlobalBounds().left &&
               mouse_pos.x <= el.second.getGlobalBounds().left+el.second.getGlobalBounds().width &&
               mouse_pos.y >= el.second.getGlobalBounds().top &&
               mouse_pos.y <= el.second.getGlobalBounds().top+el.second.getGlobalBounds().height)
            {
                if(el.first=="minus")
                {
                    if(need_points[0]>0)
                    {
                        need_points[0]-=1;
                        RefreshCounter();
                        //std::cerr << need_points[0] << std::endl;
                        //left_click=false;
                        return true;
                    }

                }
                if(el.first=="plus")
                {
                    if(need_points[0]<card_amount)
                    {
                        need_points[0]+=1;
                        RefreshCounter();
                        //std::cerr << need_points[0] << std::endl;
                        //left_click=false;
                        return true;
                    }
                }
                if(el.first=="ok")
                {
                    if(choose==3 && need_points[3]+need_points[2]+need_points[1]+need_points[0]==card_amount)
                    {

                    }
                    else
                    {
                        RefreshTurnPoints();
                        render_choose=false;
                        left_click=false;
                        choose++;
                        player=1;
                        return true;
                    }
                }
            }
        }
    }
    return true;
}

bool Game::playerLoopChoose1()
{
    float value;
    for(int i=0; i<left_hand.GetSize(); i++)
    {
        if(op_table.GetSize()==1)
        {
            if(dynamic_cast<Card*>(left_hand.ShowCard(i))->getColor()==dynamic_cast<Card*>(op_table.ShowCard(i))->getColor())
            {
                value+=1;
            }
            else
            {
                value+=dynamic_cast<Card*>(left_hand.ShowCard(i))->getDefaultValue()/14;
            }
        }
        else
        {
            value+=dynamic_cast<Card*>(left_hand.ShowCard(i))->getDefaultValue()/14;
        }
    }
    value=round(value);
    value+=rand()%((int)((card_amount-need_points[0]-need_points[2]-need_points[3]-(int)value)/(4-choose)));
    if(value>card_amount)
    {
       value=card_amount-1;
    }
    need_points[1]=(int)value;
    //std::cerr << (int)value << std::endl;
    if(choose==3 && need_points[3]+need_points[2]+need_points[1]+need_points[0]==card_amount)
    {
        int x=rand()%2;
        if(x==0)
        {
            if(need_points[1]>0)
            {
                need_points[1]--;
            }
            need_points[1]++;
        }
        else
        {
            if(need_points[1]<card_amount)
            {
                need_points[1]++;
            }
            need_points[1]--;
        }
    }
    RefreshTurnPoints();
    player=2;
    choose++;
    return true;
}

bool Game::playerLoopChoose2()
{
    float value;
    for(int i=0; i<inverted_hand.GetSize(); i++)
    {
        if(op_table.GetSize()==1)
        {
            if(dynamic_cast<Card*>(inverted_hand.ShowCard(i))->getColor()==dynamic_cast<Card*>(op_table.ShowCard(i))->getColor())
            {
                value+=1;
            }
            else
            {
                value+=dynamic_cast<Card*>(inverted_hand.ShowCard(i))->getDefaultValue()/14;
            }
        }
        else
        {
            value+=dynamic_cast<Card*>(inverted_hand.ShowCard(i))->getDefaultValue()/14;
        }
    }
    value=round(value);
    value+=rand()%((int)((card_amount-need_points[0]-need_points[1]-need_points[3]-(int)value)/(4-choose)));
    if(value>card_amount)
    {
       value=card_amount-1;
    }
    need_points[2]=(int)value;
    if(choose==3 && need_points[3]+need_points[2]+need_points[1]+need_points[0]==card_amount)
    {
        int x=rand()%2;
        if(x==0)
        {
            if(need_points[2]>0)
            {
                need_points[2]--;
            }
            need_points[2]++;
        }
        else
        {
            if(need_points[2]<card_amount)
            {
                need_points[2]++;
            }
            need_points[2]--;
        }
    }
    RefreshTurnPoints();
    player=3;
    choose++;
    return true;
}

bool Game::playerLoopChoose3()
{
    float value;
    for(int i=0; i<right_hand.GetSize(); i++)
    {
        if(op_table.GetSize()==1)
        {
            if(dynamic_cast<Card*>(right_hand.ShowCard(i))->getColor()==dynamic_cast<Card*>(op_table.ShowCard(i))->getColor())
            {
                value+=1;
            }
            else
            {
                value+=dynamic_cast<Card*>(right_hand.ShowCard(i))->getDefaultValue()/14;
            }
        }
        else
        {
            value+=dynamic_cast<Card*>(right_hand.ShowCard(i))->getDefaultValue()/14;
        }
    }
    value=round(value);
    value+=rand()%((int)((card_amount-need_points[0]-need_points[1]-need_points[2]-(int)value)/(4-choose)));
    if(value>card_amount)
    {
       value=card_amount-1;
    }
    need_points[3]=(int)value;
    if(choose==3 && need_points[3]+need_points[2]+need_points[1]+need_points[0]==card_amount)
    {
        int x=rand()%2;
        if(x==0)
        {
            if(need_points[3]>0)
            {
                need_points[3]--;
            }
            need_points[3]++;
        }
        else
        {
            if(need_points[3]<card_amount)
            {
                need_points[3]++;
            }
            need_points[3]--;
        }
    }
    RefreshTurnPoints();
    player=0;
    choose++;
    return true;
}


bool Game::playerLoopStart()
{
    if(main_table.GetSize()>=4)
    {
        step=4;
        return true;
    }
}

bool Game::playerLoopPlayer0()
{
    if (left_click==true)
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
                    left_click=false;
                    diamonds[main_table.GetSize()-1].setFillColor(sf::Color(10, 123, 255));
                    DiamondsCenterPosition(667, 238, 53, 0, main_table.GetSize());
                    clock.restart();
                    return true;
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
    diamonds[main_table.GetSize()-1].setFillColor(sf::Color(226, 0, 0));
    DiamondsCenterPosition(667, 238, 53, 0, main_table.GetSize());
    clock.restart();
    return true;
}

bool Game::playerLoopPlayer2()
{
    int z;
    while(true)
    {
        z = rand()%inverted_table.GetSize();
        if((main_table.GetSize()>0 && (dynamic_cast<Card*>(inverted_table.ShowCard(z))->getColor()==dynamic_cast<Card*>(main_table.ShowCard(0))->getColor() ||
            inverted_table.findColor(dynamic_cast<Card*>(main_table.ShowCard(0))->getColor())==false)) || main_table.GetSize()==0){break;}
    }
    main_table.AddCard(inverted_hand.ShowCard(z));
    dynamic_cast<Card*>(main_table.ShowCard(main_table.GetSize()-1))->setPlayer(2);
    inverted_hand.RemoveCard(z);
    inverted_table.RemoveCard(z);
    inverted_table.CenterPosition();
    player=3;
    diamonds[main_table.GetSize()-1].setFillColor(sf::Color(84, 216, 0));
    DiamondsCenterPosition(667, 238, 53, 0, main_table.GetSize());
    clock.restart();
    return true;
}

bool Game::playerLoopPlayer3()
{
    int z;
    while(true)
    {
        z = rand()%right_table.GetSize();
        if((main_table.GetSize()>0 && (dynamic_cast<Card*>(right_table.ShowCard(z))->getColor()==dynamic_cast<Card*>(main_table.ShowCard(0))->getColor() ||
           right_table.findColor(dynamic_cast<Card*>(main_table.ShowCard(0))->getColor())==false)) || main_table.GetSize()==0){break;}
    }
    main_table.AddCard(right_hand.ShowCard(z));
    dynamic_cast<Card*>(main_table.ShowCard(main_table.GetSize()-1))->setPlayer(3);
    right_hand.RemoveCard(z);
    right_table.RemoveCard(z);
    right_table.CenterPosition();
    player=0;
    diamonds[main_table.GetSize()-1].setFillColor(sf::Color(255, 215, 49));
    DiamondsCenterPosition(667, 238, 53, 0, main_table.GetSize());
    clock.restart();
    return true;
}

bool Game::playerLoopPlayerEnd()
{
    player=0;
    return true;
}

void Game::close()
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed){window.close();}
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){left_click=true;}
        if (event.type == sf::Event::MouseButtonReleased){left_click=false;}
    }
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
    std::random_shuffle(normal_cards.begin(), normal_cards.end());
    player_table.SetCenterPosition(408, 558, 51, 0);
    left_table.SetCenterPosition(210, 298, -36, 36);
    inverted_table.SetCenterPosition(876, 23, 51, 0);
    right_table.SetCenterPosition(942, 300, -36, 36);
    player_hand.SetCenterPosition(667, 650, 51, 0);
    op_table.SetCenterPosition(155, 210, 0, 0);
    main_table.SetCenterPosition(667, 300, 53, 0);
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
    for(auto &i : points){i=0;}
    for(auto &i : turn_points){i=0;}
    for(auto &i : need_points){i=0;}
    card_amount=13;
    step=1;
    one_card=0;
    choose=0;
    op_card=false;
}

void Game::setTexts()
{
    choose_texts.emplace("take", generateText("take", "Fyodor", {0,70,182}, 78, 640, 230));
    choose_texts.emplace("minus", generateText("-", "Fyodor", {255,255,255}, 58, 588, 275, 2));
    choose_texts.emplace("counter", generateText("0", "Fyodor", {255,255,255}, 40, 641, 296));
    choose_texts.emplace("plus1", generateText("-", "Fyodor", {255,255,255}, 55, 692, 276, 2));
    choose_texts.emplace("plus2", generateText("-", "Fyodor", {255,255,255}, 55, 727, 307, 2, 1, 90));
    choose_texts.emplace("ok", generateText("ok", "Fyodor", {255,255,255}, 40, 641, 349));
    texts.emplace("points", generateText("points", "Fyodor", {0,70,182}, 73, 156, 25));
    texts.emplace("points p0", generateText("0", "Fyodor", {255,255,255}, 29, 75, 95));
    texts.emplace("points p1", generateText("0", "Fyodor", {255,255,255}, 29, 128, 95));
    texts.emplace("points p2", generateText("0", "Fyodor", {255,255,255}, 29, 182, 95));
    texts.emplace("points p3", generateText("0", "Fyodor", {255,255,255}, 29, 236, 95));
    texts.emplace("turn points", generateText("turn points", "Fyodor", {0,70,182}, 40, 1121, 498));
    texts.emplace("turn points p0", generateText("0/0", "Fyodor", {255,255,255}, 20, 1039, 549));
    texts.emplace("turn points p1", generateText("0/0", "Fyodor", {255,255,255}, 20, 1095, 549));
    texts.emplace("turn points p2", generateText("0/0", "Fyodor", {255,255,255}, 20, 1149, 549));
    texts.emplace("turn points p3", generateText("0/0", "Fyodor", {255,255,255}, 20, 1205, 549));
}

void Game::setShapes()
{
    shapes.emplace("points p1", generateRectrangle(48, 48, 75, 104, {10, 123, 255}));
    shapes.emplace("points p2", generateRectrangle(48, 48, 129, 104, {226, 0, 0}));
    shapes.emplace("points p3", generateRectrangle(48, 48, 183, 104, {84, 216, 0}));
    shapes.emplace("points p4", generateRectrangle(48, 48, 237, 104, {255, 215, 49}));
    shapes.emplace("turn points p1", generateRectrangle(48, 48, 1040, 555, {10, 123, 255}));
    shapes.emplace("turn points p2", generateRectrangle(48, 48, 1095, 555, {226, 0, 0}));
    shapes.emplace("turn points p3", generateRectrangle(48, 48, 1150, 555, {84, 216, 0}));
    shapes.emplace("turn points p4", generateRectrangle(48, 48, 1205, 555, {255, 215, 49}));
    choose_shapes.emplace("minus", generateRectrangle(48, 48, 590, 310, {0, 70, 182}));
    choose_shapes.emplace("counter", generateRectrangle(48, 48, 642, 310, {0, 70, 182}));
    choose_shapes.emplace("plus", generateRectrangle(48, 48, 694, 310, {0, 70, 182}));
    choose_shapes.emplace("ok", generateRectrangle(152, 48, 642, 362, {0, 70, 182}));
    shapes.emplace("line p2", generateRectrangle(660, 4, 305, 300, {226, 0, 0}, -45));
    shapes.emplace("line p4", generateRectrangle(660, 4, 966, 300, {255, 215, 49}, -45));
    shapes.emplace("line p1", generateRectrangle(660, 4, 404, 532, {10, 123, 255}));
    shapes.emplace("line p3", generateRectrangle(660, 4, 868, 68, {84, 216, 0}));
    shapes.emplace("points p1", generateRectrangle(48, 48, 75, 104, {10, 123, 255}));
    shapes.emplace("points p2", generateRectrangle(48, 48, 129, 104, {226, 0, 0}));
    shapes.emplace("points p3", generateRectrangle(48, 48, 183, 104, {84, 216, 0}));
    shapes.emplace("points p4", generateRectrangle(48, 48, 237, 104, {255, 215, 49}));

    diamonds.emplace_back(generateRectrangle(14, 14, 580, 250, {255, 255, 255}, 45));
    diamonds.emplace_back(generateRectrangle(14, 14, 620, 250, {255, 255, 255}, 45));
    diamonds.emplace_back(generateRectrangle(14, 14, 660, 250, {255, 255, 255}, 45));
    diamonds.emplace_back(generateRectrangle(14, 14, 700, 250, {255, 255, 255}, 45));
    diamonds.emplace_back(generateRectrangle(14, 14, 155, 150, {0, 0, 0}, 45));
    DiamondsCenterPosition(667, 238, 53, 0, 1);
}

void Game::RefreshCounter()
{
    for(auto &el : choose_texts)
    {
        if(el.first=="counter")
        {
            el.second.setString(std::to_string(need_points[0]));
            el.second.setOrigin(el.second.getLocalBounds().width/2, el.second.getLocalBounds().height/2);
            return;
        }
    }
}

void Game::RefreshTurnPoints()
{
    for(int i=0; i<4; i++)
    {
        for(auto &el : texts)
        {
            std::string name="turn points p"+std::to_string(i);
            if(el.first==name)
            {
                el.second.setString(std::to_string(turn_points[i])+"/"+std::to_string(need_points[i]));
                el.second.setOrigin(el.second.getLocalBounds().width/2, el.second.getLocalBounds().height/2);
                break;
            }
        }
    }
}

void Game::RefreshPoints()
{
    for(int i=0; i<4; i++)
    {
        for(auto &el : texts)
        {
            std::string name="points p"+std::to_string(i);
            if(el.first==name)
            {
                el.second.setString(std::to_string(points[i]));
                el.second.setOrigin(el.second.getLocalBounds().width/2, el.second.getLocalBounds().height/2);
                break;
            }
        }
    }
}

void Game::DiamondsCenterPosition(const int &xcen, const int &ycen, const int &xc, const int &yc, const int &xd)
{
    int xo=xcen-xc*(xd)/2;
    int yo=ycen-yc*(xd)/2;
    for(int i=0; i<xd; i++)
    {
        diamonds[i].setPosition(xo,yo);
        xo=xo+xc;
        yo=yo+yc;
    }
}

sf::Text Game::generateText(const std::string &text, const std::string &font, const sf::Color &color, const int &size, const int &posx, const int &posy, const float &scalex, const float &scaley, const float &rotation)
{
    sf::Text temp;
    for(auto &i : fonts){if(i.first==font){temp.setFont(i.second);}}
    temp.setString(text);
    temp.setFillColor(color);
    temp.setCharacterSize(size);
    temp.setOrigin(temp.getLocalBounds().width/2, temp.getLocalBounds().height/2);
    temp.setPosition(posx,posy);
    temp.setScale(scalex, scaley);
    temp.setRotation(rotation);
    return temp;
}

sf::RectangleShape Game::generateRectrangle(const int &sizex, const int &sizey, const int &posx, const int &posy, const sf::Color &color, const float &rotation)
{
    sf::RectangleShape temp;
    temp.setSize(sf::Vector2f(sizex, sizey));
    temp.setOrigin(temp.getLocalBounds().width/2, temp.getLocalBounds().height/2);
    temp.setPosition(posx,posy);
    temp.setFillColor(color);
    temp.setRotation(rotation);
    return temp;
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
