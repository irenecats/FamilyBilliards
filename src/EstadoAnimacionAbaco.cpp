#include <EstadoAnimacionAbaco.h>
#include <EstadoApuntar.h>
#include <Juego.h>

EstadoAnimacionAbaco EstadoAnimacionAbaco::instancia;
void EstadoAnimacionAbaco::Inicializar()
{
	printf("Empiezo (solo debería pasar 1 vez\n");
	std::cout << "Muevo " << nuevosPuntos << " piezas" << std::endl;

	animando = true;
	puntosActuales = Jugador::Instance()->getPuntuacion();
	posFin = (100 + (puntosActuales)*10);
}
void EstadoAnimacionAbaco::Limpiar()
{
}
void EstadoAnimacionAbaco::Pausar()
{
}
void EstadoAnimacionAbaco::Continuar()
{
}

void EstadoAnimacionAbaco::ManejarEventos(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
	{
		Juego::Instance()->ventana.close();
	}
}

void EstadoAnimacionAbaco::Update(float timeElapsed)
{
	if (posFin < piezas[puntosActuales]->getPos().x)
	{
		setVelGrupo(puntosActuales, nuevosPuntos, -0.1f);
	}
	else
	{
		printf("Han llegado a su sitio\n");
		setVelGrupo(puntosActuales, nuevosPuntos, 0.f);
		Jugador::Instance()->addPuntuacion(nuevosPuntos);
		if (ganado)
		{
			Juego::Instance()->CambiarEstado(EstadoApuntar::Instancia());
		}
		else
		{
			Juego::Instance()->CambiarEstado(EstadoApuntar::Instancia());
		}
	}
	for (int i = puntosActuales; i < (puntosActuales + nuevosPuntos); i++)
	{
		piezas[i]->Update(timeElapsed);
	}
}
void EstadoAnimacionAbaco::setVelGrupo(int inicio, int fin, float vel)
{
	for (int i = inicio; i < fin; i++)
	{
		piezas[i]->setVelocidad(vel);
	}
}

void EstadoAnimacionAbaco::Render(float percentick)
{
	Juego* juego = Juego::Instance();

	juego->palo.Render(juego->ventana, percentick);
}