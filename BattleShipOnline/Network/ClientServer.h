#pragma once

#include <vector>
#include <memory>
#include <string>
#include <cstring>

#include "Serializable.h"
#include "../Vector2D.h"
#include "Socket.h"

class Game;

typedef struct {
    Vector2D pos = Vector2D(0, 0);
    bool isMessage = false;
    bool horizontal = true;
    int16_t longitud = 0;
} setupInfo;
class ChatMessage : public Serializable
{
public:
    static const size_t MAX_NAME = 20;
    static const size_t MESSAGE_SIZE = sizeof(char) * MAX_NAME + sizeof(uint8_t) + sizeof(int16_t) * 3 + sizeof(bool);
    char name[MAX_NAME];
    enum MessageType
    {
        LOGIN = 0,
        SETUP = 1,
        ATTACK = 2,
        LOGOUT = 3
    };
    ChatMessage() {};
    ChatMessage(const std::string& n, setupInfo m) :message(m) {
        std::strncpy(nick, n.c_str(), MAX_NAME - 1);
        nick[MAX_NAME - 1] = '\0';
        std::cout << nick << " es el nick";
    };
    void to_bin();
    int from_bin(char* bobj);
    uint8_t type;
    char nick[MAX_NAME];
    setupInfo message;
};

class ChatServer {

public:
    ChatServer(const char* s, const char* p) : socket(s, p){
        socket.bind();
    };

    void do_messages();

private:
    std::vector<std::unique_ptr<Socket>> clients;

    Socket socket;
};

class ChatClient {

public:
    ChatClient(const char* s, const char* p, const char* n) : socket(s, p), nick(n){};

    void login();

    void logout();

    void input_thread(setupInfo& info);

    void net_thread(Game *game);

private:

    Socket socket;

    std::string nick;

    Game *gameInstance;

};