#include <Bola.h>
#include <EstadoAnimacionGolpeo.h>
#include <EstadoApuntar.h>
#include <EstadoMovBolas.h>
#include <Juego.h>

EstadoAnimacionGolpeo EstadoAnimacionGolpeo::instancia;
void EstadoAnimacionGolpeo::Inicializar()
{
	pause = 0.f;
}

void EstadoAnimacionGolpeo::ManejarEventos(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
	{
		Juego::Instance()->ventana.close();
	}
}

void EstadoAnimacionGolpeo::Update(float timeElapsed)
{
	float vel = 0.f;
	if (pause > 700)
	{
		if (Juego::Instance()->palo.getPosFirst().x > 42.5)
		{
			vel = -1.f;
		}
		else
		{
			printf("Estado 3: Bolas en movimiento");
			Juego::Instance()->CambiarEstado(EstadoMovBolas::Instancia());
		}
	}
	else
	{
		pause += timeElapsed;
	}
	Juego::Instance()->palo.Update(timeElapsed, vel);
}
void EstadoAnimacionGolpeo::Render(float percentick)
{
	Juego* juego = Juego::Instance();

	juego->palo.Render(juego->ventana, percentick);
	Jugador::Instance()->Render(juego->ventana, percentick);
}
