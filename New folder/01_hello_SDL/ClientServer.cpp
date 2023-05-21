#include "ClientServer.h"

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
    std::string msg;

    ChatMessage em(nick, msg);
    em.type = ChatMessage::LOGIN;

    std::cout << "attempting to log in...\n";

    socket.send(em, socket);
}

void ChatClient::logout()
{
    std::string msg;

    ChatMessage om(nick, msg);
    om.type = ChatMessage::LOGOUT;

    std::cout << "logging out...\n";

    socket.send(om, socket);
}

void ChatClient::input_thread()
{
   while (true)
    {
        // Leer stdin con std::getline
        // Enviar al servidor usando socket
        std::string clientInput;
        std::getline(std::cin, clientInput);

        ChatMessage im = ChatMessage(nick, clientInput);
        im.type = ChatMessage::MESSAGE;

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

        std::cout << socketMessage.nick << ": " << socketMessage.message << "\n";

    }
}