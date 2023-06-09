#include "ClientServer.h"
#include "../Game.h"


void MessageBarco::to_bin()
{
    
    alloc_data(MESSAGE_SIZE);
    memset(_data, 0, MESSAGE_SIZE);
    char* tmp = _data;
    memcpy(tmp, &type, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    memcpy(tmp, nick, sizeof(char) * MAX_NAME);
    tmp += sizeof(char) * MAX_NAME;
    int16_t x = message.pos.getX();
    memcpy(tmp, &x, sizeof(int16_t));
    tmp += sizeof(int16_t);
    int16_t y = message.pos.getY();
    memcpy(tmp, &y, sizeof(int16_t));
    tmp += sizeof(int16_t);
    memcpy(tmp, &message.horizontal, sizeof(bool));
    tmp += sizeof(bool);
    memcpy(tmp, &message.longitud, sizeof(int16_t));
}
int MessageBarco::from_bin(char* bobj)
{
    alloc_data(MESSAGE_SIZE);
    memcpy(static_cast<void*>(_data), bobj, MESSAGE_SIZE);
    char* tmp = _data;
    memcpy(&type, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    //if (type == ChatMessage::SETUP) std::cout << " Tipo : Mensaje\n";

    memcpy(nick, tmp, sizeof(char) * 20);
    nick[19] = '0';
    tmp += sizeof(char) * 20;
    //std::cout << "Nick : " << nick << "\n";
    int16_t x;
    memcpy(&x, tmp, sizeof(int16_t));
    tmp += sizeof(int16_t);
    int16_t y;
    memcpy(&y, tmp, sizeof(int16_t));
    tmp += sizeof(int16_t);
    message.pos = Vector2D(x, y);
    //std::cout << "Pos : " << "X " << message.pos.getX() << " Y " << message.pos.getY() << "\n";
    memcpy(&message.horizontal, tmp, sizeof(bool));
    tmp += sizeof(bool);
    //std::cout << "Horizontal : " << message.horizontal << "\n";
    memcpy(&message.longitud, tmp, sizeof(int16_t));
    //std::cout << "Longitud : " << message.longitud << "\n";
    return 0;
}

void ChatServer::do_messages()
{
    int players = 0;
    while (true)
    {
        /*
         * NOTA: los clientes están definidos con "smart pointers", es necesario
         * crear un unique_ptr con el objeto socket recibido y usar std::move
         * para añadirlo al vector
         */

        //Recibir Mensajes en y en función del tipo de mensaje
        // - LOGIN: Añadir al vector clients
        // - LOGOUT: Eliminar del vector clients
        // - SETUP: Reenviar el mensaje a todos los clientes (menos el emisor)
        MessageBarco msg;
        Socket *sock;
        socket.recv(msg, sock);

        switch(msg.type){
            case MessageBarco::LOGIN:
            {
                 std::unique_ptr<Socket> uniqueSocket(sock);
                clients.push_back(std::move(uniqueSocket));
                
                 if(players < MAX_PLAYERS){
                     std::cout << msg.nick << " joined the room " << players << "\n";
                     players++;
                     if(players == 2){
                         for (auto it = clients.begin(); it != clients.end(); ++it) {
                             msg.type = MessageBarco::BEGIN_GAME;
                             socket.send(msg, **it);    
                             msg.type = MessageBarco::LOGIN;
                         }
                     }
                 }
                 else{

                     std::cout << " room is full\n";
                     auto it = clients.end();
                     --it;
                     msg.type = MessageBarco::LOGOUT;
                     socket.send(msg, **it);
                     clients.erase(it);
                     msg.type = MessageBarco::LOGIN;
                 }

            }
            break;

            case MessageBarco::LOGOUT:
            {
                for (auto it = clients.begin(); it != clients.end() && !(**it == *sock); ++it) {
                    if (it == clients.end()) {
                        std::cout << msg.nick << " left the room\n";
                    }
                    else {
                        clients.erase(it);
                    }
                }
            }
            break;

            case MessageBarco::SETUP:
            {
                for (auto it = clients.begin(); it != clients.end(); ++it) {
                    if (!(**it == *sock))
                        socket.send(msg, **it);
                }
            }
            break;
        }
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void ChatClient::login()
{
    setupInfo msg;

    MessageBarco em(nick, msg);
    em.type = MessageBarco::LOGIN;

    std::cout << "attempting to log in...\n";

    socket.send(em, socket);
}

void ChatClient::logout()
{
    setupInfo msg;

    MessageBarco om(nick, msg);
    om.type = MessageBarco::LOGOUT;

    std::cout << "logging out...\n";

    socket.send(om, socket);
}

void ChatClient::input_thread(MessageBarco& info)
{
    if (info.message.isMessage) {
        std::cout << "Enviando mensaje...\n";
        MessageBarco im = MessageBarco(nick, info.message);
        im.type = info.type;
        info.message.isMessage = false;
        socket.send(im, socket);
    }
}

void ChatClient::net_thread(Game* game)
{
    Socket* s = new Socket(socket);
    MessageBarco socketMessage;
    while (true)
    {
        //Recibir Mensajes de red
        //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
        socket.recv(socketMessage, s);

        std::cout << socketMessage.nick << ": " << socketMessage.message.pos.getX() << " " << socketMessage.message.pos.getY() << " " << socketMessage.message.horizontal << " " << socketMessage.message.longitud << "\n";

        game->captureServerMessage(socketMessage);

    }
}