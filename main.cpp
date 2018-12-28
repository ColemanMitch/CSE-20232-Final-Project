
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "snake.hpp"
#include "pong.hpp"

using namespace sf;

int main() {
    int w = 720;
    int h = 720;
    int select = 0;
    RenderWindow window(VideoMode(w, h), "Menu Screen");
    sf::Font font;
    if (!font.loadFromFile("/Users/ColeMitchell/Desktop/Main Screen/Main Screen/images/Bubble3D.ttf")) {
        return EXIT_FAILURE;
    }
    
    sf::Text Snake;
    Snake.setFont(font);
    Snake.setCharacterSize(40);
    Snake.setPosition(150.f, 250.f);
    Snake.setFillColor(sf::Color::Red);
    Snake.setString("Snake");
    
    sf::Text Pong;
    Pong.setFont(font);
    Pong.setCharacterSize(40);
    Pong.setPosition(450.f, 250.f);
    Pong.setFillColor(sf::Color::White);
    Pong.setString("Pong");
    
    sf::Text Exit;
    Exit.setFont(font);
    Exit.setCharacterSize(40);
    Exit.setPosition(300.f, 400.f);
    Exit.setFillColor(sf::Color::White);
    Exit.setString("Exit");
    
    while (window.isOpen()) {
        
        window.clear();
        
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }
        }
        
        window.draw(Snake);
        window.draw(Pong);
        window.draw(Exit);
        
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            select = 0;
            Snake.setFillColor(sf::Color::Red);
            Pong.setFillColor(sf::Color::White);
            Exit.setFillColor(sf::Color::White);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
            select = 1;
            Pong.setFillColor(sf::Color::Red);
            Snake.setFillColor(sf::Color::White);
            Exit.setFillColor(sf::Color::White);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down)) {
            select = 2;
            Exit.setFillColor(sf::Color::Red);
            Pong.setFillColor(sf::Color::White);
            Snake.setFillColor(sf::Color::White);
        }
        if (select == 0 && Keyboard::isKeyPressed(Keyboard::Return)) {
            snake();
        }
        else if (select == 1 && Keyboard::isKeyPressed(Keyboard::Return)) {
            pong();
        }
        else if (select == 2 && Keyboard::isKeyPressed(Keyboard::Return)) {
            window.close();
        }
        
        window.display();
    }
    
    return 0;
}