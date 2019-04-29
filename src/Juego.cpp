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

    sf::View pantalla(sf::FloatRect(0, 0, 800.f, 600.f));
    sf::View mapa(sf::FloatRect(0,0,100,100));
    mapa.setViewport(sf::FloatRect(0.25, 0.75, 0.5, 0.25));


    sf::CircleShape circulo(1);
    sf::CircleShape circulo2(1);
    sf::CircleShape circulo3(1);
    sf::CircleShape circulo4(1);
    circulo2.setPosition(95,0);
    circulo3.setPosition(95,50);
    circulo4.setPosition(0,50);
    std::cout<<circulo.getPosition().x<<" - "<<circulo.getPosition().y<<std::endl;

    circulo.setFillColor(sf::Color::Red);
    circulo2.setFillColor(sf::Color::Red);
    circulo3.setFillColor(sf::Color::Red);
    circulo4.setFillColor(sf::Color::Red);



    sf::RenderWindow app(sf::VideoMode(800, 600), "Family Billiards");
    app.setFramerateLimit(60);


    printf("Inicializo variables de juego\n");
    //Inicializo
    if (!textura.loadFromFile("resources/Sprite_prob.png"))
        printf("No se ha podido encontrar textura");

    sf::Sprite fondo(textura);
    fondo.setTextureRect(sf::IntRect(0,40.0,800.0,600.0));

    estado = 0;

    positions.push_back(sf::Vector2f(590.0,190.0));
    positions.push_back(sf::Vector2f(250.0,190.0));
    positions.push_back(sf::Vector2f(202.0,165.0));
    positions.push_back(sf::Vector2f(202.0,190.0));
    positions.push_back(sf::Vector2f(202.0,215.0));
    positions.push_back(sf::Vector2f(226.0,175.0));
    positions.push_back(sf::Vector2f(226.0,205.0));
    positions.push_back(sf::Vector2f(178.0,175.0));
    positions.push_back(sf::Vector2f(178.0,205.0));
    positions.push_back(sf::Vector2f(154.0,190.0));
    //Meter mas para las posiciones extra?


    paredes.push_back(sf::RectangleShape(sf::Vector2f(325,20)));
    paredes.push_back(sf::RectangleShape(sf::Vector2f(325,20)));
    paredes.push_back(sf::RectangleShape(sf::Vector2f(325,20)));

    paredes.push_back(sf::RectangleShape(sf::Vector2f(325,20)));

    paredes.push_back(sf::RectangleShape(sf::Vector2f(20,293)));
    paredes.push_back(sf::RectangleShape(sf::Vector2f(20,293)));

    paredes[0].setPosition(sf::Vector2f(215,14));
    paredes[1].setPosition(sf::Vector2f(584,14));
    paredes[2].setPosition(sf::Vector2f(215,368));


    paredes[3].setPosition(sf::Vector2f(584,368));

    paredes[4].setPosition(sf::Vector2f(778,190));
    paredes[5].setPosition(sf::Vector2f(20,190));

    for(int i=0; i<paredes.size(); i++)
    {
        paredes[i].setOrigin(paredes[i].getSize().x/2,paredes[i].getSize().y/2);
    }

    troneras.push_back(sf::CircleShape(17));
    troneras.push_back(sf::CircleShape(17));
    troneras.push_back(sf::CircleShape(17));
    troneras.push_back(sf::CircleShape(17));
    troneras.push_back(sf::CircleShape(20));
    troneras.push_back(sf::CircleShape(20));

    troneras[0].setPosition(sf::Vector2f(26,20));
    troneras[1].setPosition(sf::Vector2f(770,20));

    troneras[2].setPosition(sf::Vector2f(770,360));
    troneras[3].setPosition(sf::Vector2f(26,360));
    troneras[4].setPosition(sf::Vector2f(400,5));
    troneras[5].setPosition(sf::Vector2f(400,375));

    for(int i=0; i<troneras.size(); i++)
    {
        troneras[i].setOrigin(troneras[i].getRadius(),troneras[i].getRadius());
    }

    caidasAux = 0;
    generaBolas();

    Jugador::Instance()->setPointer(textura);
    Palo   palo(textura);
    abaco = Abaco();

    primera = nullptr;



    while (app.isOpen())
    {
        sf::Event event;
        //Proceso los eventos
        while (app.pollEvent(event))
        {
            // si cierro la ventana o pulso escape exit
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
                    printf("Estado 0: moviendo pointer\n");
                    estado = 0;
                }
                else if( estado == 0 && event.key.code == sf::Keyboard::Space)
                {
                    printf("Estado 1: animacion pre-tiro\n");
                    estado = 1;
                    palo.setTerminado(false);
                }
                else if(estado == 1 && event.key.code == sf::Keyboard::Space)
                {
                    printf("Estado 2: bolas en movimiento\n");
                    palo.tiroBola();
                    estado = 2;
                }
                else if(event.key.code == sf::Keyboard::R)
                {
//                    Reinicia();
                }
            }
        }

        if(relojUpdate.getElapsedTime().asMilliseconds() > UPDATE_TIME)
        {

            float timeElapsed = relojUpdate.restart().asMilliseconds();;
            //Llamo a los updates

            Jugador::Instance()->Update(timeElapsed);
            for(int i=0; i<bolas.size(); i++)
            {
                bolas[i].Update(timeElapsed);
            }
            palo.Update(timeElapsed, estado);

            //solo cuando las bolas empiezan a moverse detecto si se han parado y sus colisiones
            if(estado == 2 && palo.getTerminado() &&  bolasParadas())
            {
                printf("EH\n");
                if(caidas.size()>=1)
                {

                    manejaAnimaciones();
                }
                else
                {
                    if(bolas.size()>2)
                    {
                        estado=0;
                        Jugador::Instance()->apuntado(bolas[0].getPosSg(),bolas[1].getPosSg());
                    }
                }
            }
            if(estado==3)
            {
                abaco.Update(timeElapsed);
                if(abaco.getAnimando()==1)
                {
                    abaco.setAnimando(-1);
                    Jugador::Instance()->addPuntuacion(puntos);
                    estado=0;
                }
            }
            //std::cout<<"puntos "<<Jugador::Instance()->getPuntuacion()<<std::endl;
            colisionBolas();
            colisionParedes();
            colisionTronera();
        }

        float percentick = std::min(1.f,(float)relojUpdate.getElapsedTime().asMilliseconds()/UPDATE_TIME);
        app.setView(pantalla);
        // Clear screen
        app.clear();
        app.draw(fondo);
        if(estado == 0 && palo.getTerminado())
        {
            palo.setTerminado(false);
        }
        //si la animación ha terminado no dibujo el palo
        if(!palo.getTerminado())
        {
            palo.Render(app,percentick);
        }

        //Renders interpolados
        for(int i=0; i<bolas.size(); i++)
        {
            if(!bolas[i].getCaida())
                bolas[i].Render(app,percentick);
        }

        for(int i=0; i<barra.size(); i++)
        {
            barra[i].Render(app,percentick);
        }
        //Cuando las bolas están en movimiento no se dibuja el pointer
        if(!palo.getTerminado())
        {
            Jugador::Instance()->Render(app,percentick);
        }
        abaco.Render(app,percentick);

        for(int i=0; i<paredes.size(); i++)
        {
            app.draw(paredes[i]);
        }


        for(int i=0; i<troneras.size(); i++)
        {
            app.draw(troneras[i]);
        }

        app.setView(mapa);
        app.draw(circulo);
        app.draw(circulo2);
        app.draw(circulo3);
        app.draw(circulo4);


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
        bolas.push_back(Bola(i,textura,positions));
    }
}

void Juego::colisionParedes()
{
    for(int i=0; i<paredes.size(); i++)
    {
        for(int j=0; j<bolas.size(); j++)
        {
            if(paredes[i].getGlobalBounds().intersects(bolas[j].getGlobalBounds()))
            {
                printf("colisiona\n");
                sf::Vector2f vel = bolas[j].getVelocidad();
                if(i==1 || i==0)
                {
                    bolas[j].setPosSg(sf::Vector2f(bolas[j].getPosSg().x,paredes[i].getPosition().y+22));
                    vel.y=-vel.y;
                    bolas[j].setVelocidad(vel);

                }
                else if(i==2 || i==3)
                {
                    bolas[j].setPosSg(sf::Vector2f(bolas[j].getPosSg().x,paredes[i].getPosition().y-22));
                    vel.y=-vel.y;
                    bolas[j].setVelocidad(vel);

                }
                else if(i==4)
                {
                    bolas[j].setPosSg(sf::Vector2f(paredes[i].getPosition().x-22,bolas[j].getPosSg().y));
                    vel.x=-vel.x;
                    bolas[j].setVelocidad(vel);

                }
                else
                {
                    bolas[j].setPosSg(sf::Vector2f(paredes[i].getPosition().x+22,bolas[j].getPosSg().y));
                    vel.x=-vel.x;
                    bolas[j].setVelocidad(vel);

                }
            }
        }
    }

}

void Juego::colisionTronera()
{
    for(int i=0; i<troneras.size(); i++)
    {
        for(int j=0; j<bolas.size(); j++)
        {
            if(!bolas[j].getCaida())
            {
                sf::Vector2f  posB1=troneras[i].getPosition();
                sf::Vector2f  posB2=bolas[j].getPosSg();
                sf::Vector2f  vecB1B2((posB1.x-posB2.x),(posB1.y-posB2.y));

                float separacion = sqrt((vecB1B2.x*vecB1B2.x) + (vecB1B2.y*vecB1B2.y));

                if(separacion <= (troneras[i].getRadius()))
                {
                    printf("ha caido\n");
                    std::cout<<"separacion "<<separacion<<std::endl;
                    bolas[j].setVelocidad(sf::Vector2f(0,0));
                    bolas[j].setCaida(true);
                    caidas.push_back(&bolas[j]);
                }
            }
        }
    }
}

void Juego::colisionBolas()
{
    for(int i=0; i<bolas.size(); i++)
    {
        for(int j=0; j<bolas.size(); j++)
        {

            if(i!=j && abs(bolas[i].getSprite().x)!=0.f && !bolas[i].getCaida() && !bolas[j].getCaida())
            {
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
        if(bola1.getID()==0 && !primera)
        {
            std::cout<<"Primera bola: "<<bola2.getID()<<std::endl;
            primera = &bola2;
        }
        std::cout<<"Vel "<<bola1.getID()<<" :"<<bola1.getVelocidad().x<<" - "<<bola1.getVelocidad().y<<std::endl;
        std::cout<<"Vel "<<bola2.getID()<<" :"<<bola2.getVelocidad().x<<" - "<<bola2.getVelocidad().y<<std::endl;
        //printf("Chocan\n");

        float interseccion = (separacion - 21)*0.5;
        posB1.x-= (interseccion * vecB1B2.x)/separacion;
        posB1.y-= (interseccion * vecB1B2.y)/separacion;
        posB2.x+= (interseccion * vecB1B2.x)/separacion;
        posB2.y+= (interseccion * vecB1B2.y)/separacion;

        bola1.setPosSg(posB1);
        bola2.setPosSg(posB2);

        //normal
        sf::Vector2f normal=sf::Vector2f((posB2.x-posB1.x),(posB2.y-posB1.y))/separacion;


        sf::Vector2f b1vel = bola1.getVelocidad();
        sf::Vector2f b2vel = bola2.getVelocidad();

        float p = 2.0 * (normal.x * (b1vel.x-b2vel.x) + normal.y * (b1vel.y-b2vel.y)) / 4;


        bola1.setVelocidad(sf::Vector2f(b1vel.x - p *2* normal.x , b1vel.y - p *2* normal.y));
        bola2.setVelocidad(sf::Vector2f(b2vel.x + p *2* normal.x , b2vel.y + p *2* normal.y));


        std::cout<<"Vel "<<bola1.getID()<<" :"<<bola1.getVelocidad().x<<" - "<<bola1.getVelocidad().y<<std::endl;
        std::cout<<"Vel "<<bola2.getID()<<" :"<<bola2.getVelocidad().x<<" - "<<bola2.getVelocidad().y<<std::endl;
        printf("------ \n");

    }
}

void Juego::tiraBola( float vel)
{

    sf::Vector2f P=Jugador::Instance()->getPosition();
    sf::Vector2f B = bolas[0].getPosSg();

    sf::Vector2f PB(P.x-B.x,P.y-B.y);

    float angulo = atan2(PB.y,PB.x);

    bolas[0].setVelocidad(sf::Vector2f(vel*cos(angulo),vel*sin(angulo)));
    std::cout<<"Vel "<<bolas[0].getID()<<" :"<<bolas[0].getVelocidad().x<<" - "<<bolas[0].getVelocidad().y<<std::endl;

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
    return contr;
}

void Juego::manejaAnimaciones()
{
    if(caidasAux<caidas.size())
    {
        if(!caidas[caidasAux]->getAnimado())
        {
            printf("empieza animacion\n");
            std::cout<<caidasCont<<std::endl;
            caidas[caidasAux]->empezarAnimacion(212+30*caidasCont);

        }
        if(caidas[caidasAux] && caidas[caidasAux]->getPosSg().x<=(212+30*caidasCont) &&  caidas[caidasAux]->getAnimado())
        {

            printf("termina animacion\n");
            caidas[caidasAux]->terminarAnimacion();
            caidas[caidasAux]->setCaida(false);


            if(primera && primera->getID()==bolas[1].getID() && caidas[caidasAux]->getID()==9)
            {
                printf("Has ganado yay!\n");
            }
            else if( primera && primera->getID()==bolas[1].getID() && caidas[caidasAux]->getID()!=0)
            {
                printf("La dejo en el sitio y aumento el contador\n");
                barra.push_back(*caidas[caidasAux]);
                puntos+=caidas[caidasAux]->getID();
                caidasCont++;

            }
            else if((!primera || primera->getID()!=bolas[1].getID()) && caidas[caidasAux]->getID()!=0)
            {
                printf("posiciono la bola\n");
                bool contr = false;
                caidas[caidasAux]->setPosPR(positions[1]);
                caidas[caidasAux]->setPosSg(positions[1]);

                for(int i=1; i<positions.size() && !contr; i++)
                {
                    contr = posValida(positions[i]);
                    if(contr)
                    {
                        caidas[caidasAux]->setPosPR(positions[i]);
                        caidas[caidasAux]->setPosSg(positions[i]);
                    }
                }
            }
            else
            {
                printf("Hola\n");
                caidas[caidasAux]->setPosPR(positions[0]);
                caidas[caidasAux]->setPosSg(positions[0]);
            }
            caidasAux++;
        }

    }
    else
    {
        printf("estoy en el else \n");
        for(int i =0; i<barra.size(); i++)
        {
            printf("1\n");
            for(int j=0; j<bolas.size(); j++)
            {
                printf("2\n");
                if(bolas[j].getID()==barra[i].getID())
                {
                    bolas.erase(bolas.begin()+j);

                }
            }
        }
        caidasAux = 0;

        if( primera && primera->getID()==bolas[1].getID())
        {
            estado = 3;
            abaco.muevePiezas(puntos);
        }
        else
        {
            estado = 0;
        }

        caidas.clear();
        primera=nullptr;
        puntos = 0;
        if(bolas.size()>2)
        {
            Jugador::Instance()->apuntado(bolas[0].getPosSg(),bolas[1].getPosSg());
        }
    }
}

bool Juego::posValida(sf::Vector2f pos)
{

    bool contr = true;

    for(int i=1; i<bolas.size() && contr; i++)
    {

        sf::Vector2f  posBola=bolas[i].getPosSg();
        sf::Vector2f  vecPB((pos.x-posBola.x),(pos.y-posBola.y));

        float separacion = sqrt((vecPB.x*vecPB.x) + (vecPB.y*vecPB.y));

        if(separacion<21)
        {
            contr=false;
        }
    }

    return contr;
}

int Juego::getEstado()
{
    return estado;
}

Juego::Juego()
{
    //ctor
}

Juego::~Juego()
{
    //dtor
}
