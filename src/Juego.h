#pragma once

#include <Abaco.h>
#include <Bola.h>
#include <Estado.h>
#include <Jugador.h>
//#include <Mapa.h>
#include <Palo.h>
#include <SFML/Graphics.hpp>

#define UPDATE_TIME (1000 / 60)

class Juego
{
public:
	//Variables
	sf::RenderWindow ventana;
	sf::Texture textura;
	std::vector<sf::Vector2f> positions; //posiciones iniciales al generar las bolas

	std::vector<Bola> bolas;   //bolas en juego
	std::vector<Bola> barra;   //bolas en la barra
	std::vector<Bola*> caidas; //bolas que acaban de caer
	Palo palo;				   //palo de billar
	//Abaco abaco;			   //puntos actuales
	std::vector<Abaco> abaco;

	std::vector<sf::RectangleShape> paredes; //colliders de las paredes
	std::vector<sf::CircleShape> troneras;	 //colliders de las troneras

	static Juego* Instance();
	virtual ~Juego();

	void bucleJuego();
	void CambiarEstado(Estado* estado);
	void tiraBola(float);

protected:
private:
	//Variables
	static Juego* instancia;

	sf::View pantalla;
	sf::View mapa;
	sf::Clock relojUpdate;

	std::vector<Estado*> estados;

	Juego();
	void prepararVentana();
	void generaBolas();

	void Inicializa();
	//	void Reinicia();
};