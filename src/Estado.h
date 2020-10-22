#pragma once

class Estado
{
public:
	virtual void Inicializar() = 0;
	virtual void Limpiar() = 0;

	virtual void Pausar() = 0;
	virtual void Continuar() = 0;

	virtual void ManejarEventos(sf::Event event) = 0;
	virtual void Update(float timeElapsed) = 0;
	virtual void Render(float percentick) = 0;

	/*void CambiarEstado(Juego* juego, Estado* estado)
	{
		juego->CambiarEstado(estado);
	}
*/
protected:
	Estado() {};
};
