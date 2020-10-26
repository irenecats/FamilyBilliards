#include "Abaco.h"

Abaco::Abaco()
{
	//	for (int i = 0; i < 50; i++)
	//	{
	//		sf::RectangleShape rectangle;
	//		//genera la barras
	//		if (i == 1)
	//		{
	//			posInitFin.first = sf::Vector2f(290, 500);
	//			posInitFin.second = sf::Vector2f(290, 500);
	//		}
	//		if ((i + 1) % 5 != 0)
	//		{
	//			rectangle.setSize(sf::Vector2f(5, 10));
	//			rectangle.setFillColor(sf::Color::Red);
	//			rectangle.setPosition(290 + i * 10, 500);
	//		}
	//		else
	//		{
	//			rectangle.setSize(sf::Vector2f(5, 15));
	//			rectangle.setFillColor(sf::Color::Blue);
	//			rectangle.setPosition(290 + i * 10, 495);
	//		}
	//
	//		piezas.push_back(rectangle);
	//	}
	//
	//	moviendo = 0;
	//	movidas = 0;
	//	animando = -1;
	//
	//	//ctor
}

void Abaco::Update(float timeElapsed)
{
	posInitFin.first = posInitFin.second;
	posInitFin.second = sf::Vector2f(posInitFin.first.x + velocidad.x * timeElapsed, posInitFin.first.y + velocidad.y * timeElapsed);
}

void Abaco::Render(sf::RenderWindow& ventana, float percentTick)
{
	float pointerX = posInitFin.first.x * (1 - percentTick) + posInitFin.second.x * percentTick;
	float pointerY = posInitFin.first.y * (1 - percentTick) + posInitFin.second.y * percentTick;
	sprite.setPosition(pointerX, pointerY);
	ventana.draw(sprite);
}

void Abaco::muevePiezas(int num)
{

	moviendo = num;
	animando = 0;
}

int Abaco::getAnimando()
{
	return animando;
}

void Abaco::setAnimando(int val)
{
	int a = 0;
	a = a * val;
	//	animando = val;
	//	if (val == -1)
	//	{
	//
	//		if ((movidas) % 5 != 0)
	//		{
	//			sf::Vector2f pos(290, 500);
	//
	//			posicion.setPrimera(pos);
	//			posicion.setSegunda(pos);
	//		}
	//		else
	//		{
	//
	//			sf::Vector2f pos(290, 495);
	//
	//			posicion.setPrimera(pos);
	//			posicion.setSegunda(pos);
	//		}
	//	}
}
void Abaco::setPosSg(sf::Vector2f pos)
{
	posInitFin.second = pos;
}

void Abaco::setPosPR(sf::Vector2f pos)
{
	posInitFin.first = pos;
}
Abaco::~Abaco()
{
	//dtor
}
