#include "client_network.h"

ClientNetwork::ClientNetwork() { logl("Chat Client Started"); }

void ClientNetwork::LaunchReceptionThread() {
  reception_thred = std::thread(&ClientNetwork::ReceivePackets, this, &socket);
}

void ClientNetwork::Connect(const char *address, unsigned short port) {
  if (socket.connect(address, port) != sf::Socket::Done) {
    logl("Could not connect to the server\n");
  } else {
    isConnected = true;
    logl("Connected to the server\n");
  }
}

void ClientNetwork::ReceivePackets(sf::TcpSocket *socket) {
  while (true) {
    if (socket->receive(last_packet) == sf::Socket::Done) {
      std::string received_string;
      std::string sender_address;
      unsigned short sender_port;
      last_packet >> received_string >> sender_address >> sender_port;
      logl("From (" << sender_address << ":" << sender_port
                    << "): " << received_string);

      std::string fromatted_message = "[ip:";
      fromatted_message += sender_address;
      fromatted_message += ", port:";
      fromatted_message += std::to_string(sender_port);
      fromatted_message += "]:";
      fromatted_message += received_string;
      new_messages.push_back(fromatted_message);
    }

    std::this_thread::sleep_for((std::chrono::milliseconds)250);
  }
}

void ClientNetwork::SendPacket(sf::Packet &packet) {
  if (packet.getDataSize() > 0 && socket.send(packet) != sf::Socket::Done) {
    logl("Could not send packet");
  }
}

void ClientNetwork::Run() {
  if (isConnected) {
    std::string user_input;
    std::getline(std::cin, user_input);

    if (user_input.length() < 1)
      return;

    sf::Packet reply_packet;
    reply_packet << user_input;

    SendPacket(reply_packet);
  }
}

std::vector<std::string> ClientNetwork::GetNewMessages() {
  std::vector<std::string> new_messages = this->new_messages;
  this->new_messages.clear();
  return new_messages;
}
