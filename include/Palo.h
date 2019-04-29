#ifndef PALO_H
#define PALO_H
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <posInterpolacion.h>
#include <Juego.h>

#define VEL_MAX 0.4f
#define VEL_MIN 0.1f

class Palo
{
    public:
        Palo();
        Palo(sf::Texture& text);
        virtual ~Palo();
        void Render(sf::RenderWindow&,float);
        void Update(float, int);
        void tiroBola();
        bool getTerminado();
        void setTerminado(bool);
        void calculoVelocidad();
    protected:
    private:

    sf::Sprite              palo;
    float                   cont;
    float                   posPulsado;
    bool                    dir;
    bool                    terminado;
    posInterpolacion        paloPos;
};

#endif // PALO_H
