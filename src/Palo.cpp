#include "Palo.h"

Palo::Palo(sf::Texture& text)
{
	palo.setTexture(text);
	palo.setTextureRect(sf::IntRect(43.0, 22.0, 800.0, 14.0));

	posInitFin.first = sf::Vector2f(42.5f, 570.0f);
	posInitFin.second = sf::Vector2f(42.5f, 570.0f);
}

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

void Palo::Render(sf::RenderWindow& ventana, float percentTick)
{
	float paloX = posInitFin.first.x * (1 - percentTick) + posInitFin.second.x * percentTick;
	palo.setPosition(paloX, posInitFin.first.y);
	ventana.draw(palo);
}

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
