# subdirectorio para cada capítulo
CAPITULOS := cpt1 cpt2 cpt3 cpt4 cpt5

# comandos que no representan ningún archivo
.PHONY: all $(CAPITULOS) clean

# compila todos los capítulos
all: $(CAPITULOS)

# incluye el makefile de cada capítulo
include $(patsubst %, src/%.mk, $(CAPITULOS))

# crea subdirectorios en bin/ y obj/ para cada capítulo
$(patsubst %, bin/%/ ,$(CAPITULOS)): | bin/ ; mkdir $@
$(patsubst %, obj/%/ ,$(CAPITULOS)): | obj/ ; mkdir $@
bin/ obj/: ; mkdir $@

# elimina los archivos compilados
clean:
	rm -rf ./obj ./bin

