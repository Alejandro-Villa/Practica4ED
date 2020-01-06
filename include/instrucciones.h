/**
 * @file instrucciones.h
 * @brief Cabecera de la clase instrucciones.
 *
 * Este archivo define la clase instrucciones, que representa un conjunto ordenado de acciones a aplicar sobre unos ingredientes.
 */
#ifndef INSTRUCCIONES
#define INSTRUCCIONES

#include<string>
#include<iostream>
#include<stack>
#include "acciones.h"
#include "arbolbinario.h"
/**
 * @brief Clase Instruccines.
 *
 * Esta clase implementa un conjunto de acciones que se aplican siguiendo un orden definido sobre un conjunto de ingredientes.
 */
class instrucciones {
	private:
		/**
		 * @brief Este Árbol Binario almacena las instrucciones con un orden determinado: cada acción se aplica sobre sus hijos.
		 */
		ArbolBinario<std::string> datos;
		/**
		 * @brief Conjunto de acciones válidas. Debe inicializarse o no se almacenarán correctamente las instrucciones.
		 */
		static acciones &acc;
	public:
		/**
		 * @brief Constructor por defecto.
		 *
		 * Llama al constructor de @a datos.
		 */
		instrucciones() {};
		/**
		 * @brief Constructor de copia.
		 *
		 * Inicializa @a this copiando  @a otro.
		 *
		 * @param "const instrucciones& otro" Objeto del que se copia.
		 */
		instrucciones(const instrucciones& otro);
		/**
		 * @brief Constructor parametrizado.
		 *
		 * Asigna @a arbol a @a datos.
		 *
		 * @param "const ArbolBinario<string>& arbol" Árbol con instrucciones.
		 */
		instrucciones(const ArbolBinario<std::string> arbol);
		/**
		 * @brief Devuelve las acciones válidas.
		 * @retval "acciones" Las acciones que comparten todos los objetos de instucciones.
		 */
		inline acciones getAcciones() const {return acc;};
		/**
		 * @brief Devuelve el árbol de instrucciones.
		 * @retval "ArbolBinario<string>" una copia de @a datos.
		 */
		inline ArbolBinario<std::string> getArbol() const {return datos;};
		/**
		 * @brief Asigna las acciones que se consideran válidas.
		 * @param "const acciones& iniacc" Conjunto de acciones que se asignará.
		 */
		static inline void setAcciones(const acciones& iniacc) {acc = iniacc;}
		/**
		 * @brief Sobrecarga del operador de salida.
		 *
		 * Muestra las acciones en orden de aplicación, al lado de cada acción se escriben los ingredientes donde se aplica,
		 * en caso de no haber suficientes, se aplica sobre las anteriores acciones.
		 *
		 * @param "std::ostream& os" Flujo de salida.
		 * @param "const instrucciones& ins" Instrucciones a mostrar.
		 *
		 * @retval "std::ostream&" El flujo tras la escritura.
		 */
		friend ostream& operator<<(ostream& os, const instrucciones& ins);
		/**
		 * @brief Operador de asignación.
		 *
		 * Asigna @a rhs a @a this.
		 *
		 * @param "const instrucciones& rhs" Instrucciones que se asignan.
		 * @retval "instrucciones&" referencia a @a this tras la asignación.
		 */
		instrucciones& operator=(const instrucciones& rhs);
		/**
		 * @brief Operador de "suma" o fusión de instrucciones.
		 *
		 * Este operador toma dos instrucciones y las fusiona en un solo conjunto, 
		 * para ello toma los dos árboles y los convierte en hijos de un nuevo árbol cuya raíz es la acción "Acompañar"-
		 *
		 * @note Si se quiere que se muestren correctamente, Acompañar debe ser una acción válida de @a acc con ariedad 2.
		 *
		 * @param "const instrucciones& rhs" Instrucción a fusionar con @a this
		 * @retval "instrucciones" Copia de la instrucción fusionada.
		 */
		instrucciones operator+(const instrucciones& rhs);
}; // end class instrucciones
#endif // end INSTRUCCIONES
