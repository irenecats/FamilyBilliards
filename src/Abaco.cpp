#include "Abaco.h"

Abaco::Abaco()
{
	for (int i = 0; i < 50; i++)
	{
		sf::RectangleShape rectangle;
		if (i == 1)
		{
			printf("DEntro\n");
			posicion.setPrimera(sf::Vector2f(290, 500));
			posicion.setSegunda(sf::Vector2f(290, 500));
		}
		if ((i + 1) % 5 != 0)
		{
			rectangle.setSize(sf::Vector2f(5, 10));
			rectangle.setFillColor(sf::Color::Red);
			rectangle.setPosition(290 + i * 10, 500);
		}
		else
		{
			rectangle.setSize(sf::Vector2f(5, 15));
			rectangle.setFillColor(sf::Color::Blue);
			rectangle.setPosition(290 + i * 10, 495);
		}

		piezas.push_back(rectangle);
	}

	moviendo = 0;
	movidas = 0;
	animando = -1;

	//ctor
}

void Abaco::Update(float timeElapsed)
{
	if (posicion.getSegunda().x < 100)
	{
		velocidad.x = 0;
		posicion.setSegunda(sf::Vector2f(100 + (10 * (movidas)-1), posicion.getPrimera().y));
		movidas += moviendo;
		moviendo = 0;
		animando = 1;
	}
	else
	{
		velocidad.x = -0.1;
	}

	posicion.setPrimera(posicion.getSegunda());
	posicion.setSegunda(sf::Vector2f(posicion.getPrimera().x + velocidad.x * timeElapsed, posicion.getPrimera().y + velocidad.y * timeElapsed));
}

void Abaco::Render(sf::RenderWindow& window, float percentTick)
{
	float pointerX = posicion.getPrimera().x * (1 - percentTick) + posicion.getSegunda().x * percentTick;
	float pointerY = 0;

	for (int i = movidas; i < moviendo + movidas; i++)
	{
		if ((i + 1) % 5 == 0)
		{
			pointerY = 495;
		}
		else
		{
			pointerY = 500;
		}
		piezas[i].setPosition(pointerX + (i * 10), pointerY);
	}

	for (int i = 0; (size_t)i < piezas.size(); i++)
	{
		window.draw(piezas[i]);
	}
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
	animando = val;
	if (val == -1)
	{

		if ((movidas) % 5 != 0)
		{
			sf::Vector2f pos(290, 500);

			posicion.setPrimera(pos);
			posicion.setSegunda(pos);
		}
		else
		{

			sf::Vector2f pos(290, 495);

			posicion.setPrimera(pos);
			posicion.setSegunda(pos);
		}
	}
}

Abaco::~Abaco()
{
	//dtor
}
