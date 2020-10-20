#include <Juego.h>
#include <SFML/Graphics.hpp>
int main()
{

	Juego* juego = Juego::Instance();
	juego->bucleJuego();
	delete juego;
}
