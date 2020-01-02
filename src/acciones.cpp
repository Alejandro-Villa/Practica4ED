#include "acciones.h"
#include<iostream>

using namespace std;

acciones::acciones(const std::map<std::string, unsigned char>& accmap) {
	datos = accmap;
}

acciones::acciones(const acciones& otro) {
	datos = otro.datos;
}

bool acciones::addAccion(const std::string& nombre, const unsigned char& ariedad) {
	if( (ariedad == 1) | (ariedad == 2) ) {
		datos.insert(pair<string, unsigned char>(nombre, ariedad));
		return true;
	}
	else {
		cerr << "ERR:addAccion(): Ariedad no válida" << endl;
		return false;
	}
}
