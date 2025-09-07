#include "analisis.h"
#include <algorithm>

const std::set<int> Analisis::PUERTOS_MALICIOSOS = {
    // Trojans conocidos
    1243, 1999, 2001, 2115, 2140, 3129, 3150, 4590, 5000, 5001, 5011,
    6400, 6670, 6711, 6712, 6713, 6776, 7000, 7300, 7301, 7306, 7307,
    7308, 9872, 9873, 9874, 9875, 10067, 10167, 12223, 12345, 12346,
    16969, 20034, 21544, 30100, 31337, 31338, 54321
};

const std::set<int> Analisis::PUERTOS_ADMINISTRATIVOS = {
    // Servicios administrativos sensibles
    22, 23, 135, 139, 445, 1433, 1521, 3306, 3389, 5432, 5900, 5901,
    5902, 5903, 5904, 5905, 6000, 6001, 6002, 8080, 8443, 9200
};

const std::set<int> Analisis::PUERTOS_TROJANS = {
    // Puertos comúnmente usados por trojans
    1234, 1243, 1245, 1492, 1600, 1807, 1981, 1999, 2001, 2023,
    2115, 2140, 2989, 3024, 3150, 3700, 4000, 4092, 4590, 5000,
    5001, 5011, 5321, 5400, 5401, 5402, 5550, 5569, 5637, 5638,
    6400, 6670, 6771, 6776, 6912, 6969, 7000, 7300, 7301, 7306,
    7307, 7308, 7789, 9872, 9873, 9874, 9875, 9989, 10067, 10167,
    11000, 11223, 12076, 12223, 12345, 12346, 12361, 12362, 13000,
    16969, 20000, 20001, 20034, 21544, 22222, 23456, 26274, 30100,
    30101, 30102, 31336, 31337, 31338, 33333, 40412, 40421, 40422,
    40423, 40426, 47262, 50505, 50766, 53001, 54320, 54321, 61466,
    65000
};

const std::set<int> Analisis::PUERTOS_BACKDOORS = {
    // Backdoors comunes
    1524, 1999, 2001, 4444, 6667, 6668, 6669, 7000, 8080, 8888,
    9999, 10000, 31337, 31338, 54321
};

const std::set<int> Analisis::PUERTOS_P2P = {
    // Aplicaciones P2P
    411, 412, 1214, 4661, 4662, 4665, 4672, 6346, 6347, 6881, 6882,
    6883, 6884, 6885, 6886, 6887, 6888, 6889, 6890, 6891, 6892,
    6893, 6894, 6895, 6896, 6897, 6898, 6899, 6969
};

const std::set<int> Analisis::PUERTOS_DESARROLLO = {
    // Puertos comunes de desarrollo que podrían ser sospechosos en producción
    3000, 4000, 5000, 8000, 8080, 8081, 8888, 9000, 9090
};


const std::set<int> Analisis::PUERTOS_DESARROLLO = {
    // Puertos comunes de desarrollo que podrían ser sospechosos en producción
    3000, 4000, 5000, 8000, 8080, 8081, 8888, 9000, 9090
};

bool Analisis::esPuertoConocidoMalicioso(int puerto) {
    return PUERTOS_MALICIOSOS.find(puerto) != PUERTOS_MALICIOSOS.end();
}

bool Analisis::esPuertoAdministrativo(int puerto) {
    return PUERTOS_ADMINISTRATIVOS.find(puerto) != PUERTOS_ADMINISTRATIVOS.end();
}

bool Analisis::esPuertoTrojan(int puerto) {
    return PUERTOS_TROJANS.find(puerto) != PUERTOS_TROJANS.end();
}

bool Analisis::esPuertoBackdoor(int puerto) {
    return PUERTOS_BACKDOORS.find(puerto) != PUERTOS_BACKDOORS.end();
}

bool Analisis::esPuertoP2P(int puerto) {
    return PUERTOS_P2P.find(puerto) != PUERTOS_P2P.end();
}

bool Analisis::esPuertoInusual(int puerto) {
    // Puertos en rangos inusuales o específicos
    return (puerto > 49152) || // Puertos dinámicos/privados
           (puerto >= 1024 && puerto <= 5000 && puerto % 1000 == 0) || // Puertos "redondos"
           (puerto >= 31000 && puerto <= 33000); // Rango comúnmente usado por malware
}


int Analisis::calcularPuntuacionRiesgo(const Puerto& puerto) {
    int puntuacion = 0;
    
    if (puerto.estado == EstadoPuerto::ABIERTO) {
        puntuacion += 10;
        
        if (esPuertoConocidoMalicioso(puerto.numero)) puntuacion += 50;
        if (esPuertoTrojan(puerto.numero)) puntuacion += 40;
        if (esPuertoBackdoor(puerto.numero)) puntuacion += 35;
        if (esPuertoP2P(puerto.numero)) puntuacion += 25;
        if (esPuertoAdministrativo(puerto.numero)) puntuacion += 20;
        if (esPuertoInusual(puerto.numero)) puntuacion += 15;
        
        // Puertos de desarrollo en sistemas que no deberían tenerlos
        if (PUERTOS_DESARROLLO.find(puerto.numero) != PUERTOS_DESARROLLO.end()) {
            puntuacion += 15;
        }
        
        // Tiempo de respuesta muy rápido puede indicar servicio configurado
        if (puerto.tiempoRespuesta < 10) puntuacion += 5;
    }
    
    return puntuacion;
}

std::string Analisis::obtenerRazonSospecha(const Puerto& puerto, int nivelSensibilidad) {
    std::vector<std::string> razones;
    
    if (esPuertoConocidoMalicioso(puerto.numero)) {
        razones.push_back("Puerto asociado con malware conocido");
    }
    
    if (esPuertoTrojan(puerto.numero)) {
        razones.push_back("Comúnmente usado por trojans");
    }
    
    if (esPuertoBackdoor(puerto.numero)) {
        razones.push_back("Puerto típico de backdoors");
    }
    
    if (esPuertoP2P(puerto.numero)) {
        razones.push_back("Puerto P2P que puede violar políticas");
    }
    
    if (esPuertoAdministrativo(puerto.numero)) {
        razones.push_back("Servicio administrativo sensible expuesto");
    }
    
    if (esPuertoInusual(puerto.numero)) {
        razones.push_back("Puerto en rango inusual o sospechoso");
    }
    
    if (PUERTOS_DESARROLLO.find(puerto.numero) != PUERTOS_DESARROLLO.end()) {
        razones.push_back("Puerto de desarrollo en sistema de producción");
    }
    
    // Para nivel alto, agregar más criterios
    if (nivelSensibilidad >= 3) {
        if (puerto.numero > 10000 && puerto.numero < 65535) {
            razones.push_back("Puerto en rango alto poco común para servicios estándar");
        }
    }
    
    if (razones.empty()) {
        return "Puerto abierto sin clasificación específica de riesgo";
    }
    
    std::string resultado;
    for (size_t i = 0; i < razones.size(); i++) {
        if (i > 0) resultado += "; ";
        resultado += razones[i];
    }
    
    return resultado;
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
