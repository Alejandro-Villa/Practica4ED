/*
 * REQUISITOS:
 *
 * 1.- Mostrar toda la info de una receta. (ingr, info nutri, pasos)
 * 2.- Fusionar dos recetas en una sola.
 *
 * USO:
 * $ /<path>/cocinero_integral <fichero acciones> <fichero recetas> <fichero ingre> <fichero instr>
 *
 * DETALLE FUNCIONAMIENTO:
 *
 * 1.- Mostrar todos los códigos de las recetas, con los nombres y los platos.
 * 2.- Recoger un codigo receta y mostrar en detalle esa receta (ingre, info nutri, pasos).
 * 3.- Se pide otro código para fusionar dos recetas.
 * 4.- Muestra toda la info de la fusión.
 */

#include "color.h"
#include "recetas.h"
#include "receta.h"
#include "instrucciones.h"
#include "acciones.h"
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>

using namespace std;

void ArgErr() {
	cerr << FRED("Error en la llamada: número de argumentos incorrecto.") << endl;
	cerr << FRED("Llamada correcta:\n\t\t <ejecutable> <fichero acciones> <fichero recetas> <fichero ingre> <fichero instr>") << endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]) {
	if(argc != 5)
		ArgErr();
	string pathtoacc = argv[1], pathtorecetas = argv[2], pathtoingre = argv[3], pathtoinst = argv[4];
	ifstream fsacc, fsrecetas, fsingre, fsinst;

	fsacc.open(pathtoacc);
	if(!fsacc) {
		perror(FRED("Apertura de acciones: open()"));
		exit(EXIT_FAILURE);
	}
	
	fsrecetas.open(pathtorecetas);
	if(!fsrecetas) {
		perror(FRED("Apertura de recetas: open()"));
		exit(EXIT_FAILURE);
	}

	fsingre.open(pathtoingre);
	if(!fsingre) {
		perror(FRED("Apertura de ingredientes: open()"));
		exit(EXIT_FAILURE);
	}
	/* TODO: Comprobar si existe el subarchivo cuando conozca la receta */
	fsinst.open(pathtoinst);
	if(!fsinst) {
		perror(FRED("Apertura de instrucciones: open()"));
		exit(EXIT_FAILURE);
	}

	cout << fixed;
	cout << setw(50) << left << "Acciones localizadas en:" << setw(20) << left << KGRN << pathtoacc << RST << endl;
	cout << setw(30) << left << "Leyendo acciones..." << endl;

	acciones accread;
	fsacc >> accread;
	instrucciones::acc = accread;

	cout << setw(50) << left << FGRN("Acciones leídas con éxito") << endl;
	cout << setw(50) << left << "Ingredientes localizados en:" << setw(20) << left << KGRN << pathtoingre << RST << endl;
	cout << setw(30) << left << "Leyendo ingredientes..." << endl;

	recetas allrecetas;
	allrecetas.getIngredientes(fsingre);

	cout << setw(50) << left << FGRN("Ingredientes leídos con éxito") << endl;
	cout << setw(50) << left << "Recetas localizadas en:" << setw(20) << left << KGRN << pathtorecetas << RST << endl;

	fsrecetas >> allrecetas;

	cout << setw(50) << left << "Directorio de instrucciones localizado en:" << setw(20) << left << KGRN << pathtoinst << RST << endl;


	cout << endl << fixed;
	for (auto i=allrecetas.begin(); i != allrecetas.end(); ++i) {
		cout << setw(6) << left << FCYN("CODE: ") << setw(4) << left << (*i).getCode();
		cout << setw(8) << left << FCYN("NOMBRE: ") << setw(35) << left << (*i).getNombre();
		cout<< setw(7) << left <<  FCYN("PLATO: ") << setw(2) << left << (*i).getPlato() << endl;
	}

	return 0;
}
