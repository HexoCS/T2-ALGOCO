#include <iostream>
#include <string>
#include <algorithm>
#include "costos.hpp"


using namespace std;

// Función recursiva para calcular la distancia de edición
int editDistance(string str1, string str2, int m, int n) {
    // Caso base: si una de las cadenas es vacía, la distancia es el largo de la otra cadena
    if (m == 0) return n;
    if (n == 0) return m;

    // Si los últimos caracteres son iguales, ignorarlos y seguir con los anteriores
    if (str1[m - 1] == str2[n - 1])
        return editDistance(str1, str2, m - 1, n - 1);

    // Verificar si una transposición es posible
    if (m > 1 && n > 1 && str1[m - 1] == str2[n - 2] && str1[m - 2] == str2[n - 1])
        return 1 + editDistance(str1, str2, m - 2, n - 2); // Transposición

    // Considerar todas las operaciones posibles
    // 1. Insertar un carácter
    // 2. Eliminar un carácter
    // 3. Reemplazar un carácter
    return 1 + min({
        editDistance(str1, str2, m, n - 1),    // Inserción
        editDistance(str1, str2, m - 1, n),    // Eliminación
        editDistance(str1, str2, m - 1, n - 1) // Reemplazo
    });
}

int main() {
    string str1, str2;
    cout << "Ingresa la primera cadena: ";
    cin >> str1;
    cout << "Ingresa la segunda cadena: ";
    cin >> str2;

    int m = str1.length();
    int n = str2.length();

    int resultado = editDistance(str1, str2, m, n);
    cout << "La distancia mínima de edición es: " << resultado << endl;

    return 0;
}
