#include "acciones.h"
#include<iostream>
#include<exception>

using namespace std;

acciones::acciones(const std::map<std::string, unsigned char>& accmap) {
	datos = accmap;
}

acciones::acciones(const acciones& otro) {
	datos = otro.datos;
}

bool acciones::addAccion(const std::string& nombre, const unsigned char& ariedad) {
	if( (ariedad == '1') | (ariedad == '2') ) {
		datos.insert(pair<string, unsigned char>(nombre, ariedad));
		return true;
	}
	else {
		cerr << "ERR:addAccion(): Ariedad no válida" << endl;
		return false;
	}
}

istream& operator>>(istream& in, acciones& acc) {
	string name;
	unsigned char ariety;

	while(in.peek() !=	EOF && in.good()) {
		in >> name >> ariety;
		if(!acc.addAccion(name, ariety)) {
			cerr << "Saliendo bucle" << endl;
			break;
		}
	}

	return in;
}

ostream& operator<<(ostream& os, const acciones& acc) {
	for (auto i = acc.datos.begin(); i != acc.datos.end(); ++i)
		os << (*i).first << " " << (*i).second << endl;

	return os;
}

unsigned char acciones::operator[] (const string& nombre) {
	try {
		return datos.at(nombre);
	}
	catch(exception& e) {
		return '0';
	}
}

unsigned char acciones::operator[] (const string& nombre) const {
	unsigned char retval = '0';
	try {
		retval = datos.at(nombre);
	}
	catch(exception& e) {
		retval = '0';
	}

	return retval;
}
