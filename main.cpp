#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include "MoveShape.h"

using namespace std;

void update();
void draw();
void processEvents();
bool Collision(MoveShape, MoveShape);

sf::RenderWindow window;

int color1 = 40;
int color2 = 40;
int color3 = 40;

vector<MoveShape> shapes;
vector<MoveShape>::iterator shapes_it;
vector<MoveShape>::iterator shapes_it2;

vector<sf::Sound> sounds;
vector<sf::Sound>::iterator sounds_it;

bool leftClick = false;
bool rightClick = false;
bool middleClick = false;

sf::SoundBuffer buffer;
sf::Sound sound;

int pitch = 1;

bool isRunning = true;

int main()
{
    window.create(sf::VideoMode(800, 600), "Music Bounce", sf::Style::Fullscreen);
    //window.create(sf::VideoMode(800, 600), "Music Bounce");

    window.setFramerateLimit(60);

    buffer.loadFromFile("elec_a.wav");
    sound.setBuffer(buffer);

    while(isRunning)
	{
        processEvents();
        update();
        draw();
	}

    return 0;
}

void processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            isRunning = false;
            window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            isRunning = false;
            window.close();
        }
    
    }
}

void draw()
{
    window.clear(sf::Color(color1, color2, color3));

    for(shapes_it = shapes.begin(); shapes_it < shapes.end(); shapes_it++)
    {
        (*shapes_it).sprite.setPosition((*shapes_it).xPos + ((*shapes_it).xSpeed), (*shapes_it).yPos + ((*shapes_it).ySpeed));
        window.draw((*shapes_it).sprite);
    }

    window.display();
}

void update()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !leftClick)
    {
        leftClick = true;
        shapes.push_back(MoveShape(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y));
        color1 += 5;
        color2 += 20;
        color3 += 10;
    }

    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        leftClick = false;
    }
 
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !rightClick)
    {
        rightClick = true;
        shapes.push_back(MoveShape(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, 15));
    }

    if(!sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        rightClick = false;
    }

    for(shapes_it = shapes.begin(); shapes_it < shapes.end(); shapes_it++)
    {
        (*shapes_it).move();

        if((*shapes_it).yPos > 600.0)
        {
            shapes.erase(shapes_it);
        }
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !middleClick)
    {
        middleClick = true;
        shapes.clear();
    }

    if(!sf::Mouse::isButtonPressed(sf::Mouse::Middle))
    {
        middleClick = false;
    }

    for(shapes_it = shapes.begin(); shapes_it < shapes.end(); shapes_it++)
    {
        for(shapes_it2 = shapes.begin(); shapes_it2 < shapes.end(); shapes_it2++)
        {
            if(Collision((*shapes_it), (*shapes_it2)) && (*shapes_it).getWidth() < (*shapes_it2).getWidth())
            {
                pitch++;
                if(pitch > 10)
                {
                    pitch = 1;
                }
                sounds.push_back(sf::Sound(buffer));
                sounds.back().setPitch(pitch);
                sounds.back().play();
                (*shapes_it).ySpeed = -3.0;
                (*shapes_it).xSpeed = 2.0;
                shapes.erase(shapes_it2);
            }
        }
    }
}

bool Collision(MoveShape sprite1, MoveShape sprite2)
{
    return !(sprite2.getX() > sprite1.getX() + sprite1.getWidth()
        || sprite2.getX() + sprite2.getWidth() < sprite1.getX()
            || sprite2.getY() > sprite1.getY() + sprite1.getHeight()
                || sprite2.getY() + sprite2.getHeight() < sprite1.getY());
}