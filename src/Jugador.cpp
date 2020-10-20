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
	sf::Vector2f movimiento(0.f, 0.f);
	float vel = 0;
	bool meMuevo = true;
	if (Juego::Instance()->getEstado() != 0)
	{
		meMuevo = false;
	}
	if (meMuevo)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			vel = 0.2f;
		}
		else
		{
			vel = 0.06f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			movimiento.y = -vel;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			movimiento.y = vel;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			movimiento.x = -vel;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			movimiento.x = vel;
		}
	}

	posicion.setPrimera(posicion.getSegunda());

	sf::Vector2f pos2(posicion.getPrimera().x + movimiento.x * timeElapsed, posicion.getPrimera().y + movimiento.y * timeElapsed);
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

	//std::cout<<"POS "<<pos<<std::endl;

	posicion.setSegunda(pos2);
}

void Jugador::Render(sf::RenderWindow& window, float percentTick)
{

	float pointerX = posicion.getPrimera().x * (1 - percentTick) + posicion.getSegunda().x * percentTick;
	float pointerY = posicion.getPrimera().y * (1 - percentTick) + posicion.getSegunda().y * percentTick;
	pointer.setPosition(pointerX, pointerY);
	window.draw(pointer);
}

void Jugador::RenderPoints(sf::RenderWindow& window)
{
	window.draw(textoPuntos);
}

void Jugador::setPointer(sf::Texture& text)
{

	pointer.setTexture(text);

	pointer.setTextureRect(sf::IntRect(0, 0, 21.0, 21.0));
	pointer.setOrigin(20 / 2, 10);
	sf::Vector2f pos(399.0, 190.0);
	pointer.setPosition(pos.x, pos.y);
	posicion.setPrimera(pos);
	posicion.setSegunda(pos);
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
	;

	float mod = sqrt((vect.x * vect.x) + (vect.y * vect.y));

	vect = vect / mod;
	vect *= 50.f;

	posicion.setPrimera(sf::Vector2f(blanca.x + vect.x, blanca.y + vect.y));
	posicion.setSegunda(sf::Vector2f(blanca.x + vect.x, blanca.y + vect.y));

	Mapa::Instance()->setAngulo((float)atan2(vect.y, vect.x));
}

void Jugador::addPuntuacion(int puntos)
{
	std::cout << "TENGO MAS PUNTOS " << puntos << std::endl;
	puntuacion += puntos;
	std::cout << "Totales " << puntuacion << std::endl;
	textoPuntos.setString("Pts. " + std::to_string(puntuacion));
}

sf::Vector2f Jugador::getPosition()
{
	return posicion.getSegunda();
}

int Jugador::getPuntuacion()
{
	return puntuacion;
}

void Jugador::setPuntuacion(int val)
{
	puntuacion = val;
	textoPuntos.setString("Pts. " + std::to_string(puntuacion));
}

Jugador::Jugador()
{
	//ctor
}

Jugador::~Jugador()
{
	//dtor
}
