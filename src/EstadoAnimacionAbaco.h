#pragma once
#include <Abaco.h>
#include <Estado.h>
class EstadoAnimacionAbaco : public Estado
{
public:
	void Inicializar();
	void Limpiar();

	void ManejarEventos(sf::Event event);
	void Update(float timeElapsed);
	void Render(float percentick);

	static EstadoAnimacionAbaco* Instancia()
	{
		return &instancia;
	}

	int nuevosPuntos;
	int puntosActuales;
	bool ganado;
	std::vector<Abaco*> piezas;
	float posFin;
	bool animando;

protected:
	EstadoAnimacionAbaco() {};

private:
	static EstadoAnimacionAbaco instancia;

	void setVelGrupo(int inicio, int fin, float vel);
	void stopGrupo(int inicio, int fin);
};