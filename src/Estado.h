#pragma once
#include <SFML/Graphics.hpp>

class Estado
{
public:
	virtual void Inicializar() = 0;

	virtual void ManejarEventos(sf::Event event) = 0;
	virtual void Update(float timeElapsed) = 0;
	virtual void Render(float percentick) = 0;

protected:
	Estado() {};
};
