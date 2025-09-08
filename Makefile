# Makefile para Escáner de Puertos C++
# Soporta compilación para Linux (por defecto) y Cross-compile MinGW (windows)

# Compiladores
CXX        := g++
MINGW_CXX  := x86_64-w64-mingw32-g++
# Nota: Así se llama el biario el archlinux, en
# otras distribuciones podría ser distinto.

# Flags
CXXSTD     := c++11
CXXFLAGS   := -std=$(CXXSTD) -Wall -Wextra -O2

# No quiero instalar librerías en windows para testear
# el script así que las linkeo directamente
LDFLAGS_LINUX := -pthread
LDFLAGS_WIN   := -lws2_32 -static -static-libgcc -static-libstdc++

# Fuentes
SRCS := main.cpp includes/escaneo.cpp includes/analisis.cpp includes/registro.cpp

OUT_LINUX := port_scanner
OUT_WIN   := port_scanner.exe

.PHONY: all linux linux-windows test clean help

# Se compila para linux por defecto
all: linux

linux:
	@echo "Compilando para Linux: $(OUT_LINUX)"
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(OUT_LINUX) $(LDFLAGS_LINUX)
	@echo "Compilado: ./$(OUT_LINUX)"

linux-windows:
	@echo "Compilando para windows desde linux: $(OUT_WIN)"
	$(MINGW_CXX) $(CXXFLAGS) $(SRCS) -o $(OUT_WIN) $(LDFLAGS_WIN)
	@echo "Compilado: $(OUT_WIN)"

test:
	@echo "Haciendo un test contra localhost con los primeros 1024 puertos"
	./$(OUT_LINUX) 127.0.0.1 -p1-1024 -t 5 -o test.txt

clean:
	@echo "Limpiando..."
	-rm -f $(OUT_LINUX) $(OUT_WIN) test.txt

help:
	@echo "Makefile para Escáner de Puertos C++"
	@echo ""
	@echo "Objetivos disponibles:"
	@echo "  make / make linux        : Compila para Linux (por defecto) -> $(OUT_LINUX)"
	@echo "  make linux-windows       : Cross-compile para Windows (MinGW) -> $(OUT_WIN)"
	@echo "  make test                : Hace un escaneo de los primeros 1024 puertos en localhost (linux)"
	@echo "  make clean               : Elimina binarios"
	@echo "  make help                : Muestra esta ayuda"
	@echo ""
	@echo "Notas:"
	@echo " - Ambos targets usan: main.cpp e includes/*.cpp"
	@echo " - Para compilar para windows necesitas tener MinGW instalado."
