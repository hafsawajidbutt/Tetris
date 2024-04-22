#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

#include "well.h"

class Tetromino
{
public:
    Tetromino(sf::Color color, sf::Vector2f position) : m_color(color), m_position(position), m_rotation(0)
    {
    }
    virtual ~Tetromino()
    {
    }
    virtual void rotate() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual void speedUp() = 0;
    virtual bool update() = 0;
    virtual void reset(sf::Vector2f position) = 0;
    virtual void moveDown() = 0;

    sf::Color getColor() const
    {
        return m_color;
    }
    sf::Vector2f getPosition() const
    {
        return m_position;
    }
    int getRotation() const
    {
        return m_rotation;
    }

protected:
    sf::Color m_color;
    sf::Vector2f m_position;
    int m_rotation;
};

// I tetromino.

class TetrominoI : public Tetromino
{
private:
    sf::RectangleShape m_blocks[4];

public:
    static constexpr float blockSize = 50.0f;
    TetrominoI(sf::Vector2f position)
        : Tetromino(sf::Color::Cyan, position)
    {
        for (int i = 0; i < 4; ++i)
        {
            m_blocks[i].setFillColor(m_color);
            m_blocks[i].setSize(sf::Vector2f(47.0f, 47.0f));
        }
        reset(position);
    }

    void rotate()
    {
        sf::Vector2f pivot = m_blocks[1].getPosition();

        // don't rotate when shape will go out of bounds of the grid
        if (m_rotation == 0)
        {
            if (pivot.x < blockSize || pivot.x > blockSize * 7)
            {
                return;
            }
        }

        m_rotation = (m_rotation + 1) % 2;

        // // don't rotate when shape will go out of bounds of the grid
        // if (m_rotation == 1) {
        //     if (pivot.x < blockSize || pivot.x > blockSize * 7) {
        //         return;
        //     }
        // }

        switch (m_rotation)
        {
        case 1:
            m_blocks[0].setPosition(pivot.x - blockSize, pivot.y);
            m_blocks[2].setPosition(pivot.x + blockSize, pivot.y);
            m_blocks[3].setPosition(pivot.x + blockSize * 2, pivot.y);
            break;
        case 0:
            m_blocks[0].setPosition(pivot.x, pivot.y - blockSize);
            m_blocks[2].setPosition(pivot.x, pivot.y + blockSize);
            m_blocks[3].setPosition(pivot.x, pivot.y + blockSize * 2);
            break;
        }
    }

    void draw(sf::RenderWindow& window)
    {
        for (int i = 0; i < 4; ++i) {
            window.draw(m_blocks[i]);
        }
    }
    // override to move left
    void moveLeft()
    {
        // Calculate the new position when moving left
        sf::Vector2f newPosition;

        newPosition = sf::Vector2f(m_position.x - blockSize, m_position.y);

        // Check if any block would go out of bounds when moving left
        if (newPosition.x < 0 || (m_rotation == 1 && newPosition.x < blockSize)) {
            // Ignore the move if any block would go out of bounds
            return;
        }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i)
        {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x - blockSize, m_blocks[i].getPosition().y);
        }
    }
    // override to move right
    void moveRight()
    {
        // Calculate the new position when moving right
        sf::Vector2f newPosition;

        newPosition = sf::Vector2f(m_position.x + blockSize, m_position.y);

        // Check if any block would go out of bounds when moving right
        if (m_rotation == 0)
        {
            if (newPosition.x > blockSize * 9)
            {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else
        {
            if (newPosition.x > blockSize * 7)
            {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i)
        {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x + blockSize, m_blocks[i].getPosition().y);
        }
    }

    void moveDown() {
        // Calculate the new position when moving down
        sf::Vector2f newPosition(m_position.x, m_position.y + blockSize);

        // Check if any block would go out of bounds when moving down
        for (int i = 0; i < 4; ++i) {
            // Check if any block would go out of bounds when moving right
            if (m_rotation == 0)
            {
                if (newPosition.y > blockSize * 15)
                {
                    // Ignore the move if any block would go out of bounds
                    return;
                }
            }
            else
            {
                if (newPosition.y > blockSize * 17)
                {
                    // Ignore the move if any block would go out of bounds
                    return;
                }
            }
        }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x, m_blocks[i].getPosition().y + blockSize);
        }
    }
    void speedUp()
    {
    }
    bool update()
    {
        return false;
    }
    void reset(sf::Vector2f position)
    {
        m_position = position;
        m_rotation = 0;

        if (m_rotation == 1)
        {
            m_blocks[0].setPosition(m_position.x - blockSize * 2, m_position.y);
            m_blocks[1].setPosition(m_position.x - blockSize, m_position.y);
            m_blocks[2].setPosition(m_position.x, m_position.y);
            m_blocks[3].setPosition(m_position.x + blockSize, m_position.y);
        }
        else
        {
            m_blocks[0].setPosition(m_position.x, m_position.y - blockSize * 2);
            m_blocks[1].setPosition(m_position.x, m_position.y - blockSize);
            m_blocks[2].setPosition(m_position.x, m_position.y);
            m_blocks[3].setPosition(m_position.x, m_position.y + blockSize);
        }
    }
};

// O tetromino.
class TetrominoO : public Tetromino
{
private:
    sf::RectangleShape m_blocks[4];

public:
    static constexpr float blockSize = 50.0f;
    TetrominoO(sf::Vector2f position) : Tetromino(sf::Color::Yellow, position)
    {
        for (int i = 0; i < 4; i++)
        {
            m_blocks[i].setFillColor(m_color);
            m_blocks[i].setSize(sf::Vector2f(47.0f, 47.0f));
        }
        reset(position);
    }
    void rotate()
    {
        // O-shape doesnt rotate
    }
    void draw(sf::RenderWindow& window)
    {
        for (int i = 0; i < 4; i++)
        {
            window.draw(m_blocks[i]);
        }
    }

    void moveLeft()
    {
        // Calculate the new position when moving left
        sf::Vector2f newPosition(m_position.x - blockSize, m_position.y);

        // Check if any block would go out of bounds when moving left
        for (int i = 0; i < 4; ++i)
        {
            if (newPosition.x < 0)
            {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;
        for (int i = 0; i < 4; ++i)
        {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x - blockSize,
                m_blocks[i].getPosition().y);
        }
    }

    void moveRight()
    {
        sf::Vector2f newPosition(m_position.x + blockSize * 2, m_position.y);

        // Check if any block would go out of bounds when moving left
        for (int i = 0; i < 4; ++i)
        {
            if (newPosition.x > blockSize * 9)
            {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        m_position.x += blockSize;

        for (int i = 0; i < 4; ++i)
        {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x + blockSize, m_blocks[i].getPosition().y);
        }
    }

    void moveDown() {
        // Calculate the new position when moving down
        sf::Vector2f newPosition(m_position.x, m_position.y + blockSize);

        // Check if any block would go out of bounds when moving down
        for (int i = 0; i < 4; ++i) {
            if (newPosition.y > blockSize * 15) {
                // Ignore the move if any block would go out of bounds or reach the bottom
                return;
            }
        }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x, m_blocks[i].getPosition().y + blockSize);
        }
    }

    void speedUp()
    {
    }

    bool update()
    {
        return false;
    }

    void reset(sf::Vector2f position)
    {
        m_position = position;
        m_rotation = 0;

        // Set the positions of the blocks for the O-shaped Tetromino
        m_blocks[0].setPosition(m_position.x, m_position.y);
        m_blocks[1].setPosition(m_position.x + blockSize, m_position.y);
        m_blocks[2].setPosition(m_position.x, m_position.y + blockSize);
        m_blocks[3].setPosition(m_position.x + blockSize, m_position.y + blockSize);
    }
};

// S tetromino

class TetrominoS : public Tetromino
{
private:
    sf::RectangleShape m_blocks[4];

public:
    static constexpr float blockSize = 50.0f;
    TetrominoS(sf::Vector2f position)
        : Tetromino(sf::Color::Green, position)
    {
        for (int i = 0; i < 4; ++i)
        {
            m_blocks[i].setFillColor(m_color);
            m_blocks[i].setSize(sf::Vector2f(47.0f, 47.0f));
        }
        reset(position);
    }

    void rotate()
    {
        sf::Vector2f pivot = m_blocks[1].getPosition();

        // don't rotate when shape will go out of bounds of the grid
        if (m_rotation == 0)
        {
            if (pivot.x < blockSize || pivot.x > blockSize * 8)
            {
                return;
            }
        }
        else if (m_rotation == 1) {
            if (pivot.x < blockSize * 1 || pivot.x > blockSize * 8)
            {
                return;
            }
        }
        else if (m_rotation == 2) {
            if (pivot.x < blockSize || pivot.x > blockSize * 8)
            {
                return;
            }
        }
        else if (m_rotation == 3)
        {
            if (pivot.x < blockSize * 1 || pivot.x > blockSize * 8)
            {
                return;
            }
        }

        if (m_rotation == 3)
        {
            m_rotation = 0;
        }
        else
        {
            m_rotation++;
        }

        switch (m_rotation)
        {
        case 1:
            m_blocks[0].setPosition(pivot.x + blockSize, pivot.y - blockSize);
            m_blocks[2].setPosition(pivot.x, pivot.y + blockSize);
            m_blocks[3].setPosition(pivot.x + blockSize, pivot.y);
            break;
        case 2:
            m_blocks[0].setPosition(pivot.x + blockSize, pivot.y + blockSize);
            m_blocks[2].setPosition(pivot.x - blockSize, pivot.y);
            m_blocks[3].setPosition(pivot.x, pivot.y + blockSize);
            break;
        case 3:
            m_blocks[0].setPosition(pivot.x - blockSize, pivot.y + blockSize);
            m_blocks[2].setPosition(pivot.x, pivot.y - blockSize);
            m_blocks[3].setPosition(pivot.x - blockSize, pivot.y);
            break;
        case 0:
            m_blocks[0].setPosition(pivot.x - blockSize, pivot.y - blockSize);
            m_blocks[2].setPosition(pivot.x + blockSize, pivot.y);
            m_blocks[3].setPosition(pivot.x, pivot.y - blockSize);
            break;
        }
    }

    void draw(sf::RenderWindow& window)
    {
        for (int i = 0; i < 4; ++i)
        {
            window.draw(m_blocks[i]);
        }
    }

    void moveLeft()
    {
        // Calculate the new position when moving left
        sf::Vector2f newPosition;

        newPosition = sf::Vector2f(m_position.x - blockSize, m_position.y);

        // // Check if any block would go out of bounds when moving left
        // if (newPosition.x < 0 || (m_rotation == 1 && newPosition.x < blockSize)) {
        //     // Ignore the move if any block would go out of bounds
        //     return;
        // }

        cout << "newPosition.x: " << newPosition.x << endl;

        if (m_rotation == 0) {
            if (newPosition.x - blockSize < 0) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.x + blockSize < blockSize) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.x - blockSize < 0) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.x < blockSize) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x - blockSize,
                m_blocks[i].getPosition().y);
        }
    }

    void moveRight() {
        sf::Vector2f newPosition;

        newPosition = sf::Vector2f(m_position.x + blockSize, m_position.y);

        // Check if any block would go out of bounds when moving right
        if (m_rotation == 0) {
            if (newPosition.x + blockSize > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.x + blockSize > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.x + blockSize > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.x > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        m_position.x += blockSize;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x + blockSize,
                m_blocks[i].getPosition().y);
        }
    }

    void moveDown() {


        sf::Vector2f newPosition;

        newPosition = sf::Vector2f(m_position.x + blockSize, m_position.y);

        // Check if any block would go out of bounds when moving right
        if (m_rotation == 0) {
            if (newPosition.y > blockSize * 14) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.y > blockSize * 14) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.y > blockSize * 14) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.y > blockSize * 14) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x,
                m_blocks[i].getPosition().y + blockSize);
        }
    }

    void speedUp() {
    }

    bool update() {
        return false;
    }

    void reset(sf::Vector2f position) {
        m_position = position;
        m_rotation = 0;

        if (m_rotation == 0) {
            m_blocks[0].setPosition(m_position.x - blockSize, m_position.y + blockSize);
            m_blocks[1].setPosition(m_position.x, m_position.y + blockSize);
            m_blocks[2].setPosition(m_position.x, m_position.y);
            m_blocks[3].setPosition(m_position.x + blockSize, m_position.y);
        }
        else {
            m_blocks[0].setPosition(m_position.x + blockSize, m_position.y - blockSize);
            m_blocks[1].setPosition(m_position.x, m_position.y - blockSize);
            m_blocks[2].setPosition(m_position.x, m_position.y);
            m_blocks[3].setPosition(m_position.x - blockSize, m_position.y);
        }
    }
};

// Z tetromino.

class TetrominoZ : public Tetromino {
private:
    sf::RectangleShape m_blocks[4];

public:
    static constexpr float blockSize = 50.0f;
    TetrominoZ(sf::Vector2f position)
        : Tetromino(sf::Color::Red, position)
    {
        for (int i = 0; i < 4; ++i)
        {
            m_blocks[i].setFillColor(m_color);
            m_blocks[i].setSize(sf::Vector2f(47.0f, 47.0f));
        }
        reset(position);
    }

    void rotate() {
        sf::Vector2f pivot = m_blocks[1].getPosition();

        // don't rotate when shape will go out of bounds of the grid
        if (m_rotation == 0)
        {
            if (pivot.x < blockSize || pivot.x > blockSize * 8)
            {
                return;
            }
        }
        else if (m_rotation == 1)
        {
            if (pivot.x < blockSize * 1 || pivot.x > blockSize * 8)
            {
                return;
            }
        }
        else if (m_rotation == 2)
        {
            if (pivot.x < blockSize || pivot.x > blockSize * 8)
            {
                return;
            }
        }
        else if (m_rotation == 3)
        {
            if (pivot.x < blockSize * 1 || pivot.x > blockSize * 8)
            {
                return;
            }
        }

        if (m_rotation == 3) {
            m_rotation = 0;
        }
        else {
            m_rotation++;
        }

        switch (m_rotation) {
        case 0:
            m_blocks[0].setPosition(pivot.x - blockSize, pivot.y - blockSize);
            m_blocks[2].setPosition(pivot.x + blockSize, pivot.y);
            m_blocks[3].setPosition(pivot.x, pivot.y - blockSize);

            break;
        case 1:
            m_blocks[0].setPosition(pivot.x - blockSize, pivot.y + blockSize);
            m_blocks[2].setPosition(pivot.x, pivot.y - blockSize);
            m_blocks[3].setPosition(pivot.x - blockSize, pivot.y);
            break;
        case 2:
            m_blocks[0].setPosition(pivot.x + blockSize, pivot.y + blockSize);
            m_blocks[2].setPosition(pivot.x - blockSize, pivot.y);
            m_blocks[3].setPosition(pivot.x, pivot.y + blockSize);
            break;
        case 3:
            m_blocks[0].setPosition(pivot.x + blockSize, pivot.y - blockSize);
            m_blocks[2].setPosition(pivot.x, pivot.y + blockSize);
            m_blocks[3].setPosition(pivot.x + blockSize, pivot.y);
            break;
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < 4; ++i) {
            window.draw(m_blocks[i]);
        }
    }

    void moveLeft() {
        // Calculate the new position when moving left
        sf::Vector2f newPosition;

        newPosition = sf::Vector2f(m_position.x - blockSize, m_position.y);

        // // Check if any block would go out of bounds when moving left
        // if (newPosition.x < 0 || (m_rotation == 1 && newPosition.x < blockSize)) {
        //     // Ignore the move if any block would go out of bounds
        //     return;
        // }

        //cout << "newPosition.x: " << newPosition.x << endl;

        if (m_rotation == 0) {
            if (newPosition.x - blockSize < 0) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.x - blockSize < 0) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.x - blockSize < 0) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.x < blockSize) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x - blockSize,
                m_blocks[i].getPosition().y);
        }
    }

    void moveRight() {
        sf::Vector2f newPosition;

        newPosition = sf::Vector2f(m_position.x + blockSize, m_position.y);

        // Check if any block would go out of bounds when moving right
        if (m_rotation == 0) {
            if (newPosition.x + blockSize > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.x > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.x + blockSize > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.x > blockSize * 8) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        m_position.x += blockSize;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x + blockSize,
                m_blocks[i].getPosition().y);
        }
    }

    void moveDown() {


        sf::Vector2f newPosition;

        newPosition = sf::Vector2f(m_position.x + blockSize, m_position.y);

        // Check if any block would go out of bounds when moving right
        if (m_rotation == 0) {
            if (newPosition.y > blockSize * 14) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.y > blockSize * 14) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.y > blockSize * 14) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.y > blockSize * 14) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x,
                m_blocks[i].getPosition().y + blockSize);
        }
    }

    void speedUp() {
    }

    bool update() {
        return false;
    }

    void reset(sf::Vector2f position) {
        m_position = position;
        m_rotation = 0;

        if (m_rotation == 0) {
            m_blocks[0].setPosition(m_position.x - blockSize, m_position.y);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x, m_position.y + blockSize);
            m_blocks[3].setPosition(m_position.x + blockSize, m_position.y + blockSize);
        }
        else {
            m_blocks[0].setPosition(m_position.x, m_position.y - blockSize);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x - blockSize, m_position.y);
            m_blocks[3].setPosition(m_position.x - blockSize, m_position.y + blockSize);
        }
    }
};

// L tetromino.
class TetrominoL : public Tetromino {
private:
    sf::RectangleShape m_blocks[4];

public:
    static constexpr float blockSize = 50.0f;
    TetrominoL(sf::Vector2f position)
        : Tetromino(sf::Color(255, 165, 0), position) {
        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setFillColor(m_color);
            m_blocks[i].setSize(sf::Vector2f(47.0f, 47.0f));
        }
        reset(position);
    }

    void rotate() {
        sf::Vector2f pivot = m_blocks[1].getPosition();

        // don't rotate when shape will go out of bounds of the grid
        if (m_rotation == 0) {
            if (pivot.x < blockSize || pivot.x > blockSize * 8) {
                return;
            }
        }
        else if (m_rotation == 1) {
            if (pivot.x < blockSize * 1 || pivot.x > blockSize * 8) {
                return;
            }
        }
        else if (m_rotation == 2) {
            if (pivot.x < blockSize || pivot.x > blockSize * 8) {
                return;
            }
        }
        else if (m_rotation == 3) {
            if (pivot.x < blockSize * 1 || pivot.x > blockSize * 8) {
                return;
            }
        }

        m_rotation = (m_rotation + 1) % 4;
        // sf::Vector2f pivot = m_blocks[1].getPosition();
        switch (m_rotation) {
        case 0:
            m_blocks[0].setPosition(pivot.x - blockSize, pivot.y);
            m_blocks[2].setPosition(pivot.x + blockSize, pivot.y);
            m_blocks[3].setPosition(pivot.x + blockSize, pivot.y - blockSize);
            break;
        case 1:
            m_blocks[0].setPosition(pivot.x, pivot.y - blockSize);
            m_blocks[2].setPosition(pivot.x, pivot.y + blockSize);
            m_blocks[3].setPosition(pivot.x - blockSize, pivot.y + blockSize);
            break;
        case 2:
            m_blocks[0].setPosition(pivot.x + blockSize, pivot.y);
            m_blocks[2].setPosition(pivot.x - blockSize, pivot.y);
            m_blocks[3].setPosition(pivot.x - blockSize, pivot.y + blockSize);
            break;
        case 3:
            m_blocks[0].setPosition(pivot.x, pivot.y + blockSize);
            m_blocks[2].setPosition(pivot.x, pivot.y - blockSize);
            m_blocks[3].setPosition(pivot.x + blockSize, pivot.y - blockSize);
            break;
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < 4; ++i) {
            window.draw(m_blocks[i]);
        }
    }

    void moveLeft() {
        // Calculate the new position when moving left
        sf::Vector2f newPosition(m_position.x - blockSize, m_position.y);

        // Check if any block would go out of bounds when moving left
        if (m_rotation == 0) {
            if (newPosition.x - blockSize < 0) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.x < blockSize) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.x - blockSize < 0) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.x + blockSize < blockSize) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x - blockSize,
                m_blocks[i].getPosition().y);
        }
    }

    void moveRight() {
        sf::Vector2f newPosition(m_position.x + blockSize, m_position.y);

        // Check if any block would go out of bounds when moving right
        if (m_rotation == 0) {
            if (newPosition.x + blockSize > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.x > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.x + blockSize > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.x > blockSize * 8) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        m_position.x += blockSize;

        for(int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x + blockSize,
                m_blocks[i].getPosition().y);
        }
    }

    void moveDown() {
        // Calculate the new position when moving down
        sf::Vector2f newPosition(m_position.x, m_position.y + blockSize);

        // Check if any block would go out of bounds when moving down in each rotation
        if (m_rotation == 0) {
            if (newPosition.y + blockSize > blockSize * 18) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.y + blockSize * 2 > blockSize * 18) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.y + blockSize > blockSize * 18) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.y + blockSize * 3 > blockSize * 18) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x, m_blocks[i].getPosition().y + blockSize);
        }
    }

    void speedUp() {
    }

    bool update() {
        return false;
    }

    void reset(sf::Vector2f position) {
        m_position = position;
        m_rotation = 0;

        if (m_rotation == 0) {
            m_blocks[0].setPosition(m_position.x - blockSize, m_position.y);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x + blockSize, m_position.y);
            m_blocks[3].setPosition(m_position.x + blockSize, m_position.y - blockSize);
        }
        else if (m_rotation == 1) {
            m_blocks[0].setPosition(m_position.x, m_position.y - blockSize);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x, m_position.y + blockSize);
            m_blocks[3].setPosition(m_position.x - blockSize, m_position.y + blockSize);
        }
        else if (m_rotation == 2) {
            m_blocks[0].setPosition(m_position.x + blockSize, m_position.y);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x - blockSize, m_position.y);
            m_blocks[3].setPosition(m_position.x - blockSize, m_position.y + blockSize);
        }
        else if (m_rotation == 3) {
            m_blocks[0].setPosition(m_position.x, m_position.y + blockSize);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x, m_position.y - blockSize);
            m_blocks[3].setPosition(m_position.x + blockSize, m_position.y - blockSize);
        }
    }
};

// J tetromino.
class TetrominoJ : public Tetromino {
private:
    sf::RectangleShape m_blocks[4];

public:
    static constexpr float blockSize = 50.0f;
    TetrominoJ(sf::Vector2f position)
        : Tetromino(sf::Color::Blue, position) {
        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setFillColor(m_color);
            m_blocks[i].setSize(sf::Vector2f(47.0f, 47.0f));
        }
        reset(position);
    }

    void rotate() {
        sf::Vector2f pivot = m_blocks[1].getPosition();

        // don't rotate when shape will go out of bounds of the grid
        if (m_rotation == 0) {
            if (pivot.x < blockSize || pivot.x > blockSize * 8) {
                return;
            }
        }
        else if (m_rotation == 1) {
            if (pivot.x < blockSize * 1 || pivot.x > blockSize * 8) {
                return;
            }
        }
        else if (m_rotation == 2) {
            if (pivot.x < blockSize || pivot.x > blockSize * 8) {
                return;
            }
        }
        else if (m_rotation == 3) {
            if (pivot.x < blockSize * 1 || pivot.x > blockSize * 8) {
                return;
            }
        }

        m_rotation = (m_rotation + 1) % 4;
        switch (m_rotation) {
        case 0:
            m_blocks[0].setPosition(pivot.x - blockSize, pivot.y);
            m_blocks[2].setPosition(pivot.x + blockSize, pivot.y);
            m_blocks[3].setPosition(pivot.x + blockSize, pivot.y + blockSize);
            break;
        case 1:
            m_blocks[0].setPosition(pivot.x, pivot.y - blockSize);
            m_blocks[2].setPosition(pivot.x, pivot.y + blockSize);
            m_blocks[3].setPosition(pivot.x - blockSize, pivot.y + blockSize);
            break;
        case 2:
            m_blocks[0].setPosition(pivot.x + blockSize, pivot.y);
            m_blocks[2].setPosition(pivot.x - blockSize, pivot.y);
            m_blocks[3].setPosition(pivot.x - blockSize, pivot.y - blockSize);
            break;
        case 3:
            m_blocks[0].setPosition(pivot.x, pivot.y + blockSize);
            m_blocks[2].setPosition(pivot.x, pivot.y - blockSize);
            m_blocks[3].setPosition(pivot.x + blockSize, pivot.y - blockSize);
            break;
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < 4; ++i) {
            window.draw(m_blocks[i]);
        }
    }

    void moveLeft() {
        // Calculate the new position when moving left
        sf::Vector2f newPosition(m_position.x - blockSize, m_position.y);

        // Check if any block would go out of bounds when moving left
        if (m_rotation == 0) {
            if (newPosition.x - blockSize < 0) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.x < blockSize) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.x - blockSize < 0) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.x + blockSize < blockSize) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        // for (int i = 0; i < 4; ++i) {
        //     if (newPosition.x < 0) {
        //         // Ignore the move if any block would go out of bounds
        //         return;
        //     }
        // }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x - blockSize,
                m_blocks[i].getPosition().y);
        }
    }

    void moveRight() {
        sf::Vector2f newPosition(m_position.x + blockSize, m_position.y);

        // Check if any block would go out of bounds when moving right
        if (m_rotation == 0) {
            if (newPosition.x + blockSize > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.x > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.x + blockSize > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.x > blockSize * 8) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        m_position.x += blockSize;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x + blockSize,
                m_blocks[i].getPosition().y);
        }
    }

    void moveDown() {
        // Calculate the new position when moving down
        sf::Vector2f newPosition(m_position.x, m_position.y + blockSize);

        // Check if any block would go out of bounds when moving down in each rotation
        if (m_rotation == 0) {
            if (newPosition.y + blockSize > blockSize * 18) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.y + blockSize * 3 > blockSize * 18) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.y + blockSize > blockSize * 18) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.y + blockSize * 2 > blockSize * 18) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x, m_blocks[i].getPosition().y + blockSize);
        }
    }
    void speedUp() {
        // Implementation for speedUp if needed.
    }

    bool update() {
        return false;
    }
    void reset(sf::Vector2f position) {
        m_position = position;
        m_rotation = 0;

        if (m_rotation == 0) {
            m_blocks[0].setPosition(m_position.x - blockSize, m_position.y);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x + blockSize, m_position.y);
            m_blocks[3].setPosition(m_position.x + blockSize, m_position.y + blockSize);
        }
        else if (m_rotation == 1) {
            m_blocks[0].setPosition(m_position.x, m_position.y - blockSize);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x, m_position.y + blockSize);
            m_blocks[3].setPosition(m_position.x - blockSize, m_position.y + blockSize);
        }
        else if (m_rotation == 2) {
            m_blocks[0].setPosition(m_position.x + blockSize, m_position.y);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x - blockSize, m_position.y);
            m_blocks[3].setPosition(m_position.x - blockSize, m_position.y - blockSize);
        }
        else if (m_rotation == 3) {
            m_blocks[0].setPosition(m_position.x, m_position.y + blockSize);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x, m_position.y - blockSize);
            m_blocks[3].setPosition(m_position.x + blockSize, m_position.y - blockSize);
        }
    }
};
// T tetromino

class TetrominoT : public Tetromino {
private:
    sf::RectangleShape m_blocks[4];

public:
    static constexpr float blockSize = 50.0f;
    TetrominoT(sf::Vector2f position)
        : Tetromino(sf::Color::Magenta, position) {
        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setFillColor(m_color);
            m_blocks[i].setSize(sf::Vector2f(47.0f, 47.0f));
        }
        reset(position);
    }

    void rotate() {
        sf::Vector2f pivot = m_blocks[1].getPosition();

        // don't rotate when shape will go out of bounds of the grid
        if (m_rotation == 0) {
            if (pivot.x < blockSize || pivot.x > blockSize * 8) {
                return;
            }
        }
        else if (m_rotation == 1) {
            if (pivot.x < blockSize * 1 || pivot.x > blockSize * 8) {
                return;
            }
        }
        else if (m_rotation == 2) {
            if (pivot.x < blockSize || pivot.x > blockSize * 8) {
                return;
            }
        }
        else if (m_rotation == 3) {
            if (pivot.x < blockSize * 1 || pivot.x > blockSize * 8) {
                return;
            }
        }

        m_rotation = (m_rotation + 1) % 4;
        // sf::Vector2f pivot = m_blocks[1].getPosition();/
        switch (m_rotation) {
        case 0:
            m_blocks[0].setPosition(pivot.x - blockSize, pivot.y);
            m_blocks[2].setPosition(pivot.x + blockSize, pivot.y);
            m_blocks[3].setPosition(pivot.x, pivot.y + blockSize);
            break;
        case 1:
            m_blocks[0].setPosition(pivot.x, pivot.y - blockSize);
            m_blocks[2].setPosition(pivot.x, pivot.y + blockSize);
            m_blocks[3].setPosition(pivot.x + blockSize, pivot.y);
            break;
        case 2:
            m_blocks[0].setPosition(pivot.x - blockSize, pivot.y);
            m_blocks[2].setPosition(pivot.x + blockSize, pivot.y);
            m_blocks[3].setPosition(pivot.x, pivot.y - blockSize);
            break;
        case 3:
            m_blocks[0].setPosition(pivot.x, pivot.y - blockSize);
            m_blocks[2].setPosition(pivot.x, pivot.y + blockSize);
            m_blocks[3].setPosition(pivot.x - blockSize, pivot.y);
            break;
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < 4; ++i) {
            window.draw(m_blocks[i]);
        }
    }

    void moveLeft() {
        // Calculate the new position when moving left
        sf::Vector2f newPosition(m_position.x - blockSize, m_position.y);

        // Check if any block would go out of bounds when moving left
        if (m_rotation == 0) {
            if (newPosition.x - blockSize < 0) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.x + blockSize < blockSize) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.x - blockSize < 0) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.x < blockSize) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        // for (int i = 0; i < 4; ++i) {
        //     if (newPosition.x < 0) {
        //         // Ignore the move if any block would go out of bounds
        //         return;
        //     }
        // }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x - blockSize,
                m_blocks[i].getPosition().y);
        }
    }

    void moveRight() {
        sf::Vector2f newPosition(m_position.x + blockSize, m_position.y);

        // Check if any block would go out of bounds when moving right
        if (m_rotation == 0) {
            if (newPosition.x + blockSize > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.x > blockSize * 8) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.x + blockSize > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.x > blockSize * 9) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        m_position.x += blockSize;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x + blockSize,
                m_blocks[i].getPosition().y);
        }
    }

    void moveDown() {
        // Calculate the new position when moving down
        sf::Vector2f newPosition(m_position.x, m_position.y + blockSize);

        // Check if any block would go out of bounds when moving down in each rotation
        if (m_rotation == 0) {
            if (newPosition.y > blockSize * 18) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 1) {
            if (newPosition.y > blockSize * 16) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 2) {
            if (newPosition.y > blockSize * 18) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }
        else if (m_rotation == 3) {
            if (newPosition.y > blockSize * 16) {
                // Ignore the move if any block would go out of bounds
                return;
            }
        }

        // Update the position of the Tetromino and its blocks
        m_position = newPosition;

        for (int i = 0; i < 4; ++i) {
            m_blocks[i].setPosition(m_blocks[i].getPosition().x, m_blocks[i].getPosition().y + blockSize);
        }
    }

    void speedUp() {
    }

    bool update() {
        return false;
    }

    void reset(sf::Vector2f position) {
        m_position = position;
        m_rotation = 0;

        if (m_rotation == 0) {
            m_blocks[0].setPosition(m_position.x - blockSize, m_position.y);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x + blockSize, m_position.y);
            m_blocks[3].setPosition(m_position.x, m_position.y + blockSize);
        }
        else if (m_rotation == 1) {
            m_blocks[0].setPosition(m_position.x, m_position.y - blockSize);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x, m_position.y + blockSize);
            m_blocks[3].setPosition(m_position.x + blockSize, m_position.y);
        }
        else if (m_rotation == 2) {
            m_blocks[0].setPosition(m_position.x - blockSize, m_position.y);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x + blockSize, m_position.y);
            m_blocks[3].setPosition(m_position.x, m_position.y - blockSize);
        }
        else if (m_rotation == 3) {
            m_blocks[0].setPosition(m_position.x, m_position.y - blockSize);
            m_blocks[1].setPosition(m_position.x, m_position.y);
            m_blocks[2].setPosition(m_position.x, m_position.y + blockSize);
            m_blocks[3].setPosition(m_position.x - blockSize, m_position.y);
        }
    }
};
