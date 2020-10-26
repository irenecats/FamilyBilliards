#include "Palo.h"

Palo::Palo(sf::Texture& text)
{
	palo.setTexture(text);
	palo.setTextureRect(sf::IntRect(43.0, 22.0, 800.0, 14.0));

	posInitFin.first = sf::Vector2f(42.5f, 570.0f);
	posInitFin.second = sf::Vector2f(42.5f, 570.0f);
}
/*
    Permite que el palo pueda moverse de un lado a otro de la pantalla
    para simular el apuntado.
    Una vez se haya decidido apuntar, el palo se quedara quieto unos segundos
    y efectuara el golpe de la bola al finalizar el recorrido.
*/
void Palo::Update(float timeElapsed, float vel)
{
	posInitFin.first = posInitFin.second;

	float pos = posInitFin.first.x + vel * timeElapsed;
	if (pos < 42.5)
	{
		pos = 42.5;
	}
	else if (pos > 670)
	{
		pos = 670;
	}

	posInitFin.second = sf::Vector2f(pos, posInitFin.first.y);
}
/*
void UpdateMovimiento(float timeElapsed)
{
}
void UpdateGolpe(float timeElapsed)
{
	if (estado == 2 && cont > 700)
	{
		if (paloPos.getPrimera().x > 42.5 && dir == true)
		{
			movimiento = -1.f;
		}
		else if (paloPos.getPrimera().x <= 42.5 && dir == true)
		{
			dir = false;
			terminado = true;
			calculoVelocidad();
		}
	}
	else if (estado == 2 && cont < 700)
	{
		cont += timeElapsed;
	}
}
*/
void Palo::Render(sf::RenderWindow& ventana, float percentTick)
{
	float paloX = posInitFin.first.x * (1 - percentTick) + posInitFin.second.x * percentTick;
	palo.setPosition(paloX, posInitFin.first.y);
	ventana.draw(palo);
}

void Palo::tiro()
{
	//dir = true;
	//terminado=false;

	//TODO: Ponerlo en el nuevo estado
	//animPause = 0.f;
	//posPulsado = palo.getPosition().x;
}

/*
bool Palo::getTerminado()
{
	return terminado;
}

void Palo::setTerminado(bool val)
{
	terminado = val;
}
*/
sf::Vector2f Palo::getPosSecond()
{
	return posInitFin.second;
}
sf::Vector2f Palo::getPosFirst()
{
	return posInitFin.first;
}
sf::Vector2f Palo::getCurrentPos()
{
	return palo.getPosition();
}

Palo::Palo()
{
	//ctor
}

Palo::~Palo()
{
	//dtor
}
