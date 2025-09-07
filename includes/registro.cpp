#include "registro.h"
#include <fstream>
#include <string>
#include <vector>

const std::string Registro::SEPARADOR = "================================================";

std::string Registro::obtenerFechaHora() {
    // que regrese la fecha en Y-m-d H:M:S
    return std::string();
}

std::string Registro::formatearEstado(EstadoPuerto estado) {
    // un switch case que regrese el valor del estado del puerto
    // dependiendo de si esta EstadoPuerto::Abierto return "ABIERTO" o cerrado y así
    return std::string();
}

bool Registro::validarNombreArchivo(const std::string& nombreArchivo) {
    // ps eso, verificar si no tiene caracteres vacíos o inválidos
    return false;
}

void Registro::manejarErrorArchivo(const std::string& nombreArchivo, const std::string& operacion) {
    // algo como std::cerr << el error y << std:endl
}

void Registro::escribirEncabezado(std::ofstream& archivo, const std::string& ip) {
    // aquí sean creativos o algo, solo redirigan los strings a el archivo
    // archivo << "string"
}

void Registro::escribirResultadosCompletos(std::ofstream& archivo, const std::vector<Puerto>& resultados) {
    // solo imprimir los puertos ABIERTOS y redigirlo al archivo
}

void Registro::escribirPuertosSospechosos(std::ofstream& archivo, const std::vector<Puerto>& sospechosos) {
    // Esto va a ser la sección de puertos sospechosos, aquí usen puerto.servicio, puerto.estado, puerto.tiempoRespuesta
    // etc para vaciar la info
}

void Registro::escribirEstadisticas(std::ofstream& archivo, const std::vector<Puerto>& resultados) {
    // Aqui pongan stats de los puertos en general, totales, porcentaje de puertos abiertos y así
}

void Registro::escribirRecomendaciones(std::ofstream& archivo, const std::vector<Puerto>& sospechosos) {
    // Esto está medio a discusión, no recuerdo si es un requisito pero pueden buscar así:
    // if sospechosos.empty() y dar recomendaciones generales, y así, utilizar los outputs de puerto.razonSospecha.find("malware")
    // para categorizar si hay maliciosos o si hay p2p y tal.
}

bool Registro::guardarResultados(const std::string& nombreArchivo,
                                 const std::string& ip,
                                 const std::vector<Puerto>& resultados,
                                 const std::vector<Puerto>& sospechosos) {
    // Esto ya es usar todas las funciones juntas, en este orden:
    // validarNombreArchivo
    // manejarErrorArchivo
    // escribirEncabezado, resultadosCompletos bbla bla bla, hasta "escribirRecomendaciones"
    // Se puede agregar un pie del reporte
    return false;
}
