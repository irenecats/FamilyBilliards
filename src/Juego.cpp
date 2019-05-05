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
    printf("Movimiento con las flechas del teclado\n");
    printf("Shift para que el pointer se mueva mas rapido\n");
    printf("Espacio para preparar golpe y otra vez espacio para golpear\n");
    printf("Espacio para preparar golpe y otra vez espacio para golpear\n");
    printf("---------\n");
    printf("Pulsa R para resetar la partida\n");
    printf("Pulsa D para ver las colisiones\n");



    sf::View pantalla(sf::FloatRect(0, 0, 800.f, 600.f));
    sf::View mapa(sf::FloatRect(0,0,200,60));
    mapa.setViewport(sf::FloatRect(0.25, 0.75, 0.5, 0.20));
    sf::RenderWindow app(sf::VideoMode(800, 600), "Family Billiards");
    app.setFramerateLimit(60);


    //Inicializo
    Palo   palo(textura);
    sf::Sprite fondo(textura);
    fondo.setTextureRect(sf::IntRect(0,40.0,800.0,600.0));
    sf::CircleShape circulo(1);
    sf::CircleShape circulo2(1);
    sf::CircleShape circulo3(1);
    sf::CircleShape circulo4(1);
    circulo2.setPosition(mapa.getSize().x-2,0);
    circulo3.setPosition(mapa.getSize().x-2,mapa.getSize().y-2);
    circulo4.setPosition(0,mapa.getSize().y-2);

    circulo.setFillColor(sf::Color::Red);
    circulo2.setFillColor(sf::Color::Red);
    circulo3.setFillColor(sf::Color::Red);
    circulo4.setFillColor(sf::Color::Red);

    Inicializa();

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
                    Reinicia();
                }
                else if(event.key.code == sf::Keyboard::D)
                {
                    debug = !debug;
                }
            }
        }

        if(relojUpdate.getElapsedTime().asMilliseconds() > UPDATE_TIME)
        {

            float timeElapsed = relojUpdate.restart().asMilliseconds();;
            //Llamo a los updates
            if(estado == 0 && palo.getTerminado())
            {
                palo.setTerminado(false);
            }
            Jugador::Instance()->Update(timeElapsed);
            sf::Vector2f P=Jugador::Instance()->getPosition();
            sf::Vector2f B = bolas[0].getPosSg();

            sf::Vector2f PB(P.x-B.x,P.y-B.y);

            float angulo = atan2(PB.y,PB.x);

            Mapa::Instance()->setAngulo(angulo);
            for(unsigned int i=0; i<bolas.size(); i++)
            {
                bolas[i].Update(timeElapsed);
            }
            palo.Update(timeElapsed, estado);

            if(estado==0){
                for(unsigned int i=0;i<bolas.size();i++){
                    bolas[i].calcDistancia(bolas[0].getPosSg());
                }
            }

            //solo cuando las bolas empiezan a moverse detecto si se han parado
            if(estado == 2 && palo.getTerminado() &&  bolasParadas())
            {
                if(caidas.size()>=1)
                {

                    manejaAnimaciones();
                }
                else
                {
                    printf("estado 2 ELSE\n");
                    if(bolas.size()>1)
                    {
                        estado=0;
                        printf("hey\n");
                        primera = nullptr;
                        Jugador::Instance()->apuntado(bolas[0].getPosSg(),bolas[1].getPosSg());
                    }
                }
            }
            else if(estado == 2){
               // std::cout<<"Estado "<<estado<<std::endl;
                std::cout<<"Palo "<<palo.getTerminado()<<std::endl;
                std::cout<<"Paradas "<<bolasParadas()<<std::endl;
            }
            //durante el estado 3 el abaco es lo unico que se calcula
            if(estado==3)
            {
                abaco.Update(timeElapsed);
                if(abaco.getAnimando()==1)
                {
                    abaco.setAnimando(-1);
                    estado=0;
                }
            }

            colisionBolas();
            colisionParedes();
            colisionTronera();
        }

        float percentick = std::min(1.f,(float)relojUpdate.getElapsedTime().asMilliseconds()/UPDATE_TIME);
        app.setView(pantalla);
        // Clear screen
        app.clear();
        app.draw(fondo);


        //Renders interpolados
        for(unsigned int i=0; i<bolas.size(); i++)
        {
            if(!bolas[i].getCaida() || bolas[i].getAnimado())
                bolas[i].Render(app,percentick);
        }



        for(unsigned int i=0; i<barra.size(); i++)
        {
            barra[i].Render(app,percentick);
        }

        if(estado==0 || estado==1)
        {
            Jugador::Instance()->Render(app,percentick);
        }

        if((estado == 2 && palo.getTerminado()) || estado == 3)
        {
            Jugador::Instance()->RenderPoints(app);
            abaco.Render(app,percentick);
        }

        if(debug)
        {

            for(unsigned int i=0; i<troneras.size(); i++)
            {
                app.draw(troneras[i]);
            }
            for(unsigned int i=0; i<paredes.size(); i++)
            {
                app.draw(paredes[i]);
            }
        }

        if(estado == 0 || estado == 1 || (estado == 2 && !palo.getTerminado()))
        {
            palo.Render(app,percentick);

            app.setView(mapa);
            app.draw(circulo);
            app.draw(circulo2);
            app.draw(circulo3);
            app.draw(circulo4);
            Mapa::Instance()->Render(app,bolas);
        }




        // Update the window
        app.display();
    }
}
/*
    Genera las bolas mandandoles la textura y la posicion en la que se tienen que generar
*/
void Juego::generaBolas()
{
    //genero 9 bolas
    printf("Genero las bolas\n");
    for(int i=0; i<10; i++)
    {
        bolas.push_back(Bola(i,textura,positions));
    }
}

/*
    Detecta la colision y dependiendo del tipo de pared invierte la x o y del vector velocidad de la bola
*/
void Juego::colisionParedes()
{
    for(unsigned int i=0; i<paredes.size(); i++)
    {
        for(unsigned int j=0; j<bolas.size(); j++)
        {
            if(paredes[i].getGlobalBounds().intersects(bolas[j].getGlobalBounds()))
            {
                sf::Vector2f vel = bolas[j].getVelocidad();
                if(i==1 || i==0)
                {
                    bolas[j].setPosSg(sf::Vector2f(bolas[j].getPosSg().x,paredes[i].getPosition().y+23));
                    bolas[j].setPosPR(sf::Vector2f(bolas[j].getPosSg().x,paredes[i].getPosition().y+23));

                    vel.y=-vel.y;
                    bolas[j].setVelocidad(vel);

                }
                else if(i==2 || i==3)
                {
                    bolas[j].setPosSg(sf::Vector2f(bolas[j].getPosSg().x,paredes[i].getPosition().y-23));
                    bolas[j].setPosPR(sf::Vector2f(bolas[j].getPosSg().x,paredes[i].getPosition().y-23));
                    vel.y=-vel.y;
                    bolas[j].setVelocidad(vel);

                }
                else if(i==4)
                {
                    bolas[j].setPosSg(sf::Vector2f(paredes[i].getPosition().x-23,bolas[j].getPosSg().y));
                    bolas[j].setPosPR(sf::Vector2f(paredes[i].getPosition().x-23,bolas[j].getPosSg().y));

                    vel.x=-vel.x;
                    bolas[j].setVelocidad(vel);

                }
                else
                {
                    bolas[j].setPosSg(sf::Vector2f(paredes[i].getPosition().x+23,bolas[j].getPosSg().y));
                    bolas[j].setPosPR(sf::Vector2f(paredes[i].getPosition().x+23,bolas[j].getPosSg().y));
                    vel.x=-vel.x;
                    bolas[j].setVelocidad(vel);

                }
            }
        }
    }

}

/*
    Calcula la distancia entre las troneras y las bolas para detectar si estas han caido,
    en caso de caer, las bolas dejan de moverse y setean su variable caida a true para
    dejar de ser renderizadas. Además se crea un puntero a la bola.
*/
void Juego::colisionTronera()
{
    for(unsigned int i=0; i<troneras.size(); i++)
    {
        for(unsigned int j=0; j<bolas.size(); j++)
        {
            if(!bolas[j].getCaida() && !bolas[j].getAnimado() && caidasAux==0)
            {
                sf::Vector2f  posB1=troneras[i].getPosition();
                sf::Vector2f  posB2=bolas[j].getPosSg();
                sf::Vector2f  vecB1B2((posB1.x-posB2.x),(posB1.y-posB2.y));

                float separacion = sqrt((vecB1B2.x*vecB1B2.x) + (vecB1B2.y*vecB1B2.y));

                if(separacion <= (troneras[i].getRadius()+9))
                {
                    printf("ha caido\n");
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
    for(unsigned int i=0; i<bolas.size(); i++)
    {
        for(unsigned int j=0; j<bolas.size(); j++)
        {

            if(i!=j && abs(bolas[i].getSprite().x)!=0.f && !bolas[i].getCaida() && !bolas[j].getCaida())
            {
                choque(bolas[i],bolas[j]);
            }
        }
    }
}

/*
    Calucla la distancia entre cada una de las bolas y en el caso de ser menor que la suma de los
    2 radios significa que estan colisionando. En caso de colision, muevo manualmente las bolas
    para que no se solapen y calculo los nuevos vectores de velocidad.
*/
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

        float p =2*(normal.x * (b1vel.x-b2vel.x) + normal.y * (b1vel.y-b2vel.y)) / 2;


        bola1.setVelocidad(sf::Vector2f(b1vel.x - p * 0.8 * normal.x , b1vel.y - p * 0.8  * normal.y));
        bola2.setVelocidad(sf::Vector2f(b2vel.x + p * 0.8 * normal.x , b2vel.y + p * 0.8  * normal.y));

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

    for(unsigned int i=0; i<bolas.size(); i++)
    {
        if(!bolas[i].heParado())
        {
            contr = false;
        }
    }
    return contr;
}
/*
    Maneja lo relacionado con la animacion de caida de las bolas y su vuelta a la mesa en
    caso de no golpear a la menor bola o sumar los puntos en caso de ser un golpe valido.
    Las bolas se van moviendo de uno en uno y en cada iteracion miro si han llegado a su
    posicion fina, en caso afirmativo empiezo a animar la siguiente bola hasta no quedar
    ninguna.

    Al hacer un golpe no valido las bolas vuelven al tablero en la primera posicion de las
    predeterminadas que se encuentre disponible.

    La bola blanca siempre vuelve al mismo punto y nunca se quedará en la barra lateral.
*/
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

            if(primera && primera->getID()==bolas[1].getID() && caidas[caidasAux]->getID()==9)
            {
                printf("Has ganado yay!\n");
                Reinicia();
                caidasAux--;
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

                for(unsigned int i=1; i<positions.size() && !contr; i++)
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
                caidas[caidasAux]->setPosPR(positions[0]);
                caidas[caidasAux]->setPosSg(positions[0]);
            }
            caidasAux++;
        }

    }
    else
    {
        for(unsigned int i =0; i<barra.size(); i++)
        {
            for(unsigned int j=0; j<bolas.size(); j++)
            {
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
        Jugador::Instance()->addPuntuacion(puntos);
        puntos = 0;
        if(bolas.size()>1)
        {
            Jugador::Instance()->apuntado(bolas[0].getPosSg(),bolas[1].getPosSg());
        }
    }
}


/*
    Comprueba cuales de las posiciones predeterminadas se encuentran libres
*/
bool Juego::posValida(sf::Vector2f pos)
{

    bool contr = true;

    for(unsigned int i=1; i<bolas.size() && contr; i++)
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
/*
    Inicia una nueva partida desde cero
*/
void Juego::Reinicia()
{
    estado = 0;
    caidasAux = 0;
    caidasCont = 0;
    puntos = 0;
    primera = nullptr;
    bolas.clear();
    caidas.clear();
    barra.clear();
    generaBolas();
    abaco = Abaco();
    Jugador::Instance()->setPuntuacion(puntos);
    Jugador::Instance()->apuntado(bolas[0].getPosSg(),bolas[1].getPosSg());

}

void Juego::Inicializa()
{
    if (!textura.loadFromFile("resources/Sprite_prob.png"))
        printf("No se ha podido encontrar textura");

    estado = 0;
    //posiciones en las que se generaran las bolas al inicar/reiniciar o al volver a la mesa
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

    for(unsigned int i=0; i<paredes.size(); i++)
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

    for(unsigned int i=0; i<troneras.size(); i++)
    {
        troneras[i].setOrigin(troneras[i].getRadius(),troneras[i].getRadius());
    }

    caidasAux = 0;
    generaBolas();
    Jugador::Instance()->setPointer(textura);
    abaco = Abaco();
    primera = nullptr;
    debug = false;
    Mapa::Instance()->setValues();
}

Juego::Juego()
{
    //ctor
}

Juego::~Juego()
{

    //dtor
}
