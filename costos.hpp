#ifndef COST_FUNCTIONS_HPP
#define COST_FUNCTIONS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

namespace edit_distance {

/**
 * @brief Carga una matriz de costos desde un archivo de texto
 * @param nombreArchivo Nombre del archivo que contiene los costos
 * @param esUnaFila Indica si se debe leer solo una fila (true) o una matriz completa (false)
 * @return Vector bidimensional con los costos cargados
 */
std::vector<std::vector<int>> cargarMatrizDeCostos(const std::string& nombreArchivo, bool esUnaFila) {
    std::ifstream archivo(nombreArchivo);
    std::vector<std::vector<int>> matriz;
    std::string linea;

    if (archivo.is_open()) {
        if (esUnaFila) {
            // Leer una sola fila y almacenarla en un vector de una fila
            getline(archivo, linea);
            std::vector<int> fila;
            int valor;
            std::stringstream ss(linea);
            while (ss >> valor) {
                fila.push_back(valor);
            }
            matriz.push_back(fila);
        } else {
            // Leer una matriz cuadrada
            while (getline(archivo, linea)) {
                std::vector<int> fila;
                int valor;
                std::stringstream ss(linea);
                while (ss >> valor) {
                    fila.push_back(valor);
                }
                matriz.push_back(fila);
            }
        }
        archivo.close();
    } else {
        std::cerr << "Error al abrir el archivo " << nombreArchivo << std::endl;
    }
    return matriz;
}

/**
 * @brief Calcula el costo de sustituir un carácter 'a' por un carácter 'b'
 * @param a Carácter original
 * @param b Carácter de reemplazo
 * @return Costo de la sustitución
 */
inline int costo_sub(char a, char b) {
    static const std::vector<std::vector<int>> matriz = cargarMatrizDeCostos("cost_replace.txt", false);
    return matriz[a - 'a'][b - 'a'];
}

/**
 * @brief Calcula el costo de insertar un carácter
 * @param b Carácter a insertar
 * @return Costo de la inserción
 */
inline int costo_ins(char b) {
    static const std::vector<std::vector<int>> fila = cargarMatrizDeCostos("cost_insert.txt", true);
    return fila[0][b - 'a'];
}

/**
 * @brief Calcula el costo de eliminar un carácter
 * @param a Carácter a eliminar
 * @return Costo de la eliminación
 */
inline int costo_del(char a) {
    static const std::vector<std::vector<int>> fila = cargarMatrizDeCostos("cost_delete.txt", true);
    return fila[0][a - 'a'];
}

/**
 * @brief Calcula el costo de transponer dos caracteres
 * @param a Primer carácter
 * @param b Segundo carácter
 * @return Costo de la transposición
 */
inline int costo_trans(char a, char b) {
    static const std::vector<std::vector<int>> matriz = cargarMatrizDeCostos("cost_transpose.txt", false);
    return matriz[a - 'a'][b - 'a'];
}

} // namespace edit_distance

#endif // COST_FUNCTIONS_HPP