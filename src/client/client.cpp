#include "client.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include <SFML/Network/Packet.hpp>

Client::Client(const char *ip, unsigned short port)
    : window(sf::VideoMode(800, 600), "Chat Client"),
      ip(ip),
      port(port)
{
    ImGui::SFML::Init(window);
}

void Client::run() {
    client_network.Connect(ip, port);
    client_network.LaunchReceptionThread();

    sf::Clock deltaClock;

    while (window.isOpen()) {
        sf::Time deltaTime = deltaClock.restart();

        processEvents();
        update(deltaTime);
        draw();
    }
}

void Client::processEvents() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } 

        ImGui::SFML::ProcessEvent(event);
    }
}

void Client::update(sf::Time deltaTime) {
    ImGui::SFML::Update(window, deltaTime);

    for (auto &message : client_network.GetNewMessages()) {
        chat_messages.push_back(message);
    }

    drawChatWindow();
}

void Client::draw() {
    window.clear(sf::Color(40,40,40));
    ImGui::SFML::Render(window);
    window.display();
}

void Client::drawChatWindow() {
    int flags = ImGuiWindowFlags_NoMove | 
                ImGuiWindowFlags_NoResize | 
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_HorizontalScrollbar |
                ImGuiWindowFlags_NoTitleBar;

    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(window.getSize().x, window.getSize().y));
    if (ImGui::Begin("Chat", NULL, flags)) {
        static char buf[256];
        ImGui::Text("Chat Window");
        ImGui::Separator();

        ImGui::BeginChild("scrolling", ImVec2(0, window.getSize().y - 100), false, ImGuiWindowFlags_HorizontalScrollbar);

        for (auto &message : chat_messages)
            ImGui::Text(message.c_str());

        ImGui::EndChild();
        ImGui::Separator();
        ImGui::InputText("", buf, IM_ARRAYSIZE(buf));
        ImGui::SameLine();

        if (ImGui::Button("Send")) {
            sf::Packet packet;
            packet << buf;
            chat_messages.push_back(std::string("[me]:") + std::string(buf));
            client_network.SendPacket(packet);
            buf[0] = '\0';
        }

        ImGui::End();
    }
}
