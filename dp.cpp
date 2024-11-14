#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "costos.hpp"

using namespace std;
using namespace edit_distance;

// Función para calcular la distancia de edición usando programación dinámica
int editDistance(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();
    
    // Crear matriz dp[m+1][n+1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Inicializar primera fila y columna
    // Primera fila: costo de insertar caracteres
    for (int j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j-1] + costo_ins(str2[j-1]);
    }
    
    // Primera columna: costo de eliminar caracteres
    for (int i = 1; i <= m; i++) {
        dp[i][0] = dp[i-1][0] + costo_del(str1[i-1]);
    }

    // Llenar el resto de la matriz
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // Si los caracteres son iguales, no hay costo adicional
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                // Calcular costos de las operaciones básicas
                int insert_cost = dp[i][j-1] + costo_ins(str2[j-1]);
                int delete_cost = dp[i-1][j] + costo_del(str1[i-1]);
                int replace_cost = dp[i-1][j-1] + costo_sub(str1[i-1], str2[j-1]);
                
                // Obtener el mínimo de las operaciones básicas
                dp[i][j] = min({insert_cost, delete_cost, replace_cost});

                // Verificar si es posible una transposición
                if (i > 1 && j > 1 && 
                    str1[i-1] == str2[j-2] && 
                    str1[i-2] == str2[j-1]) {
                    int trans_cost = dp[i-2][j-2] + costo_trans(str1[i-2], str1[i-1]);
                    dp[i][j] = min(dp[i][j], trans_cost);
                }
            }
        }
    }

    return dp[m][n];
}

// Función opcional para reconstruir la secuencia de operaciones
void reconstructOperations(const string& str1, const string& str2, 
                         const vector<vector<int>>& dp) {
    int i = str1.length();
    int j = str2.length();
    
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && str1[i-1] == str2[j-1]) {
            // No hay operación, caracteres iguales
            i--; j--;
            continue;
        }
        
        // Verificar transposición
        if (i > 1 && j > 1 && 
            str1[i-1] == str2[j-2] && 
            str1[i-2] == str2[j-1] &&
            dp[i][j] == dp[i-2][j-2] + costo_trans(str1[i-2], str1[i-1])) {
            cout << "Transponer " << str1[i-2] << " y " << str1[i-1] << endl;
            i -= 2; j -= 2;
            continue;
        }
        
        // Verificar otras operaciones
        if (i > 0 && j > 0 && 
            dp[i][j] == dp[i-1][j-1] + costo_sub(str1[i-1], str2[j-1])) {
            cout << "Sustituir " << str1[i-1] << " por " << str2[j-1] << endl;
            i--; j--;
        }
        else if (j > 0 && dp[i][j] == dp[i][j-1] + costo_ins(str2[j-1])) {
            cout << "Insertar " << str2[j-1] << endl;
            j--;
        }
        else if (i > 0 && dp[i][j] == dp[i-1][j] + costo_del(str1[i-1])) {
            cout << "Eliminar " << str1[i-1] << endl;
            i--;
        }
    }
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

    int resultado = editDistance(str1, str2);
    cout << "La distancia mínima de edición es: " << resultado << endl;

    return 0;
}