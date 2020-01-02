// FICHERO acciones.h
#ifndef ACCIONES
#define ACCIONES

#include<string>
#include<map>
//#include<pair>
//#include<utility>

class acciones {
	private:
		std::map<std::string, unsigned char> datos;
	public:
		acciones() {};
		acciones(const std::map<std::string, unisgned char>& accmap);
		acciones(const acciones& otro);

		inline unsigned char getAriedad(const std::string& nombre) const {return datos[nombre];};

		//std::pair<std::string, unsigned char>& operator[] (const std::string& nombre) {return std::makepair(nombre, datos[nombre]);};
		unsigned char& operator[] (const std::string& nombre) const {return getAriedad(nombre);};

		bool addAccion(const std::string& nombre, const unsigned char& ariedad);
};
#endif
