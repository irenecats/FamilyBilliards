#include "Bola.h"

Bola::Bola(int id, sf::Texture& text, std::vector<sf::Vector2f> positions)
{
	ID = id;

	sprite.setTexture(text);
	sprite.setTextureRect(sf::IntRect(21 * (id + 1), 0, 21, 21));
	sprite.setOrigin(21 / 2, 21 / 2);

	posInitFin.first = positions[ID];
	posInitFin.second = positions[ID];
}

bool Bola::heParado()
{
	bool parado = false;
	if (velocidad.x == 0 && velocidad.y == 0)
	{
		parado = true;
	}
	return parado;
}

void Bola::Update(float timeElapsed)
{
	posInitFin.first = posInitFin.second;
	controlaVelocidad();
	posInitFin.second = sf::Vector2f(posInitFin.first.x + velocidad.x * timeElapsed, posInitFin.first.y + velocidad.y * timeElapsed);
}

void Bola::Render(sf::RenderWindow& ventana, float percentTick)
{
	float pointerX = posInitFin.first.x * (1 - percentTick) + posInitFin.second.x * percentTick;
	float pointerY = posInitFin.first.y * (1 - percentTick) + posInitFin.second.y * percentTick;
	sprite.setPosition(pointerX, pointerY);
	ventana.draw(sprite);
}

/*
    En caso de que la bola debido a las colisiones supere el maximo
     de velocidad permitido, la velocidad sera la maxima.
     Por otro lado, si la velocidad es demasiado pequeña esta se volvera cero.
*/

void Bola::controlaVelocidad()
{
	if (velocidad.x > max_vel)
	{
		velocidad.x = max_vel;
	}
	else if (velocidad.x < -max_vel)
	{
		velocidad.x = -max_vel;
	}

	if (velocidad.y > max_vel)
	{
		velocidad.y = max_vel;
	}
	else if (velocidad.y < -max_vel)
	{
		velocidad.y = -max_vel;
	}

	if ((velocidad.x > 0 && velocidad.x < 0.001) || (velocidad.x < 0 && velocidad.x > -0.001))
	{
		velocidad.x = 0;
	}

	if ((velocidad.y > 0 && velocidad.y < 0.001) || (velocidad.y < 0 && velocidad.y > -0.001))
	{
		velocidad.y = 0;
	}
}
/*
void Bola::calcDistancia(sf::Vector2f blanca)
{

	sf::Vector2f vect((posicion.getSegunda().x - blanca.x), (posicion.getSegunda().y - blanca.y));

	dist = sqrt((vect.x * vect.x) + (vect.y * vect.y));
}


void Bola::empezarAnimacion(float pos)
{
	posicion.setPrimera(sf::Vector2f(590, 400));
	posicion.setSegunda(sf::Vector2f(590, 400));
	animado = true;
	posfinal = pos;
}

void Bola::terminarAnimacion()
{
	animado = false;
	caida = false;
	posfinal = 0;
}

sf::Vector2f Bola::getPosSg()
{
	return posicion.getSegunda();
}
sf::Vector2f Bola::getPosPr()
{
	return posicion.getPrimera();
}



bool Bola::getAnimado()
{
	return animado;
}



void Bola::setPos(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}
*/

sf::Vector2f Bola::getVelocidad()
{
	return velocidad;
}
int Bola::getID()
{
	return ID;
}
/*
void Bola::setCaida(bool val)
{
	caida = val;
}

bool Bola::getCaida()
{
	return caida;
}



float Bola::getDist()
{
	return dist;
}

sf::Vector2f Bola::getSprite()
{
	return sprite.getPosition();
}
*/
sf::Vector2f Bola::getCurrentPos()
{
	return sprite.getPosition();
	;
}

sf::Vector2f Bola::getPosSecond()
{
	return posInitFin.second;
}
sf::FloatRect Bola::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}
void Bola::setPosSg(sf::Vector2f pos)
{
	posInitFin.second = pos;
}

void Bola::setPosPR(sf::Vector2f pos)
{
	posInitFin.first = pos;
}
void Bola::setVelocidad(sf::Vector2f vel)
{
	velocidad = vel;
	controlaVelocidad();
}
Bola::Bola()
{}

Bola::~Bola()
{
	//dtor
}
