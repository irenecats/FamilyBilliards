#include "Juego.h"


Juego* Juego::instancia = 0;
Juego* Juego::Instance()
{

    if(instancia == 0)
    {
        instancia = new Juego;
    }

    return instancia;
}

void Juego::bucleJuego()
{
    printf("Creo la ventana\n");
    sf::RenderWindow app(sf::VideoMode(800, 600), "Family Billiards");
    app.setFramerateLimit(60);

    sf::Clock relojUpdate;

    printf("Inicializo variables de juego\n");
    //Inicializo
    if (!textura.loadFromFile("resources/Sprite_prob.png"))
        printf("No se ha podido encontrar textura");

    sf::Sprite fondo(textura);
    fondo.setTextureRect(sf::IntRect(0,40.0,800.0,600.0));

    estado = 0;
    generaBolas();

    Jugador::Instance()->setPointer(textura);
    Animacion   animacion(textura);
    float timeElapsed;

    sf::VertexArray lines(sf::LinesStrip, 2);
    // primera = nullptr;


    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        lines[0].position = bolas[1].getSprite();
        lines[1].position = sf::Vector2f(0, 0);

        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                app.close();
            }
            else if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    app.close();
                }
                else if(estado == 1 && (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down
                                        || event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right))
                {
                    //TODO estado == 1 //asi SOLO cambio cuando estoy en la animacion, no durante el tiro
                    printf("Estado 0: moviendo pointer\n");
                    estado = 0;
                }
                else if( estado == 0 && event.key.code == sf::Keyboard::Space)
                {
                    printf("Estado 1: animacion pre-tiro\n");
                    estado = 1;
                }
                else if(estado == 1 && event.key.code == sf::Keyboard::Space)
                {
                    printf("Estado 2: bolas en movimiento\n");
                    animacion.tiroBola();
                    estado = 2;
                }
            }

        }

        if(relojUpdate.getElapsedTime().asMilliseconds() > UPDATE_TIME)
        {

            timeElapsed = relojUpdate.restart().asMilliseconds();;
            //Llamo a los updates

            Jugador::Instance()->Update(timeElapsed);
            for(int i=0; i<bolas.size(); i++)
            {
                bolas[i].Update(timeElapsed);
            }

            animacion.Update(timeElapsed, estado);

            if(estado == 2 && animacion.getTerminado())
            {
                bolasParadas();
            }
            colisionBolas();
        }
        float percentick = std::min(1.f,(float)relojUpdate.getElapsedTime().asMilliseconds()/UPDATE_TIME);

        // Clear screen
        app.clear();
        app.draw(fondo);
        //si la animación ha terminado no dibujo esto
        animacion.RenderPalo(app,percentick);
//        app.draw(palo);

        //Renders interpolados

        for(int i=0; i<bolas.size(); i++)
        {
            bolas[i].Render(app,percentick);
        }
        if(estado != 2)
        {
            Jugador::Instance()->Render(app,percentick);
        }
        // Draw the sprite

        // Update the window
        app.display();
    }
}

void Juego::generaBolas()
{
    //genero 9 bolas
    printf("Genero las bolas\n");
    for(int i=0; i<10; i++)
    {
        bolas.push_back(Bola(i,textura));
    }
}

int Juego::getEstado()
{
    return estado;
}

void Juego::colisionBolas()
{
    for(int i=0; i<bolas.size(); i++)
    {
        for(int j=0; j<bolas.size(); j++)
        {

            if(i!=j && abs(bolas[i].getSprite().x)!=0.f)
            {
//                if(i==0 && !primera){
//                   printf("Dentro\n");
//                   primera = &bolas[j];
//               }

                choque(bolas[i],bolas[j]);
            }
        }
    }
}

void Juego::choque(Bola& bola1, Bola& bola2)
{
    sf::Vector2f  posB1=bola1.getPosSg();
    sf::Vector2f  posB2=bola2.getPosSg();
    sf::Vector2f  vecB1B2((posB1.x-posB2.x),(posB1.y-posB2.y));

    float separacion = sqrt((vecB1B2.x*vecB1B2.x) + (vecB1B2.y*vecB1B2.y));



    if(separacion<21)
    {
        printf("Chocan\n");
        std::cout<<"B1 "<<bola1.getID()<<std::endl;
        std::cout<<"B2 "<<bola2.getID()<<std::endl;
        std::cout<<"pos1: "<<posB1.x<<" - "<<posB1.y<<std::endl;
        std::cout<<"pos2: "<<posB2.x<<" - "<<posB2.y<<std::endl;
        //std::cout<<"vec12: "<<vecB1B2.x<<" - "<<vecB1B2.y<<std::endl;
        std::cout<<"sep "<<separacion<<std::endl;
        float interseccion = (separacion - 21)*0.5;
        posB1.x-= (interseccion * vecB1B2.x)/separacion;
        posB1.y-= (interseccion * vecB1B2.y)/separacion;
        std::cout<<"int "<<interseccion<<std::endl;
        posB2.x+= (interseccion * vecB1B2.x)/separacion;
        posB2.y+= (interseccion * vecB1B2.y)/separacion;

        bola1.setPosSg(posB1);
        // bola1.setPos(posB1);
        bola2.setPosSg(posB2);
        // bola2.setPos(posB2);
        std::cout<<"pos1: "<<posB1.x<<" - "<<posB1.y<<std::endl;
        std::cout<<"pos2: "<<posB2.x<<" - "<<posB2.y<<std::endl;


        //normal
        sf::Vector2f normal=vecB1B2/separacion;
        //tangente
        sf::Vector2f tang(-normal.y,normal.x);
        //tg*vel
        float vtanb1=bola1.getVelocidad().x*tang.x + bola1.getVelocidad().y*tang.y;
        float vtanb2=bola2.getVelocidad().x*tang.x + bola2.getVelocidad().y*tang.y;
        //nomal*vel
        float vnormb1=bola1.getVelocidad().x*normal.x + bola1.getVelocidad().y*normal.y;
        float vnormb2=bola2.getVelocidad().x*normal.x + bola2.getVelocidad().y*normal.y;

        float m1=(2.f * 2 * vnormb2 )/ 4;
        float m2=(2.f * 2 * vnormb1 )/ 4;

        std::cout<<"Normal "<<normal.x<<" - "<<normal.y<<std::endl;
        std::cout<<"N*     "<<m1<<" - "<<m2<<std::endl;

        std::cout<<"Vel1 "<<bola1.getVelocidad().x<<" - "<<bola1.getVelocidad().y<<std::endl;
        std::cout<<"Vel2 "<<bola2.getVelocidad().x<<" - "<<bola2.getVelocidad().y<<std::endl;

        bola1.setVelocidad(sf::Vector2f(tang.x*vtanb1 + normal.x * m1, tang.y*vtanb1 + normal.y * m1));
        bola2.setVelocidad(sf::Vector2f(tang.x*vtanb2 + normal.x * m2,tang.y*vtanb2 + normal.x * m2));

        std::cout<<"Vel1 "<<bola1.getVelocidad().x<<" - "<<bola1.getVelocidad().y<<std::endl;
        std::cout<<"Vel2 "<<bola2.getVelocidad().x<<" - "<<bola2.getVelocidad().y<<std::endl;

    }
}



void Juego::tiraBola( float vel)
{

    sf::Vector2f P=Jugador::Instance()->getPosition();
    sf::Vector2f B = bolas[0].getPosSg();

    sf::Vector2f PB(P.x-B.x,P.y-B.y);

    float angulo = atan2(PB.y,PB.x);

    bolas[0].setVelocidad(sf::Vector2f(vel*cos(angulo),vel*sin(angulo)));


}

bool Juego::bolasParadas()
{

    bool contr = true;

    for(int i=0; i<bolas.size(); i++)
    {
        if(!bolas[i].heParado())
        {
            contr = false;
        }
    }

    if(contr)
    {
        estado = 0;
        printf("Apunto de nuevo\n");
        /*if(primera)
        {
            std::cout<<"Primera "<<primera->getID()<<std::endl;
        }*/

        if(bolas.size()>2)
        {
            Jugador::Instance()->apuntado(bolas[0].getPosSg(),bolas[1].getPosSg());
        }
/*        if(primera->getID() == bolas[1].getID())
        {
            printf("Valido\n");
        }
        else
        {
            printf("NO valido\n");
        }*/
    }

    return contr;
}

Juego::Juego()
{
    //ctor
}

Juego::~Juego()
{
    //dtor
}
