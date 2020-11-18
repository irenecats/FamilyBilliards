#include <Bola.h>
#include <EstadoApuntar.h>
#include <EstadoGolpear.h>
#include <Juego.h>
#include <Jugador.h>
EstadoApuntar EstadoApuntar::instancia;
void EstadoApuntar::Inicializar()
{
}

void EstadoApuntar::ManejarEventos(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
	{
		Juego::Instance()->ventana.close();
	}
	if (event.key.code == sf::Keyboard::Space)
	{
		printf("Estado 1: animacion pre-tiro\n");
		Juego::Instance()->CambiarEstado(EstadoGolpear::Instancia());
	}

	float vel;
	sf::Vector2f movimiento(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		vel = 0.2f;
	}
	else
	{
		vel = 0.06f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		movimiento.y = -vel;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		movimiento.y = vel;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		movimiento.x = -vel;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		movimiento.x = vel;
	}
	Jugador::Instance()->movimiento = movimiento;
}
void EstadoApuntar::Update(float timeElapsed)
{
	Jugador::Instance()->Update(timeElapsed);
	Juego::Instance()->palo.Update(timeElapsed, 0.f);
}
void EstadoApuntar::Render(float percentick)
{
	Juego* juego = Juego::Instance();

	juego->palo.Render(juego->ventana, percentick);

	Jugador::Instance()->Render(juego->ventana, percentick);
}