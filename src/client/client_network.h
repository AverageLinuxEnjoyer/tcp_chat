#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Network.hpp>

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x

class ClientNetwork{
     sf::TcpSocket socket;
     sf::Packet last_packet;
     std::thread reception_thred;

     bool isConnected = false;
     std::vector<std::string> new_messages;
     
public:
     ClientNetwork();
     void LaunchReceptionThread();
     void Connect(const char *, unsigned short);
     void ReceivePackets(sf::TcpSocket *);
     void SendPacket(sf::Packet &);
     void Run();
     std::vector<std::string> GetNewMessages();
};
