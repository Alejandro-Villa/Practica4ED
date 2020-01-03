#include "receta.h"
#include<utility>
#include<regex>
#include<fstream>

using namespace std;

receta::receta() {
	code = "0";
	plato = 0;
	nombre = "Undefined";
	calorias = 0;
	hc = 0;
	grasas = 0;
	proteinas = 0;
	fibra = 0;
}

receta::receta(const receta& orig) {
	code = orig.code;
	plato = orig.plato;
	nombre = orig.nombre;
	calorias = orig.calorias;
	hc = orig.hc;
	grasas = orig.grasas;
	proteinas = orig.proteinas;
	fibra = orig.fibra;

	for (auto i=orig.ings.begin(); i != orig.ings.end(); ++i)
		ings.push_back(*i);
}

unsigned receta::ningredientes() const {
	return ings.size();
}

receta::iterator receta::begin() {
	iterator ite(ings.begin());
	return ite;
}

receta::iterator receta::end() {
	iterator ite(ings.end());
	return ite;
}

receta::const_iterator receta::begin() const {
	const_iterator ite(ings.cbegin());
	return ite;
}

receta::const_iterator receta::end() const {
	const_iterator ite(ings.cend());
	return ite;
}

receta& receta::operator=(const receta& rhs) {
	code = rhs.code;
	plato = rhs.plato;
	nombre = rhs.nombre;
	ings = rhs.ings;
	calorias = rhs.calorias;
	hc = rhs.hc;
	grasas = rhs.grasas;
	proteinas = rhs.proteinas;
	fibra = rhs.fibra;
	
	return *this;
}

void receta::addIngre(const pair<string, unsigned>& nuevo) {
	ingrediente tmp;
	tmp = disp.get(nuevo.first);
	if(tmp.getNombre() != "Undefined") {
		double num = nuevo.second / (double)100;

		ings.push_back(nuevo);
		calorias += num * tmp.getCalorias();
		hc += num * tmp.getHc();
		grasas += num * tmp.getGrasas();
		proteinas += num * tmp.getProteinas();
		fibra += num * tmp.getFibra();
	}
	else 
		cerr << "ERR: addIngre(): el ingrediente " << nuevo.first << " no existe." << endl;
}

ostream& operator<<(ostream& out, const receta& r) {
	char sep = ';';
	out << r.code << sep << r.plato << sep << r.nombre << sep;

	for (auto i=r.ings.begin(); i != r.ings.end(); ++i)
		out << (*i).first << " " << (*i).second << sep;

	return out;
}

istream& operator>>(istream& in, receta& r) {
	string codigo="", splato="", snombre="", allingre="", uningre="", ingre="", scant="";
	unsigned pl=0, cant=0;
	const char delim = ';';

	getline(in, codigo, delim);
	r.setCode(codigo);
	getline(in, splato, delim);
	pl = stoul(splato, nullptr, 10);
	r.setPlato(pl);
	getline(in, snombre, delim);
	r.setNombre(snombre);

	getline(in, allingre);
	
	while(allingre.back() == ' ')
		allingre.pop_back();

	if(allingre.back() != ';')
		allingre.append(";");	
	
	int splitpos = -1;
	while ((splitpos = allingre.find_first_of(';')) != -1) {
		uningre = allingre.substr(0, splitpos);
		allingre = allingre.substr(splitpos + 1, allingre.npos);

		int space = uningre.find_last_of(' ');
		if (space != -1) {
			ingre = uningre.substr(0, space);
			scant = uningre.substr(space+1, uningre.npos);
		
			cant = stoul(scant, nullptr, 10);
			
			pair<string, unsigned> nuevo = make_pair(ingre, cant);
			r.addIngre(nuevo);
		} else 
			cerr << "Error en el procesamiento de ingredientes..." << endl;
	}

	return in;
}

void receta::cargaInstrucciones(istream& is) {
	/*
	 * PASOS:
	 * 1.- Leer la línea. DONE
	 * 2.- Separar la accion. DONE
	 * 3.- Según la ariedad, buscar ingredientes en la linea o en la pila. 
	 * 4.- Construir el árbol.
	 * 5.- Añadirlo a la pila.
	 * 6.- Repetir hasta EOF.
	 */
	string linea, accion, ingr1, ingr2;
	std::stack<ArbolBinario<string>> pila;
	int ari, pos;
	acciones tmpacc(inst.getAcciones());
	
	while(is.good() && (is.peek() != EOF)) {
		is >> accion;
		getline(is, linea);

		while(linea.front() == ' ')
			linea.erase(linea.begin());
		while(linea.back() == ' ')
			linea.pop_back();

		ari = tmpacc[accion];

		if(!linea.empty()) {
			if(ari == '1')  {
				ingr1 = linea;
				if(disp.get(ingr1).getNombre() == "Undefined") {
					cerr << "ERR: cargaInstrucciones(): el ingrediente " << ingr1 << " no está registrado." << endl;
					exit(EXIT_FAILURE);
				}
				else {
					// Construimos el árbol de la acción.
					ArbolBinario<string> tmp(accion);
					tmp.Insertar_Hi(tmp.getRaiz(), ingr1);
					// Lo añadimos al tope de la pila.
					pila.push(tmp);
				}
			}
			else if(ari == '2') {
				pos = 0;
				if(disp.get(linea).getNombre() == "Undefined") {
					do {
						++pos;
						if( linea.empty() || ((pos = linea.find_first_of(" ", pos) ) == (int) linea.npos) ) {
							cerr << "ERR: cargaInstrucciones(): el ingrediente " << ingr1 << " no está registrado." << endl;
							break;
						}
						ingr1 = linea.substr(0, pos);
						cout << "Comprobando: " << ingr1 << endl;
					} while (disp.get(ingr1).getNombre() == "Undefined");
					ingr2 = linea.substr(pos, linea.npos);
					
					while(ingr2.front() == ' ')
						ingr2.erase(ingr2.begin());
					while(ingr2.back() == ' ')
						ingr2.pop_back();
					
					if(disp.get(ingr2).getNombre() == "Undefined")
						cerr << "ERR: cargaInstrucciones(): el ingrediente " << ingr2 << " no está registrado." << endl;

					ArbolBinario<string> tmp(accion);
					tmp.Insertar_Hi(tmp.getRaiz(), ingr1);
					tmp.Insertar_Hd(tmp.getRaiz(), ingr2);
					pila.push(tmp);
				}
				else {
					ingr1 = linea;
					// Buscamos el segundo ingrediente, que sería el tope de la pila
					ArbolBinario<string> tmp(accion);
					tmp.Insertar_Hd(tmp.getRaiz(), ingr1);
					tmp.Insertar_Hi(tmp.getRaiz(), pila.top());
					pila.pop();
					pila.push(tmp);
				}
			}
			instrucciones tmpins(pila.top());
			inst = tmpins;
		}
		else {
			// Buscamos 1 o 2 ingredientes en la pila.
			if(ari == '1') {
				ArbolBinario<string> tmp(accion);
				tmp.Insertar_Hi(tmp.getRaiz(), pila.top());
				pila.pop();
				pila.push(tmp);
			}
			if(ari == '2') {
				ArbolBinario<string> tmp(accion);
				tmp.Insertar_Hd(tmp.getRaiz(), pila.top());
				pila.pop();
				tmp.Insertar_Hi(tmp.getRaiz(), pila.top());
				pila.pop();
				pila.push(tmp);
			}
		}
	}
}

void receta::cargaInstrucciones(const string& pathname) {
	ifstream fin(pathname);

	cargaInstrucciones(fin);
}

void receta::cargaIngredientes(istream& is) {
	is >> disp;
}

void receta::cargaIngredientes(const string& pathname) {
	ifstream fin(pathname);
	
	cargaIngredientes(fin);
}
