#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include "costos.hpp"

using namespace std;
using namespace edit_distance;
using namespace std::chrono;

pair<int, double> editDistance(const string& str1, const string& str2) {
    auto start = high_resolution_clock::now();
    
    int m = str1.length();
    int n = str2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

 
    for (int i = 1; i <= m; i++) {
        dp[i][0] = dp[i-1][0] + costo_del(str1[i-1]);
    }
    
    
    for (int j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j-1] + costo_ins(str2[j-1]);
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                int insert_cost = dp[i][j-1] + costo_ins(str2[j-1]);
                int delete_cost = dp[i-1][j] + costo_del(str1[i-1]);
                int replace_cost = dp[i-1][j-1] + costo_sub(str1[i-1], str2[j-1]);
                
                dp[i][j] = min({insert_cost, delete_cost, replace_cost});

                // transposicion
                if (i > 1 && j > 1 && 
                    str1[i-1] == str2[j-2] && 
                    str1[i-2] == str2[j-1]) {
                    int trans_cost = dp[i-2][j-2] + costo_trans(str1[i-2], str1[i-1]);
                    dp[i][j] = min(dp[i][j], trans_cost);
                }
            }
        }
    }

    auto end = high_resolution_clock::now();
    duration<double, milli> duration = end - start;
    
    return {dp[m][n], duration.count()};
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
        cerr << "Error: ingresa una cadena valida" << endl;
        return 1;
    }

    auto [resultado, tiempo] = editDistance(str1, str2);
    cout << "La distancia mínima de edición es: " << resultado << endl;
    cout << "Tiempo de ejecución: " << tiempo << " milisegundos" << endl;

    return 0;
}