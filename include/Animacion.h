#ifndef ANIMACION_H
#define ANIMACION_H
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <posInterpolacion.h>
#include <Juego.h>

#define VEL_MAX 0.4f
#define VEL_MIN 0.1f
class Animacion
{
    public:
        Animacion(sf::Texture& text);
        virtual ~Animacion();
        void RenderPuntos(sf::RenderWindow&,float);
        void RenderPalo(sf::RenderWindow&,float);
        void Update(float, int);
        void tiroBola();
        bool getTerminado();
        void calculoVelocidad();
    protected:
    private:

    sf::Sprite  palo;
    float cont;
    std::vector<sf::Sprite> puntos;
    float                   posPulsado;
    bool                    dir;
    bool                    terminado;
    posInterpolacion        paloPos;
    posInterpolacion        puntosPos;

};

#endif // ANIMACION_H
