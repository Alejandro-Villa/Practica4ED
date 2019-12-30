// FICHERO instrucciones.h
#ifndef INSTRUCCIONES
#define INSTRUCCIONES

#include<string>
#include "acciones.h"
#include "arbolbinario.h"

class instrucciones {
	private:
		ArbolBinario<std::string> datos;
		static acciones &acc;
};

#endif
