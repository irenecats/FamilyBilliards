#include <EstadoAnimacionAbaco.h>
#include <EstadoApuntar.h>
#include <EstadoVictoria.h>
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
	nuevosPuntos = 0;
	ganado = false;
	piezas.clear();
	posFin = 100;
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
	if ( nuevosPuntos != 0 && posFin < piezas[puntosActuales]->getPos().x)
	{
		setVelGrupo(puntosActuales, puntosActuales + nuevosPuntos, -0.1f);
	}
	else
	{
		printf("Han llegado a su sitio\n");
		stopGrupo(puntosActuales, puntosActuales + nuevosPuntos);
		Jugador::Instance()->addPuntuacion(nuevosPuntos);
		if (ganado)
		{
			std::cout<<"has ganado, yay"<<std::endl;
			Juego::Instance()->CambiarEstado(EstadoVictoria::Instancia());
		}
		else
		{
			std::cout<<"Vuelvo a apuntar"<<std::endl;
			if(Juego::Instance()->bolas.size()>1)
			{
				Jugador::Instance()->apuntado(Juego::Instance()->bolas[0].getCurrentPos(),Juego::Instance()->bolas[1].getCurrentPos());
			}
			Juego::Instance()->CambiarEstado(EstadoApuntar::Instancia());
		}
		nuevosPuntos = 0;
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

void EstadoAnimacionAbaco::stopGrupo(int inicio, int fin){
	for (int i = inicio; i < fin; i++)
	{
		piezas[i]->setPosSg(piezas[i]->getPos());
		piezas[i]->setPosPR(piezas[i]->getPos());
	}
	setVelGrupo(inicio, fin, 0.f);
}

void EstadoAnimacionAbaco::Render(float percentick)
{
	Juego* juego = Juego::Instance();

	juego->palo.Render(juego->ventana, percentick);
}