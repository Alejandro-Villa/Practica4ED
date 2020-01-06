/**
 * @file receta.h
 * @author Alejandro Villanueva Prados
 * @brief Cabecera de la clase receta.
 *
 * En este archivo se declara la clase receta y sus métodos. Esta clase 
 * almacena la información para manejar recetas de cocina.
 */
#ifndef RECETA
#define RECETA

#include "instrucciones.h"
#include "ingredientes.h"
#include<string>
#include<list>
#include<iostream>

/**
 * @brief Clase receta, representa una receta de cocina.
 *
 * Esta clase representa una receta de cocina, que se simboliza con un código 
 * "R+número" y además se almacena el plato y los macronutrientes.
 */
class receta {
	private:
		/**
		 * @brief Código alfanumérico de la receta. Debe ser único en caso de existir varias.
		 */
		std::string code;
		/**
		 * @brief Indica si es un primero (1), segundo (2) o postre (3)
		 */
		unsigned plato;
		/**
		 * @brief Nombre de la receta.
		 */
		std::string nombre;
		/**
		 * @brief Lista de los ingredientes necesarios para la receta junto
		 * a su cantidad.
		 */
		std::list<std::pair<std::string, unsigned>> ings;
		/**
		 * @brief Calorías de la receta.
		 */
		double calorias;
		/**
		 * @brief Hidratos de Carbono de la receta.
		 */
		double hc;
		/**
		 * @brief Grasas de la receta.
		 */
		double grasas;
		/**
		 * @brief Proteínas de la receta.
		 */
		double proteinas;
		/**
		 * @brief Fibra de la receta.
		 */
		double fibra;
		/*
		 * @brief Instrucciones para realizar la receta.
		 */
		instrucciones inst;
		/**
		 * @brief ingredientes disponibles o válidos para la receta.
		 */
		ingredientes disp;

	public:
		/**
		 * @brief Constructor por defecto
		 *
		 * Inicializa los macronutrientes a 0, el código a cadena nula,
		 * el nombre a "Undefined", y la lista queda vacía.
		 */
		receta();
		/**
		 * @brief Constructor de copia.
		 *
		 * Inicializa la receta copiando @a original en ella.
		 *
		 * @param "const receta& original" La receta que se va a copiar.
		 * @post @a this ahora contiene una copia de @a original.
		 */
		receta(const receta& original);
		/**
		 * @brief Halla el número de ingredientes en la receta.
		 *
		 * Utiliza el método @a size de @a list.
		 * @retval "unsigned" Número de ingredientes en @a this.
		 */
		unsigned ningredientes() const;
		inline std::string getCode() const {return code;};
		inline unsigned getPlato() const {return plato;};
		inline std::string getNombre() const {return nombre;};
		inline double getCalorias() const {return calorias;};
		inline double getHc() const {return hc;};
		inline double getGrasas() const {return grasas;};
		inline double getProteinas() const {return proteinas;};
		inline double getFibra() const {return fibra;};

		inline void setCode(const std::string& codigo) {code = codigo;};
		inline void setPlato(const unsigned& pl) {plato = pl;};
		inline void setNombre(const std::string& name) {nombre = name;};
		inline void setCalorias(const double& cal) {calorias = cal;};
		inline void setHc(const double& HC) {hc = HC;};
		inline void setGrasas(const double& gra) {grasas = gra;};
		inline void setProteinas(const double& prote) {proteinas = prote;};
		inline void setFibra(const double& fib) {fibra = fib;};
		
		/**
		 * @brief Añade uno o varios ingredientes a la receta.
		 *
		 * @param "const std::pair<std::string, unsigned>& nuevo" Representa el ingrediente(s) que se añade(n).
		 */
		void addIngre(const std::pair<std::string, unsigned>& nuevo);
		/**
		 * @brief Carga instrucciones desde un flujo de entrada ya abierto.
		 */
		void cargaInstrucciones(istream& is);
		/**
		 * @brief Carga instrucciones de un archivo con ruta @a pathname.
		 * @note Llama al método con parámetro @c istream
		 *
		 * @see cargaInstrucciones(istream& is).
		 */
		void cargaInstrucciones(const string& pathname);
		/**
		 * @brief Carga instrucciones desde un objeto en memoria.
		 */
		inline void cargaInstrucciones(const instrucciones& otro) {inst = otro;};
		/**
		 * @brief Carga ingredientes desde un flujo de entrada ya abierto.
		 */
		void cargaIngredientes(istream& is);
		/**
		 * @brief Carga ingredientes de un archivo con ruta @a pathname.
		 * @note Llama al método con parámetro @c istream
		 *
		 * @see cargaIngredientes(istream& is).
		 */
		void cargaIngredientes(const string& pathname);
		/**
		 * @brief Carga ingredientes desde un objeto en memoria.
		 */
		inline void cargaIngredientes(const ingredientes& todos) {disp = todos;};
		/**
		 * @brief Muestra las instrucciones por el flujo de salida @a os.
		 */
		inline ostream& muestraInstrucciones(ostream& os) const {os << inst; return os;};
		/**
		 * @brief operador de "suma" o fusión de dos recetas.
		 *
		 * Une dos recetas en una, de la siguiente forma:
		 * - Código: "F_RXX_RYY" donde RXX es el código de la receta a la izquierda de "+" y RYY la receta a la derecha de "+".
		 * - Nombre: "Fusión de RECETA1 y RECETA2"
		 * - Plato: Primero si alguno es primero, segundo si ambos son segundo, o uno postre y postre si ambos son postre.
		 * - Ingredientes: los de ambas recetas, combinandose también la información nutricional.
		 * - Instrucciones: la fusión de ambas.
		 */
		receta operator+(const receta& rhs);
		/**
		 * @brief Operador de asignación.
		 */
		receta& operator=(const receta& rhs);
		/**
		 * @brief Sobrecarga del operador de entrada de flujo.
		 */
		friend std::istream& operator>>(std::istream& in, receta& r);
		/**
		 * @brief Sobrecarga del operador de salida de flujo.
		 */
		friend std::ostream& operator<<(std::ostream& out, const receta& r);

		/**
		 * @brief Iterador interno de receta.
		 *
		 * Es una clase iterador construida a partir del iterador de lista.
		 */
		class iterator {
			private:
				std::list<std::pair<std::string, unsigned>>::iterator it;
			public:
				iterator() {};
				iterator(const std::list<std::pair<std::string, unsigned>>::iterator& origen) : it(origen) {};
				iterator(const receta::iterator& origen) : it(origen.it) {};
				iterator& operator++() {++it; return *this;};
				iterator& operator--() {--it; return *this;};
				bool operator==(const receta::iterator& rhs) const {return it == rhs.it;};
				bool operator!=(const receta::iterator& rhs) const {return it != rhs.it;};
				std::pair<std::string, unsigned>& operator*() const {return *it;};
				inline const std::list<std::pair<std::string, unsigned>>::iterator getIterator() const {return it;};
		}; // end iterator
		/**
		 * @brief Iterador constante interno de receta.
		 *
		 * Un iterador constante construido a partir del iterador de lista.
		 */
		class const_iterator {
			private:
				std::list<std::pair<std::string, unsigned>>::const_iterator it;
			public:
				const_iterator() {};
				const_iterator(const std::list<std::pair<std::string, unsigned>>::const_iterator& origen) : it(origen) {};
				const_iterator(const receta::const_iterator& origen) : it(origen.it) {};
				const_iterator& operator++() {++it; return *this;};
				const_iterator& operator--() {--it; return *this;};
				bool operator==(const receta::const_iterator& rhs) const {return it == rhs.it;};
				bool operator!=(const receta::const_iterator& rhs) const {return it != rhs.it;};
				const std::pair<std::string, unsigned>& operator*() const {return *it;};
				inline const std::list<std::pair<std::string, unsigned>>::const_iterator getIterator() const {return it;};
		}; // end const_ iterator

		/**
		 * @brief Devuelve un iterador al inicio de @a this
		 *
		 * @retval "iterator" Iterador al inicio de @a this
		 */
		iterator begin();
		/**
		 * @brief Devuelve un iterador al fin de @a this
		 *
		 * @retval "iterator" Iterador al fin de @a this
		 */
		iterator end();
		/**
		 * @brief Devuelve un iterador constante al inicio de @a this
		 *
		 * @retval "iterator" Iterador constante al inicio de @a this
		 */
		const_iterator begin() const;
		/**
		 * @brief Devuelve un iterador constante al fin de @a this
		 *
		 * @retval "iterator" Iterador constante al fin de @a this
		 */
		const_iterator end() const;
		/**
		 * @brief Busca un ingrediente.
		 *
		 * @param "const std::string& nombre" Ingrediente a buscar.
		 * @retval "iterator" La posición del ingrediente, o @a receta::end() si no se encuentra.
		 */
		iterator find(const string& nombre);
}; // end receta
#endif // end RECETA
