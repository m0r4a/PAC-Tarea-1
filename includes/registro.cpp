// NOTA: ESTO NO ESTÁ LISTO, NO TRABAJAR CON EL

#include "registro.h"

const std::string Registro::SEPARADOR = "================================================";

// función que tenga la fecha

// una función que formatee el estado del puerto

// función que valide el nombre del archivo
// parametro -o para poner outputs custom

// función para manejar los errores al manejar archivos
// log o std::cerr

// función que escriba el o los encabezados del reporte
// fecha, ip objetivo, título

// escribir una lista con los puertos abiertos, una tabla con
// puerto, estado, tiempo, servicio

// escribir la lista de puertos sospechosos con sus motivos y criterios
// lo de anlisis.cpp, algo así como puerto.tiempoRespuesta

// no sé si vaya a ser necesario pero escribir estadísticas del escaneo
// puertos totales, porcentajes, tiempo promedio y así

// escribir las recomendaciones basadas en tipos de puerto sospechoso, esto puede
// cambiar mucho, pero el core es usar var = puerto.razonSospecha.find("malware"), luego
// en base a si var entonces emitir recomendaciones


// Y ya guardar el reporte
// validar el nombre
// abrirlo
// escribir el encabezado, resultados, bla bla, recomendaciones
// pasar las funciones por la funcion de manejo de errores
// cerrar el archivo y retornar true si todo bn
