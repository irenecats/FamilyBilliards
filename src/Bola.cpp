#include "Bola.h"

Bola::Bola(int id,sf::Texture&  text)
{
    ID = id;

    sprite.setTexture(text);
    sprite.setTextureRect(sf::IntRect(21*(id+1),0,21,21));
    sprite.setOrigin(21/2 , 21/2);
    //sprite.set
    sf::Vector2f pos;
    switch(ID)
    {
    case 1:
        pos = sf::Vector2f(250.0,180.0);
        break;
    case 2:
        pos = sf::Vector2f(202.0,155.0);
        break;
    case 3:
        pos = sf::Vector2f(202.0,180.0);
        break;
    case 4:
        pos = sf::Vector2f(202.0,205.0);
        break;
    case 5:
        pos = sf::Vector2f(226.0,165.0);
        break;
    case 6:
        pos = sf::Vector2f(226.0,195.0);
        break;
    case 7:
        pos = sf::Vector2f(178.0,165.0);
        break;
    case 8:
        pos = sf::Vector2f(178.0,195.0);
        break;
    case 9:
        pos = sf::Vector2f(154.0,180.0);
        break;
    default:
        pos = sf::Vector2f(590.0,180.0);
        sf::Vertex line[2];
        break;
    }

    posicion.setPrimera(pos);
    posicion.setSegunda(pos);
    // velocidad = sf::Vector2f(0.f,0.f);
    //ctor
}

sf::Vector2f Bola::getSprite()
{
    return sprite.getPosition();
}

Bola::~Bola()
{
    //dtor
}

void Bola::Update(float timeElapsed)
{
    //std::cout<<"velocidad "<<ID<<" "<<velocidad.x<<" - "<<velocidad.y<<std::endl;
    if(abs(velocidad.y)<1.f && ID == -1)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            velocidad.y-=0.05f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            velocidad.y+=0.05f;
        }
    }
    if(abs(velocidad.x)<1.f  && ID == -1)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            velocidad.x-=0.05f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            velocidad.x+=0.05f;
        }
    }
    float max_vel = 0.4;

    if(velocidad.x>max_vel){
        velocidad.x=max_vel;
    }
    else if(velocidad.x<-max_vel){
        velocidad.x=-max_vel;
    }

    if(velocidad.y>max_vel){
        velocidad.y=max_vel;
    }else if(velocidad.y<-max_vel){
        velocidad.y=-max_vel;
    }





    if((velocidad.x>0 && velocidad.x<0.001) || (velocidad.x<0 && velocidad.x>-0.001)){
        velocidad.x = 0;
    }
    else
    {
            velocidad.x-=velocidad.x*0.05f;

    }

    if((velocidad.y>0 && velocidad.y<0.001) || (velocidad.y<0 && velocidad.y>-0.001)){
        velocidad.y = 0;
    }
    else
    {
            velocidad.y-=velocidad.y*0.05f;

    }


    posicion.setPrimera(posicion.getSegunda());
    posicion.setSegunda(sf::Vector2f(posicion.getPrimera().x+velocidad.x*timeElapsed,posicion.getPrimera().y + velocidad.y*timeElapsed));

}

void Bola::Render(sf::RenderWindow& window, float percentTick)
{
    float pointerX = posicion.getPrimera().x*(1-percentTick) + posicion.getSegunda().x*percentTick;
    float pointerY = posicion.getPrimera().y*(1-percentTick) + posicion.getSegunda().y*percentTick;
    sprite.setPosition(pointerX, pointerY);
    window.draw(sprite);
}

sf::Vector2f Bola::getPosSg()
{
    return posicion.getSegunda();
}

sf::Vector2f Bola::getVelocidad()
{
    return velocidad;
}

int Bola::getID()
{
    return ID;
}

void Bola::setPosSg(sf::Vector2f pos)
{
    posicion.setSegunda(pos);
}

void Bola::setPos(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

void Bola::setVelocidad(sf::Vector2f vel)
{
    velocidad = vel;
    printf("Cambio velocidad %i",ID);
    std::cout<<velocidad.x<<" - "<<velocidad.y<<std::endl;
}

bool Bola::heParado()
{
    bool parado = false;
    if(velocidad.x==0 && velocidad.y==0)
    {
        parado = true;
    }
    return parado;
}
