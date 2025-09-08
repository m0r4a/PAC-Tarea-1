# Escáner de Puertos en C++

## Tabla de Contenidos

### 1. [Descripción general](#descripción-general)

### 2. [Integrantes del equipo](#integrantes-del-equipo)

### 3. [Instrucciones de compilación y ejecución](#instrucciones-de-compilación-y-ejecución)
  - 3.1 [Requisitos](#requisitos)
  - 3.2 [Compilación](#compilación)
  - 3.3 [Ejecución](#ejecución)
    - 3.3.1 [Opciones disponibles](#opciones-disponibles)

### 4. [Enfoque técnico del escaneo](#enfoque-técnico-del-escaneo)

### 5. [Criterios para puertos sospechosos](#criterios-para-puertos-sospechosos)

### 6. [Salida generada](#salida-generada)
  - 6.1 [Salida en Consola](#salida-en-consola)
  - 6.2 [Salida en Archivo (Reporte)](#salida-en-archivo-reporte)

### 7. [Documentación de Módulos](#documentación-de-módulos-escáner-de-puertos-en-c)
  - 7.1 [Módulo: Escaneo.cpp](#módulo-escaneocpp)
    - 7.1.1 [Funciones principales](#funciones-principales)
  - 7.2 [Módulo: Analisis.cpp](#módulo-analisiscpp)
    - 7.2.1 [Funciones principales](#funciones-principales-1)
   - 7.3 [Módulo: Registro.cpp](#módulo-registrocpp)
     - 7.3.1 [Funciones principales](#funciones-principales-2)

## Descripción general

Este proyecto es un escáner de puertos en C++ que realiza un escaneo
real de puertos TCP en una dirección IP específica.
Su objetivo es identificar puertos abiertos, categorizar los que son
potencialmente sospechosos según un conjunto de criterios definidos, y
registrar los resultados en un archivo de texto.

El programa está diseñado de forma modular, con módulos separados
para: 
- Escaneo (escaneo.cpp)
- Análisis de riesgo(analisis.cpp)
- Registro de resultados (registro.cpp)

------------------------------------------------------------------------

## Integrantes del equipo

-   GAEL MORA AGUIRRE
-   ANDRES TADEO FLORES PINAL
-   JORGE LUIS CASAS CRUZ
-   EDUARDO FLORES SMITH

------------------------------------------------------------------------

## Instrucciones de compilación y ejecución

### Requisitos

-   **Sistema operativo:** Compatible con Linux .
-   **Compilador:** g++ (para Linux) y x86_64-w64-mingw32-g++ para Windows.
-   **Librerías:** API nativa de sockets
    -   Winsock2 en Windows
    -   sys/socket.h en Linux
-   **Soporte para Windows:** La compilación para Windows usando MinGW está implementada como una prueba de concepto (PoC). Funciona, pero el rendimiento es significativamente más lento que en Linux, especialmente con un alto número de hilos, por lo que se recomienda escanear un rango reducido de puertos para evitar tiempos de espera prolongados.

### Compilación

El proyecto incluye un **Makefile** para simplificar la compilación.

-   Para compilar en Linux:

``` bash
make 
```

-   Para compilar para Windows (desde Linux, usando MinGW):

``` 
make linux-windows
```

### Ejecución

El programa espera una dirección IP como primer argumento, seguida de
opciones.

Ejemplo de uso:

``` bash
./port_scanner <IP> [-pPUERTOS] [-sNIVEL] [-tTHREADS] [-oARCHIVO]

# Ejemplo
./port_scanner 127.0.0.1 -p 20-1000,8080 -s 3 -t 10 -o reporte.txt
```

#### Opciones disponibles:

-   `-p` o `--puertos`: Especifica los puertos a escanear.

    -   Puede ser un rango (ej. 1-1000) o una lista separada por comas
        (ej. 22,80,443).
    -   Valor por defecto: 1-1024.

-   `-s` o `--sensibilidad`: Define el nivel de sensibilidad para el análisis
    de riesgo.

    -   1 = Bajo
    -   2 = Medio (por defecto)
    -   3 = Alto

-   `-t` o `--threads`: Número de hilos a utilizar en el escaneo.

-   `-o` o `--output`: Nombre del archivo donde se guardará el reporte.

-   `-h` o `--help`: Muestra con detalle la funcionalidad de cada argumento, asi como algunos ejemplos.

------------------------------------------------------------------------

## Enfoque técnico del escaneo

-   Uso de sockets en C++ para realizar conexiones reales a cada
    puerto TCP.
-   Sockets no bloqueantes con timeout de 500ms, diferenciando
    entre:
    -   Puertos abiertos
    -   Puertos cerrados
    -   Puertos filtrados
-   Implementación paralela con hilos (std::thread) y la librería
    `<future>`.
-   El número de hilos se determina automáticamente según el hardware o
    puede ser configurado por el usuario.

------------------------------------------------------------------------

## Criterios para puertos sospechosos

El módulo Analisis.cpp marca un puerto abierto como *sospechoso*
según los siguientes criterios:

1.  **Puertos de malware conocido** → usados por troyanos, backdoors,
    etc.
2.  **Servicios administrativos expuestos** → SSH, RDP, MySQL, etc.
3.  **Puertos P2P** → asociados a aplicaciones de intercambio de
    archivos.
4.  **Puertos en rangos inusuales** → dinámicos o con patrones numéricos
    sospechosos.
5.  **Secuencias consecutivas de puertos abiertos** → detección de al
    menos 5 consecutivos.

La sensibilidad se ajusta con `-s` para:
- Poco sensible (s1)
- Normal (s2)
- Muy sensible (s3)

> Con sensibilidad nos referimos a la cantidad mínima de puntos que un puerto necesita para ser considerado sospechoso, entre más sensible, menos puntos necesita.

------------------------------------------------------------------------

## Salida generada
El programa genera dos tipos de salida, una en la consola y otra opcional en un archivo.

## Salida en Consola
La consola mostrará el progreso del escaneo y, una vez finalizado, una lista de los puertos que se encontraron abiertos en el sistema objetivo, así como una lista separada de los puertos que se categorizaron como sospechosos.

## Salida en Archivo (Reporte)
Si se especifica la opción de salida (-o), el programa generará un archivo de texto con un reporte detallado que incluye:

-Fecha y hora del escaneo.

-La dirección IP objetivo.

-Un listado de los puertos escaneados con su estado (abierto, cerrado o filtrado).

-Una lista de los puertos sospechosos con una justificación clara de por qué fueron marcados como tal.

-Estadísticas del escaneo.

------------------------------------------------------------------------

# Documentación de Módulos - Escáner de Puertos en C++

## Módulo: `escaneo.cpp`

Este módulo contiene la lógica principal para realizar el escaneo de puertos.

### Funciones principales

- **escanearPuertos()**  
  Orquesta el escaneo paralelo utilizando hilos. Controla la distribución de los puertos entre los hilos y recopila los resultados.

- **verificarPuerto(puerto, IP)**  
  Realiza la conexión real a un puerto específico para determinar si está **abierto**, **cerrado** o **filtrado**.  
  - Implementa **sockets no bloqueantes** y un **timeout** para manejar los diferentes estados.  

- **validarIP(IP)**  
  Verifica que la dirección IP ingresada sea válida.

- **obtenerServicio(puerto)**  
  Devuelve el nombre del servicio asociado a un puerto común (ej.: 80 → HTTP).

## Módulo: `analisis.cpp`

Este módulo analiza los resultados del escaneo para identificar **puertos sospechosos**.

### Funciones principales

- **identificarSospechosos(resultados, nivelSensibilidad)**  
  Función principal de análisis.  
  - Calcula la **puntuación de riesgo** de cada puerto abierto según los criterios definidos.  
  - Compara con el **nivel de sensibilidad** del usuario para determinar si el puerto es sospechoso.

- **calcularPuntuacionRiesgo(puerto)**  
  Asigna una **puntuación numérica** a un puerto según sus características:  
  - Si pertenece a la lista de puertos maliciosos.  
  - Si es un puerto administrativo expuesto.  
  - Otros criterios definidos por la política de análisis.

- **obtenerRazonSospecha(puerto)**  
  Devuelve una **cadena de texto** explicando por qué un puerto fue marcado como sospechoso.

- **detectarSecuenciasSospechosas(puertosAbiertos)**  
  Identifica **secuencias de puertos consecutivos abiertos**, lo que podría indicar un patrón de escaneo o comportamiento anómalo.

## Módulo: `registro.cpp`
Este módulo se encarga de generar reportes detallados de los resultados del escaneo en archivos de texto con formato profesional.

### Funciones principales
- **guardarResultados(nombreArchivo, ip, resultados, sospechosos)**  
  Función principal que coordina la generación completa del reporte.  
  - Valida el nombre del archivo antes de la escritura.  
  - Orquesta la escritura de todas las secciones del reporte.  
  - Implementa manejo robusto de errores.

- **escribirEncabezado(archivo, ip)**  
  Genera el encabezado del reporte con información básica.  
  - Título del reporte con formato profesional.  
  - IP objetivo del escaneo y fecha/hora de generación.

- **escribirResultadosCompletos(archivo, resultados)**  
  Crea una tabla formateada con todos los puertos abiertos encontrados.  
  - Columnas: Puerto, Estado, Tiempo de respuesta, Servicio.  
  - Filtra automáticamente solo los puertos abiertos.

- **escribirPuertosSospechosos(archivo, sospechosos)**  
  Genera el análisis detallado de puertos potencialmente peligrosos.  
  - Lista cada puerto sospechoso con su justificación.  
  - Incluye los criterios de evaluación utilizados.

- **escribirEstadisticas(archivo, resultados)**  
  Calcula y presenta estadísticas del escaneo.  
  - Distribución porcentual de estados de puertos.  
  - Tiempo promedio de respuesta y total de puertos escaneados.

- **escribirRecomendaciones(archivo, sospechosos)**  
  Genera recomendaciones de seguridad contextualizadas según el nivel de riesgo detectado.  
  - **CRÍTICO**: Para puertos asociados con malware.  
  - **ALTO RIESGO**: Para servicios administrativos expuestos.  
  - **MEDIO RIESGO**: Para aplicaciones P2P no autorizadas.

