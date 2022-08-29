#include "client/client.h"
#include "client/client_network.h"
#include "server/server_network.h"
#include <thread>

#define SERVER_IP "localhost"
#define SERVER_PORT 6294

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (strcmp(argv[1], "server") == 0) {
      ServerNetwork server(SERVER_PORT);
      server.Run();
    } else if (strcmp(argv[1], "client") == 0) {
      Client client(SERVER_IP, SERVER_PORT);
      client.run();
    }
  } else {
    std::cout << "Please specify a mode: server or client" << std::endl;
  }
}