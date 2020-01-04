#include "instrucciones.h"
#include<stack>
#include<iomanip>

using namespace std;

acciones global;
acciones& instrucciones::acc = global;

instrucciones::instrucciones(const ArbolBinario<string> arbol) {
	datos = arbol;
}

instrucciones::instrucciones(const instrucciones& otro) {
	datos = otro.datos;
}

instrucciones& instrucciones::operator=(const instrucciones& rhs) {
	datos = rhs.datos;
	return *this;
}

ostream& operator<<(ostream& os, const instrucciones& ins) {
	stack<string> pilaingre;

	os << endl;
	for(auto i = ins.datos.beginpostorden(); i != ins.datos.endpostorden(); ++i) {
		if(ins.acc[(*i)] == '0') { // Esto indica que la etiqueta del nodo es una acción.
			pilaingre.push((*i)); // Si es un ingrediente, lo almacena en la pila.
		}
		else { // Si es una acción:
			os << setw(8) << left << " " << (*i) << " ";
			while(!pilaingre.empty()) {
				os << pilaingre.top() << " ";
				pilaingre.pop();
			}
			os << endl;
		}
	}
	return os;
}

instrucciones instrucciones::operator+(const instrucciones& rhs) {
	ArbolBinario<string> tmp("Acompañar");
	ArbolBinario<string> arbol1(getArbol());
	ArbolBinario<string> arbol2(rhs.getArbol());
	tmp.Insertar_Hi(tmp.getRaiz(), arbol1);
	tmp.Insertar_Hd(tmp.getRaiz(), arbol2);

	instrucciones fusion(tmp);
	return fusion;
}
