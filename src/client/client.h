#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Graphics.hpp>
#include "client_network.h"
#include <vector>

class Client {
public:
    Client(const char *ip, unsigned short port);
    ~Client() = default;

    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void draw();

    void drawChatWindow();

private:
    sf::RenderWindow window;
    ClientNetwork client_network;

    const char* ip;
    unsigned short port;

    std::vector<std::string> chat_messages;
};

#endif // CLIENT_H
