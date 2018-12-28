//
//  pong.cpp
//  Main Screen
//
//  Created by Cole Mitchell on 12/2/17.
//  Copyright © 2017 Cole Mitchell. All rights reserved.
//

#include "pong.hpp"



// *********** C++ Final Project *************************
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "ResourcePath.hpp"
//#include "playGame.hpp"
#include <iostream>
// *******************************************************

// *******************************************************
// *** CONVERT TO STRING ***************
std::string toString( int32_t integer){
    char number[10];
    sprintf(number, "%i", integer);
    return number;
}


void pong()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    
    // Define some constants
    const float pi = 3.14159f;
    const int gameWidth = 720;
    const int gameHeight = 720;
    sf::Vector2f paddleSize(25, 100);
    float ballRadius = 10.f;
    // flags to differentiate "enter" key events
    int gameScreen = 0; // 0 for initial screen, 1 for end screen
    int gameOption; //
    
    // Create the window of the application
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "C++ Pong",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    
    // Create the left paddle
    sf::RectangleShape leftPaddle;
    leftPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    leftPaddle.setOutlineThickness(3);
    leftPaddle.setOutlineColor(sf::Color::Black);
    leftPaddle.setFillColor(sf::Color(255, 255, 255));
    leftPaddle.setOrigin(paddleSize / 2.f);
    
    // Create the right paddle
    sf::RectangleShape rightPaddle;
    rightPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    rightPaddle.setOutlineThickness(3);
    rightPaddle.setOutlineColor(sf::Color::Black);
    rightPaddle.setFillColor(sf::Color(200, 100, 100));
    rightPaddle.setOrigin(paddleSize / 2.f);
    
    // Create the ball
    sf::CircleShape ball;
    ball.setRadius(ballRadius - 3);
    ball.setOutlineThickness(3);
    ball.setOutlineColor(sf::Color::Black);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);
    
    // Load the text font
    sf::Font font;
    if (!font.loadFromFile("/Users/ColeMitchell/Desktop/Main Screen/Main Screen/images/Bubble3D.ttf")) {
        return EXIT_FAILURE;
    }
    
    // Initialize the pause message
    sf::Text pauseMessage;
    pauseMessage.setFont(font);
    pauseMessage.setCharacterSize(40);
    pauseMessage.setPosition(75.f, 200.f);
    pauseMessage.setFillColor(sf::Color::White);
    pauseMessage.setString("    Welcome to pong!\nPress enter to start");
    
    
    sf::Text scoreMessage;
    scoreMessage.setFont(font);
    scoreMessage.setCharacterSize(40);
    scoreMessage.setPosition(200.f, 20.f);
    scoreMessage.setFillColor(sf::Color::White);
    scoreMessage.setString("Score : 0 to 0");
    
    sf::Text playOption;
    playOption.setFont(font);
    playOption.setCharacterSize(40);
    playOption.setPosition(100.f, 300.f);
    playOption.setFillColor(sf::Color::Red);
    playOption.setString("Play Again");
    
    sf::Text exitOption;
    exitOption.setFont(font);
    exitOption.setCharacterSize(40);
    exitOption.setPosition(430.f, 300.f);
    exitOption.setFillColor(sf::Color::White);
    exitOption.setString("Exit");
    
    //sf::Text mainOption;
    //mainOption.setFont(font);
    //mainOption.setCharacterSize(40);
    //mainOption.setPosition(430.f, 300.f);
    //mainOption.setFillColor(sf::Color::White);
    //mainOption.setString("Main Menu");
    
    // Initialize counter ********
    int counter1 = 0; // right paddle counter
    int counter2 = 0; // left paddle counter
    
    // Define the paddles properties
    sf::Clock AITimer;
    const sf::Time AITime   = sf::seconds(0.1f);
    const float paddleSpeed = 400.f;
    float rightPaddleSpeed  = 0.f;
    const float ballSpeed   = 400.f;
    float ballAngle         = 0.f; // to be changed later

    
    sf::Clock clock;
    bool isPlaying = false;
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) ||
                ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)&&(gameScreen == 1)&&(gameOption == 1)))
            {
                window.close();
                break;
            }
            
            // Enter key pressed on initial screen: play
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return)&&(gameScreen == 0))
            {
                if (!isPlaying)
                {
                    // (re)start the game
                    isPlaying = true;
                    clock.restart();
                    
                    // Reset the position of the paddles and ball
                    leftPaddle.setPosition(10 + paddleSize.x / 2, gameHeight / 2);
                    rightPaddle.setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
                    ball.setPosition(gameWidth / 2, gameHeight / 2);
                    
                    // Reset the ball angle
                    do
                    {
                        // Make sure the ball initial angle is not too much vertical
                        ballAngle = (std::rand() % 360) * 2 * pi / 360;
                    }
                    while (std::abs(std::cos(ballAngle)) < 0.7f);
                }
            }
            // Enter key pressed on end screen, play again option: play
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)&&(gameScreen == 1)&&(gameOption == 0))
            {
                if (!isPlaying)
                {
                    // (re)start the game
                    isPlaying = true;
                    clock.restart();
                    
                    // Reset the position of the paddles and ball
                    leftPaddle.setPosition(10 + paddleSize.x / 2, gameHeight / 2);
                    rightPaddle.setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
                    ball.setPosition(gameWidth / 2, gameHeight / 2);
                    
                    // Reset the ball angle
                    do
                    {
                        // Make sure the ball initial angle is not too much vertical
                        ballAngle = (std::rand() % 360) * 2 * pi / 360;
                    }
                    while (std::abs(std::cos(ballAngle)) < 0.7f);
                }
            }
            
        }
        
        if (isPlaying)
        {
            float deltaTime = clock.restart().asSeconds();
            
            // Move the player's paddle
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &&
                (leftPaddle.getPosition().y - paddleSize.y / 2 > 5.f))
            {
                leftPaddle.move(0.f, -paddleSpeed * deltaTime);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
                (leftPaddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
            {
                leftPaddle.move(0.f, paddleSpeed * deltaTime);
            }
            
            // Move the computer's paddle
            if (((rightPaddleSpeed < 0.f) && (rightPaddle.getPosition().y - paddleSize.y / 2 > 5.f)) ||
                ((rightPaddleSpeed > 0.f) && (rightPaddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f)))
            {
                rightPaddle.move(0.f, rightPaddleSpeed * deltaTime);
            }
            
            // Update the computer's paddle direction according to the ball position
            if (AITimer.getElapsedTime() > AITime)
            {
                AITimer.restart();
                if (ball.getPosition().y + ballRadius > rightPaddle.getPosition().y + paddleSize.y / 2)
                    rightPaddleSpeed = paddleSpeed;
                else if (ball.getPosition().y - ballRadius < rightPaddle.getPosition().y - paddleSize.y / 2)
                    rightPaddleSpeed = -paddleSpeed;
                else
                    rightPaddleSpeed = 0.f;
            }
            
            // Move the ball
            float factor = ballSpeed * deltaTime;
            ball.move(std::cos(ballAngle) * factor, std::sin(ballAngle) * factor);
            
            // Check collisions between the ball and the screen
            if (ball.getPosition().x - ballRadius < 0.f)
            {
                isPlaying = false;
                // Convert the score to a string *********
                std::string comp = toString(++counter1);
                std::string user = toString(counter2);
                // Pause message **************
                pauseMessage.setString( "                You lost!");
                std::string mess = "Score: " + user + " to " + comp;
                scoreMessage.setString(mess);
                gameScreen = 1;
                gameOption = 0;
            }
            if (ball.getPosition().x + ballRadius > gameWidth)
            {
                isPlaying = false;
                // Convert the score to a string **********
                std::string comp = toString(counter1);
                std::string user = toString(++counter2);
                // Pause message **************
                pauseMessage.setString( "                You won!");
                std::string mess = "Score: "+ user + " to " + comp;
                scoreMessage.setString(mess);
                gameScreen = 1;
                gameOption = 0;
            }
            if (ball.getPosition().y - ballRadius < 0.f)
            {
                ballAngle = -ballAngle;
                ball.setPosition(ball.getPosition().x, ballRadius + 0.1f);
            }
            if (ball.getPosition().y + ballRadius > gameHeight)
            {
                ballAngle = -ballAngle;
                ball.setPosition(ball.getPosition().x, gameHeight - ballRadius - 0.1f);
            }
            
            // Check the collisions between the ball and the paddles
            // Left Paddle
            if (ball.getPosition().x - ballRadius < leftPaddle.getPosition().x + paddleSize.x / 2 &&
                ball.getPosition().x - ballRadius > leftPaddle.getPosition().x &&
                ball.getPosition().y + ballRadius >= leftPaddle.getPosition().y - paddleSize.y / 2 &&
                ball.getPosition().y - ballRadius <= leftPaddle.getPosition().y + paddleSize.y / 2)
            {
                if (ball.getPosition().y > leftPaddle.getPosition().y)
                    ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                else
                    ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
                
                ball.setPosition(leftPaddle.getPosition().x + ballRadius + paddleSize.x / 2 + 0.1f, ball.getPosition().y);
            }
            
            // Right Paddle
            if (ball.getPosition().x + ballRadius > rightPaddle.getPosition().x - paddleSize.x / 2 &&
                ball.getPosition().x + ballRadius < rightPaddle.getPosition().x &&
                ball.getPosition().y + ballRadius >= rightPaddle.getPosition().y - paddleSize.y / 2 &&
                ball.getPosition().y - ballRadius <= rightPaddle.getPosition().y + paddleSize.y / 2)
            {
                if (ball.getPosition().y > rightPaddle.getPosition().y)
                    ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                else
                    ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
                
                ball.setPosition(rightPaddle.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f, ball.getPosition().y);
            }
        }
        
        // Clear the window
        window.clear(sf::Color(49, 10, 156));
        
        if (isPlaying)
        {
            // Draw the paddles and the ball
            window.draw(leftPaddle);
            window.draw(rightPaddle);
            window.draw(ball);
            window.draw(scoreMessage);
        }
        else
        {
            // Draw the pause message
            window.draw(pauseMessage);
            window.draw(scoreMessage);
            
            if(gameScreen == 1){
                window.draw(exitOption);
                window.draw(playOption);
                //window.draw(mainOption);
                // exit
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    gameOption = 1;
                    playOption.setFillColor(sf::Color::White);
                    exitOption.setFillColor(sf::Color::Red);
                    //mainOption.setFillColor(sf::Color::White);
                }
                // play again
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    gameOption = 0;
                    playOption.setFillColor(sf::Color::Red);
                    exitOption.setFillColor(sf::Color::White);
                    //mainOption.setFillColor(sf::Color::White);
                }
            }
            
            
        }
        
        // Display things on screen
        window.display();
    }
    
    return EXIT_SUCCESS;
}