#include <EstadoVictoria.h>
#include <Juego.h>
EstadoVictoria EstadoVictoria::instancia;
void EstadoVictoria::Inicializar()
{

}

void EstadoVictoria::Render(float percentick){

}
void EstadoVictoria::ManejarEventos(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
	{
		Juego::Instance()->ventana.close();
	}
}

void EstadoVictoria::Update(float timeElapsed)
{
}