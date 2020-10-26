#pragma once
#include <Estado.h>

class EstadoAnimacionBolas : public Estado
{
public:
	void Inicializar();
	void Limpiar();

	void Pausar();
	void Continuar();

	void ManejarEventos(sf::Event event);
	void Update(float timeElapsed);
	void Render(float percentick);

	static EstadoAnimacionBolas* Instancia()
	{
		return &instancia;
	}

	void addCaidas(std::vector<Bola*> bolas);
	void esValida(Bola* bola);
	sf::Vector2f posValida();

	int primera { -1 };

protected:
	EstadoAnimacionBolas() {};

private:
	std::vector<Bola*> caidas;
	float pause { 0.f };
	unsigned int bolaActual { 0 };
	float posFinal { 0 };
	bool finAnimado { false };
	bool animando { false };
	static EstadoAnimacionBolas instancia;
};
