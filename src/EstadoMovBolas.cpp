#include <Bola.h>
#include <EstadoAnimacionBolas.h>
#include <EstadoMovBolas.h>
#include <EstadoApuntar.h>
#include <Juego.h>
#include <iostream>
EstadoMovBolas EstadoMovBolas::instancia;
void EstadoMovBolas::Inicializar()
{
	primera = nullptr;
}

void EstadoMovBolas::ManejarEventos(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
	{
		Juego::Instance()->ventana.close();
	}
}
void EstadoMovBolas::Update(float timeElapsed)
{
	Juego* juego = Juego::Instance();
	Bola* bola;
	sf::Vector2f velocidad;
	for (unsigned int i = 0; i < juego->bolas.size(); i++)
	{
		bola = &juego->bolas[i];
		velocidad = bola->getVelocidad();
		if ((velocidad.x > 0 && velocidad.x < 0.001) || (velocidad.x < 0 && velocidad.x > -0.001))
		{
			velocidad.x = 0;
		}
		else
		{
			velocidad.x -= velocidad.x * 0.01f;
		}

		if ((velocidad.y > 0 && velocidad.y < 0.001) || (velocidad.y < 0 && velocidad.y > -0.001))
		{
			velocidad.y = 0;
		}
		else
		{
			velocidad.y -= velocidad.y * 0.01f;
		}
		bola->setVelocidad(velocidad);
		bola->Update(timeElapsed);
	}
	Juego::Instance()->palo.Update(timeElapsed, 0.f);
	colisionBolas();
	colisionParedes();
	colisionTronera();
	if (comprobarParadas())
	{
		Juego::Instance()->CambiarEstado(EstadoAnimacionBolas::Instancia());
		if(Juego::Instance()->bolas.size()>1)
		{
			Jugador::Instance()->apuntado(Juego::Instance()->bolas[0].getCurrentPos(),Juego::Instance()->bolas[1].getCurrentPos());
		}
	} //si están paradas cambio de estado
}
void EstadoMovBolas::Render(float percentick)
{
	Juego* juego = Juego::Instance();
	juego->palo.Render(juego->ventana, percentick);
}

bool EstadoMovBolas::comprobarParadas()
{

	for (unsigned int i = 0; i < Juego::Instance()->bolas.size(); i++)
	{
		if (!Juego::Instance()->bolas[i].heParado())
		{
			return false;
		}
	}
	return true;
}
/*
    Detecta la colision y dependiendo del tipo de pared invierte la x o y del vector velocidad de la bola
*/
void EstadoMovBolas::colisionParedes()
{
	std::vector<sf::RectangleShape> paredes = Juego::Instance()->paredes;

	Bola* bola = nullptr;
	sf::RectangleShape* pared = nullptr;
	for (unsigned int i = 0; i < paredes.size(); i++)
	{
		pared = &Juego::Instance()->paredes[i];
		for (unsigned int j = 0; j < Juego::Instance()->bolas.size(); j++)
		{
			bola = &Juego::Instance()->bolas[j];
			if (paredes[i].getGlobalBounds().intersects(bola->getGlobalBounds()))
			{
				sf::Vector2f vel = bola->getVelocidad();
				if (i == 1 || i == 0)
				{
					bola->setPosSg(sf::Vector2f(bola->getPosSecond().x, pared->getPosition().y + 23));
					bola->setPosPR(sf::Vector2f(bola->getPosSecond().x, pared->getPosition().y + 23));

					vel.y = -vel.y;
					bola->setVelocidad(vel);
				}
				else if (i == 2 || i == 3)
				{
					bola->setPosSg(sf::Vector2f(bola->getPosSecond().x, pared->getPosition().y - 23));
					bola->setPosPR(sf::Vector2f(bola->getPosSecond().x, pared->getPosition().y - 23));
					vel.y = -vel.y;
					bola->setVelocidad(vel);
				}
				else if (i == 4)
				{
					bola->setPosSg(sf::Vector2f(pared->getPosition().x - 23, bola->getPosSecond().y));
					bola->setPosPR(sf::Vector2f(pared->getPosition().x - 23, bola->getPosSecond().y));

					vel.x = -vel.x;
					bola->setVelocidad(vel);
				}
				else
				{
					bola->setPosSg(sf::Vector2f(pared->getPosition().x + 23, bola->getPosSecond().y));
					bola->setPosPR(sf::Vector2f(pared->getPosition().x + 23, bola->getPosSecond().y));
					vel.x = -vel.x;
					bola->setVelocidad(vel);
				}
			}
		}
	}
}
/*
    Calcula la distancia entre las troneras y las bolas para detectar si estas han caido,
    en caso de caer, las bolas dejan de moverse y setean su variable caida a true para
    dejar de ser renderizadas. Además se crea un puntero a la bola.
*/
void EstadoMovBolas::colisionTronera()
{
	Bola* bola = nullptr;
	sf::CircleShape* tronera = nullptr;
	std::vector<Bola*> caidas;
	for (unsigned int i = 0; i < Juego::Instance()->troneras.size(); i++)
	{
		tronera = &Juego::Instance()->troneras[i];
		for (unsigned int j = 0; j < Juego::Instance()->bolas.size(); j++)
		{
			bola = &Juego::Instance()->bolas[j];
			if (!bola->caida)
			{
				sf::Vector2f posB1 = tronera->getPosition();
				sf::Vector2f posB2 = bola->getPosSecond();
				sf::Vector2f vecB1B2((posB1.x - posB2.x), (posB1.y - posB2.y));

				float separacion = sqrt((vecB1B2.x * vecB1B2.x) + (vecB1B2.y * vecB1B2.y));

				if (separacion <= (tronera->getRadius() + 4))
				{
					std::cout << "Ha caido " << bola->getID() << std::endl;
					bola->setVelocidad(sf::Vector2f(0, 0));
					bola->caida = true;
					bola->setPosPR(sf::Vector2f(590, 400));
					bola->setPosSg(sf::Vector2f(590, 400));
					caidas.push_back(bola);
				}
			}
		}
	}
	EstadoAnimacionBolas::Instancia()->addCaidas(caidas);
}

void EstadoMovBolas::colisionBolas()
{
	Bola* bola1 = nullptr;
	Bola* bola2 = nullptr;
	for (unsigned int i = 0; i < Juego::Instance()->bolas.size(); i++)
	{
		bola1 = &Juego::Instance()->bolas[i];
		if (!bola1->caida)
		{
			for (unsigned int j = 0; j < Juego::Instance()->bolas.size(); j++)
			{
				bola2 = &Juego::Instance()->bolas[j];
				if (!bola2->caida && i != j)
				{
					choque(bola1, bola2);
				}
			}
		}
	}
}

/*
    Calucla la distancia entre cada una de las bolas y en el caso de ser menor que la suma de los
    2 radios significa que estan colisionando. En caso de colision, muevo manualmente las bolas
    para que no se solapen y calculo los nuevos vectores de velocidad.
*/
void EstadoMovBolas::choque(Bola* bola1, Bola* bola2)
{
	sf::Vector2f posB1 = bola1->getPosSecond();
	sf::Vector2f posB2 = bola2->getPosSecond();
	sf::Vector2f vecB1B2((posB1.x - posB2.x), (posB1.y - posB2.y));

	float separacion = sqrt((vecB1B2.x * vecB1B2.x) + (vecB1B2.y * vecB1B2.y));

	if (separacion < 21)
	{
		if (bola1->getID() == 0)
		{
			if (!primera)
			{
				primera = bola2;
				EstadoAnimacionBolas::Instancia()->primera = bola2->getID();
				std::cout << "\nPrimera bola: " << bola2->getID() << std::endl;
			}
		}

		float interseccion = (separacion - 21) * 0.5;
		posB1.x -= (interseccion * vecB1B2.x) / separacion;
		posB1.y -= (interseccion * vecB1B2.y) / separacion;
		posB2.x += (interseccion * vecB1B2.x) / separacion;
		posB2.y += (interseccion * vecB1B2.y) / separacion;

		bola1->setPosSg(posB1);
		bola2->setPosSg(posB2);

		//normal
		sf::Vector2f normal = sf::Vector2f((posB2.x - posB1.x), (posB2.y - posB1.y)) / separacion;

		sf::Vector2f b1vel = bola1->getVelocidad();
		sf::Vector2f b2vel = bola2->getVelocidad();

		float p = 2 * (normal.x * (b1vel.x - b2vel.x) + normal.y * (b1vel.y - b2vel.y)) / 2;

		bola1->setVelocidad(sf::Vector2f(b1vel.x - p * 0.75f * normal.x, b1vel.y - p * 0.75f * normal.y));
		bola2->setVelocidad(sf::Vector2f(b2vel.x + p * 0.75f * normal.x, b2vel.y + p * 0.75f * normal.y));
	}
}