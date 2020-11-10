#pragma once
#include <Juego.h>
//#include <Mapa.h>
#include <SFML/Graphics.hpp>

class Jugador
{
public:
	static Jugador* Instance();
	virtual ~Jugador();
	void Render(sf::RenderWindow&, float);
	void RenderPoints(sf::RenderWindow& ventana);

	void Update(float);
	void setPointer(sf::Texture&);
	void apuntado(sf::Vector2f, sf::Vector2f);

	sf::Vector2f getPos();
	sf::Vector2f getCurrentPos();
	int getPuntuacion();
	void addPuntuacion(int);

	sf::Vector2f movimiento;

protected:
private:
	static Jugador* instancia;
	sf::Texture textura;
	sf::Sprite pointer;
	std::pair<sf::Vector2f, sf::Vector2f> posInitFin;

	int puntuacion;
	sf::Font fuente;
	sf::Text textoPuntos;

	Jugador();
};
