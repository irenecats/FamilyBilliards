
#include <Bola.h>
#include <Estado.h>
class EstadoMovBolas : public Estado
{
public:
	void Inicializar();
	void Limpiar();

	void Pausar();
	void Continuar();

	void ManejarEventos(sf::Event event);
	void Update(float timeElapsed);
	void Render(float percentick);

	static EstadoMovBolas* Instancia()
	{
		return &instancia;
	}

protected:
	EstadoMovBolas() {};
	void tiraBola(sf::Vector2f player, sf::Vector2f bola, float vel);
	float calcVel(sf::Vector2f posicion);
	void colisionParedes();
	void colisionTronera();
	void colisionBolas();
	void choque(Bola& bola1, Bola& bola2);
	bool comprobarParadas();

private:
	static EstadoMovBolas instancia;
	bool dir { false };
	Bola* primera { nullptr };
};
