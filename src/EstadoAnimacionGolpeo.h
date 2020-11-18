#pragma once
#include <Estado.h>

class EstadoAnimacionGolpeo : public Estado
{
public:
	void Inicializar();

	void ManejarEventos(sf::Event event);
	void Update(float timeElapsed);
	void Render(float percentick);

	static EstadoAnimacionGolpeo* Instancia()
	{
		return &instancia;
	}

protected:
	EstadoAnimacionGolpeo() {};

private:
	float pause { 0.f };
	static EstadoAnimacionGolpeo instancia;
};
