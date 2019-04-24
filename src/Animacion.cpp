#include "Animacion.h"

Animacion::Animacion(sf::Texture& text)
{
    palo.setTexture(text);
    palo.setTextureRect(sf::IntRect(43.0,22.0,800.0,14.0));
    //ctor
    sf::Vector2f pos(42.5,570.0);
    paloPos.setPrimera(pos);
    paloPos.setSegunda(pos);
    dir=false;
    terminado=false;
    cont=0;
}

Animacion::~Animacion()
{
    //dtor
}

void Animacion::Update(float timeElapsed, int estado)
{
    float   vel = 0;
    float   movimiento=0;

    if(estado == 1)
    {
        //printf("Animo\n");
        if(paloPos.getPrimera().x>=42.5 && dir == false && paloPos.getPrimera().x<670)
        {
            //printf("1\n");
            //std::cout<<"DIR: "<<dir<<std::endl;
            movimiento = 0.5f;

        }
        else if(paloPos.getPrimera().x>=670 && dir == false)
        {
            //printf("2\n");
            //std::cout<<"DIR: "<<dir<<std::endl;
            //movimiento = -0.5f;
            dir=true;
        }
        if(paloPos.getPrimera().x>42.5  && dir == true)
        {
            //printf("1\n");
            //std::cout<<"DIR: "<<dir<<std::endl;
            movimiento = -0.5f;

        }
        else if(paloPos.getPrimera().x<=42.5 && dir == true)
        {
            //printf("2\n");
            //std::cout<<"DIR: "<<dir<<std::endl;
            movimiento = 0.5f;
            dir=false;
        }
    }
    if(estado == 2 && cont>700)
    {
        if(paloPos.getPrimera().x>42.5  && dir == true)
        {
            //printf("1\n");
            //std::cout<<"DIR: "<<dir<<std::endl;
            movimiento = -1.f;

        }
        else if(paloPos.getPrimera().x<=42.5 && dir == true)
        {
            printf("ESTOY AQUI\n");
            //tiroBola();
            dir=false;
            terminado=true;
            calculoVelocidad();

        }


    }
    else if(estado == 2 && cont<700)
    {
        //std::cout<<"Cont: "<<cont<<std::endl;
        cont+=timeElapsed;
    }
    //printf("----\n");




    paloPos.setPrimera(paloPos.getSegunda());

    float pos = paloPos.getPrimera().x+movimiento*timeElapsed;

    if(pos<42.5)
    {
        pos=42.5;
    }
    else if(pos>670)
    {
        pos=670;
    }
    //std::cout<<"POS "<<pos<<std::endl;

    paloPos.setSegunda(sf::Vector2f(pos,paloPos.getPrimera().y));

    //posicion.setPrimera(posicion.getSegunda());

    //posicion.setSegunda(sf::Vector2f(posicion.getPrimera().x+velocidad.x*timeElapsed,posicion.getPrimera().y + velocidad.y*timeElapsed));


}

void Animacion::RenderPalo(sf::RenderWindow& window, float percentTick)
{
    float paloX = paloPos.getPrimera().x*(1-percentTick) + paloPos.getSegunda().x*percentTick;
    palo.setPosition(paloX, paloPos.getPrimera().y);
    window.draw(palo);
}

void Animacion::tiroBola()
{
    dir = true;
    terminado=false;
    cont = 0;
    posPulsado = palo.getPosition().x;
    //paloPos.setSegunda(palo.getPosition());


}

void Animacion::calculoVelocidad(){
    float posNorm = 0;
            if(palo.getPosition().x<42.5)
            {
                posNorm = 42.5;
            }
            else if(palo.getPosition().x>670)
            {
                posNorm = 670;
            }
            else
            {
                posNorm =posPulsado;
            }
            std::cout<<"POS TIRO "<<posNorm<<std::endl;
            posNorm = (posNorm-42.5)/627.5;
            float vel = (0.4*posNorm) + 0.1;
            std::cout<<"POS TIRO "<<posNorm<<std::endl;
            std::cout<<"VEL TIRO "<<vel<<std::endl;
            posPulsado = 0;
            Juego::Instance()->tiraBola(vel);
}

bool Animacion::getTerminado(){
    return terminado;
}
