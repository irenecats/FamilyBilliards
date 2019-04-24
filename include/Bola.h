#ifndef BOLA_H
#define BOLA_H
#include <SFML/Graphics.hpp>
#include <posInterpolacion.h>
#include <iostream>
#include <math.h>
class Bola
{
    public:
        Bola(int,sf::Texture&);
        virtual ~Bola();
        void        Render(sf::RenderWindow&,float);
        void        Update(float);
        sf::Vector2f   getSprite();
        sf::Vector2f    getPosPr();
        sf::Vector2f    getPosSg();
        sf::Vector2f    getVelocidad();
        void            setPosPR(sf::Vector2f);
        void            setPosSg(sf::Vector2f);
        void            setPos(sf::Vector2f);
        void            setVelocidad(sf::Vector2f);
        int             getID();
        bool            heParado();
    protected:
    private:
    int                 ID;
    sf::Vector2f        velocidad;
    posInterpolacion    posicion;
    sf::Sprite          sprite;
    //sf::Texture textura;
};

#endif // BOLA_H
