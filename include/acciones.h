// FICHERO acciones.h
#ifndef ACCIONES
#define ACCIONES

#include<string>
#include<map>
#include<iostream>
//#include<pair>
//#include<utility>

class acciones {
	private:
		std::map<std::string, unsigned char> datos;
	public:
		acciones() {};
		acciones(const std::map<std::string, unsigned char>& accmap);
		acciones(const acciones& otro);

		//inline unsigned char getAriedad(const std::string& nombre) const {return datos.at(nombre);};

		//std::pair<std::string, unsigned char>& operator[] (const std::string& nombre) {return std::makepair(nombre, datos[nombre]);};
		unsigned char operator[] (const std::string& nombre);
		unsigned char operator[] (const std::string& nombre) const;

		bool addAccion(const std::string& nombre, const unsigned char& ariedad);

		friend std::istream& operator>>(std::istream& in, acciones& acc);
};
#endif
