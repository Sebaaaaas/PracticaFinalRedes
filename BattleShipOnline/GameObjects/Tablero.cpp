#include "Tablero.h"

#include "../Texture.h"
#include "Barco.h"

#include <vector>
#include <iostream>

Tablero::Tablero(Vector2D* pos, int w, int h, Texture* t, Game *game) : BattleShipObject(pos, w, h, t), m_game(game)
{
    printf( "tablero creado!\n" );

    //tablero de 10x10
    casillas.assign(filas, std::vector<bool>(columnas, false));
    casillasEnemigo.assign(filas, std::vector<cEnemigo>(columnas, {false, false}));
    barcosRestantes = 0;
}

Tablero::~Tablero()
{
}

void Tablero::render(){
    tex->render(getRect());
}

void Tablero::handleEvents(SDL_Event &event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN && m_game->getAttackPhase()){
        if(event.button.button == SDL_BUTTON_LEFT){
        // creo un evento auxiliar
            setupInfo info;
            int x, y;
            SDL_GetMouseState(&x, &y);
            Vector2D pos = Vector2D(x,y);
            std::cout << "handleEvents " << pos.getX() << " " << pos.getY() <<" \n";
            processAttack(pos);
        }
    }

}

bool Tablero::getPuedeColocar()
{
    if(barcosRestantes == 0){
        return false;
    }
    else return true;
}

void Tablero::processEnemy(setupInfo info)
{
    int columnaActual = (info.pos.getX()- OFFSET_X)/PIXELES_COLUMNA;
    int filaActual = (info.pos.getY() - OFFSET_Y)/PIXELES_FILA;

    if(info.horizontal){
        int i = columnaActual;
        int longCheck = i + info.longitud;
        while( i < longCheck){
            casillasEnemigo[filaActual][i] = {false, true};
            std::cout << " processEnemy (Tablero) X : "<< info.pos.getX() << " Y : " << info.pos.getY() << "\n";
            i++;
        }

    }
    else{
        int j = filaActual;
        int longCheck = j + info.longitud;
        while(j < longCheck){
            casillasEnemigo[j][columnaActual] = {false, true};
            j++;
        }

    }
}

void Tablero::processDefense(setupInfo info)
{
    int columnaActual = (info.pos.getX()- OFFSET_X)/PIXELES_COLUMNA;
    int filaActual = (info.pos.getY() - OFFSET_Y)/PIXELES_FILA;
    std::cout << " processDefense " << columnaActual << " " << filaActual <<  "\n";
    int newPosX = (columnaActual*PIXELES_COLUMNA)+OFFSET_X;
    int newPosY = (filaActual*PIXELES_FILA)+OFFSET_Y;
    if(casillas[filaActual][columnaActual]){
        m_game->crearCasillaHitDefense(true, new Vector2D(newPosX, newPosY));
        std::cout << " processDefense (Tablero) Hit en X : "<< info.pos.getX() << " Y : " << info.pos.getY() << "\n";
    }
    else{
        m_game->crearCasillaHitDefense(false, new Vector2D(newPosX, newPosY));
        std::cout << " processDefense (Tablero) No Hit en X : "<< info.pos.getX() << " Y : " << info.pos.getY() << "\n";
    }
}

void Tablero::processAttack(const Vector2D &clickPos)
{
    int columnaActual = (clickPos.getX()- OFFSET_X)/PIXELES_COLUMNA;
    int filaActual = (clickPos.getY() - OFFSET_Y)/PIXELES_FILA;
    int newPosX = (columnaActual*PIXELES_COLUMNA)+OFFSET_X;
    int newPosY = (filaActual*PIXELES_FILA)+OFFSET_Y;
    std::cout << "processAttack " << columnaActual << " " << filaActual <<" \n";
    setupInfo info;
    //comprobamos que no se sale por los lados del tablero(x >> columnas, y >> filas)
    if(!((clickPos.getX()-OFFSET_X) < 0 || (columnaActual>= getColumnas()) 
    || (clickPos.getY() - OFFSET_Y) < 0 || (filaActual >= getFilas())))
    {
        if(!casillasEnemigo[filaActual][columnaActual].clicado){
            if(casillasEnemigo[filaActual][columnaActual].hayBarco){
                m_game->crearCasillaHitAttack(true, new Vector2D(newPosX, newPosY));
                std::cout << " processAttack (Tablero) Hit en X : "<< info.pos.getX() << " Y : " << info.pos.getY() << "\n";
            }
            else{
                m_game->crearCasillaHitAttack(false, new Vector2D(newPosX, newPosY));
                std::cout << " processAttack (Tablero) No Hit en X : "<< info.pos.getX() << " Y : " << info.pos.getY() << "\n";
            }
            casillasEnemigo[filaActual][columnaActual].clicado = true;
            info.pos = Vector2D(clickPos.getX(), clickPos.getY());
            info.isMessage = true;
            std::cout << "attackMessage: Pos " << info.pos.getX() << " " << info.pos.getX() << "\n";
            m_game->createMessage(info);
        }
    }
    
}
