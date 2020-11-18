#pragma once
#include <Estado.h>

class EstadoApuntar : public Estado
{
public:
	void Inicializar();

	void ManejarEventos(sf::Event event);
	void Update(float timeElapsed);
	void Render(float percentick);

	static EstadoApuntar* Instancia()
	{
		return &instancia;
	}

protected:
	EstadoApuntar() {};

private:
	static EstadoApuntar instancia;
};
