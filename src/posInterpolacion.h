#ifndef POSINTERPOLACION_H
#define POSINTERPOLACION_H
#include <stdio.h>
#include <SFML/Graphics.hpp>
class posInterpolacion
{
    public:
        posInterpolacion();
        virtual ~posInterpolacion();
        sf::Vector2f getPrimera();
        sf::Vector2f getSegunda();
        void setPrimera(sf::Vector2f);
        void setSegunda(sf::Vector2f);
    protected:
    private:
    sf::Vector2f primeraPos;
    sf::Vector2f segundaPos;
};

#endif // POSINTERPOLACION_H
