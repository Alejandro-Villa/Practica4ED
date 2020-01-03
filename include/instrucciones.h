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
		
		instrucciones() {};
		instrucciones(const instrucciones& otro);
		instrucciones(const ArbolBinario<std::string> arbol);

		inline acciones getAcciones() const {return acc;};
		inline ArbolBinario<std::string> getArbol() const {return datos;};

		friend ostream& operator<<(ostream& os, const instrucciones& ins);
		instrucciones& operator=(const instrucciones& rhs);
};
#endif
