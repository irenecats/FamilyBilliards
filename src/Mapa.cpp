#include "Mapa.h"

Mapa* Mapa::instancia = 0;
Mapa* Mapa::Instance()
{

	if (instancia == 0)
	{
		instancia = new Mapa;
	}

	return instancia;
}

void Mapa::setValues()
{
	angulo = 0;
	printf("es 0\n");
}

Mapa::Mapa()
{
	//ctor
}

Mapa::~Mapa()
{
	//dtor
}

/*
    No realiza correctamente la rotacio pero las bolas se dibujan segun la lejania de las bolas,
    primeras las mas lejanas.
*/
void Mapa::Render(sf::RenderWindow& window, std::vector<Bola> bolas)
{

	sf::CircleShape circulo(5);
	float maxim = 0;
	int num = 1;
	unsigned int siz = bolas.size();

	for (unsigned int j = 1; j < siz; j++)
	{
		//std::cout<<"J "<<j<<std::endl;
		for (unsigned int i = 1; i < bolas.size(); i++)
		{
			//std::cout<<"dist "<<bolas[i].getDist()<<std::endl;
			if (maxim < bolas[i].getDist())
			{
				maxim = bolas[i].getDist();
				num = i;
			}
		}
		//std::cout<<"I "<<bolas[num].getID()<<std::endl;
		sf::Vector2f pos = Proyecta(200, 60, 100, 10, sf::Vector2f(bolas[num].getPosSg().x - bolas[0].getPosSg().x, bolas[num].getPosSg().y - bolas[0].getPosSg().y));
		pos = RotaY(pos, angulo);

		circulo.setPosition(pos);
		switch (bolas[num].getID())
		{
			case 1:
				circulo.setFillColor(sf::Color(255, 148, 0));
				break;
			case 2:
				circulo.setFillColor(sf::Color(0, 131, 255));
				break;
			case 3:
				circulo.setFillColor(sf::Color::Red);
				break;
			case 4:
				circulo.setFillColor(sf::Color(196, 93, 252));
				break;
			case 5:
				circulo.setFillColor(sf::Color(255, 148, 0));
				break;
			case 6:
				circulo.setFillColor(sf::Color(0, 131, 255));
				break;
			case 7:
				circulo.setFillColor(sf::Color::Red);
				break;
			case 8:
				circulo.setFillColor(sf::Color(0, 131, 255));
				break;
			case 9:
			default:
				circulo.setFillColor(sf::Color(255, 148, 0));
		}

		window.draw(circulo);

		bolas.erase(bolas.begin() + num);
		num = 1;
		maxim = 0;
	}
}

sf::Vector2f Mapa::Proyecta(float viewWidth, float viewHeight, float fov, float viewDistance, sf::Vector2f pos)
{

	float factor;
	float x = pos.y;
	float z = pos.x;
	float y = 0;

	factor = fov / (viewDistance + z);
	x = x * factor + viewWidth / 2;
	y = y * factor + viewHeight / 2;

	return sf::Vector2f(x, y);
}

sf::Vector2f Mapa::RotaY(sf::Vector2f pos, float rad)
{

	float coseno = cos(rad);
	//float seno = sin(rad);
	float x = 0;

	x = pos.x * coseno;

	return sf::Vector2f(x, pos.y);
}

void Mapa::setAngulo(float rad)
{
	angulo = rad - 3.14159;
}
