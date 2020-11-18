#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
class Bola
{
public:
	Bola(int, sf::Texture&, std::vector<sf::Vector2f>);
	Bola();
	virtual ~Bola();
	void Update(float timeElapsed);
	void Render(sf::RenderWindow& ventana, float percentTick);

	void controlaVelocidad();
	bool heParado();

	//GETTERS
	sf::Vector2f getVelocidad();
	sf::Vector2f getCurrentPos();
	sf::Vector2f getPosSecond();
	sf::FloatRect getGlobalBounds();
	int getID();
	//SETTERS
	void setVelocidad(sf::Vector2f);
	void setPosPR(sf::Vector2f);
	void setPosSg(sf::Vector2f);

	/*void Update(float);
	void empezarAnimacion(float);
	void terminarAnimacion();

	void calcDistancia(sf::Vector2f);
	sf::Vector2f getSprite();
	sf::Vector2f getPosPr();
	sf::Vector2f getPosSg();
	bool getAnimado();

	void setPos(sf::Vector2f);

	void setCaida(bool);
	bool getCaida();
	float getDist();
*/
	bool caida { false };

protected:
private:
	int ID;
	sf::Vector2f velocidad;
	std::pair<sf::Vector2f, sf::Vector2f> posInitFin;
	sf::Sprite sprite;
	float max_vel { 0.4f };

	bool animado { false };
	//float posfinal;
	//float dist = 0;
	//void controlaVelocidad();
};