
#include <Estado.h>

class EstadoGolpear : public Estado
{
public:
	void Inicializar();
	void Limpiar();

	void Pausar();
	void Continuar();

	void ManejarEventos(sf::Event event);
	void Update(float timeElapsed);
	void Render(float percentick);

	static EstadoGolpear* Instancia()
	{
		return &instancia;
	}

protected:
	EstadoGolpear() {};
	void tiraBola(sf::Vector2f player, sf::Vector2f bola, float vel);
	float calcVel(sf::Vector2f posicion);

private:
	static EstadoGolpear instancia;
	bool dir { false };
};
