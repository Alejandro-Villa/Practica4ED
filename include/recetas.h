/**
 * @file recetas.h
 * @author Alejandro Villanueva Prados
 * @brief Archivo de cabecera de la clase recetas.
 *
 * En este archivo se declara la clase recetas y sus métodos.
 */

#ifndef RECETAS
#define RECETAS

#include "receta.h"
#include "ingredientes.h"
#include<string>
#include<map>
#include<utility>
#include<iostream>

/**
 * @brief Clase recetas, para manejar un conjunto de recetas distintas.
 *
 * Esta clase emplea un objeto @a map de la STL para manejar y trabajar con 
 * objetos @a receta usando como clave su código.
 */
class recetas {
	private:
		/**
		 * @brief Mapa de receta con sus claves
		 */
		std::map<std::string, receta> datos;
		/**
		 * @brief Ingredientes disponibles para las recetas
		 */
		ingredientes allingre;
	public:
			/**
			 * @brief Constructor por defecto.
			 *
			 * Inicializa @a datos a un mapa vacío.
			 */
			recetas();

			/**
			 * @brief Halla el tamaño de @a this.
			 *
			 * Este método usa el método @a size de @a datos para hallar el 
			 * total de recetas.
			 *
			 * @retval "unsigned" El número de recetas almacenadas.
			 */
			unsigned size() const;
			/**
			 * @brief Borra una receta según código.
			 *
			 * Este método borra una receta de la cual se conoce su código,
			 * si existe.
			 *
			 * @param "std::string codigo" el código de la receta (su key)
			 * @pre El código debe existir, sino no se borra.
			 * @post La receta es borrada de @a this.
			 */
			void borrar(std::string codigo);
			/**
			 * @brief Añade una nueva receta.
			 *
			 * Añade una receta que no existiese previamente.
			 *
			 * @param "const receta& nueva" La receta que se intentará añadir.
			 * @pre El código de @a nueva debe ser diferente a los ya almacenados, sino no añade.
			 * @post @a nueva es añadida.
			 */
			void addReceta(receta nueva);
			/**
			 * @brief Inicializa los nutrientes de las recetas.
			 *
			 * Usando el objeto ingredientes que se le ha pasado como argumento, 
			 * actualiza los valores nutricionales de @a this.
			 *
			 * @param "const ingredientes& ings" El objeto que se usará para actualizar @a this.
			 * @post Cambian los macronutrientes de todas las recetas.
			 */
			//void setNutrientes(const ingredientes& ings);
			/**
			 * @brief Comprueba si @a datos está vacío.
			 *
			 * @retval "True" si @a datos está vacío.
			 * @retval "False" si @a datos tiene elementos.
			 */
			bool empty() {return datos.empty();};
			inline void getIngredientes(istream& is) {is >> allingre;}
			
			/**
			 * @brief Operador de acceso a receta.
			 *
			 * Accede a la receta cuyo código es @a codigo.
			 *
			 * @param "const string& codigo" El codigo de la receta.
			 * @retval "receta" La receta consultada.
			 */
			receta operator[](const std::string& codigo);
			/**
			 * @brief Operador de acceso a receta (Constante)
			 *
			 * Versioón constante de @a "operator[]"
			 */
			const receta operator[](const std::string& codigo) const;
			/**
			 * @brief Sobrecarga del operador de entrada de flujo.
			 *
			 */
			friend std::istream& operator>>(std::istream& in, recetas& rs);
			/**
			 * @brief Sobrecarga del operador de salida de flujo.
			 *
			 */
			friend std::ostream& operator<<(std::ostream& out, const recetas& rs);

			/**
			 * @brief Iterador interno de la clase recetas.
			 */
			class iterator {
				private:
					std::map<std::string, receta>::iterator it;
				public:
					iterator() {};
					iterator(const std::map<std::string, receta>::iterator& origen) : it(origen) {};
					iterator(const recetas::iterator& origen) : it(origen.it) {};
					iterator& operator++() {++it; return *this;};
					iterator& operator--() {--it; return *this;};
					bool operator==(const recetas::iterator& rhs) const {return it == rhs.it;};
					bool operator!=(const recetas::iterator& rhs) const {return it != rhs.it;};
					receta& operator*() const {return (*it).second;};
			}; // end iterator
			/**
			 * @brief Iterador constante interno de la clase receta.
			 */
			class const_iterator {
				private:
					std::map<std::string, receta>::const_iterator it;
				public:
					const_iterator() {};
					const_iterator(const std::map<std::string, receta>::const_iterator& origen) : it(origen) {};
					const_iterator(const recetas::const_iterator& origen) : it(origen.it) {};
					const_iterator& operator++() {++it; return *this;};
					const_iterator& operator--() {--it; return *this;};
					bool operator==(const recetas::const_iterator& rhs) const {return it == rhs.it;};
					bool operator!=(const recetas::const_iterator& rhs) const {return it != rhs.it;};
					const receta& operator*() const {return (*it).second;};
			}; // end const_ iterator

			/**
			 * @brief Iterador al inicio de @a this.
			 */
			iterator begin();
			/**
			 * @brief Iterador al final de @a this.
			 */
			iterator end();
			/**
			 * @brief Iterador constante al inicio de @a this.
			 */
			const_iterator begin() const;
			/**
			 * @brief Iterador constante al fin de @a this.
			 */
			const_iterator end() const;

			recetas::iterator findReceta(const string& key);
}; // end recetas

#endif
