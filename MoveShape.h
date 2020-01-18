#ifndef MOVESHAPE_H
#define MOVESHAPE_H

#include <SFML/Graphics.hpp>
#include <cstdlib>

class MoveShape
{
    public:
        MoveShape();
        MoveShape(float xPos, float yPos);
        MoveShape(float posX, float posY, int howBig);
        ~MoveShape();
        void move();
        float getX();
        float getY();
        float getWidth();
        float getHeight();

        sf::RectangleShape sprite;
        float size;
        float xSpeed;
        float ySpeed;
        float xPos;
        float yPos;
        bool gravity;
        sf::Color color;

    private:
};

#endif