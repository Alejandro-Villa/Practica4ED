/**
 * @file ingredientes.cpp
 * @brief Implementación de la clase @c ingredientes::ingredientes.
 */
#include "ingredientes.h"
#include "ingrediente.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
/**
 * @brief Directiva de preprocesamiento para depuración.
 *
 * Si esta macro está definida a @c 1 o @c true, se mostrarán mensajes de depuración por salida estándar.
 *
 * Si está definida a @c 0 o @c false, no se mostrarán mensajes.
 */
#define DEBUG 0

using namespace std;

ingredientes::iterator ingredientes::begin() {
	return ingredientes::iterator(datos.begin());
}

ingredientes::iterator ingredientes::end() {
	return ingredientes::iterator(datos.end());
}

ingredientes::const_iterator ingredientes::begin() const {
	return ingredientes::const_iterator(datos.cbegin());
}

ingredientes::const_iterator ingredientes::end() const {
	return ingredientes::const_iterator(datos.cend());
}

ingredientes::ingredientes() {
	// No es necesario, pues el constructor de vector ya asigna el puntero a nullptr. 
}

ingredientes::ingredientes(const ingredientes& original) {
	datos = original.datos;
	indice = original.indice;	
}

unsigned ingredientes::size() const {
	return datos.size();
}

bool comparaNombre(const ingrediente& primero, const ingrediente& segundo) {
	return primero.getNombre() < segundo.getNombre();
}

void ingredientes::insertar(const ingrediente& nuevo) {
	if(size() > 0) {
		if (nuevo.getNombre() > datos.back().getNombre()) {
			datos.push_back(nuevo);
			indice.push_back(indice.size());
		}
		else {
		iterator pos(lower_bound(datos.begin(), datos.end(), nuevo, comparaNombre));
	
		if( !((*pos).getNombre() == nuevo.getNombre()) ) {
			int posicion = pos - begin();
			for(auto it = indice.begin(); it != indice.end(); ++it)
				if(*it >= posicion)
					++(*it);

			datos.insert(pos.getIterator(), nuevo);

            auto comparaTipo = [&](int primero, const ingrediente& segundo) {
				if(datos[primero].getTipo() < segundo.getTipo())
					return true;
				else if (datos[primero].getTipo() == segundo.getTipo())
					return datos[primero].getNombre() < segundo.getNombre();
				else
					return false;
			};

			vector<int>::iterator indicepos = lower_bound(indice.begin(), indice.end(), nuevo, comparaTipo);
			indice.insert(indicepos, posicion);
			}
		}
	}
	else { 
		datos.push_back(nuevo);
		indice.push_back(0);
	}
}

ostream& operator<< (ostream &out, const ingredientes &is) {
	for (auto i = is.begin(); i != is.end(); ++i) 
		out << *i;

	return out;
}

istream& operator>> (istream &in, ingredientes &is) {
	ingrediente tmp;
	string linea;
	getline(in, linea);

	unsigned i=0;

	while (in.peek() != EOF && in.good()) {
		in >> tmp;
		if(DEBUG) {
			cout << "DEBUG:Ingrediente a insertar " << tmp << endl;
		}
		++i;
		is.insertar(tmp);
	}

	if(DEBUG)
		cout << "DEBUG: Total insertados: " << i << endl;

	return in;
}

ostream& ingredientes::ImprimirPorTipo(ostream& out) const {
	for (auto i=indice.begin(); i != indice.end(); ++i) {
		out << datos[*i];
	}
	return out;
}

ingredientes ingredientes::getIngredienteTipo(string tipo) const {
	ingredientes resultado;

	for (auto i = begin(); i != end(); ++i) {
		if((*i).getTipo() == tipo)
			resultado.insertar((*i));
	}

	return resultado;
}

ingrediente ingredientes::get(string nombre) const {
	ingrediente resultado;
	bool encontrado = false;

	for (unsigned i=0; i < size() && !encontrado; ++i)
		if (datos[i].getNombre() == nombre) {
			encontrado = true;
			resultado = datos[i];
			if(DEBUG)
				cout << "DEBUG:indice: " << i << endl;
		}

	return resultado;
}

vector<string> ingredientes::getTipos() const {
	vector<string> totalTipos;
	
	for (auto i = indice.begin(); i != indice.end(); ++i) {
		string tipo = datos[(*i)].getTipo();
		bool repetido = false;
		for (auto j = totalTipos.begin(); j != totalTipos.end(); ++j)
			if(*j == tipo) {
				repetido = true;
				break;
			}
		if(!repetido)
			totalTipos.push_back(tipo);
	}
	
	return totalTipos;
}

void ingredientes::borrar(string nombre) {
	ingrediente borrado(get(nombre));
	if (borrado.getNombre() != "Undefined") {
		vector<ingrediente>::iterator pos = lower_bound(datos.begin(), datos.end(), borrado, comparaNombre);
		int ipos = pos - datos.begin();
		datos.erase(pos);
		
		for (auto i = indice.begin(); i != indice.end(); ++i)
		   if ((*i) == ipos) {
				indice.erase(i);
				break;
		   }

		for (auto i = indice.begin(); i != indice.end(); ++i)
			if ((*i) > ipos)
				--(*i);

	}
}
