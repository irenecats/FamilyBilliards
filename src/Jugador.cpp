#include "Jugador.h"
Jugador* Jugador::instancia = 0;
Jugador* Jugador::Instance()
{

    if(instancia == 0)
    {
        instancia = new Jugador;
    }

    return instancia;
}

void Jugador::Update(float timeElapsed)
{
    sf::Vector2f movimiento(0.f,0.f);
    float   vel = 0;
    bool    meMuevo = true;
    if(Juego::Instance()->getEstado() != 0)
    {
        meMuevo = false;
    }
    if(meMuevo)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
        {
            vel = 0.2f;
        }
        else
        {
            vel = 0.06f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            movimiento.y=-vel;
            //movimiento.y = -1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            movimiento.y=vel;
            //movimiento.y = 1;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            movimiento.x=-vel;
            //movimiento.x = -1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            movimiento.x=vel;
            //movimiento.x = 1;
        }
    }

    velocidad = movimiento;

    posicion.setPrimera(posicion.getSegunda());

    //std::cout<<"POS "<<pos<<std::endl;

    posicion.setSegunda(sf::Vector2f(posicion.getPrimera().x+movimiento.x*timeElapsed,posicion.getPrimera().y+movimiento.y*timeElapsed));
    /*
     std::cout<<"Primera pos:"<<posicion.getPrimera().x<<" - "<<posicion.getPrimera().y<<std::endl;
     std::cout<<"Segunda pos:"<<posicion.getSegunda().x<<" - "<<posicion.getSegunda().y<<std::endl;*/
    // std::cout<<"velocidad "<<velocidad.x<<" - "<<velocidad.y<<std::endl;

    //pointer.move(0,);
}

void Jugador::setPointer(sf::Texture& text)
{

    pointer.setTexture(text);

    pointer.setTextureRect(sf::IntRect(0,0,21.0,21.0));
    pointer.setOrigin(20/2 , 10);
    sf::Vector2f pos(399.0,190.0);
    pointer.setPosition(pos.x,pos.y);
    posicion.setPrimera(pos);
    posicion.setSegunda(pos);
    velocidad = sf::Vector2f(0.f,0.f);
}

void Jugador::Render(sf::RenderWindow& window, float percentTick)
{

    float pointerX = posicion.getPrimera().x*(1-percentTick) + posicion.getSegunda().x*percentTick;
    float pointerY = posicion.getPrimera().y*(1-percentTick) + posicion.getSegunda().y*percentTick;
    pointer.setPosition(pointerX, pointerY);
    window.draw(pointer);
}

sf::Vector2f Jugador::getPosition(){
    return  posicion.getSegunda();
}

void    Jugador::apuntado(sf::Vector2f blanca,sf::Vector2f menor){
    sf::Vector2f vect(menor.x-blanca.x, menor.y-blanca.y);;

    float angulo = atan2(vect.y,vect.x);
    float mod = sqrt((vect.x*vect.x)+(vect.y*vect.y));
    std::cout<<"POS Blanca: "<<blanca.x<<" - "<<blanca.y<<std::endl;
    std::cout<<"POS Menor : "<<menor.x<<" - "<<menor.y<<std::endl;
    vect = vect/mod;
    vect*=50.f;
    std::cout<<"Vector :"<<vect.x<<" - "<<vect.y<<std::endl;
    posicion.setPrimera(sf::Vector2f(blanca.x + vect.x, blanca.y + vect.y));
    posicion.setSegunda(sf::Vector2f(blanca.x + vect.x,blanca.y + vect.y));
    //bolas[0].setVelocidad(sf::Vector2f(vel*cos(angulo),vel*sin(angulo)));


     //std::cout<<"Angulo"<<(angulo* 180 / 3.14159265)<<std::endl;
     //std::cout<<"cos "<<cos(angulo)<<" sin "<<sin(angulo)<<std::endl;
}

Jugador::Jugador()
{
    //ctor
}

Jugador::~Jugador()
{
    //dtor
}
