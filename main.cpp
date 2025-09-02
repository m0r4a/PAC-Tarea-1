#include <iostream>
#include <string>
#include <vector>
#include "Escaneo.h"
#include "Analisis.h"
#include "Registro.h"

using namespace std;

int main() {
    string ipObjetivo;
    int puertoInicio, puertoFin;
    string archivoSalida;

    cout << "=== Escaner de Puertos en C++ ===" << endl;

    try {
        // Entrada de datos
        cout << "Ingrese la direccion IP objetivo: ";
        cin >> ipObjetivo;

        cout << "Ingrese puerto inicial: ";
        cin >> puertoInicio;

        cout << "Ingrese puerto final: ";
        cin >> puertoFin;

        cout << "Ingrese el nombre del archivo de salida: ";
        cin >> archivoSalida;

        // Vector dinámico de resultados
        vector<ResultadoPuerto> resultados;

        // Escaneo
        resultados = escanearPuertos(ipObjetivo, puertoInicio, puertoFin);

        // Analisis de puertos sospechosos
        vector<ResultadoPuerto> sospechosos = analizarPuertos(resultados);

        // Registro en archivo
        guardarResultados(archivoSalida, ipObjetivo, resultados, sospechosos);

        cout << "\nEscaneo completado. Resultados guardados en " << archivoSalida << endl;
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
