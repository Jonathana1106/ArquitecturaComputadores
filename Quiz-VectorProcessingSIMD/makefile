CXX = g++                      	# Compilador
CXXFLAGS = -std=c++11 -O3     	# Opciones de compilación
SRC1 = pregunta3.1.cpp         	# Nombre del primer archivo fuente
SRC2 = pregunta3.2.cpp         	# Nombre del segundo archivo fuente

# Nombres de los ejecutables
TARGET1 = pregunta31
TARGET2 = pregunta32

.PHONY: all clean

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(SRC1)
	$(CXX) $(CXXFLAGS) -o $(TARGET1) $(SRC1)

$(TARGET2): $(SRC2)
	$(CXX) $(CXXFLAGS) -o $(TARGET2) $(SRC2)

clean:
	rm -f $(TARGET1) $(TARGET2)
