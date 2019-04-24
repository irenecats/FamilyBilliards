#ifndef JUGADOR_H
#define JUGADOR_H
#include <SFML/Graphics.hpp>
#include <posInterpolacion.h>
#include <iostream>
#include <Juego.h>

class Jugador
{
    public:
    static Jugador* Instance();
        virtual ~Jugador();
        void Render(sf::RenderWindow&,float);
        void Update(float);
        void setPointer(sf::Texture&);
        sf::Vector2f    getPosition();
        void            apuntado(sf::Vector2f,sf::Vector2f);
    protected:
    private:
    static Jugador* instancia;
            sf::Texture textura;
            sf::Sprite   pointer;
            sf::Vector2f velocidad;
            posInterpolacion    posicion;
            Jugador();
};

#endif // JUGADOR_H
