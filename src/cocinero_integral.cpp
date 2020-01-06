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

string makepathtoins(const string& base, const string& rcode);

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
	cout << setw(50) << left << "Acciones localizadas en: " << KGRN << pathtoacc << RST << endl;
	cout << setw(30) << left << "Leyendo acciones..." << endl;

	acciones accread;
	fsacc >> accread;
	instrucciones::setAcciones(accread);

	cout << setw(8) << "" << setw(50) << left << FGRN("Acciones leídas con éxito") << endl;
	cout << setw(50) << left << "Ingredientes localizados en: " << KGRN << pathtoingre << RST << endl;
	cout << setw(30) << left << "Leyendo ingredientes..." << endl;

	recetas allrecetas;
	allrecetas.getIngredientes(fsingre);

	cout << setw(8) << "" << setw(50) << left << FGRN("Ingredientes leídos con éxito") << endl;
	cout << setw(50) << left << "Recetas localizadas en: " << KGRN << pathtorecetas << RST << endl;
	cout << setw(30) << left << "Leyendo ingredientes..." << endl;

	fsrecetas >> allrecetas;

	cout << setw(8) << "" << setw(50) << left << FGRN("Recetas leídas con éxito") << endl;
	cout << setw(50) << left << "Directorio de instrucciones localizado en: " << KGRN << pathtoinst << RST << endl;
	cout << endl << fixed;
	for (auto i=allrecetas.begin(); i != allrecetas.end(); ++i) {
		cout << setw(6) << left << FCYN("CODE: ") << setw(4) << left << (*i).getCode();
		cout << setw(8) << left << FCYN("NOMBRE: ") << setw(35) << left << (*i).getNombre();
		cout << setw(7) << left <<  FCYN("PLATO: ") << setw(2) << left << (*i).getPlato() << endl;
	}

	cout << "Selecciona un código de receta:\t";
	string elegido;
	cin >> elegido;

	recetas::iterator pos = allrecetas.end();
	if((pos = allrecetas.findReceta(elegido)) == allrecetas.end()) {
		cerr << FRED("El código introducido no es válido o no existe") << endl;
		exit(EXIT_FAILURE);
	}

	cout << endl << fixed;
	cout << setw(6) << left << FCYN("CODE: ") << setw(4) << left << (*pos).getCode();
	cout << setw(8) << left << FCYN("NOMBRE: ") << setw(35) << left << (*pos).getNombre();
	cout << setw(7) << left <<  FCYN("PLATO: ") << setw(2) << left << (*pos).getPlato() << endl;

	cout << left << UNDL("Ingredientes:") << endl;

	for(auto i = (*pos).begin(); i != (*pos).end(); ++i)
		cout << setw(8) << left << " " << (*i).first << " " << (*i).second << endl;

	cout << left << UNDL("Valores Nutricionales:") << endl;
	cout << setw(8) << left << " " << "Calorías: " << (*pos).getCalorias() << endl;
	cout << setw(8) << left << " " << "Hidratos de Carbono: " << (*pos).getHc() << endl;
	cout << setw(8) << left << " " << "Grasas: " << (*pos).getGrasas() << endl;
	cout << setw(8) << left << " " << "Proteínas " << (*pos).getProteinas() << endl;
	cout << setw(8) << left << " " << "Fibra: " << (*pos).getFibra() << endl;

	string pathtorinst = makepathtoins(pathtoinst, (*pos).getCode());

	(*pos).cargaInstrucciones(pathtorinst);

	cout << left << UNDL("Pasos a Seguir:") << endl;

	(*pos).muestraInstrucciones(cout);

	string code1, code2;
	cout << endl << "Elige dos códigos para fusionar: " << endl << setw(8) << " " << "Código 1: ";
	cin >> code1;

	recetas::iterator pos1 = allrecetas.end();
	if((pos1 = allrecetas.findReceta(code1)) == allrecetas.end()) {
		cerr << FRED("El código introducido no es válido o no existe") << endl;
		exit(EXIT_FAILURE);
	}

	string r1path = makepathtoins(pathtoinst, (*pos1).getCode());
	(*pos1).cargaInstrucciones(r1path);

	cout << setw(8) << " " << "Código 2: ";
	cin >> code2;

	recetas::iterator pos2 = allrecetas.end();
	if((pos2 = allrecetas.findReceta(code2)) == allrecetas.end()) {
		cerr << FRED("El código introducido no es válido o no existe") << endl;
		exit(EXIT_FAILURE);
	}
	
	string r2path = makepathtoins(pathtoinst, (*pos2).getCode());
	(*pos2).cargaInstrucciones(r2path);

	receta r1 = (*pos1);
	receta r2 = (*pos2);
	//receta fusion = (*pos1) + (*pos2);
	receta fusion;
	fusion = r1 + r2;

	cout << endl << fixed;
	cout << setw(6) << left << FCYN("CODE: ") << setw(9) << left << fusion.getCode();
	cout << setw(8) << left << FCYN("NOMBRE: ") << setw(40) << left << fusion.getNombre();
	cout << setw(7) << left <<  FCYN("PLATO: ") << setw(2) << left << fusion.getPlato() << endl;

	cout << left << UNDL("Ingredientes:") << endl;

	for(auto i = fusion.begin(); i != fusion.end(); ++i)
		cout << setw(8) << left << " " << (*i).first << " " << (*i).second << endl;

	cout << left << UNDL("Valores Nutricionales:") << endl;
	cout << setw(8) << left << " " << "Calorías: " << fusion.getCalorias() << endl;
	cout << setw(8) << left << " " << "Hidratos de Carbono: " << fusion.getHc() << endl;
	cout << setw(8) << left << " " << "Grasas: " << fusion.getGrasas() << endl;
	cout << setw(8) << left << " " << "Proteínas " << fusion.getProteinas() << endl;
	cout << setw(8) << left << " " << "Fibra: " << fusion.getFibra() << endl;

	cout << left << UNDL("Pasos a Seguir:") << endl;

	fusion.muestraInstrucciones(cout);

	return 0;
}

string makepathtoins(const string& base, const string& rcode) {
	string pathtorinst;
	pathtorinst += base;
	pathtorinst += '/';
	pathtorinst += rcode;
	pathtorinst += "m.txt";

	return pathtorinst;
}
