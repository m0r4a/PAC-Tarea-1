#include "escaneo.h"
#include <iostream>
#include <chrono>
#include <map>
#include <regex>
#include <thread>
#include <future>
#include <vector>
#include <algorithm>
#include <fcntl.h> // esta creo que puede ser opcional
#include <cstring>

#ifdef _WIN32
  #include <winsock2.h>
  #include <ws2tcpip.h>
  typedef SOCKET socket_t;
  #define CLOSESOCKET closesocket
#else
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <errno.h>
  typedef int socket_t;
  #define INVALID_SOCKET (-1)
  #define SOCKET_ERROR   (-1)
  #define CLOSESOCKET close
#endif

/**
 * Mapa de servicios comunes con puertos conocidos.
 * Permite mostrar nombre del servicio segun el puerto.
 */
static std::map<int, std::string> serviciosComunes = {
    {20, "FTP Data"}, {21, "FTP Control"}, {22, "SSH"}, {23, "Telnet"},
    {25, "SMTP"}, {53, "DNS"}, {67, "DHCP Server"}, {68, "DHCP Client"},
    {69, "TFTP"}, {80, "HTTP"}, {110, "POP3"}, {123, "NTP"},
    {135, "RPC"}, {139, "NetBIOS"}, {143, "IMAP"}, {161, "SNMP"},
    {389, "LDAP"}, {443, "HTTPS"}, {445, "SMB"}, {993, "IMAPS"},
    {995, "POP3S"}, {1433, "MSSQL"}, {1521, "Oracle"}, {3306, "MySQL"},
    {3389, "RDP"}, {5432, "PostgreSQL"}, {5900, "VNC"}, {6379, "Redis"},
    {8080, "HTTP-Alt"}, {8443, "HTTPS-Alt"}, {9200, "Elasticsearch"}
};

#ifdef _WIN32
/**
 * Implementacion a windows
 * Inicializa Winsock en Windows.
 * Debe llamarse antes de usar cualquier función de sockets.
 * Lanza una excepción si la inicialización falla.
 */
void Escaneo::inicializarWinsock() {
    WSADATA wsaData;
    int resultado = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (resultado != 0) {
        throw std::runtime_error("Error al inicializar Winsock: " + std::to_string(resultado));
    }
}

/**
 * Limpia Winsock en Windows.
 * Debe llamarse al final del uso de sockets para liberar recursos.
 */
void Escaneo::limpiarWinsock() {
    WSACleanup();
}
#else

/**
 * En Linux/Unix no se requiere inicialización de sockets,
 * pero se mantienen las funciones para compatibilidad cross-platform.
 */
void Escaneo::inicializarWinsock() {
    // No es necesario en Linux/Unix
}

/**
 * En Linux/Unix no se requiere limpieza de sockets,
 * pero se mantiene para compatibilidad cross-platform.
 */
void Escaneo::limpiarWinsock() {
    // No es necesario en Linux/Unix
}
#endif


/**
 * Valida si una cadena es una dirección IPv4 válida.
 * Utiliza expresiones regulares para comprobar el formato.
 * parametro: ip Dirección IP en formato string.
 * return: true si la IP es válida, false en caso contrario.
 */
bool Escaneo::validarIP(const std::string& ip) {
    std::regex ipRegex(
        R"(^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)"
    );
    return std::regex_match(ip, ipRegex);
}

/**
 * Determina si una IP pertenece a la red local.
 * Incluye 127.0.0.1, localhost, redes privadas 192.168.x.x, 10.x.x.x y 172.16-31.x.x
 * parametro: ip Dirección IP en formato string.
 * return: true si es una IP local, false en caso contrario.
 */
bool Escaneo::esIPLocal(const std::string& ip) {
    if (ip == "127.0.0.1" || ip == "localhost") return true;
    if (ip.size() >= 8 && ip.substr(0, 8) == "192.168.") return true;
    if (ip.size() >= 3 && ip.substr(0, 3) == "10.") return true;
    if (ip.size() >= 7 && ip.substr(0, 7) == "172.") {
        try {
            size_t pos = ip.find('.', 4);
            std::string segunda = ip.substr(4, pos - 4);
            int val = std::stoi(segunda);
            return val >= 16 && val <= 31;
        } catch (...) {
            return false;
        }
    }
    return false;
}




std::string Escaneo::obtenerServicio(int puerto) {
    // Ver si el puerto está en servicios comúnes, en pseudocódigo que sea algo así
    // var = servicioComún.find(puerto)
    // si no está en los servicios comunes entoces
    // si puerto < 1024 entonces es como de sistema o privilegiado
    // si < 49152 otro tipo especial, pero no sé cómo ponerle
    // de otra forma, entonces Dinámico o Privado
    return std::string();
}

EstadoPuerto Escaneo::verificarPuerto(const std::string& ip, int puerto, int& tiempoRespuesta) {
    // -> Cerrar socket en todos los caminos y manejar errores/errno/WSA
    //  Esta va a ser una función muy importante, se va a usar mucho el ifdef _WIN32, para usar ioctlsocket
    //    si estás en windows o fcntl en linux
    //  Se intenta medir el tiempo de respuesta, quizá la respuesta? esto te SYN, ACK, SYN/ACK
    //    no sé, pero esto tiene que devolver EstadoPuerto::ABIERTO o ::CERRADO o ::FILTRADO
    tiempoRespuesta = -1;
    return EstadoPuerto::FILTRADO;
}

static Puerto escanearPuertoIndividual(const std::string& ip, int puerto) {
    // aquí llama a la función verificarPuerto, luego obtenerServicio y
    // al final construir el puerto, el struct va a estar en el .h
    return Puerto(puerto, EstadoPuerto::FILTRADO, std::string(), -1);
}

std::vector<Puerto> Escaneo::escanearPuertos(const std::string& ip, const std::vector<int>& puertos, size_t requestedThreads /* = 0 */) {
    // Esto idealmente va a ser en paralelo, va a tener una función -t el script para definir hilos
    // para linux en tests me va bien los 40 hilos completos pero en windows no, así que en linux usamos
    // std::thread::hardware_concurrency, en windows que se usen 4 o así por default
    // esto creo que va a tener varias formas de return así que no sé cómo documentar más
    return std::vector<Puerto>{};
}
