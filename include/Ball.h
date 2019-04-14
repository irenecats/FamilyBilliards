#ifndef BALL_H
#define BALL_H
#include <SFML/Graphics.hpp>
#include <vector>

class Ball
{
    public:
        sf::CircleShape getCirculo(){return circulo;}
        int getNumero(){return numero;}

        Ball(int num);
        virtual ~Ball();
    protected:
    private:
        sf::CircleShape circulo;
        sf::Texture textura;
        int numero;
};

#endif // BALL_H
