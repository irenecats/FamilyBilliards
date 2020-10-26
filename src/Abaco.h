#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Abaco
{
public:
	Abaco();
	virtual ~Abaco();
	void Update(float);
	void Render(sf::RenderWindow& ventana, float);
	void muevePiezas(int);
	int getAnimando();
	void setAnimando(int);
	sf::Vector2f getPos();

	void setPosPR(sf::Vector2f);
	void setPosSg(sf::Vector2f);
	sf::RectangleShape sprite;

protected:
private:
	//std::pair<sf::RectangleShape, std::pair<sf::Vector2f, sf::Vector2f>> ha;
	std::pair<sf::Vector2f, sf::Vector2f> posInitFin;
	//viejo

	std::vector<sf::RectangleShape> piezas;
	sf::Vector2f velocidad;
	int moviendo;
	int movidas;
	int animando;
};
