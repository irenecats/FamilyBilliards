#include "posInterpolacion.h"

posInterpolacion::posInterpolacion()
{
    //ctor
}

posInterpolacion::~posInterpolacion()
{
    //dtor
}

sf::Vector2f posInterpolacion::getPrimera()
{
    return primeraPos;
}

sf::Vector2f posInterpolacion::getSegunda()
{
    return segundaPos;
}

void posInterpolacion::setPrimera(sf::Vector2f pos)
{
    primeraPos.x = pos.x;
    primeraPos.y = pos.y;
}

void posInterpolacion::setSegunda(sf::Vector2f pos)
{
    segundaPos.x = pos.x;
    segundaPos.y = pos.y;
}
