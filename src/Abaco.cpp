#include "Abaco.h"

void Abaco::Update(float timeElapsed)
{
	posInitFin.first = posInitFin.second;
	posInitFin.second = sf::Vector2f(posInitFin.first.x + velocidad * timeElapsed, posInitFin.first.y + 0 * timeElapsed);
}

void Abaco::Render(sf::RenderWindow& ventana, float percentTick)
{
	float pointerX = posInitFin.first.x * (1 - percentTick) + posInitFin.second.x * percentTick;
	float pointerY = posInitFin.first.y * (1 - percentTick) + posInitFin.second.y * percentTick;
	sprite.setPosition(pointerX, pointerY);
	ventana.draw(sprite);
}

sf::Vector2f Abaco::getPos()
{
	return sprite.getPosition();
}

void Abaco::setPosSg(sf::Vector2f pos)
{
	posInitFin.second = pos;
}

void Abaco::setPosPR(sf::Vector2f pos)
{
	posInitFin.first = pos;
}
void Abaco::setVelocidad(float vel)
{
	velocidad = vel;
}

Abaco::~Abaco()
{
	//dtor
}
Abaco::Abaco()
{
}