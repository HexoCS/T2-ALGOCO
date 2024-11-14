#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
#include "costos.hpp"

using namespace std;
using namespace edit_distance;

// Función recursiva para calcular la distancia de edición con costos variables
int editDistance(string str1, string str2, int m, int n) {
    // Caso base: si una de las cadenas es vacía, la distancia es la suma de los costos
    // de insertar o eliminar todos los caracteres restantes
    if (m == 0) {
        int cost = 0;
        for (int j = 0; j < n; j++) {
            cost += costo_ins(str2[j]);
        }
        return cost;
    }
    if (n == 0) {
        int cost = 0;
        for (int i = 0; i < m; i++) {
            cost += costo_del(str1[i]);
        }
        return cost;
    }

    // Si los últimos caracteres son iguales, ignorarlos y seguir con los anteriores
    if (str1[m - 1] == str2[n - 1])
        return editDistance(str1, str2, m - 1, n - 1);

    // Verificar si una transposición es posible y calcular su costo
    int transCost = INT_MAX;
    if (m > 1 && n > 1 && 
        str1[m - 1] == str2[n - 2] && 
        str1[m - 2] == str2[n - 1]) {
        transCost = costo_trans(str1[m - 2], str1[m - 1]) + 
                    editDistance(str1, str2, m - 2, n - 2);
    }

    // Calcular costos para cada operación posible
    int insCost = costo_ins(str2[n - 1]) + 
                  editDistance(str1, str2, m, n - 1);    // Inserción
    
    int delCost = costo_del(str1[m - 1]) + 
                  editDistance(str1, str2, m - 1, n);    // Eliminación
    
    int subCost = costo_sub(str1[m - 1], str2[n - 1]) + 
                  editDistance(str1, str2, m - 1, n - 1); // Sustitución

    // Retornar el mínimo entre todas las operaciones posibles
    return min({insCost, delCost, subCost, transCost});
}

int main() {
    string str1, str2;
    cout << "Ingresa la primera cadena: ";
    cin >> str1;
    cout << "Ingresa la segunda cadena: ";
    cin >> str2;

    // Verificar que las cadenas solo contengan letras minúsculas del alfabeto inglés
    auto isValidString = [](const string& str) {
        return all_of(str.begin(), str.end(), [](char c) {
            return c >= 'a' && c <= 'z';
        });
    };

    if (!isValidString(str1) || !isValidString(str2)) {
        cerr << "Error: Las cadenas deben contener solo letras minúsculas del alfabeto inglés." << endl;
        return 1;
    }

    int m = str1.length();
    int n = str2.length();

    int resultado = editDistance(str1, str2, m, n);
    cout << "La distancia mínima de edición es: " << resultado << endl;

    return 0;
}