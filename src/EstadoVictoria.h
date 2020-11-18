#pragma once
#include <Estado.h>

class EstadoVictoria : public Estado
{
public:
	void Inicializar();

	void ManejarEventos(sf::Event event);
	void Update(float timeElapsed);
	void Render(float percentick);

	static EstadoVictoria* Instancia()
	{
		return &instancia;
	}

protected:
	EstadoVictoria() {};

private:
	static EstadoVictoria instancia;
};
