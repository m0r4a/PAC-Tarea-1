#include "analisis.h"
#include <algorithm>

// Esta va a ser la lista de puertos que vamos a considerar como sospechosos
const std::set<int> Analisis::PUERTOS_MALICIOSOS = {
    // Ejemplo: 12345, 31337, etc.
};

const std::set<int> Analisis::PUERTOS_ADMINISTRATIVOS = {
    // Ejemplo: 22 (SSH), 3389 (RDP), 3306 (MySQL)
};

const std::set<int> Analisis::PUERTOS_TROJANS = {
    // Y bueno, se entiende...
};

const std::set<int> Analisis::PUERTOS_BACKDOORS = {
};

const std::set<int> Analisis::PUERTOS_P2P = {
};

const std::set<int> Analisis::PUERTOS_DESARROLLO = {
};


bool Analisis::esPuertoConocidoMalicioso(int puerto) {
    // Esto tiene que ver si el puerto está en malicioso
    // algo como PUERTO_malicioso.find(puerto)
    return false;
}

bool Analisis::esPuertoAdministrativo(int puerto) {
    // las estructuras son iguales, CONST.find(puerto) y si != CONST.end()
    return false;
}

bool Analisis::esPuertoTrojan(int puerto) {
    return false;
}

bool Analisis::esPuertoBackdoor(int puerto) {
    return false;
}

bool Analisis::esPuertoP2P(int puerto) {
    return false;
}

bool Analisis::esPuertoInusual(int puerto) {
    // Esto va a ser algo especial, vamos a revisar si el puerto es "raro"
    // puerto > 49152
    // puerto > 1024 y puert < 5000 y es mod 1000 == 0, es decir, algo como 2000, 3000
    // entre 31000 y 33000 se supone que se suele usar para malware
    return false;
}


int Analisis::calcularPuntuacionRiesgo(const Puerto& puerto) {
    // Esto va a asignar un puntaje de "riesgo" basado en ciertas características medio arbitrarias
    //
    // Va a ser algo así:
    // 1. Ver si el puerto está abierto, si no, su puntaje es 0
    // 2. Sumar puntos según el tipo:
    //    +50 si es malicioso
    //    +40 si es Trojan
    //    +35 si es Backdoor
    //    +25 si es P2P
    //    +20 si es administrativo
    //    +15 si es inusual
    //    +15 si es de desarrollo en un entorno productivo 
    // 3. Podría ser que agreguemos puntos si la respuesta es muy rápida (podría ser una config especial)
    // 4. Return el total
    return 0;
}

std::string Analisis::obtenerRazonSospecha(const Puerto& puerto, int nivelSensibilidad) {
    // Esta función va a devolver un texto con los motivos por los cuales es sospechoso
    //
    // 1. Se crea una lista de "razones" (como que está asociado a un puerto con malware o así)
    // 2. Revisar si el puerto está en x o y lista y agregar la razón
    // 3. Si el nivel de senssibilidad es alto (creo que 3 va a ser el máximo), agregas más razones
    // 4. So no hay razones -> devuelves un texto de que no tienen clasificación especifica de riesgo
    // 5. unir todo en un string y devolverlo
    return "";
}


std::vector<int> Analisis::detectarSecuenciasSospechosas(const std::vector<Puerto>& puertos) {
    // Esto va a a ver si varios puertos están consecutivamente abiertos
    //
    // 1. Agarrar todos los puertos que estén abiertos
    // 2. Se ordenan
    // 3. Ver si están en secuencia por al menos 5 puertos seguidos
    // 4. Regresar una lista con los números consecutivos de puerto
    return {};
}

bool Analisis::tienePatronSospechoso(const std::vector<Puerto>& puertos) {
    // Ver patrones generales en el host
    // 1. Contar cuantos puertos hay abiertos (rima btw)
    // 2. Verificar si:
    //   2.1. Más de 3 puertos administrativos abiertos
    //   2.2. Al menos 1 puerto malicioso abierto
    //   2.3. Muchos puertos abiertos (como 20 o así)
    // 3. regresar true si cumple alguna condición, false si no
    return false;
}


std::vector<Puerto> Analisis::identificarSospechosos(const std::vector<Puerto>& puertos, int nivelSensibilidad) {
    // Esto va a regresar todos los puertos raros y su motivo
    //
    // 1. Primero definir un "umbral" de riesgo según la sensibilidad, es decir, si por ejemplo
    // -s1 osea, sensibilidad 1, se va a necesitar un puntaje más alto para aparecer como riesgoso, pero si s3
    // entonces va a ser más sensible y requiere de un puntaje menor para aparecer.
    // 
    //  - Nivel 1: alto (ej: >=40)
    //  - Nivel 2: medio (ej: >=25)
    //  - Nivel 3: bajo (ej: >=15)
    // 
    // 2. Para cada puerto que esté abierto:
    //    - Calcular sus puntos de riesgo
    //    - Si entra en el umbral se mete en la lista de sospechosos
    //    - Guardar el por qué se sospecha
    // 
    // 3. Usar la funcion de secuenciasSospechosas
    // 4. Ordenar la lista final
    // 5. Regresar la lista
    return {};
}
