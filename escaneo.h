#ifndef ESCANEO_H
#define ESCANEO_H

#include <string>
#include <vector>

struct Puerto {
    int numero;
    std::string estado;   // abierto, cerrado, error
    bool sospechoso;
};

std::vector<Puerto> escanearPuertos(const std::string& ip, int puertoInicio, int puertoFin);

#endif
