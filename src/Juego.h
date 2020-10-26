#pragma once

#include <Abaco.h>
#include <Bola.h>
#include <Estado.h>
#include <Jugador.h>
//#include <Mapa.h>
#include <Palo.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>

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

	//Estados
	void CambiarEstado(Estado* estado);

	//Juego
	void tiraBola(float);

protected:
private:
	//Variables
	static Juego* instancia;

	sf::View pantalla;
	sf::View mapa;
	sf::Clock relojUpdate;

	bool debug;

	std::vector<Estado*> estados;

	int caidasCont;

	//Metodos
	Juego();
	void prepararVentana();
	void generaBolas();

	void Inicializa();
	//	void Reinicia();
};