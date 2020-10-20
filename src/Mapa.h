#ifndef MAPA_H
#define MAPA_H
#include <SFML/Graphics.hpp>
#include <math.h>
#include <Bola.h>

class Mapa
{

public:
    static Mapa*        Instance();
    virtual ~Mapa();
    sf::Vector2f        RotaBolas(float);
    void                Render(sf::RenderWindow&,std::vector<Bola>);
    void                setAngulo(float);
    void                setValues();
protected:
private:

    static Mapa*    instancia;
    float           angulo;

    Mapa();
    sf::Vector2f Proyecta(float, float, float, float, sf::Vector2f);
    sf::Vector2f RotaY(sf::Vector2f, float);

};

#endif // MAPA_H
