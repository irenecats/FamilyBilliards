#include <Bola.h>
#include <EstadoAnimacionAbaco.h>
#include <EstadoAnimacionBolas.h>
#include <EstadoApuntar.h>
#include <Juego.h>

EstadoAnimacionBolas EstadoAnimacionBolas::instancia;
void EstadoAnimacionBolas::Inicializar()
{
	bolaActual = 0;
}
void EstadoAnimacionBolas::Limpiar()
{
	caidas.clear();
}

void EstadoAnimacionBolas::ManejarEventos(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
	{
		Juego::Instance()->ventana.close();
	}
}

void EstadoAnimacionBolas::Update(float timeElapsed)
{

	if (bolaActual < caidas.size())
	{
		if (posFinal <= caidas[bolaActual]->getCurrentPos().x)
		{
			if (!animando)
			{
				//inicio animación y calculo la posición en la que quedaría en la barra
				animando = true;
				posFinal = 212 + 30 * Juego::Instance()->barra.size();
			}
			//no ha llegado por lo que se sigue moviendo
			caidas[bolaActual]->setVelocidad(sf::Vector2f(-0.1, 0.0f));
			caidas[bolaActual]->Update(timeElapsed);
		}
		else
		{
			//ha llegado por lo que paso a la siguiente Bola
			caidas[bolaActual]->setVelocidad(sf::Vector2f(0.0f, 0.0f));
			caidas[bolaActual]->setPosSg(sf::Vector2f(posFinal, 400));
			caidas[bolaActual]->setPosPR(sf::Vector2f(posFinal, 400));
			posFinal = 0;
			animando = false;

			esValida(caidas[bolaActual]);

			++bolaActual;
			if (bolaActual == caidas.size())
			{
				//he pasado por todas las bolas y cambio de estado
				printf("paso por el abaco");
				Juego::Instance()->CambiarEstado(EstadoAnimacionAbaco::Instancia());
				caidas.clear();
				primera = -1;
			}
		}
	}else if (caidas.size() == 0)
	{
		printf("apunto otra vez y no paso por el abaco");
		Juego::Instance()->CambiarEstado(EstadoApuntar::Instancia());
		primera = -1;
	}	
}
void EstadoAnimacionBolas::esValida(Bola* bola)
{
	if (bola->getID() == 0)
	{
		//ha caido la bola blanca
		//colocar en el centro
		caidas[bolaActual]->setPosPR(Juego::Instance()->positions[0]);
		caidas[bolaActual]->setPosSg(Juego::Instance()->positions[0]);
		caidas[bolaActual]->caida = false;
		printf("es la 0, la dejo donde estaba\n");
	}
	else if (primera != Juego::Instance()->bolas[1].getID())
	{
		//no ha golpeado a la bola menor la primera. Ninguna bola cuenta
		// O no ha golpeado a ninguna
		printf("El primer golpe no era la bola menor\n");
		std::cout << "Primera golpeada:" << primera << " bola menor" << Juego::Instance()->bolas[1].getID() << std::endl;
		//colocar en alguna de las posiciones iniciales
		sf::Vector2f recolocar = posValida();
		caidas[bolaActual]->setPosPR(recolocar);
		caidas[bolaActual]->setPosSg(recolocar);
		caidas[bolaActual]->setVelocidad(sf::Vector2f(0.f, 0.f));
		caidas[bolaActual]->caida = false;
	}
	else
	{
		printf("Golpe y bola validos\n");
		//no es la bola blanca y el primer golpe es valido
		//Cambio a estado abaco
		//si es la 9 has ganado yay
		if (caidas[bolaActual]->getID() == 9)
		{
			printf("has ganado, yay \n");
			EstadoAnimacionAbaco::Instancia()->ganado = true;
		}
		printf("cambio de estado\n");
		EstadoAnimacionAbaco::Instancia()->nuevosPuntos += caidas[bolaActual]->getID();
		Juego::Instance()->barra.push_back(*caidas[bolaActual]);
	}
}
void EstadoAnimacionBolas::addCaidas(std::vector<Bola*> bolas)
{
	for (unsigned int i = 0; i < bolas.size(); i++)
	{
		caidas.push_back(bolas[i]);
	}
}
void EstadoAnimacionBolas::Render(float percentick)
{
	Juego* juego = Juego::Instance();
	if(caidas.size() > 0){
		caidas[bolaActual]->Render(juego->ventana, percentick);
	}
}

/*
    Comprueba cuales de las posiciones predeterminadas se encuentran libres
*/
sf::Vector2f EstadoAnimacionBolas::posValida()
{
	sf::Vector2f posBola = sf::Vector2f(0.f, 0.f);
	sf::Vector2f vecPB = sf::Vector2f(0.f, 0.f);
	sf::Vector2f pos = sf::Vector2f(0.f, 0.f);

	for (unsigned int i = 1; i < Juego::Instance()->positions.size(); i++)
	{
		pos = Juego::Instance()->positions[i];
		for (unsigned int j = 0; j < Juego::Instance()->bolas.size(); j++)
		{
			posBola = Juego::Instance()->bolas[i].getPosSecond();

			vecPB = sf::Vector2f(pos.x - posBola.x, pos.y - posBola.y);

			if (sqrt((vecPB.x * vecPB.x) + (vecPB.y * vecPB.y)) > 21)
			{
				return pos;
			}
		}
	}
	return sf::Vector2f(-1, -1);
}
