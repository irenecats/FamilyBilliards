#include <SFML/Graphics.hpp>
#include <Juego.h>
int main()
{

    Juego* juego = Juego::Instance();
    juego->bucleJuego();
    delete juego;
}

