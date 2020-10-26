#include "Juego.h"
#include "Platform/Platform.hpp"
#include <EstadoAnimacionAbaco.h>
#include <algorithm>
#include <math.h>
Juego* Juego::instancia = 0;
Juego* Juego::Instance()
{

	if (instancia == 0)
	{
		instancia = new Juego;
	}

	return instancia;
}
void Juego::prepararVentana()
{
	printf("Movimiento con las flechas del teclado\n");
	printf("Shift para que el pointer se mueva mas rapido\n");
	printf("Espacio para preparar golpe y otra vez espacio para golpear\n");
	printf("Si volver al moddo apuntar vuelve a pulsar las flechas del teclado\n");
	printf("---------\n");
	printf("Pulsa R para resetar la partida\n");
	printf("Pulsa D para ver las colisiones\n");
	printf("---------\n");
	printf("Estado 0: Apunto");

	util::Platform platform;

	// in Windows at least, this must be called before creating the ventana
	float screenScalingFactor = platform.getScreenScalingFactor(ventana.getSystemHandle());

	ventana.create(sf::VideoMode(800.0f * screenScalingFactor, 600.0f * screenScalingFactor), "Family Billiards");
	ventana.setFramerateLimit(60);
	ventana.setKeyRepeatEnabled(false);
	platform.setIcon(ventana.getSystemHandle());

	pantalla = sf::View(sf::FloatRect(0, 0, 800.f, 600.f));
	mapa = sf::View(sf::FloatRect(0, 0, 200, 60));
	mapa.setViewport(sf::FloatRect(0.25, 0.75, 0.5, 0.20));
}
void Juego::bucleJuego()
{
	prepararVentana();

	//Inicializo mapa y fondos
	palo = Palo(textura);
	sf::Sprite fondo(textura);
	fondo.setTextureRect(sf::IntRect(0, 40.0, 800.0, 600.0));
	sf::CircleShape circulo(1);
	sf::CircleShape circulo2(1);
	sf::CircleShape circulo3(1);
	sf::CircleShape circulo4(1);
	circulo2.setPosition(mapa.getSize().x - 2, 0);
	circulo3.setPosition(mapa.getSize().x - 2, mapa.getSize().y - 2);
	circulo4.setPosition(0, mapa.getSize().y - 2);

	circulo.setFillColor(sf::Color::Red);
	circulo2.setFillColor(sf::Color::Red);
	circulo3.setFillColor(sf::Color::Red);
	circulo4.setFillColor(sf::Color::Red);

	Inicializa(); //inicializar juego
	sf::Event event;

	while (ventana.isOpen())
	{
		//Proceso los eventos
		while (ventana.pollEvent(event))
		{
			estados.back()->ManejarEventos(event);
		}

		if (relojUpdate.getElapsedTime().asMilliseconds() > UPDATE_TIME)
		{
			float timeElapsed = relojUpdate.restart().asMilliseconds();
			estados.back()->Update(timeElapsed);
		}

		float percentick = std::min(1.f, (float)relojUpdate.getElapsedTime().asMilliseconds() / UPDATE_TIME);

		ventana.setView(pantalla);
		// Clear screen
		ventana.clear();
		ventana.draw(fondo);

		estados.back()->Render(percentick);

		// Update the window
		ventana.display();
	}
}
/*
    Genera las bolas mandandoles la textura y la posicion en la que se tienen que generar
*/
void Juego::generaBolas()
{
	//genero 9 bolas
	printf("Genero las bolas\n");
	for (int i = 0; i < 10; i++)
	{
		bolas.push_back(Bola(i, textura, positions));
	}
}

void Juego::CambiarEstado(Estado* estado)
{
	estados.push_back(estado);
}

/*
    Inicia una nueva partida desde cero
*/

void Juego::Inicializa()
{
	if (!textura.loadFromFile("resources/Sprite_prob.png"))
		printf("No se ha podido encontrar textura");

	//estado = 0;
	//estados.push_back(EstadoApuntar());
	//posiciones en las que se generaran las bolas al inicar/reiniciar o al volver a la mesa
	positions.push_back(sf::Vector2f(590.0, 190.0));
	positions.push_back(sf::Vector2f(250.0, 190.0));
	positions.push_back(sf::Vector2f(202.0, 165.0));
	positions.push_back(sf::Vector2f(202.0, 190.0));
	positions.push_back(sf::Vector2f(202.0, 215.0));
	positions.push_back(sf::Vector2f(226.0, 175.0));
	positions.push_back(sf::Vector2f(226.0, 205.0));
	positions.push_back(sf::Vector2f(178.0, 175.0));
	positions.push_back(sf::Vector2f(178.0, 205.0));
	positions.push_back(sf::Vector2f(154.0, 190.0));

	paredes.push_back(sf::RectangleShape(sf::Vector2f(325, 20)));
	paredes.push_back(sf::RectangleShape(sf::Vector2f(325, 20)));
	paredes.push_back(sf::RectangleShape(sf::Vector2f(325, 20)));
	paredes.push_back(sf::RectangleShape(sf::Vector2f(325, 20)));
	paredes.push_back(sf::RectangleShape(sf::Vector2f(20, 293)));
	paredes.push_back(sf::RectangleShape(sf::Vector2f(20, 293)));

	paredes[0].setPosition(sf::Vector2f(215, 14));
	paredes[1].setPosition(sf::Vector2f(584, 14));
	paredes[2].setPosition(sf::Vector2f(215, 368));
	paredes[3].setPosition(sf::Vector2f(584, 368));
	paredes[4].setPosition(sf::Vector2f(778, 190));
	paredes[5].setPosition(sf::Vector2f(20, 190));

	for (unsigned int i = 0; i < paredes.size(); i++)
	{
		paredes[i].setOrigin(paredes[i].getSize().x / 2, paredes[i].getSize().y / 2);
	}

	troneras.push_back(sf::CircleShape(17));
	troneras.push_back(sf::CircleShape(17));
	troneras.push_back(sf::CircleShape(17));
	troneras.push_back(sf::CircleShape(17));
	troneras.push_back(sf::CircleShape(20));
	troneras.push_back(sf::CircleShape(20));

	troneras[0].setPosition(sf::Vector2f(26, 20));
	troneras[1].setPosition(sf::Vector2f(770, 20));
	troneras[2].setPosition(sf::Vector2f(770, 360));
	troneras[3].setPosition(sf::Vector2f(26, 360));
	troneras[4].setPosition(sf::Vector2f(400, 5));
	troneras[5].setPosition(sf::Vector2f(400, 375));

	for (unsigned int i = 0; i < troneras.size(); i++)
	{
		troneras[i].setOrigin(troneras[i].getRadius(), troneras[i].getRadius());
	}

	generaBolas();
	Jugador::Instance()->setPointer(textura);
	debug = false;
	//Mapa::Instance()->setValues();

	//TODO: cambiar por 45?
	Abaco pieza;
	sf::RectangleShape sprite;
	for (int i = 0; i < 50; i++)
	{
		//genera la barras
		if ((i + 1) % 5 != 0)
		{
			sprite.setSize(sf::Vector2f(5, 10));
			sprite.setFillColor(sf::Color::Red);
			sprite.setPosition(290 + i * 10, 500);
			pieza.setPosPR(sf::Vector2(290.f + i * 10, 500.f));
			pieza.setPosSg(sf::Vector2f(290.f + i * 10, 500.f));
		}
		else
		{
			sprite.setSize(sf::Vector2f(5, 15));
			sprite.setFillColor(sf::Color::Blue);
			sprite.setPosition(290 + i * 10, 495);
			pieza.setPosPR(sf::Vector2(290.f + i * 10, 495.f));
			pieza.setPosSg(sf::Vector2f(290.f + i * 10, 495.f));
		}
		pieza.sprite = sprite;
		abaco.push_back(pieza);
		EstadoAnimacionAbaco::Instancia()->piezas.push_back(&abaco.back());
	}
}

Juego::Juego()
{
	//ctor
}

Juego::~Juego()
{

	//dtor
}
