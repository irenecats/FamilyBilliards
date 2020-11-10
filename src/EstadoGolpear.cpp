#include <Bola.h>
#include <EstadoAnimacionGolpeo.h>
#include <EstadoApuntar.h>
#include <EstadoGolpear.h>
#include <Juego.h>
#include <Jugador.h>
EstadoGolpear EstadoGolpear::instancia;
void EstadoGolpear::Inicializar()
{
	dir = false;
}
void EstadoGolpear::Limpiar()
{
}
void EstadoGolpear::Pausar()
{
}
void EstadoGolpear::Continuar()
{
}

void EstadoGolpear::ManejarEventos(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
	{
		Juego::Instance()->ventana.close();
	}
	if (event.key.code == sf::Keyboard::Space && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		printf("Estado 2: animacion de tiro\n");
		dir = true; //TODO: mirar si hacer esto al inicializar de todas
		tiraBola(Jugador::Instance()->getCurrentPos(), Juego::Instance()->bolas[0].getPosSecond(), calcVel(Juego::Instance()->palo.getPosSecond()));
		Juego::Instance()->CambiarEstado(EstadoAnimacionGolpeo::Instancia());
	}
	if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
	{
		printf("Estado 0: moviendo pointer\n");
		Juego::Instance()->CambiarEstado(EstadoApuntar::Instancia());
	}
}

void EstadoGolpear::tiraBola(sf::Vector2f player, sf::Vector2f bola, float vel)
{

	sf::Vector2f PB(player.x - bola.x, player.y - bola.y);

	float angulo = atan2(PB.y, PB.x);

	Juego::Instance()->bolas[0].setVelocidad(sf::Vector2f(vel * cos(angulo), vel * sin(angulo)));
}
/*
    Normalizo la posicion actual del palo para obtener un valor de
    velocidad entre 0.1 y 0.4
*/
float EstadoGolpear::calcVel(sf::Vector2f posicion)
{
	float posNorm = (posicion.x - 42.5) / 627.5;
	float vel = (0.4 * posNorm) + 0.1;
	return vel;
}
void EstadoGolpear::Update(float timeElapsed)
{
	float pos = Juego::Instance()->palo.getPosFirst().x;
	float vel = 0;

	if (pos >= 42.5 && dir == false && pos < 670)
	{
		vel = 0.5f;
	}
	else if (pos >= 670 && dir == false)
	{
		dir = true;
	}
	if (pos > 42.5 && dir == true)
	{
		vel = -0.5f;
	}
	else if (pos <= 42.5 && dir == true)
	{
		vel = 0.5f;
		dir = false;
	}
	Juego::Instance()->palo.Update(timeElapsed, vel);
}
void EstadoGolpear::Render(float percentick)
{
	Juego* juego = Juego::Instance();

	juego->palo.Render(juego->ventana, percentick);

	Jugador::Instance()->Render(juego->ventana, percentick);
}