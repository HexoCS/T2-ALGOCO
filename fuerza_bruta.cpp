#include <iostream>
#include <string>
#include<vector>
#include <algorithm>
#include <chrono>
#include "costos.hpp"

using namespace std;
using namespace std::chrono;
using namespace edit_distance;

pair<int, double> editDistance(const string& str1, const string& str2, int m, int n) {
    auto start = high_resolution_clock::now();
    
    int resultado;
    
    if (m == 0) {
        resultado = 0;
        for (int j = 0; j < n; j++) {
            resultado += costo_ins(str2[j]);
        }
    }
    else if (n == 0) {
        resultado = 0;
        for (int i = 0; i < m; i++) {
            resultado += costo_del(str1[i]);
        }
    }
    else if (str1[m - 1] == str2[n - 1]) {
        resultado = editDistance(str1, str2, m - 1, n - 1).first;
    }
    else {
      
        int ins = editDistance(str1, str2, m, n - 1).first + costo_ins(str2[n-1]);
        int del = editDistance(str1, str2, m - 1, n).first + costo_del(str1[m-1]);
        int rep = editDistance(str1, str2, m - 1, n - 1).first + costo_sub(str1[m-1], str2[n-1]);
        
        resultado = min({ins, del, rep});
        
        
        if (m > 1 && n > 1 && 
            str1[m - 1] == str2[n - 2] && 
            str1[m - 2] == str2[n - 1]) {
            int trans = editDistance(str1, str2, m - 2, n - 2).first + 
                       costo_trans(str1[m-2], str1[m-1]);
            resultado = min(resultado, trans);
        }
    }
    
    auto end = high_resolution_clock::now();
    duration<double, milli> duration = end - start;
    
    return {resultado, duration.count()};
}

int main() {

    string str1, str2;
    cout << "Ingresa la primera cadena: ";
    getline(cin, str1);
    cout << "Ingresa la segunda cadena: ";
    getline(cin, str2);

   
    auto isValidString = [](const string& str) {
        return str.empty() || all_of(str.begin(), str.end(), [](char c) {
            return c >= 'a' && c <= 'z';
        });
    };

    if (!isValidString(str1) || !isValidString(str2)) {
        cerr << "Error: inserta un caracter valido." << endl;
        return 1;
    }

    auto [resultado, tiempo] = editDistance(str1, str2, str1.length(), str2.length());
    cout << "La distancia mínima de edición es: " << resultado << endl;
    cout << "Tiempo de ejecución: " << tiempo << " milisegundos" << endl;

    return 0;
}
