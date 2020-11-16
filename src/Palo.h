#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#define VEL_MAX 0.4f
#define VEL_MIN 0.1f

class Palo
{
public:
	Palo();
	Palo(sf::Texture& text);
	virtual ~Palo();
	void Render(sf::RenderWindow& ventana, float percentTick);
	void Update(float timeElapsed, float vel);

	void tiro();
	//bool getTerminado();
	//void setTerminado(bool);
	//void calculoVelocidad();
	sf::Vector2f getPosSecond();
	sf::Vector2f getPosFirst();
	sf::Vector2f getCurrentPos();

protected:
private:
	sf::Sprite palo;
	std::pair<sf::Vector2f, sf::Vector2f> posInitFin;
	float posPulsado { 0.f };
	float animPause { 0.f };
};