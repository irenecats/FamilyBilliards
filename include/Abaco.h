#ifndef ABACO_H
#define ABACO_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <posInterpolacion.h>

class Abaco
{
    public:
        Abaco();
        virtual ~Abaco();
        void Update(float);
        void Render(sf::RenderWindow& window,float);
        void muevePiezas(int);
        int  getAnimando();
        void setAnimando(int);
        void getPos();

    protected:
    private:

        sf::Vector2f     velocidad;
        int              moviendo;
        int              movidas;
        int             animando;
        posInterpolacion posicion;
        sf::RectangleShape rect;
        std::vector<sf::RectangleShape> piezas;
};

#endif // ABACO_H
