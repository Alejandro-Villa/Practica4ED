#include<utility>
#include "recetas.h"

using namespace std;

recetas::recetas() {
	datos.clear();
}

unsigned recetas::size() const {
   return datos.size();
} 

void recetas::addReceta(const receta& nueva) {
		pair<string, receta> nelem = make_pair(nueva.getCode(), nueva);
		pair<map<string, receta>::iterator, bool> res;
		res	= datos.insert(nelem);
}

void recetas::borrar(const string codigo) {
	datos.erase(codigo);
}

void recetas::setNutrientes(const ingredientes& ings) {
	for (auto i=begin(); i != end(); ++i) {
		for (auto j=(*i).begin(); j != (*i).end(); ++j) {
			ingrediente ing = ings.get((*j).first); 
			double num = (*j).second / (double)100;

			(*i).setCalorias(((*i).getCalorias() + (num * ing.getCalorias())));
			(*i).setHc(((*i).getHc() + (num * ing.getHc())));
			(*i).setGrasas(((*i).getGrasas() + (num * ing.getGrasas())));
			(*i).setProteinas(((*i).getProteinas() + (num * ing.getProteinas())));
			(*i).setFibra(((*i).getFibra() + (num * ing.getFibra())));
		}
	}
}

receta recetas::operator[](const string& codigo) {
	receta res;
	iterator ite(datos.find(codigo));
	
	if (ite != end())
		res = *ite;
	
	return res;
}

const receta recetas::operator[](const string& codigo) const {
	receta res;
	const_iterator ite(datos.find(codigo));
	
	if (ite != end())
		res = *ite;
	
	return res;
}
istream& operator>>(std::istream& in, recetas& rs) {
	while(((in.peek()) != EOF) && (in.good())) {
		receta r;
		in >> r;
		rs.addReceta(r);
	}

	return in;
}

ostream& operator<<(std::ostream& out, const recetas& rs) {
	
	for(auto i = rs.begin(); i != rs.end(); ++i) {
		out << (*i).getCode() << ": " << (*i).getNombre() << endl; 
	}

	return out;
}

recetas::iterator recetas::begin() {
	iterator ite(datos.begin());
	return ite;
}

recetas::iterator recetas::end() {
	iterator ite(datos.end());
	return ite;
}

recetas::const_iterator recetas::begin() const {
	const_iterator ite(datos.cbegin());
	return ite;
}

recetas::const_iterator recetas::end() const {
	const_iterator ite(datos.cend());
	return ite;
}
