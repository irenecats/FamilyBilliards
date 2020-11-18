#include <EstadoVictoria.h>
#include <Juego.h>
EstadoVictoria EstadoVictoria::instancia;
void EstadoVictoria::Inicializar()
{

}

void EstadoVictoria::setFuente(){
	if (!fuente.loadFromFile("resources/VCR_OSD_MONO.ttf"))
	{
		std::cerr << "Error al cargar la fuente\n"
				  << std::endl;
		exit(0);
	}
	textoVictoria.setFillColor(sf::Color::White);
	textoVictoria.setFont(fuente);
	textoVictoria.setCharacterSize(50);
	textoVictoria.setString("Victoria!");
	textoVictoria.setPosition(250, 200);
	
	textoReset.setFillColor(sf::Color::White);
	textoReset.setFont(fuente);
	textoReset.setCharacterSize(50);
	textoReset.setString("Pulsa enter para reiniciar");
	textoReset.setPosition(30, 350);
}

void EstadoVictoria::Render(float percentick){
	Juego::Instance()->Instance()->ventana.draw(textoVictoria);
	Juego::Instance()->Instance()->ventana.draw(textoReset);
}
void EstadoVictoria::ManejarEventos(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
	{
		Juego::Instance()->ventana.close();
	}
	if(event.key.code == sf::Keyboard::Enter){
		Juego::Instance()->Reinicia();
	}
}

void EstadoVictoria::Update(float timeElapsed)
{
}