# establece los directorios a ser utilizados
CPT:= cpt3
SRC_DIR:= src/$(CPT)/
BIN_DIR:= bin/$(CPT)/
OBJ_DIR:= obj/$(CPT)/

# archivos binarios ejecutables
NAMES := print-pid system fork fork-exec sigusr1 zombie sigchld
BIN := $(addprefix $(BIN_DIR),$(NAMES))

$(BIN): $(BIN_DIR)%: $(OBJ_DIR)%.o | $(BIN_DIR)
	gcc $(CFLAGS) -o $@ $<

# codigo objeto sin enlazar
OBJ := $(patsubst %, $(OBJ_DIR)%.o ,$(NAMES))

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	gcc $(CFLAGS) -o $@ -c $<

# compila todas las recetas
$(CPT): $(BIN) $(OBJ)

