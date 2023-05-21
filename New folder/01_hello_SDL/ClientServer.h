#pragma once

#include <vector>
#include <memory>
#include <string.h>

#include "Serializable.h"
#include "Socket.h"

class Server{

public:
    Server(const char* s, const char* p) : socket(s, p){
        socket.bind();
    };

    void do_messages();

private:
    std::vector<std::unique_ptr<Socket>> clients;

    Socket socket;
};

class Client{

public:
    Client(const char* s, const char* p, const char* n) : socket(s, p), nick(n){};

    void login();

    void logout();

    void input_thread();

    void net_thread();

private:

    Socket socket;

    std::string nick;

};