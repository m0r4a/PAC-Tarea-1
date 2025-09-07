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
void Escaneo::inicializarWinsock() {
    // Aquí hay que usar WASTartup para cuando sea windows
}

void Escaneo::limpiarWinsock() {
    // Y aquí se usa WSACleanup
}
#else
void Escaneo::inicializarWinsock() {
    // Esto no se necesita para linux así que esto vacío
}

void Escaneo::limpiarWinsock() {
    // Lo mismo
}
#endif

bool Escaneo::validarIP(const std::string& ip) {
    // Esto es medio opcional pero estaría bien poner una regex para verificar
    // que sea una IP válida
    return false;
}

bool Escaneo::esIPLocal(const std::string& ip) {
    // hay que ver si la ip es local. 192.168, 10. o 172.
    // esto a lo mejor no es necesario
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
