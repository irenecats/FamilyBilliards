#include <Bola.h>
#include <EstadoAnimacionGolpeo.h>
#include <EstadoApuntar.h>
#include <EstadoMovBolas.h>
#include <Juego.h>

EstadoAnimacionGolpeo EstadoAnimacionGolpeo::instancia;
void EstadoAnimacionGolpeo::Inicializar()
{
}
void EstadoAnimacionGolpeo::Limpiar()
{
}
void EstadoAnimacionGolpeo::Pausar()
{
}
void EstadoAnimacionGolpeo::Continuar()
{
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
			pause = 0.f; // Todo: ponerlo en el init?
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
	for (unsigned int i = 0; i < juego->bolas.size(); i++)
	{
		if (!juego->bolas[i].caida)
		{
			juego->bolas[i].Render(juego->ventana, percentick);
		}
	}

	for (unsigned int i = 0; i < juego->barra.size(); i++)
	{
		juego->barra[i].Render(juego->ventana, percentick);
	}

	juego->palo.Render(juego->ventana, percentick);
	Jugador::Instance()->Render(juego->ventana, percentick);
}
