#define _WIN32_WINNT 0x0601
#include "Escaneo.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>
#include <vector>

#pragma comment(lib, "ws2_32.lib")

std::vector<Puerto> escanearPuertos(const std::string& ip, int puertoInicio, int puertoFin) {
    std::vector<Puerto> resultados;

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        throw std::runtime_error("Error iniciando Winsock");
    }

    for (int port = puertoInicio; port <= puertoFin; port++) {
        Puerto p;
        p.numero = port;
        p.sospechoso = false;

        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) {
            WSACleanup();
            throw std::runtime_error("Error al crear socket");
        }

        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);

        // Usar inet_addr para compatibilidad con MinGW
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        if (addr.sin_addr.s_addr == INADDR_NONE) {
            closesocket(sock);
            WSACleanup();
            throw std::runtime_error("Dirección IP inválida");
        }

        int timeout = 1000; // milisegundos
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

        int conn = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
        if (conn == 0) {
            p.estado = "abierto";
        } else {
            p.estado = "cerrado";
        }

        closesocket(sock);
        resultados.push_back(p);
    }

    WSACleanup();
    return resultados;
}
