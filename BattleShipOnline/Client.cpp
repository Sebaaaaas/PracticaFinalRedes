 /*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

// Using SDL and standard IO

#include <stdio.h>
#include <thread>

#include "Network/ClientServer.h"
#include "Game.h"

int main(int argc, char** argv)
{
    Game *juego = new Game();

    ChatClient battleShipClient(argv[1], argv[2], argv[3]); // Direcci�n servidor, puerto servidor y nick jugador
    //Initialize net thread
    std::thread net_thread([&battleShipClient, juego]() { battleShipClient.net_thread(juego); });

    battleShipClient.login();

    juego->run(battleShipClient);

    return 0;
}
