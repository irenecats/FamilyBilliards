#ifndef BOLA_H
#define BOLA_H
#include <SFML/Graphics.hpp>
#include <posInterpolacion.h>
#include <iostream>
#include <math.h>
class Bola
{
    public:
        Bola(int,sf::Texture&,std::vector<sf::Vector2f>);
        virtual ~Bola();
        void        Render(sf::RenderWindow&,float);
        void        Update(float);
        bool        heParado();
        void        empezarAnimacion(float);
        void        terminarAnimacion();

        sf::Vector2f    getSprite();
        sf::Vector2f    getPosPr();
        sf::Vector2f    getPosSg();
        sf::Vector2f    getVelocidad();
        int             getID();
        bool            getAnimado();
        void            setPosPR(sf::Vector2f);
        void            setPosSg(sf::Vector2f);
        void            setPos(sf::Vector2f);
        void            setVelocidad(sf::Vector2f);
        void            setCaida(bool);
        bool            getCaida();
        sf::FloatRect   getGlobalBounds();

    protected:
    private:
    int                 ID;
    sf::Vector2f        velocidad;
    posInterpolacion    posicion;
    sf::Sprite          sprite;
    bool                animado;
    float               posfinal;
    bool                caida;

    void   controlaVelocidad();
};

#endif // BOLA_H
