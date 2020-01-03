// FICHERO instrucciones.h
#ifndef INSTRUCCIONES
#define INSTRUCCIONES

#include<string>
#include<iostream>
#include<stack>
#include "acciones.h"
#include "arbolbinario.h"

class instrucciones {
	private:
		ArbolBinario<std::string> datos;
	
	public:
		static acciones &acc;
		static int prueba;
		
		instrucciones() {};
		instrucciones(const instrucciones& otro);

		inline acciones getAcciones() const {return acc;};
		inline ArbolBinario<std::string> getArbol() const {return datos;};
};
#endif
