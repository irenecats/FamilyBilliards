#include "Jugador.h"
Jugador* Jugador::instancia = 0;
Jugador* Jugador::Instance()
{

	if (instancia == 0)
	{
		instancia = new Jugador;
	}

	return instancia;
}
/*
    El funcion de las teclas pulsadas el poninter se movera hacia un lado u
    otro pudiendo moverse en diagonal. Además, el pointer no podra superar
    los limites del mesa.

    Si la tecla shift es pulsada, tanto la derecha como la izquierda,
    el pointer se movera a mayor velocidad.
*/
void Jugador::Update(float timeElapsed)
{
	posInitFin.first = posInitFin.second;

	sf::Vector2f pos2(posInitFin.first.x + movimiento.x * timeElapsed, posInitFin.first.y + movimiento.y * timeElapsed);
	if (pos2.x < 45)
	{
		pos2.x = 45;
	}
	else if (pos2.x > 757)
	{
		pos2.x = 757;
	}

	if (pos2.y < 38)
	{
		pos2.y = 38;
	}
	else if (pos2.y > 346)
	{
		pos2.y = 346;
	}

	posInitFin.second = pos2;
}

void Jugador::Render(sf::RenderWindow& ventana, float percentTick)
{
	float pointerX = posInitFin.first.x * (1 - percentTick) + posInitFin.second.x * percentTick;
	float pointerY = posInitFin.first.y * (1 - percentTick) + posInitFin.second.y * percentTick;
	pointer.setPosition(pointerX, pointerY);
	ventana.draw(pointer);
}

void Jugador::RenderPoints(sf::RenderWindow& ventana)
{
	ventana.draw(textoPuntos);
}

void Jugador::setPointer(sf::Texture& text)
{

	pointer.setTexture(text);

	pointer.setTextureRect(sf::IntRect(0, 0, 21.0, 21.0));
	pointer.setOrigin(20 / 2, 10);
	sf::Vector2f pos(399.0, 190.0);
	pointer.setPosition(pos.x, pos.y);
	posInitFin.first = pos;
	posInitFin.second = pos;

	puntuacion = 0;

	if (!fuente.loadFromFile("resources/VCR_OSD_MONO.ttf"))
	{
		std::cerr << "Error al cargar la fuente\n"
				  << std::endl;
		exit(0);
	}
	textoPuntos.setFillColor(sf::Color::White);
	textoPuntos.setFont(fuente);
	textoPuntos.setCharacterSize(20);
	textoPuntos.setString("Pts. " + std::to_string(puntuacion));
	textoPuntos.setPosition(100, 550);
}

/*
    Calculo el vector unitario entre la bola blanca y el puntero y lo multiplico
    por la distancia de separacion que he visto correspondiente
*/

void Jugador::apuntado(sf::Vector2f blanca, sf::Vector2f menor)
{
	sf::Vector2f vect(menor.x - blanca.x, menor.y - blanca.y);

	float mod = sqrt((vect.x * vect.x) + (vect.y * vect.y));

	vect = vect / mod;
	vect *= 50.f;

	posInitFin.first = sf::Vector2f(blanca.x + vect.x, blanca.y + vect.y);
	posInitFin.second = sf::Vector2f(blanca.x + vect.x, blanca.y + vect.y);
}

void Jugador::addPuntuacion(int puntos)
{
	std::cout << "TENGO MAS PUNTOS " << puntos << std::endl;
	puntuacion += puntos;
	std::cout << "Totales " << puntuacion << std::endl;
	textoPuntos.setString("Pts. " + std::to_string(puntuacion));
}

int Jugador::getPuntuacion()
{
	return puntuacion;
}
void Jugador::setPuntuacion(int puntos){
	puntuacion = puntos;
}

sf::Vector2f Jugador::getPos()
{
	return posInitFin.second;
}
sf::Vector2f Jugador::getCurrentPos()
{
	return pointer.getPosition();
}

Jugador::Jugador()
{
	//ctor
}

Jugador::~Jugador()
{
	//dtor
}
