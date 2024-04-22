#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Tetromino.h"
#include "Well.h"
using namespace std;

Tetromino* getRandomTetromino(sf::Vector2f startPosition)
{
    srand(time(0));

    cout << "Random number: " << rand();

    int random = rand() % 7;
    cout << random << endl;
    switch (random) {
    case 0:
        return new TetrominoI(startPosition);
    case 1:
        return new TetrominoO(startPosition);
    case 2:
        return new TetrominoS(startPosition);
    case 3:
        return new TetrominoZ(startPosition);
    case 4:
        return new TetrominoT(startPosition);
    case 5:
        return new TetrominoL(startPosition);
    case 6:
        return new TetrominoJ(startPosition);
    }
}

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(750, 850), "Tetris");
    sf::Vector2f startPosition(200.0f, 0.0f);


    /* sf::Font font;
     if (!font.loadFromFile("path/to/font/arial.ttf"))
     {

         return 1;
     }*/

    sf::RectangleShape rectangle1(sf::Vector2f(150.0f, 80.0f));
    rectangle1.setPosition(550.0f, 100.0f);
    rectangle1.setOutlineColor(sf::Color::Red);
    rectangle1.setFillColor(sf::Color::Magenta);
    /*  sf::Text text1("tetris", font, 24);
      text1.setFillColor(sf::Color::White);
      text1.setPosition(120.0f, 115.0f);*/


    sf::RectangleShape rectangle2(sf::Vector2f(150.0f, 80.0f));
    rectangle2.setPosition(550.0f, 300.0f);
    rectangle2.setFillColor(sf::Color::Green);
    /*  sf::Text text2("   score:   ", font, 24);
      text2.setFillColor(sf::Color::White);
      text2.setPosition(310.0f, 215.0f);*/

    sf::RectangleShape rectangle3(sf::Vector2f(150.0f, 80.0f));
    rectangle3.setPosition(550.0f, 500.0f);
    rectangle3.setFillColor(sf::Color::Blue);
    /*sf::Text text3("LeveL 1", font, 24);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(520.0f, 315.0f);*/

    Tetromino* currTetromino = getRandomTetromino(startPosition);

    //TetrominoI I(startPosition);
   //TetrominoO O(startPosition);
   //TetrominoS S(startPosition);
   //TetrominoJ J(startPosition);
   //TetrominoT T(startPosition);
   //TetrominoL L(startPosition);
   //TetrominoZ Z(startPosition);

    Well well(window);
    sf::Clock clock;
    sf::Time elapsed;

    clock.restart();

    while (window.isOpen())
    {
        elapsed = clock.getElapsedTime();
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }


            // Handle input to rotate the tetrimino
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    currTetromino->rotate();
                    /* I.rotate();
                       O.rotate();
                       S.rotate();
                       Z.rotate();
                       T.rotate();
                       L.rotate();
                       J.rotate();*/

                }
                // To move Left

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Left)
                    {
                        currTetromino->moveLeft();

                        /* I.moveLeft();
                           O.moveLeft();
                           S.moveLeft();
                           Z.moveLeft();
                           L.moveLeft();
                           J.moveLeft();
                           T.moveLeft();*/
                    }
                }
                // To move Down

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Down)
                    {
                        currTetromino->moveDown();

                        /* I.moveDown();
                         O.moveDown();
                         S.moveDown();
                         Z.moveDown();
                         T.moveDown();
                         L.moveDown();
                         J.moveDown();*/

                    }
                }
                // To move right 
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Right)
                    {
                        currTetromino->moveRight();

                        /*I.moveRight();
                          O.moveRight();
                          S.moveRight();
                          Z.moveRight();
                          T.moveRight();
                          L.moveRight();
                          J.moveRight();*/

                    }
                }
            }
        }

        // move down once every second
        if (elapsed.asSeconds() > 1)
        {
            currTetromino->moveDown();

            /* I.moveDown();
               O.moveDown();
               S.moveDown();
               Z.moveDown();
               L.moveDown();
               T.moveDown();
               J.moveDown();*/
            clock.restart();
        }

        well.draw(window);

        /*I.draw(window);
        O.draw(window);
        S.draw(window);
        Z.draw(window);
        L.draw(window);
        T.draw(window);
        J.draw(window);*/

        window.draw(rectangle1);
        window.draw(rectangle2);
        window.draw(rectangle3);

        // Draw the texts
       /* window.draw(text1);
        window.draw(text2);
        window.draw(text3);*/


        currTetromino->draw(window);


        window.display();
    }

    //  int scores[5] = {};
    // string scoreNames[5];


    // ifstream file("./highscores.txt");


    // if (!file.is_open()) 
    // {
    //     // Highscore file does not exist
    //     for (int i = 0; i < 5; i++) 
    //     {
    //         scores[i] = 0;
    //         scoreNames[i] = "";
    //     }
    //     return;
    // }

    // for (int i = 0; i < 5; i++)
    // {
    //     file >> line;
    //     scoreNames[i] = line;
    //     file >> line;
    //     scores[i] = stoi(line);
    // }


    // ofstream file("./highscores.txt");

    ////  Check if the file was opened successfully:


    //  if (!file.is_open()) {
    //      // Highscore file does not exist
    //      // Creating the file...
    //      file.open("./highscores.txt");
    //  }

    //  // Loop over the arrays and save the name and highscores
    //  for (int i = 0; i < 5; i++) {
    //      file << scoreNames[i] << endl;
    //      file << scores[i] << endl;
    //  }

    //   //close the file at the end

    //  file.close();






    return 0;
}