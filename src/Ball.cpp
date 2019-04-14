#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <vector>

Ball::Ball(int num)
{
    //ctor
    numero = num;
    textura.loadFromFile("bola1.png");

    circulo.setRadius(9.5);
    std::size_t count=20;
    circulo.setPointCount(count);
    circulo.setTexture(&textura);
    //circulo.setFillColor(sf::Color::Red);
    circulo.setOrigin(circulo.getRadius() / 2, circulo.getRadius() / 2);
    circulo.setPosition(400,400);
    printf("Inicializado");
}

Ball::~Ball()
{
    //dtor
}
