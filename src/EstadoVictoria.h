#pragma once
#include <Estado.h>

class EstadoVictoria : public Estado
{
public:
	void Inicializar();

	void ManejarEventos(sf::Event event);
	void Update(float timeElapsed);
	void Render(float percentick);
	void setFuente();

	static EstadoVictoria* Instancia()
	{
		return &instancia;
	}

protected:
	EstadoVictoria() {};

private:
	static EstadoVictoria instancia;
	sf::Text textoVictoria;
	sf::Text textoReset;
	sf::Font fuente;
};
