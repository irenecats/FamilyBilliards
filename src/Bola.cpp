#include "Bola.h"

Bola::Bola(int id,sf::Texture&  text, std::vector<sf::Vector2f> positions)
{
    ID = id;

    sprite.setTexture(text);
    sprite.setTextureRect(sf::IntRect(21*(id+1),0,21,21));
    sprite.setOrigin(21/2 , 21/2);

    //sprite.set
    sf::Vector2f pos = positions[ID];

    posicion.setPrimera(pos);
    posicion.setSegunda(pos);
    animado = false;
    caida = false;
//    caidas = 0;
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
    if(!animado){

        if(abs(velocidad.y)<1.f && ID==2 )
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
        if(abs(velocidad.x)<1.f && ID==2)
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

        if((velocidad.x>0 && velocidad.x<0.001) || (velocidad.x<0 && velocidad.x>-0.001)){
            velocidad.x = 0;
        }
        else
        {
                velocidad.x-=velocidad.x*0.03f;

        }

        if((velocidad.y>0 && velocidad.y<0.001) || (velocidad.y<0 && velocidad.y>-0.001)){
            velocidad.y = 0;
        }
        else
        {
                velocidad.y-=velocidad.y*0.03f;

        }
        controlaVelocidad();
    }
    else{
        if(posicion.getSegunda().x<posfinal){
            velocidad.x = 0;
            posicion.setSegunda(sf::Vector2f(posfinal,posicion.getPrimera().y));
        }
        else{
        velocidad.x = -0.1;
        }
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


bool Bola::heParado()
{
    bool parado = false;
    if(velocidad.x==0 && velocidad.y==0)
    {
        parado = true;
    }
    return parado;
}

void Bola::empezarAnimacion(float pos){
    posicion.setPrimera(sf::Vector2f(590,400));
    posicion.setSegunda(sf::Vector2f(590,400));
    animado = true;
    posfinal = pos;
    caida = false;
}

void Bola::terminarAnimacion(){
    animado = false;
    posfinal = 0;
}

sf::Vector2f Bola::getPosSg()
{
    return posicion.getSegunda();
}
sf::Vector2f Bola::getPosPr()
{
    return posicion.getPrimera();
}
sf::Vector2f Bola::getVelocidad()
{
    return velocidad;
}

int Bola::getID()
{
    return ID;
}
bool Bola::getAnimado(){
    return animado;
}

void Bola::setPosSg(sf::Vector2f pos)
{
    posicion.setSegunda(pos);
}

void Bola::setPosPR(sf::Vector2f pos)
{
    posicion.setPrimera(pos);
}

void Bola::setPos(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}

void Bola::setVelocidad(sf::Vector2f vel)
{
    velocidad = vel;
    controlaVelocidad();
}

void Bola::setCaida(bool val){
    caida=val;
}

bool Bola::getCaida(){
    return caida;
}

sf::FloatRect Bola::getGlobalBounds(){
    return sprite.getGlobalBounds();
}

void Bola::controlaVelocidad(){
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

        if((velocidad.y>0 && velocidad.y<0.001) || (velocidad.y<0 && velocidad.y>-0.001)){
            velocidad.y = 0;
        }
}
