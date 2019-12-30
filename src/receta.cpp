#include "receta.h"
#include<utility>
#include<regex>

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
