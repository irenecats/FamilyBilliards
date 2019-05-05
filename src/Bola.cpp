#include "Bola.h"

Bola::Bola(int id,sf::Texture&  text, std::vector<sf::Vector2f> positions)
{
    ID = id;

    sprite.setTexture(text);
    sprite.setTextureRect(sf::IntRect(21*(id+1),0,21,21));
    sprite.setOrigin(21/2 , 21/2);

    sf::Vector2f pos = positions[ID];

    posicion.setPrimera(pos);
    posicion.setSegunda(pos);
    animado = false;
    caida = false;
    dist = 0;

}
/*
    Si no esta cayendo, disminuyo la velocidad un pocentaje determinado y segun el nuevo valor de velocidad
    calculo la posicion.
    Si esta cayendo, la bola se mueve hacia la izquierda hasta llegar a su posicion final que vendra determinada
    por el numero de bolas que ya han caido.
*/
void Bola::Update(float timeElapsed)
{
    //std::cout<<"velocidad "<<ID<<" "<<velocidad.x<<" - "<<velocidad.y<<std::endl;
    if(!animado){
        if((velocidad.x>0 && velocidad.x<0.001) || (velocidad.x<0 && velocidad.x>-0.001)){
            velocidad.x = 0;
        }
        else
        {
                velocidad.x-=velocidad.x*0.01f;

        }

        if((velocidad.y>0 && velocidad.y<0.001) || (velocidad.y<0 && velocidad.y>-0.001)){
            velocidad.y = 0;
        }
        else
        {
                velocidad.y-=velocidad.y*0.01f;

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


/*
    En caso de que la bola debido a las colisiones supere el maximo
     de velocidad permitido, la velocidad sera la maxima.
     Por otro lado, si la velocidad es demasiado pequeña esta se volvera cero.
*/
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

void Bola::calcDistancia(sf::Vector2f blanca){

    sf::Vector2f  vect((posicion.getSegunda().x-blanca.x),(posicion.getSegunda().y-blanca.y));

    dist = sqrt((vect.x*vect.x) + (vect.y*vect.y));
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

}

void Bola::terminarAnimacion(){
    animado = false;
    caida = false;
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


float Bola::getDist(){
    return dist;
}

sf::Vector2f Bola::getSprite()
{
    return sprite.getPosition();
}

Bola::Bola(){}

Bola::~Bola()
{
    //dtor
}
