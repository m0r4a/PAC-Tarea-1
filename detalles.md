# Objetivo

Desarrollar en C++ un programa modular que realice un escaneo real de puertos en una 
dirección IP específica, identifique puertos potencialmente sospechosos según criterios 
definidos por el equipo, y registre los resultados en un archivo. El reto busca integrar 
conocimientos técnicos y éticos de ciberseguridad, manejo de memoria, modularidad, 
validación de entrada y documentación profesional

## Descripción del reto

### Escaneo real obligatorio 

El programa debe realizar un escaneo real de puertos en una IP local o remota 
(preferentemente 127.0.0.1 o una máquina virtual controlada). No se aceptan simulaciones ni 
generación ficticia de resultados.

El equipo deberá investigar cómo implementar el escaneo en C++, utilizando alguna de las 
siguientes estrategias:

#### Pistas para investigar 

- Sockets en C++: Usar la API de sockets (<winsock2.h> en Windows o <sys/socket.h> en 
Linux) para intentar conectarse a cada puerto y determinar si está abierto.

- Comandos externos: Invocar herramientas como nmap o netstat desde C++ usando 
system() o popen() para capturar resultados.

- Librerías de red: Explorar librerías como Boost.Asio para manejo de conexiones 
TCP/UDP.

- Tiempo de espera: Implementar lógica para detectar puertos filtrados o cerrados según 
el tiempo de respuesta.

El enfoque elegido debe estar documentado y justificado en el README.md.

## Entrada esperada del programa

El programa debe solicitar al usuario:

- Dirección IP objetivo (string)
- Puerto inicial (int) y puerto final (int) o lista de puertos a escanear (int[])
- Nombre del archivo de salida (string)
- (Opcional) Nivel de sensibilidad para marcar puertos como sospechosos

## Salida esperada del programa

El programa debe generar:
- En consola:
  - Lista de puertos escaneados con su estado: 
    - Abierto
    - Cerrado
    - Filtrado (solo si se puede detectar)
  - Identificación de puertos sospechosos según criterios definidos por el equipo. Definir los parámetros con los que ustedes categorizarían como sospechoso a un puerto abierto.
- En archivo de texto (registro.txt o nombre definido por el usuario):
  - Fecha y hora del escaneo
  - Dirección IP objetivo
  - Rango de puertos o lista de puertos con estado
  - Lista de puertos sospechosos con detalles
  - Justificación de por qué se consideran sospechosos

## Requisitos técnicos para el desarrollo del programa 

- Uso de estructuras (struct) para representar cada puerto
- Memoria dinámica para almacenar resultados del escaneo
  - Modularidad: mínimo tres módulos separados: 
  - Escaneo.cpp / Escaneo.h: lógica de escaneo real
  - Analisis.cpp / Analisis.h: criterios de sospecha
  - Registro.cpp / Registro.h: escritura en archivo y manejo de errores
  - No olvidar el archivo principal con el main()
- Manejo de errores: IP inválida, rangos incorrectos, fallos de conexión
- Validación de entrada y uso de excepciones (try/catch)
- Documentación clara en README.md

## Entregables 

- Repositorio público en GitHub con: 
  - Código fuente (.cpp y .h)
  - Archivo de salida generado por el programa
  - README.md con: 
    - Descripción del proyecto
    - Integrantes del equipo
    - Instrucciones de compilación y ejecución
    - Enfoque técnico elegido para el escaneo
    - Criterios definidos para puertos sospechosos
- Fecha límite: 7 de septiembre
- No se aceptan modificaciones posteriores a la fecha límite (se evalúa con 0 si las hay)

 ## Investigación sugerida

- API de sockets en C++ (connect(), bind(), recv(), timeout)
- Uso de system() o popen() para ejecutar comandos externos
- Librerías como Boost.Asio o POCO C++ Libraries
- Asociación de puertos con servicios conocidos (std::map)
- Buenas prácticas de modularidad, documentación y control de versiones


