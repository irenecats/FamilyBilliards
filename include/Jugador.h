#ifndef JUGADOR_H
#define JUGADOR_H
#include <SFML/Graphics.hpp>
#include <posInterpolacion.h>
#include <iostream>
#include <Juego.h>

class Jugador
{
    public:
    static Jugador*     Instance();
        virtual         ~Jugador();
        void            Render(sf::RenderWindow&,float);
        void            Update(float);
        void            setPointer(sf::Texture&);
        void            apuntado(sf::Vector2f,sf::Vector2f);
        void            addPuntuacion(int);

        sf::Vector2f    getPosition();
        int             getPuntuacion();
        void            setPuntuacion(int);


    protected:
    private:
    static Jugador*             instancia;
            sf::Texture         textura;
            sf::Sprite          pointer;
            posInterpolacion    posicion;
            int                 puntuacion;

            Jugador();
};

#endif // JUGADOR_H
