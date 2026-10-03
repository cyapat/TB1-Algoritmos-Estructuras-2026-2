#include <iostream>
#include <string>

// Cabeceras base de infraestructura del grupo
#include "Entidades.h"
#include "Nodo.h"
#include "ListaSimple.h"
#include "GestorArchivos.h"
#include "Utils.h"

using namespace std;

// ==========================================
// SECCIÓN DE MÓDULOS POR INTEGRANTE
// ==========================================

// Integrante 1: Usuarios y Tableros
void menuModuloUsuariosYTableros() {
    ListaSimple<Tablero> listaTableros;
    int opcion = -1;

    vector<string> lineasTableros = GestorArchivos::leerLineas("data/tableros.csv");
    for (const string& linea : lineasTableros) {
        vector<string> datos = GestorArchivos::dividirLinea(linea, ',');
        if (datos.size() >= 4 && datos[0] != "idTablero") {
            int idTablero = stoi(datos[0]);
            int idUsuario = datos.size() > 4 ? stoi(datos[2]) : stoi(datos[1]);
            string nombre = datos.size() > 4 ? datos[1] : datos[2];
            bool esPrivado = datos.size() > 4 ? datos[4] != "1" : datos[3] == "1";
            listaTableros.insertarFinal(Tablero(idTablero, idUsuario, nombre, esPrivado));
        }
    }

    do {
        Utils::limpiarPantalla();
        cout << "========================================\n";
        cout << "   MODULO 1: USUARIOS Y TABLEROS\n";
        cout << "========================================\n";
        cout << "1. Registrar usuario\n";
        cout << "2. Crear nuevo tablero (Lista Simple)\n";
        cout << "3. Listar todos los tableros\n";
        cout << "4. Ver usuarios registrados (CSV)\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";

        if (!(cin >> opcion)) {
            Utils::limpiarEntrada();
            continue;
        }

        switch (opcion) {
        case 1: {
            Utils::limpiarPantalla();
            int id;
            string nombre, email;
            cout << "--- REGISTRAR USUARIO ---\n";
            cout << "ID Usuario: "; cin >> id;
            Utils::limpiarEntrada();
            cout << "Nombre: "; getline(cin, nombre);
            cout << "Email: "; getline(cin, email);

            string lineaCSV = to_string(id) + "," + nombre + ",," + email + ",";
            if (GestorArchivos::guardarLinea("data/usuarios.csv", lineaCSV)) {
                cout << "\n[OK] Usuario guardado con exito en CSV.\n";
            } else {
                cout << "\n[Error] No se pudo guardar el usuario.\n";
            }
            Utils::pausar();
            break;
        }
        case 2: {
            Utils::limpiarPantalla();
            int idTablero, idUsuario, esPrivado;
            string nombre;
            cout << "--- CREAR TABLERO ---\n";
            cout << "ID Tablero: "; cin >> idTablero;
            cout << "ID Usuario Propietario: "; cin >> idUsuario;
            Utils::limpiarEntrada();
            cout << "Nombre del Tablero: "; getline(cin, nombre);
            cout << "Es privado? (1 = Si, 0 = No): "; cin >> esPrivado;

            listaTableros.insertarFinal(Tablero(idTablero, idUsuario, nombre, esPrivado == 1));
            string lineaCSV = to_string(idTablero) + "," + nombre + "," + to_string(idUsuario)
                + ",," + to_string(esPrivado == 0 ? 1 : 0) + ",0,";
            GestorArchivos::guardarLinea("data/tableros.csv", lineaCSV);

            cout << "\n[OK] Tablero insertado en ListaSimple y guardado en CSV.\n";
            Utils::pausar();
            break;
        }
        case 3:
            Utils::limpiarPantalla();
            cout << "--- LISTA DE TABLEROS EN MEMORIA (" << listaTableros.getCantidad() << ") ---\n";
            if (listaTableros.esVacia()) {
                cout << "No hay tableros registrados en la lista.\n";
            } else {
                listaTableros.recorrer([](Tablero tablero) {
                    tablero.mostrarInfo();
                });
            }
            Utils::pausar();
            break;
        case 4: {
            Utils::limpiarPantalla();
            cout << "--- USUARIOS EN USUARIOS.CSV ---\n";
            vector<string> lineasUsuarios = GestorArchivos::leerLineas("data/usuarios.csv");
            for (const string& linea : lineasUsuarios) {
                vector<string> usuario = GestorArchivos::dividirLinea(linea, ',');
                if (usuario.size() >= 3 && usuario[0] != "idUsuario") {
                    string email = usuario.size() >= 4 ? usuario[3] : usuario[2];
                    Usuario usuarioActual(stoi(usuario[0]), usuario[1], email);
                    usuarioActual.mostrarInfo();
                }
            }
            Utils::pausar();
            break;
        }
        case 0:
            break;
        default:
            cout << "\nOpcion no valida.\n";
            Utils::pausar();
            break;
        }
    } while (opcion != 0);
}

// Integrante 2: Pines y Categorías
void menuModuloPinesYCategorias() {
    int opcion = -1;
    do {
        Utils::limpiarPantalla();
        cout << "========================================\n";
        cout << "   MODULO 2: PINES Y CATEGORIAS\n";
        cout << "========================================\n";
        cout << "1. Agregar categoria (Lista Doble)\n";
        cout << "2. Agregar Pin a una categoria\n";
        cout << "3. Ordenar Pines por popularidad (MergeSort)\n";
        cout << "4. Cargar / Guardar datos desde CSV\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";

        if (!(cin >> opcion)) {
            Utils::limpiarEntrada();
            continue;
        }

        switch (opcion) {
        case 1:
            cout << "\n[En desarrollo por Integrante 2]\n";
            Utils::pausar();
            break;
        case 2:
            cout << "\n[En desarrollo por Integrante 2]\n";
            Utils::pausar();
            break;
        case 3:
            cout << "\n[En desarrollo por Integrante 2]\n";
            Utils::pausar();
            break;
        case 4:
            cout << "\n[En desarrollo por Integrante 2]\n";
            Utils::pausar();
            break;
        case 0:
            break;
        default:
            cout << "\nOpcion no valida.\n";
            Utils::pausar();
            break;
        }
    } while (opcion != 0);
}

// Integrante 3: Recomendaciones y Métricas
void menuModuloRecomendaciones() {
    int opcion = -1;
    do {
        Utils::limpiarPantalla();
        cout << "========================================\n";
        cout << "   MODULO 3: RECOMENDACIONES Y METRICAS\n";
        cout << "========================================\n";
        cout << "1. Encolar recomendacion (Cola)\n";
        cout << "2. Procesar siguiente recomendacion\n";
        cout << "3. Calcular similitud entre Pines (Recursividad)\n";
        cout << "4. Generar reporte / metricas\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";

        if (!(cin >> opcion)) {
            Utils::limpiarEntrada();
            continue;
        }

        switch (opcion) {
        case 1:
            cout << "\n[En desarrollo por Integrante 3]\n";
            Utils::pausar();
            break;
        case 2:
            cout << "\n[En desarrollo por Integrante 3]\n";
            Utils::pausar();
            break;
        case 3:
            cout << "\n[En desarrollo por Integrante 3]\n";
            Utils::pausar();
            break;
        case 4:
            cout << "\n[En desarrollo por Integrante 3]\n";
            Utils::pausar();
            break;
        case 0:
            break;
        default:
            cout << "\nOpcion no valida.\n";
            Utils::pausar();
            break;
        }
    } while (opcion != 0);
}

// ==========================================
// MENÚ PRINCIPAL
// ==========================================

void mostrarEncabezado() {
    cout << "========================================\n";
    cout << "   TB1 Pinterest - AED 2026-2\n";
    cout << "========================================\n";
}

void mostrarRequisitos() {
    Utils::limpiarPantalla();
    cout << "========================================\n";
    cout << "   REQUISITOS DEL PROYECTO PINTEREST\n";
    cout << "========================================\n";
    cout << "- Lista simple: Administracion de Tableros (Int. 1)\n";
    cout << "- Lista doble: Administracion de Categorias (Int. 2)\n";
    cout << "- Cola: Sistema de Recomendaciones (Int. 3)\n";
    cout << "- MergeSort: Ordenar Pines por popularidad (Int. 2)\n";
    cout << "- Recursividad: Calculo de similitud entre Pines (Int. 3)\n";
    cout << "- Archivos: Persistencia en formato .csv\n";
    Utils::pausar();
}

int main() {
    int opcion = -1;

    do {
        Utils::limpiarPantalla();
        mostrarEncabezado();
        cout << "\nMenu Principal\n";
        cout << "1. Modulo: Usuarios y Tableros (Integrante 1)\n";
        cout << "2. Modulo: Pines y Categorias (Integrante 2)\n";
        cout << "3. Modulo: Recomendaciones (Integrante 3)\n";
        cout << "4. Ver requisitos del sistema\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";

        if (!(cin >> opcion)) {
            Utils::limpiarEntrada();
            cout << "\nIngresa un numero valido.\n";
            Utils::pausar();
            continue;
        }

        switch (opcion) {
        case 1:
            menuModuloUsuariosYTableros();
            break;
        case 2:
            menuModuloPinesYCategorias();
            break;
        case 3:
            menuModuloRecomendaciones();
            break;
        case 4:
            mostrarRequisitos();
            break;
        case 0:
            cout << "\nGracias por usar el sistema Pinterest.\n";
            break;
        default:
            cout << "\nOpcion no reconocida.\n";
            Utils::pausar();
            break;
        }
    } while (opcion != 0);

    return 0;
}
