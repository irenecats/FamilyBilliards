#ifndef JUEGO_H
#define JUEGO_H
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <math.h>
#include <Bola.h>
#include <Jugador.h>
#include <Animacion.h>

#define UPDATE_TIME (1000/15)

class Juego
{
    public:
        static Juego*   Instance();
        virtual         ~Juego();
        void            bucleJuego();
        int             getEstado();
               void tiraBola(float);

    protected:
    private:
        //Variables
       static Juego* instancia;
       std::vector<Bola> bolas;
       sf::Texture      textura;
       sf::Clock        reloj;
       int              estado; //0 apuntado, 1 tirando, 2 en movimiento
       float            velTiro;
      // Bola*            primera;

       void            colisionBolas();
        //Metodos
        Juego();
        void generaBolas();
        void choque(Bola& , Bola& );

        bool bolasParadas();
};

#endif // JUEGO_H
