#include "server.h"
#include <iostream>

void Server::run() {
    sf::Clock clock;
    while(true) {
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() > 2) {
            std::cout << "Hello from the server!" << std::endl;
            clock.restart();
        }
    }
}

