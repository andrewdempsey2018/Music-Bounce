#include "MoveShape.h"

MoveShape::MoveShape()
{
    srand(3);

    size = rand() % 50;
    xSpeed = rand() % 30;;
    color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
    xPos = rand() % 750;
    yPos = rand() % 550;

    sprite.setFillColor(color);
    sprite.setSize(sf::Vector2f(size, size));
}

MoveShape::MoveShape(float posX, float posY)
{
    size = 3;
    xSpeed = 0.0;
    ySpeed = 3.0;
    color = sf::Color::Red;
    xPos = posX;
    yPos = posY;
    gravity = true;

    sprite.setFillColor(color);
    sprite.setSize(sf::Vector2f(size, size));
}

MoveShape::MoveShape(float posX, float posY, int howBig)
{
    size = howBig;
    xSpeed = 0.0;
    ySpeed = 0.0;
    color = sf::Color(180, 247, 50);
    xPos = posX;
    yPos = posY;
    gravity = false;

    sprite.setFillColor(color);
    sprite.setSize(sf::Vector2f(size, size));
}

void MoveShape::move()
{
    xPos += xSpeed;

    if(xSpeed > 0.0)
    {
        xSpeed -= 0.25;
    }

    if(gravity)
    {
        if(ySpeed < 3.0)
        {
            ySpeed += 0.25;
        }
        yPos += ySpeed;
    }
}

float MoveShape::getX()
{
    return xPos;
}

float MoveShape::getY()
{
    return yPos;
}

float MoveShape::getWidth()
{
    return size;
}

float MoveShape::getHeight()
{
    return size;
}

MoveShape::~MoveShape()
{
}