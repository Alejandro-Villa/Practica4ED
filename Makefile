SRC = src
INC = include
OBJ = obj
BIN = bin
CXX = g++
WARN = -Wall -Wpedantic -Wextra # Añadir si se quieren warnings detalladas
CPPFLAGS = -g $(WARN) -I$(INC) -c --std=c++11

all: dirs $(BIN)/cocinero_integral 

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Creación de Directorios ***********
dirs: | $(OBJ) $(BIN)


$(OBJ):
	mkdir -p $@
$(BIN):
	mkdir -p $@
	
# ************ Compilación de módulos ************
$(OBJ)/ingredientes.o: $(SRC)/ingredientes.cpp $(INC)/ingredientes.h $(INC)/ingrediente.h
	$(CXX) $(CPPFLAGS) $(SRC)/ingredientes.cpp -o $(OBJ)/ingredientes.o 	

$(OBJ)/ingrediente.o: $(SRC)/ingrediente.cpp $(INC)/ingrediente.h 
	$(CXX) $(CPPFLAGS) $(SRC)/ingrediente.cpp -o $(OBJ)/ingrediente.o 	
	
$(OBJ)/receta.o: $(SRC)/receta.cpp $(INC)/receta.h $(INC)/ingrediente.h $(INC)/ingredientes.h
	$(CXX) $(CPPFLAGS) $(SRC)/receta.cpp -o $(OBJ)/receta.o

$(OBJ)/recetas.o: $(SRC)/recetas.cpp $(INC)/recetas.h $(INC)/receta.h $(INC)/ingrediente.h $(INC)/ingredientes.h
	$(CXX) $(CPPFLAGS) $(SRC)/recetas.cpp -o $(OBJ)/recetas.o
			
$(OBJ)/cocinero_integral.o: $(SRC)/cocinero_integral.cpp $(INC)/acciones.h $(INC)/receta.h $(INC)/recetas.h $(INC)/ingrediente.h $(INC)/ingredientes.h
	$(CXX) $(CPPFLAGS)  $(SRC)/cocinero_integral.cpp -o  $(OBJ)/cocinero_integral.o 	
	
$(OBJ)/instrucciones.o: $(SRC)/instrucciones.cpp $(INC)/acciones.h $(INC)/instrucciones.h $(INC)/arbolbinario.h $(INC)/arbolbinario.tpp 
	$(CXX) $(CPPFLAGS)  $(SRC)/instrucciones.cpp -o  $(OBJ)/instrucciones.o 	
	
$(OBJ)/acciones.o: $(SRC)/acciones.cpp $(INC)/acciones.h 
	$(CXX) $(CPPFLAGS)  $(SRC)/acciones.cpp -o  $(OBJ)/acciones.o 	

$(BIN)/cocinero_integral: $(OBJ)/cocinero_integral.o $(OBJ)/receta.o $(OBJ)/recetas.o $(OBJ)/ingrediente.o $(OBJ)/ingredientes.o $(OBJ)/instrucciones.o $(OBJ)/acciones.o 	
	$(CXX) -o $(BIN)/cocinero_integral $(OBJ)/cocinero_integral.o  $(OBJ)/receta.o $(OBJ)/recetas.o $(OBJ)/ingrediente.o $(OBJ)/ingredientes.o $(OBJ)/instrucciones.o $(OBJ)/acciones.o 	
	
# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm -r $(BIN)/* doc/html/* doc/latex/*

# ************ Entrega *************
entrega: all mrproper
	-rm -f practica4.tgz
	tar -czvf practica4.tgz \
		--exclude-vcs --exclude-vcs-ignores --exclude='datos/*' \
		--exclude='README.md' --exclude='practica4.tgz' \
		../`basename $(PWD)` 
