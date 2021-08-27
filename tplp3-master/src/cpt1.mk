# establece los directorios a ser utilizados
CPT:= cpt1
SRC_DIR:= src/$(CPT)/
BIN_DIR:= bin/$(CPT)/
OBJ_DIR:= obj/$(CPT)/

# enlaza los archivos de código objeto
$(BIN_DIR)reciprocal: $(OBJ_DIR)main.o $(OBJ_DIR)reciprocal.o | $(BIN_DIR)
	g++ $(CFLAGS) -o $@ $^

# compila el código fuente
$(OBJ_DIR)main.o: $(SRC_DIR)main.c $(SRC_DIR)reciprocal.hpp | $(OBJ_DIR)
	gcc $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)reciprocal.o: $(SRC_DIR)reciprocal.cpp $(SRC_DIR)reciprocal.hpp | $(OBJ_DIR)
	g++ $(CFLAGS) -o $@ -c $<

# reciprocal representa todo el capítulo
$(CPT): $(BIN_DIR)reciprocal

