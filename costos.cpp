#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Función para leer una matriz de costos desde un archivo
vector<vector<int>> cargarMatrizDeCostos(const string& nombreArchivo, bool esUnaFila) {
    ifstream archivo(nombreArchivo);
    vector<vector<int>> matriz;
    string linea;

    if (archivo.is_open()) {
        if (esUnaFila) {
            // Leer una sola fila y almacenarla en un vector de una fila
            getline(archivo, linea);
            vector<int> fila;
            int valor;
            stringstream ss(linea);
            while (ss >> valor) {
                fila.push_back(valor);
            }
            matriz.push_back(fila); // Añadir solo una fila a la matriz
        } else {
            // Leer una matriz cuadrada
            while (getline(archivo, linea)) {
                vector<int> fila;
                int valor;
                stringstream ss(linea);
                while (ss >> valor) {
                    fila.push_back(valor);
                }
                matriz.push_back(fila);
            }
        }
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
    }
    return matriz;
}

// Función para calcular el costo de sustitución de 'a' por 'b'
int costo_sub(char a, char b) {
    static vector<vector<int>> matriz = cargarMatrizDeCostos("cost_replace.txt", false);
    int costo = matriz[a - 'a'][b - 'a'];
    return costo;
}

// Función para calcular el costo de inserción del carácter 'b'
int costo_ins(char b) {
    static vector<vector<int>> fila = cargarMatrizDeCostos("cost_insert.txt", true);
    int costo = fila[0][b - 'a'];
    return costo;
}

// Función para calcular el costo de eliminación del carácter 'a'
int costo_del(char a) {
    static vector<vector<int>> fila = cargarMatrizDeCostos("cost_delete.txt", true);
    int costo = fila[0][a - 'a'];
    return costo;
}

// Función para calcular el costo de transposición de 'a' y 'b'
int costo_trans(char a, char b) {
    static vector<vector<int>> matriz = cargarMatrizDeCostos("cost_transpose.txt", false);
    int costo = matriz[a - 'a'][b - 'a'];
    return costo;
}

int main() {
    // Ejemplo de uso de las funciones de costo
    char a = 'c', b = 'd';
    //cout << "Costo de sustitución de " << a << " por " << b << ": " << costo_sub(a, b) << endl;
    cout << "Costo de inserción de " << b << ": " << costo_ins(b) << endl;
    //cout << "Costo de eliminación de " << a << ": " << costo_del(a) << endl;
    //cout << "Costo de transposición de " << a << " y " << b << ": " << costo_trans(a, b) << endl;

    return 0;
}
