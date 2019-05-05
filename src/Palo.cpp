#include "Palo.h"


Palo::Palo(sf::Texture& text)
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
/*
    Permite que el palo pueda moverse de un lado a otro de la pantalla
    para simular el apuntado.
    Una vez se haya decidido apuntar, el palo se quedara quieto unos segundos
    y efectuara el golpe de la bola al finalizar el recorrido.
*/
void Palo::Update(float timeElapsed, int estado)
{
    float   movimiento=0;

    if(estado == 1)
    {
        if(paloPos.getPrimera().x>=42.5 && dir == false && paloPos.getPrimera().x<670)
        {
            movimiento = 0.5f;

        }
        else if(paloPos.getPrimera().x>=670 && dir == false)
        {
            dir=true;
        }
        if(paloPos.getPrimera().x>42.5  && dir == true)
        {
            movimiento = -0.5f;

        }
        else if(paloPos.getPrimera().x<=42.5 && dir == true)
        {
            movimiento = 0.5f;
            dir=false;
        }
    }
    if(estado == 2 && cont>700)
    {
        if(paloPos.getPrimera().x>42.5  && dir == true)
        {
            movimiento = -1.f;

        }
        else if(paloPos.getPrimera().x<=42.5 && dir == true)
        {
            dir=false;
            terminado=true;
            calculoVelocidad();

        }


    }
    else if(estado == 2 && cont<700)
    {
        cont+=timeElapsed;
    }

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

    paloPos.setSegunda(sf::Vector2f(pos,paloPos.getPrimera().y));

}

void Palo::Render(sf::RenderWindow& window, float percentTick)
{
    float paloX = paloPos.getPrimera().x*(1-percentTick) + paloPos.getSegunda().x*percentTick;
    palo.setPosition(paloX, paloPos.getPrimera().y);
    window.draw(palo);
}

void Palo::tiroBola()
{
    dir = true;
    //terminado=false;
    cont = 0;
    posPulsado = palo.getPosition().x;
}
/*
    Normalizo la posicion actual del palo para obtener un valor de
    velocidad entre 0.1 y 0.4
*/
void Palo::calculoVelocidad(){
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

            posNorm = (posNorm-42.5)/627.5;
            float vel = (0.3*posNorm) + 0.1;

            posPulsado = 0;
            Juego::Instance()->tiraBola(vel);
}

bool Palo::getTerminado(){
    return terminado;
}

void Palo::setTerminado(bool val){
    terminado = val;
}


Palo::Palo()
{
    //ctor
}

Palo::~Palo()
{
    //dtor
}
