#include <EstadoAnimacionAbaco.h>
#include <EstadoApuntar.h>
#include <Juego.h>

EstadoAnimacionAbaco EstadoAnimacionAbaco::instancia;
void EstadoAnimacionAbaco::Inicializar()
{
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
	int a = 0;
	a = timeElapsed + a;
	//TODO: ponerlo en el init
	if (!animando)
	{
		animando = true;
		puntosActuales = Jugador::Instance()->getPuntuacion();
		//float posX = (piezas[puntosActuales]->getPos().x) + (i * 10);
	}

	//posicion.setSegunda(sf::Vector2f(100 + (10 * (puntosActuales -1), posicion.getPrimera().y));

	//Abaco* abaco = &Juego::Instance()->abaco;
	//abaco->Update(timeElapsed);

	//if (posicion.getSegunda().x < 100)
	//{
	//	velocidad.x = 0;
	//	posicion.setSegunda(sf::Vector2f(100 + (10 * (movidas)-1), posicion.getPrimera().y));
	//	movidas += moviendo;
	//	moviendo = 0;
	//	animando = 1;
	//}
	//else
	//{
	//	velocidad.x = -0.1;
	//}

	//if (abaco->getAnimando())
	//{
	//	abaco->setAnimando(false);
	//	printf("Las piezas estan en su sitio\n");
	//	Juego::Instance()->CambiarEstado(EstadoApuntar::Instancia());
	//}
}

void EstadoAnimacionAbaco::Render(float percentick)
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
		juego->barra[i].Render(juego->ventana, 0);
	}
	juego->palo.Render(juego->ventana, percentick);
}