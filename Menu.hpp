//
//  Menu.hpp
//  Main Screen
//
//  Created by Cole Mitchell on 11/27/17.
//  Copyright © 2017 Cole Mitchell. All rights reserved.
//

#include <stdio.h>
#define MAX_NUMBER_OF_ITEMS 3

#include <iostream>
#include <stdio.h>
#include <SFML/Graphics.hpp>

class Menu
{
public:
    Menu(float width, float height);
    ~Menu();
    
    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int getPressedItem() {return selectedItemIndex;}
    
    
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    
};