#include <EstadoApuntar.h>
#include <Juego.h>
#include <SFML/Graphics.hpp>
int main()
{

	Juego* juego = Juego::Instance();
	juego->CambiarEstado(EstadoApuntar::Instancia());
	juego->bucleJuego();
	delete juego;
}
