//
//  snake.cpp
//  Main Screen
//
//  Created by Cole Mitchell on 12/2/17.
//  Copyright © 2017 Cole Mitchell. All rights reserved.
//

#include "snake.hpp"
#include "Menu.hpp"
#include "pong.hpp"

#include <SFML/Graphics.hpp>
#include <cstring>
#include <cstdio>
#include <string>
#include <time.h>
#include <sstream>
#include <iostream>
//#include "playGame.hpp"


using namespace sf;

int N = 45, M = 45;
int L = 5;
int size = 16;
int w = size*N;
int h = size*M;

int dir, num = 1;

struct Snake {
    int x, y;
} s[100];

struct Fruit {
    int x, y;
} f;

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        std::swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
    
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    
    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
    
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
    
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
    
    str[i] = '\0'; // Append string terminator
    
    // Reverse the string
    reverse(str, i);
    
    return str;
}

void Tick(bool GO) {
    if (GO == false) {
        // Sets the tail of the snake to follow the head. IE the second bit moves to where the first bit was and so on
        for (int i = num; i > 0; --i) {
            s[i].x = s[i - 1].x;
            s[i].y = s[i - 1].y;
        }
        // Sets where the head of the snake will move based on the current value of direction
        if (dir == 0) {
            s[0].y += 1;
        }
        if (dir == 1) {
            s[0].x -= 1;
        }
        if (dir == 2) {
            s[0].x += 1;
        }
        if (dir == 3) {
            s[0].y -= 1;
        }
        // If the snake hits the fruit, the snake length is increased by one and the position of the fruit is randomized
        
        
        // Sets the wrap conditions so that if it goes through an edge it comes out the other side
        
    }
    
}


void snake() {
    
    srand(time(0));
    
    RenderWindow window(VideoMode(w, h), "Snake Game!");
    
    // creates the sprites for the snake, fruit, background, and game over screen
    Texture t1, t2, t3;
    t1.loadFromFile("/Users/ColeMitchell/Desktop/Main Screen/Main Screen/images/white.png");
    t2.loadFromFile("/Users/ColeMitchell/Desktop/Main Screen/Main Screen/images/green.png");
    t3.loadFromFile("/Users/ColeMitchell/Desktop/Main Screen/Main Screen/images/red.png");
    Sprite sprite1(t1);
    Sprite sprite2(t2);
    Sprite sprite3(t3);
    
    sf::Font font;
    if (!font.loadFromFile("/Users/ColeMitchell/Desktop/Main Screen/Main Screen/images/Bubble3D.ttf")) {
        return EXIT_FAILURE;
    }
    
    Clock clock;
    float timer = 0, delay = 0.05, di = .0001;
    
    f.x = 10;
    f.y = 10;
    bool GO = false;
    int score = num - 1;
    int highscore = 0;
    int play = 1;
    int exit = 0;
    int menu = 0;
    
    s[0].x = 20;
    s[0].y = 20;
    
    // Sets the text for the game messages
    sf::Text GameOver;
    GameOver.setFont(font);
    GameOver.setCharacterSize(60);
    GameOver.setPosition(300.f, 200.f);
    GameOver.setFillColor(sf::Color::White);
    GameOver.setString("Game\n Over");
    
    sf::Text Score;
    Score.setFont(font);
    Score.setCharacterSize(40);
    Score.setPosition(0.f, 0.f);
    Score.setFillColor(sf::Color::White);
    
    sf::Text HighScore;
    HighScore.setFont(font);
    HighScore.setCharacterSize(40);
    HighScore.setPosition(150.f, 0.f);
    HighScore.setFillColor(sf::Color::White);
    
    sf::Text playOption;
    playOption.setFont(font);
    playOption.setCharacterSize(40);
    playOption.setPosition(150.f, 400.f);
    playOption.setFillColor(sf::Color::Red);
    playOption.setString("Play\n Again");
    
    //sf::Text MenuOption;
    //MenuOption.setFont(font);
    //MenuOption.setCharacterSize(40);
    //MenuOption.setPosition(500.f, 425.f);
    //MenuOption.setFillColor(sf::Color::White);
   // MenuOption.setString("Menu");
    
    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setCharacterSize(40);
    exitOption.setPosition(500.f, 425.f);
    exitOption.setFillColor(sf::Color::White);
    exitOption.setString("Exit");
    
    while (window.isOpen()) {
        
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
        
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            }
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            if (s[1].x != s[0].x - 1) {
                dir = 1;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            if (s[1].x != s[0].x + 1) {
                dir = 2;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            if (s[1].y != s[0].y - 1) {
                dir = 3;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            if (s[1].y != s[0].y + 1) {
                dir = 0;
            }
        }
        
        if (timer > delay) {
            timer = 0;
            Tick(GO);
        }
        
        window.clear();
        
        // Controls the drawing of the background
        for (int i = 0; i < N; i++) {
            for (int j = L; j < M; j++) {
                sprite1.setPosition(i*size, j*size);
                window.draw(sprite1);
            }
        }
        
        // Controls the drawing of the snake
        for (int i = 0; i < num; i++) {
            sprite2.setPosition(s[i].x*size, s[i].y*size);
            window.draw(sprite2);
        }
        
        // Sprite controls for the fruit including generation and position
        sprite3.setPosition(f.x*size, f.y*size);
        window.draw(sprite3);
        
        // Every time the head collides with a fruit, length is increased, the speed is increased, and a new fruit piece is generated at random
        if ((s[0].x == f.x) && (s[0].y == f.y)) {
            num++;
            if (num % 10 == 0) {
                di = .0005;
            }
            f.x = rand() % N;
            f.y = L + rand() % (M-L);
            delay = delay - di;
            di = .0001;
            // prevents the fruit piece from generating inside the snake
            for (int i = 1; i < num; i++) {
                if (f.x == s[i].x && f.y == s[i].y) {
                    f.x = rand() % N;
                    f.y = rand() % M;
                }
            }
        }
        
        // If the snake goes out of the bounds of the arena, the Game Over flag is turned on
        if (s[0].x >= N || s[0].x < 0 || s[0].y >= M || s[0].y < L) {
            GO = true;
        }
        
        // This detects if the snake hits itself and turns on the Game Over flag if it does
        for (int i = 1; i < num; i++) {
            if (s[0].x == s[i].x && s[0].y == s[i].y) {
                GO = true;
            }
        }
        
        char buffer[100];
        
        
        char *snum = itoa(num-1, buffer, 10);
        
        
        String nums = String(snum);
        Score.setString(nums);
        window.draw(Score);
        score = num - 1;
        if (score > highscore) {
            highscore = score;
        }
        char *hsnum = itoa(highscore, buffer, 10);
        String hsnums = "High Score -  " + String(hsnum);
        HighScore.setString(hsnums);
        window.draw(HighScore);
        
        // If the Game Over flag is on, this draws a game over message
        if (GO == true) {
            window.clear();
            window.draw(GameOver);
            window.draw(HighScore);
            window.draw(Score);
            window.draw(playOption);
            //window.draw(MenuOption);
            window.draw(exitOption);
            
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                playOption.setFillColor(sf::Color::Red);
              //  MenuOption.setFillColor(sf::Color::White);
                exitOption.setFillColor(sf::Color::White);
                play = 1;
                exit = 0;
                menu =0;
            }
            // if (Keyboard::isKeyPressed(Keyboard::Right)) {
                //playOption.setFillColor(sf::Color::White);
                //MenuOption.setFillColor(sf::Color::Red);
                //exitOption.setFillColor(sf::Color::White);
                //play = 0;
                //exit = 0;
              //  menu = 1;
            //}
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                playOption.setFillColor(sf::Color::White);
                //MenuOption.setFillColor(sf::Color::White);
                exitOption.setFillColor(sf::Color::Red);
                play = 0;
                exit = 1;
                menu =0;

            }
            // This rebegins the game if return is pressed. It resest the Game Over flag, sets the snake length back to 1, and randomizes it's position
            if (Keyboard::isKeyPressed(Keyboard::Down) && play == 1) {
                GO = false;
                delay = .05;
                num = 1;
                s[0].x = 20; 
                s[0].y = 20; 
                dir = 0;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Down) && exit == 1) {
                window.close();
            }
            //else if (Keyboard::isKeyPressed(Keyboard::Return) && menu == 1) {
                // window.clear();
              //  std::cout << "This should restart" << std::endl;
                //return;
              

                // The function to return to the menu screen should go here
            //}
        }
        
        
        // Don't put anything below this or it won't work properly
        window.display();
        
    }
    
    return 0;
}