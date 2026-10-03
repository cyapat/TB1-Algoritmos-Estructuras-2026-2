
#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class GestorArchivos {
public:
    static vector<string> dividirLinea(const string& linea, char delimitador) {
        vector<string> campos;
        string campo;
        stringstream flujo(linea);

        while (getline(flujo, campo, delimitador)) {
            campos.push_back(campo);
        }
        return campos;
    }

    // Lee un archivo CSV linea por linea
    static vector<string> leerLineas(const string& rutaArchivo) {
        vector<string> lineas;
        ifstream archivo(rutaArchivo);
        string linea;

        if (archivo.is_open()) {
            while (getline(archivo, linea)) {
                if (!linea.empty()) {
                    lineas.push_back(linea);
                }
            }
            archivo.close();
        }
        else {
            cout << "[Aviso] No se pudo abrir el archivo o esta vacio: " << rutaArchivo << "\n";
        }
        return lineas;
    }

    // Guarda una linea al final del archivo CSV
    static bool guardarLinea(const string& rutaArchivo, const string& lineaCSV) {
        ofstream archivo(rutaArchivo, ios::app);
        if (archivo.is_open()) {
            archivo << lineaCSV << "\n";
            archivo.close();
            return true;
        }
        return false;
    }
};

#endif // GESTOR_ARCHIVOS_H
