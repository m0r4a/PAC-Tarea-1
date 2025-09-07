#include "registro.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

const std::string Registro::SEPARADOR = "================================================";

std::string Registro::obtenerFechaHora() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string Registro::formatearEstado(EstadoPuerto estado) {
    switch (estado) {
        case EstadoPuerto::ABIERTO: return "ABIERTO";
        case EstadoPuerto::CERRADO: return "CERRADO";
        case EstadoPuerto::FILTRADO: return "FILTRADO";
        default: return "DESCONOCIDO";
    }
}

bool Registro::validarNombreArchivo(const std::string& nombreArchivo) {
    if (nombreArchivo.empty()) return false;
    
    // Verificar caracteres inválidos en el nombre del archivo
    const std::string caracteresInvalidos = "<>:\"/\\|?*";
    for (char c : nombreArchivo) {
        if (caracteresInvalidos.find(c) != std::string::npos) {
            return false;
        }
    }
    
    return true;
}

void Registro::manejarErrorArchivo(const std::string& nombreArchivo, const std::string& operacion) {
    std::cerr << "Error al " << operacion << " el archivo: " << nombreArchivo << std::endl;
    std::cerr << "Verifique que:" << std::endl;
    std::cerr << "  - El directorio existe y tiene permisos de escritura" << std::endl;
    std::cerr << "  - El nombre del archivo es válido" << std::endl;
    std::cerr << "  - No hay otro programa usando el archivo" << std::endl;
}

void Registro::escribirEncabezado(std::ofstream& archivo, const std::string& ip) {
    archivo << "================================================" << std::endl;
    archivo << "           REPORTE DE ESCANEO DE PUERTOS     " << std::endl;
    archivo << "                (GENERADO POR C++)  " << std::endl;
    archivo << "================================================" << std::endl;
    archivo << std::endl;

    archivo << "  > Objetivo de Escaneo: " << ip << std::endl;
    archivo << "  > Fecha y Hora       : " << obtenerFechaHora() << std::endl;
    archivo << std::endl;
}

void Registro::escribirResultadosCompletos(std::ofstream& archivo, const std::vector<Puerto>& resultados) {
    archivo << SEPARADOR << std::endl;
    archivo << "      >>>> LISTADO DE PUERTOS ABIERTOS <<<<" << std::endl;
    archivo << SEPARADOR << std::endl;
    archivo << std::endl;

    // Filtrar solo puertos abiertos
    std::vector<Puerto> puertosAbiertos;
    for (const auto& puerto : resultados) {
        if (puerto.estado == EstadoPuerto::ABIERTO) {
            puertosAbiertos.push_back(puerto);
        }
    }
    
    if (puertosAbiertos.empty()) {
        archivo << "  ✓ No se encontraron puertos abiertos. ¡Excelente!" << std::endl;
        archivo << std::endl;
        return;
    }
    
    archivo << std::left << std::setw(10) << "PUERTO" 
            << "|" << std::setw(15) << "ESTADO" 
            << "|" << std::setw(15) << "RESPUESTA(ms)"
            << "|" << "SERVICIO" << std::endl;
    archivo << "----------+---------------+---------------+--------------------" << std::endl;

    for (const auto& puerto : puertosAbiertos) {
        archivo << std::left << std::setw(10) << puerto.numero
                << "|" << std::setw(15) << formatearEstado(puerto.estado)
                << "|" << std::setw(15) << (puerto.tiempoRespuesta >= 0 ? std::to_string(puerto.tiempoRespuesta) : "N/A")
                << "|" << puerto.servicio << std::endl;
    }
    archivo << std::endl;
}

void Registro::escribirPuertosSospechosos(std::ofstream& archivo, const std::vector<Puerto>& sospechosos) {
    archivo << SEPARADOR << std::endl;
    archivo << "           ANÁLISIS DE PUERTOS SOSPECHOSOS" << std::endl;
    archivo << SEPARADOR << std::endl;
    archivo << std::endl;
    
    if (sospechosos.empty()) {
        archivo << "✓ No se encontraron puertos sospechosos según los criterios definidos." << std::endl;
        archivo << "  Esto es un buen indicador de seguridad." << std::endl;
        archivo << std::endl;
        return;
    }
    
    archivo << "⚠ ATENCIÓN: Se encontraron " << sospechosos.size() 
            << " puerto(s) potencialmente sospechoso(s):" << std::endl << std::endl;
    
    for (const auto& puerto : sospechosos) {
        archivo << "Puerto " << puerto.numero << " (" << puerto.servicio << "):" << std::endl;
        archivo << "  Estado: " << formatearEstado(puerto.estado) << std::endl;
        archivo << "  Tiempo de respuesta: " << puerto.tiempoRespuesta << " ms" << std::endl;
        archivo << "  Razón de sospecha: " << puerto.razonSospecha << std::endl;
        archivo << std::endl;
    }
    
    // Criterios utilizados
    archivo << "CRITERIOS DE EVALUACIÓN UTILIZADOS:" << std::endl;
    archivo << "- Puertos asociados con malware conocido" << std::endl;
    archivo << "- Puertos comúnmente usados por trojans y backdoors" << std::endl;
    archivo << "- Servicios administrativos sensibles expuestos" << std::endl;
    archivo << "- Puertos P2P que pueden violar políticas de seguridad" << std::endl;
    archivo << "- Puertos en rangos inusuales o sospechosos" << std::endl;
    archivo << "- Puertos de desarrollo en sistemas de producción" << std::endl;
    archivo << "- Secuencias consecutivas extensas de puertos abiertos" << std::endl;
    archivo << std::endl;
}

void Registro::escribirEstadisticas(std::ofstream& archivo, const std::vector<Puerto>& resultados) {
    int abiertos = 0, cerrados = 0, filtrados = 0;
    int tiempoTotal = 0, tiempoValido = 0;
    
    for (const auto& puerto : resultados) {
        switch (puerto.estado) {
            case EstadoPuerto::ABIERTO: abiertos++; break;
            case EstadoPuerto::CERRADO: cerrados++; break;
            case EstadoPuerto::FILTRADO: filtrados++; break;
        }
        
        if (puerto.tiempoRespuesta >= 0) {
            tiempoTotal += puerto.tiempoRespuesta;
            tiempoValido++;
        }
    }
    
    archivo << SEPARADOR << std::endl;
    archivo << "           ESTADÍSTICAS DEL ESCANEO" << std::endl;
    archivo << SEPARADOR << std::endl;
    archivo << std::endl;
    
    archivo << "Total de puertos escaneados: " << resultados.size() << std::endl;
    archivo << "Puertos abiertos: " << abiertos << " (" 
            << std::fixed << std::setprecision(1) 
            << (100.0 * abiertos / resultados.size()) << "%)" << std::endl;
    archivo << "Puertos cerrados: " << cerrados << " (" 
            << std::fixed << std::setprecision(1) 
            << (100.0 * cerrados / resultados.size()) << "%)" << std::endl;
    archivo << "Puertos filtrados: " << filtrados << " (" 
            << std::fixed << std::setprecision(1) 
            << (100.0 * filtrados / resultados.size()) << "%)" << std::endl;
    
    if (tiempoValido > 0) {
        archivo << "Tiempo promedio de respuesta: " 
                << std::fixed << std::setprecision(1) 
                << (static_cast<double>(tiempoTotal) / tiempoValido) << " ms" << std::endl;
    }
    archivo << std::endl;
}

void Registro::escribirRecomendaciones(std::ofstream& archivo, const std::vector<Puerto>& sospechosos) {
    archivo << SEPARADOR << std::endl;
    archivo << "           RECOMENDACIONES DE SEGURIDAD" << std::endl;
    archivo << SEPARADOR << std::endl;
    archivo << std::endl;
    
    if (sospechosos.empty()) {
        archivo << "RECOMENDACIONES GENERALES:" << std::endl;
        archivo << "✓ Mantener un inventario actualizado de servicios autorizados" << std::endl;
        archivo << "✓ Realizar escaneos periódicos para detectar cambios" << std::endl;
        archivo << "✓ Implementar monitoreo continuo de puertos" << std::endl;
        archivo << "✓ Mantener actualizados todos los servicios" << std::endl;
        archivo << std::endl;
        return;
    }
    
    archivo << "ACCIONES RECOMENDADAS URGENTES:" << std::endl;
    archivo << std::endl;
    
    bool hayMaliciosos = false, hayAdministrativos = false, hayP2P = false;
    
    for (const auto& puerto : sospechosos) {
        if (puerto.razonSospecha.find("malware") != std::string::npos) {
            hayMaliciosos = true;
        }
        if (puerto.razonSospecha.find("administrativo") != std::string::npos) {
            hayAdministrativos = true;
        }
        if (puerto.razonSospecha.find("P2P") != std::string::npos) {
            hayP2P = true;
        }
    }
    
    if (hayMaliciosos) {
        archivo << "🚨 CRÍTICO - Puertos asociados con malware detectados:" << std::endl;
        archivo << "   • Realizar análisis antimalware completo inmediatamente" << std::endl;
        archivo << "   • Aislar el sistema de la red si es posible" << std::endl;
        archivo << "   • Verificar logs del sistema y de red" << std::endl;
        archivo << "   • Considerar restauración desde backup limpio" << std::endl;
        archivo << std::endl;
    }
    
    if (hayAdministrativos) {
        archivo << "⚠ ALTO RIESGO - Servicios administrativos expuestos:" << std::endl;
        archivo << "   • Restringir acceso mediante firewall" << std::endl;
        archivo << "   • Implementar VPN para acceso remoto" << std::endl;
        archivo << "   • Verificar credenciales fuertes" << std::endl;
        archivo << "   • Activar logging y monitoreo" << std::endl;
        archivo << std::endl;
    }
    
    if (hayP2P) {
        archivo << "📋 MEDIO RIESGO - Aplicaciones P2P detectadas:" << std::endl;
        archivo << "   • Verificar si están autorizadas por política" << std::endl;
        archivo << "   • Considerar bloqueo si violan políticas" << std::endl;
        archivo << "   • Evaluar impacto en ancho de banda" << std::endl;
        archivo << std::endl;
    }
    
    archivo << "RECOMENDACIONES GENERALES:" << std::endl;
    archivo << "• Implementar principio de menor privilegio" << std::endl;
    archivo << "• Configurar firewall para bloquear puertos no necesarios" << std::endl;
    archivo << "• Establecer monitoreo continuo de puertos" << std::endl;
    archivo << "• Realizar escaneos periódicos de vulnerabilidades" << std::endl;
    archivo << "• Mantener documentación actualizada de servicios" << std::endl;
    archivo << "• Implementar sistema de detección de intrusiones (IDS)" << std::endl;
    archivo << std::endl;
}

bool Registro::guardarResultados(const std::string& nombreArchivo, 
                                const std::string& ip,
                                const std::vector<Puerto>& resultados,
                                const std::vector<Puerto>& sospechosos) {
    try {
        // Validar nombre de archivo
        if (!validarNombreArchivo(nombreArchivo)) {
            manejarErrorArchivo(nombreArchivo, "validar");
            return false;
        }
        
        // Abrir archivo para escritura
        std::ofstream archivo(nombreArchivo, std::ios::out | std::ios::trunc);
        if (!archivo.is_open()) {
            manejarErrorArchivo(nombreArchivo, "abrir");
            return false;
        }
        
        // Escribir contenido del reporte
        escribirEncabezado(archivo, ip);
        escribirResultadosCompletos(archivo, resultados);
        escribirPuertosSospechosos(archivo, sospechosos);
        escribirEstadisticas(archivo, resultados);
        escribirRecomendaciones(archivo, sospechosos);
        
        // Pie del reporte
        archivo << SEPARADOR << std::endl;
        archivo << "Reporte generado por Escáner de Puertos C++ v1.01" << std::endl;
        archivo << "Fecha de generación: " << obtenerFechaHora() << std::endl;
        archivo << SEPARADOR << std::endl;
        
        archivo.close();
        
        return true;
        
    } catch (const std::exception& e) {
        std::cerr << "Excepción al guardar archivo: " << e.what() << std::endl;
        manejarErrorArchivo(nombreArchivo, "escribir");
        return false;
    }
}