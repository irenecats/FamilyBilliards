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
	sf::Vector2f getPos();

	void setPosPR(sf::Vector2f);
	void setPosSg(sf::Vector2f);
	void setVelocidad(float vel);
	sf::RectangleShape sprite;

protected:
private:
	std::pair<sf::Vector2f, sf::Vector2f> posInitFin;
	float velocidad;
};
