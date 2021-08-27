# establece los directorios a ser utilizados
CPT:= cpt4
SRC_DIR:= src/$(CPT)/
BIN_DIR:= bin/$(CPT)/
OBJ_DIR:= obj/$(CPT)/

# archivos binarios ejecutables
NAMES := thread-create thread-create2 primes detached critical-section tsd cleanup job-queue1 job-queue2 job-queue3 spin-condvar condvar thread-pid
BIN := $(addprefix $(BIN_DIR),$(NAMES))

$(BIN): $(BIN_DIR)%: $(OBJ_DIR)%.o | $(BIN_DIR)
	g++ $(CFLAGS) -o $@ $< -lpthread

# codigo objeto sin enlazar
OBJ := $(patsubst %, $(OBJ_DIR)%.o ,$(NAMES))

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	gcc $(CFLAGS) -o $@ -c $<

$(OBJ_DIR)/cxx-exit.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	g++ $(CFLAGS) -o $@ -c $<

# compila todas las recetas
$(CPT): $(BIN) $(OBJ)

