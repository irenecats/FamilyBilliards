#ifndef JUEGO_H
#define JUEGO_H
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <math.h>
#include <Bola.h>
#include <Jugador.h>
#include <Palo.h>
#include <Abaco.h>

#define UPDATE_TIME (1000/60)

class Juego
{
    public:
        static Juego*   Instance();
        virtual         ~Juego();
        void            bucleJuego();
        int             getEstado();
        void            tiraBola(float);

    protected:
    private:
        //Variables
       static Juego*        instancia;
       sf::Texture          textura;
       sf::Clock            relojUpdate;
       std::vector<sf::Vector2f>  positions;
       int                  estado; //0 apuntado, 1 tirando, 2 bolas en movimiento, 3 abaco
       std::vector<sf::RectangleShape> paredes;
       std::vector<sf::CircleShape> troneras;
     //  float                velTiro;

       Bola*                primera;
       std::vector<Bola>    bolas;
       std::vector<Bola>    barra;
       std::vector<Bola*>   caidas;
       int                  caidasAux;
       int                  caidasCont;

       Abaco                abaco;
       int                  puntos;


        //Metodos
        Juego();
        void    colisionBolas();
        void    colisionParedes();
        void    colisionTronera();

        void    choque(Bola& , Bola& );
        void    generaBolas();
        bool    bolasParadas();

        bool    posValida(sf::Vector2f);
        void    manejaAnimaciones();

        void    Inicializa();
        void    Reinicia();
};

#endif // JUEGO_H
