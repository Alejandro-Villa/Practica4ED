/**
 * @file acciones.h
 * @brief Cabecera de la clase @c acciones
 *
 * En esta clase se almacenan las posibles acciones y el número de ingredientes 
 * que requieren (su ariedad)
 */

#ifndef ACCIONES
#define ACCIONES

#include<string>
#include<map>
#include<iostream>

/**
 * @brief Clase usada para representar un conjunto de acciones.
 *
 * Esta clase está formada por un mapa de acciones, representadas por su nombre (clave primaria), y su ariedad.
 */
class acciones {
	private:
		/**
		 * @brief Representa el conjunto de acciones con su respectiva ariedad.
		 */
		std::map<std::string, unsigned char> datos;
	public:
		/**
		 * @brief Constructor por defecto.
		 *
		 * Llama al constructor por defecto de @c "std::map<std::string, unsigned char>"
		 */
		acciones() {};
		/**
		 * @brief Constructor con parámetros.
		 *
		 * El usuario de la clase puede inicializar un objeto de esta usando un objeeto @c std::map compatible.
		 *
		 * @param "const std::map<std::string, unsigned char>& accmap" Conjunto de acciones y su ariedad. Puede ser vacío.
		 * @post @c datos ahora está inicializado a @a accmap.
		 */
		acciones(const std::map<std::string, unsigned char>& accmap);
		/**
		 * @brief Constructor de copia.
		 *
		 * Copia un objeto de @c acciones. 
		 *
		 * @param "const acciones& otro" Objeto que se usa para inicializar.
		 * @post @a datos es igual a @a otro.datos.
		 */
		acciones(const acciones& otro);
		/**
		 * @brief Devuelve la ariedad de una acción.
		 *
		 * Este método devuelve la ariedad de la acción @a nombre.
		 * @param "const std::string& nombre" La acción de la que se quiere su paridad.
		 * @retval "unsigned char" La paridad de la acción, o @c '0' si no se ha encontrado.
		 */
		inline unsigned char getAriedad(const std::string& nombre) const {return (*this)[nombre];};
		/**
		 * @nrief Añade una acción nueva
		 * @param "const std::string& nombre" Nombre de la acción.
		 * @param "const unsigned char& ariedad" Ariedad de la acción.
		 * @retval "bool" @c True si fue posible añadir la acción, @c false en caso contrario.
		 */ 
		bool addAccion(const std::string& nombre, const unsigned char& ariedad);

		/**
		 * @brief operador de acceso.
		 *
		 * Accede al la accíom con nombre @a nombre, y devuelve su ariedad.
		 *
		 * @param "const std::string& nombre" Nombre de la acción que se va a consultar.
		 * @retval "unsigned char" ariedad de la acción.
		 */
		unsigned char operator[] (const std::string& nombre);
		/**
		 * @brief operador de acceso constante.
		 *
		 * Accede al la accíom con nombre @a nombre, y devuelve su ariedad.
		 *
		 * @param "const std::string& nombre" Nombre de la acción que se va a consultar.
		 * @retval "unsigned char" ariedad de la acción.
		 */
		unsigned char operator[] (const std::string& nombre) const;
		/**
		 * @brief Sobrecarga del operador de entrada.
		 *
		 * Permite leer acciones desde un flujo de entrada.
		 * @param "std::iostream& is" flujo de entrada.
		 * @param "acciones& acc" objeto donde se almacenan las acciones leídas.
		 *
		 * @retval "std::istream&" flujo de entrada tras la lectura.
		 */
		friend std::istream& operator>>(std::istream& in, acciones& acc);
		/**
		 * @brief Sobrecarga del operador de salida.
		 *
		 * Permite escribir acciones a un flujo de salida.
		 * @param "std::ostream& os" flujo de salida.
		 * @param "const acciones& acc" el objeto que se escribirá.
		 *
		 * @retval "std::ostream&" flujo de entrada tras la escritura.
		 */
		friend std::ostream& operator<<(std::ostream& os, const acciones& acc);
}; // end class acciones
#endif // end ACCIONES
