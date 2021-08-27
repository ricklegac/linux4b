# establece los directorios a ser utilizados
CPT:= cpt2
SRC_DIR:= src/$(CPT)/
BIN_DIR:= bin/$(CPT)/
OBJ_DIR:= obj/$(CPT)/

# archivos binarios ejecutables
NAMES := arglist getopt_long print-env client temp_file readfile
BIN := $(addprefix $(BIN_DIR),$(NAMES))

$(BIN): $(BIN_DIR)%: $(OBJ_DIR)%.o | $(BIN_DIR)
	gcc $(CFLAGS) -o $@ $<

# codigo objeto sin enlazar
NAMES += test app tifftest
OBJ := $(patsubst %, $(OBJ_DIR)%.o ,$(NAMES))

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	gcc $(CFLAGS) -o $@ -c $<

# convierte test.o en la libreria libtest.a
$(OBJ_DIR)libtest.a: $(OBJ_DIR)test.o | $(OBJ_DIR)
	ar cr $@ $<

# enlaza app.o con libtest.a
CPT2_LIB := $(OBJ_DIR)
$(BIN_DIR)app: $(OBJ_DIR)app.o $(OBJ_DIR)libtest.a | $(BIN_DIR)
	gcc -o $@ $< -L$(CPT2_LIB) -ltest

# enlaza tifftest.o con la librería libtiff
$(BIN_DIR)tifftest: $(OBJ_DIR)tifftest.o | $(BIN_DIR)
	gcc -o $@ $< -ltiff

# compila todas las recetas
$(CPT): $(BIN) $(OBJ) $(OBJ_DIR)libtest.a $(BIN_DIR)app $(BIN_DIR)tifftest

