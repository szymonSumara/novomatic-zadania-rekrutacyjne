#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


#include "../Collision/collision.h"



class Circle : public sf::Drawable{


public:

    const float radius;
    sf::CircleShape circle;
    sf::Vector2f centerPosition;

    Circle( sf::Vector2f centerPosition,const float radius) : centerPosition(centerPosition), radius(radius), circle(radius){

        circle.setPosition(centerPosition);
        circle.setOrigin(radius , radius);
        circle.setFillColor(  sf::Color::Red );
    }

    void paintToRed(){
        circle.setFillColor(  sf::Color::Red );
    }

    void paintToGreen(){
        circle.setFillColor(  sf::Color::Green );

    }

    void draw(sf::RenderTarget& target, sf::RenderStates states)  const {
        std::cout << "draw" << '\n';
        target.draw(circle, states);
    }

};


const int RECTANGLE_WIDTH = 1200;
const int RECTANGLE_HEIGHT = 60;

const int RECTANGLE_POSITION_X = 600;
const int RECTANGLE_POSITION_Y = 600;


int main(int argc, char const *argv[])
{
    sf::RenderWindow window(sf::VideoMode(1000,1000), "Hello From SFML");
    Circle circle(sf::Vector2f(500,500), 100);

    sf::RectangleShape rectangle(sf::Vector2f(RECTANGLE_WIDTH,RECTANGLE_HEIGHT));
    rectangle.setPosition(RECTANGLE_POSITION_X,RECTANGLE_POSITION_Y);
    rectangle.setOrigin(RECTANGLE_WIDTH/2,RECTANGLE_HEIGHT/2);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }


        sf::Vector2f A =   rectangle.getTransform().transformPoint(rectangle.getPoint(0));
        sf::Vector2f B =   rectangle.getTransform().transformPoint(rectangle.getPoint(1));
        sf::Vector2f C =   rectangle.getTransform().transformPoint(rectangle.getPoint(2));
        sf::Vector2f D =   rectangle.getTransform().transformPoint(rectangle.getPoint(3));

        circle.paintToRed();
        if(isCircleCollidingWithRectangle(
                {circle.centerPosition.x ,circle.centerPosition.y}, circle.radius,
                {A.x,A.y},{B.x,B.y},{C.x,C.y},{D.x,D.y} ))
            circle.paintToGreen();


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            rectangle.rotate(1.f);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            rectangle.rotate(-1.f);
        }

        window.clear();
        window.draw(rectangle);

        window.draw(circle);
        usleep(16*1000); //  sleep(1);
        window.display();

    }

    return 0;
}