//
//  Menu.cpp
//  Main Screen
//
//  Created by Cole Mitchell on 11/27/17.
//  Copyright © 2017 Cole Mitchell. All rights reserved.
//

#include "Menu.hpp"



Menu:: Menu(float width, float height) {
    if (!font.loadFromFile("/Users/ColeMitchell/Desktop/Main Screen/Main Screen/Bubble3D.ttf")) {
        // handle error
    }
    
    //Snake
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setString("Snake");
    menu[0].setCharacterSize(height/15);
    menu[0].setPosition(width/2, height/(MAX_NUMBER_OF_ITEMS+1) * 1);
    
    //Pong
    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setString("Pong");
    menu[1].setCharacterSize(height/15);
    menu[1].setPosition(width/2, height/(MAX_NUMBER_OF_ITEMS+1) * 2);
    
    //Exit
    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setCharacterSize(height/15);
    menu[2].setPosition(width/2, height/(MAX_NUMBER_OF_ITEMS+1) * 3);

}

Menu:: ~Menu() {
    
}

void Menu::draw(sf::RenderWindow &window) {
    for (int i=0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp() {
    if (selectedItemIndex - 1 >=0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);

    }
}

void Menu::MoveDown() {
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
        
    }

}

