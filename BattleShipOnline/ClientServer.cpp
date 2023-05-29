#include "ClientServer.h"

void ChatMessage::to_bin()
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
int ChatMessage::from_bin(char* bobj)
{
    alloc_data(MESSAGE_SIZE);
    memcpy(static_cast<void*>(_data), bobj, MESSAGE_SIZE);
    char* tmp = _data;
    memcpy(&type, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    if (type == ChatMessage::MESSAGE) std::cout << " Tipo : Mensaje\n";

    memcpy(nick, tmp, sizeof(char) * 20);
    nick[19] = '0';
    tmp += sizeof(char) * 20;
    std::cout << "Nick : " << nick << "\n";
    int16_t x;
    memcpy(&x, tmp, sizeof(int16_t));
    tmp += sizeof(int16_t);
    int16_t y;
    memcpy(&y, tmp, sizeof(int16_t));
    tmp += sizeof(int16_t);
    message.pos = Vector2D(x, y);
    std::cout << "Pos : " << "X " << message.pos.getX() << " Y " << message.pos.getY() << "\n";
    memcpy(&message.horizontal, tmp, sizeof(bool));
    tmp += sizeof(bool);
    std::cout << "Horizontal : " << message.horizontal << "\n";
    memcpy(&message.longitud, tmp, sizeof(int16_t));
    std::cout << "Longitud : " << message.longitud << "\n";
    return 0;
}

void ChatServer::do_messages()
{
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
        // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)
        ChatMessage msg;
        Socket *sock;
        socket.recv(msg, sock);

        switch(msg.type){
            case ChatMessage::LOGIN:
            {
                std::cout << msg.nick << " joined the room\n";
                std::unique_ptr<Socket> uniqueSocket(sock);
                
                clients.push_back(std::move(uniqueSocket));

            }
            break;

            case ChatMessage::LOGOUT:
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

            case ChatMessage::MESSAGE:
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
    messageInfo msg;

    ChatMessage em(nick, msg);
    em.type = ChatMessage::LOGIN;

    std::cout << "attempting to log in...\n";

    socket.send(em, socket);
}

void ChatClient::logout()
{
    messageInfo msg;

    ChatMessage om(nick, msg);
    om.type = ChatMessage::LOGOUT;

    std::cout << "logging out...\n";

    socket.send(om, socket);
}

void ChatClient::input_thread(messageInfo& info)
{
    if (info.isMessage) {
        ChatMessage im = ChatMessage(nick, info);
        im.type = ChatMessage::MESSAGE;
        info.isMessage = false;
        socket.send(im, socket);
    }
}

void ChatClient::net_thread()
{
    Socket* s = new Socket(socket);
    ChatMessage socketMessage;
    while (true)
    {
        //Recibir Mensajes de red
        //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
        socket.recv(socketMessage, s);

        std::cout << socketMessage.nick << ": " << socketMessage.message.pos.getX() << " " << socketMessage.message.pos.getY() << " " << socketMessage.message.horizontal << " " << socketMessage.message.longitud << "\n";

    }
}