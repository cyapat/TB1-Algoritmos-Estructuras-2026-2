#include <iostream>
#include <string>
#include <vector>
#include <cmath>

// Cabeceras base e infraestructura del proyecto
#include "Entidades.h"
#include "Nodo.h"
#include "ListaSimple.h"
#include "ListaDoble.h"
#include "Cola.h"
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
    ListaDoble<Categoria> listaCategorias;
    vector<Pin> listaPines;

    // Cargar categorias desde categorias.csv
    vector<string> lineasCategorias = GestorArchivos::leerLineas("data/categorias.csv");
    for (const string& linea : lineasCategorias) {
        vector<string> datos = GestorArchivos::dividirLinea(linea, ',');
        if (datos.size() >= 4 && datos[0] != "idCategoria") {
            listaCategorias.insertarFinal(Categoria(stoi(datos[0]), datos[1], datos[2], stoi(datos[3])));
        }
    }

    // Cargar pines desde pines.csv
    vector<string> lineasPines = GestorArchivos::leerLineas("data/pines.csv");
    for (const string& linea : lineasPines) {
        vector<string> datos = GestorArchivos::dividirLinea(linea, ',');
        if (datos.size() >= 7 && datos[0] != "idPin") {
            listaPines.push_back(Pin(stoi(datos[0]), datos[1], datos[2], stoi(datos[3]), stoi(datos[4]), stoi(datos[5]), datos[6]));
        }
    }

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
        case 1: {
            Utils::limpiarPantalla();
            int idCategoria;
            string nombre, descripcion;

            cout << "--- AGREGAR CATEGORIA ---\n";
            cout << "ID Categoria: ";
            while (!(cin >> idCategoria)) {
                cout << "[Error] Debes ingresar un numero.\n";
                Utils::limpiarEntrada();
                cout << "ID Categoria: ";
            }
            Utils::limpiarEntrada();

            bool categoriaExiste = false;
            listaCategorias.recorrer([&](Categoria categoria) {
                if (categoria.getIdCategoria() == idCategoria) {
                    categoriaExiste = true;
                }
            });

            if (categoriaExiste) {
                cout << "\n[Error] Ya existe una categoria con ese ID.\n";
                Utils::pausar();
                break;
            }

            cout << "Nombre: "; getline(cin, nombre);
            cout << "Descripcion: "; getline(cin, descripcion);

            Categoria nuevaCategoria(idCategoria, nombre, descripcion, 0);
            string lineaCSV = to_string(idCategoria) + "," + nombre + "," + descripcion + ",0";

            if (GestorArchivos::guardarLinea("data/categorias.csv", lineaCSV)) {
                listaCategorias.insertarFinal(nuevaCategoria);
                cout << "\n[OK] Categoria insertada en ListaDoble y guardada en CSV.\n";
            } else {
                cout << "\n[Error] No se pudo guardar la categoria.\n";
            }
            Utils::pausar();
            break;
        }
        case 2: {
            Utils::limpiarPantalla();
            int idPin, idTablero, idCategoria, popularidad;
            string titulo, descripcion, fechaCreacion;

            cout << "--- AGREGAR PIN ---\n";
            cout << "ID Pin: ";
            while (!(cin >> idPin)) {
                cout << "[Error] Debes ingresar un numero.\n";
                Utils::limpiarEntrada();
                cout << "ID Pin: ";
            }

            bool pinExiste = false;
            for (const Pin& pin : listaPines) {
                if (pin.getIdPin() == idPin) {
                    pinExiste = true;
                    break;
                }
            }

            if (pinExiste) {
                Utils::limpiarEntrada();
                cout << "\n[Error] Ya existe un Pin con ese ID.\n";
                Utils::pausar();
                break;
            }

            cout << "ID Categoria (numero): ";
            while (!(cin >> idCategoria)) {
                cout << "[Error] Debes ingresar el ID numerico de la categoria.\n";
                Utils::limpiarEntrada();
                cout << "ID Categoria (numero): ";
            }

            bool categoriaExiste = false;
            listaCategorias.recorrer([&](Categoria categoria) {
                if (categoria.getIdCategoria() == idCategoria) {
                    categoriaExiste = true;
                }
            });

            if (!categoriaExiste) {
                Utils::limpiarEntrada();
                cout << "\n[Error] La categoria indicada no existe.\n";
                Utils::pausar();
                break;
            }

            cout << "ID Tablero: ";
            while (!(cin >> idTablero)) {
                cout << "[Error] Debes ingresar un numero.\n";
                Utils::limpiarEntrada();
                cout << "ID Tablero: ";
            }

            cout << "Popularidad inicial: ";
            while (!(cin >> popularidad)) {
                cout << "[Error] Debes ingresar un numero.\n";
                Utils::limpiarEntrada();
                cout << "Popularidad inicial: ";
            }

            Utils::limpiarEntrada();
            cout << "Titulo: "; getline(cin, titulo);
            cout << "Descripcion: "; getline(cin, descripcion);
            cout << "Fecha de creacion (AAAA-MM-DD): "; getline(cin, fechaCreacion);

            Pin nuevoPin(idPin, titulo, descripcion, idTablero, idCategoria, popularidad, fechaCreacion);
            string lineaCSV = to_string(idPin) + "," + titulo + "," + descripcion + "," +
                to_string(idTablero) + "," + to_string(idCategoria) + "," +
                to_string(popularidad) + "," + fechaCreacion;

            if (GestorArchivos::guardarLinea("data/pines.csv", lineaCSV)) {
                listaPines.push_back(nuevoPin);
                cout << "\n[OK] Pin agregado y guardado en CSV.\n";
            } else {
                cout << "\n[Error] No se pudo guardar el Pin.\n";
            }
            Utils::pausar();
            break;
        }
        case 3:
            cout << "\n[Pendiente: Implementacion de MergeSort por Integrante 2]\n";
            Utils::pausar();
            break;
        case 4: {
            Utils::limpiarPantalla();
            cout << "--- CARGAR DATOS DESDE CSV ---\n\n";

            listaCategorias.limpiar();
            listaPines.clear();

            vector<string> lineasCategorias = GestorArchivos::leerLineas("data/categorias.csv");
            for (const string& linea : lineasCategorias) {
                vector<string> datos = GestorArchivos::dividirLinea(linea, ',');
                if (datos.size() >= 4 && datos[0] != "idCategoria") {
                    listaCategorias.insertarFinal(Categoria(stoi(datos[0]), datos[1], datos[2], stoi(datos[3])));
                }
            }

            vector<string> lineasPines = GestorArchivos::leerLineas("data/pines.csv");
            for (const string& linea : lineasPines) {
                vector<string> datos = GestorArchivos::dividirLinea(linea, ',');
                if (datos.size() >= 7 && datos[0] != "idPin") {
                    listaPines.push_back(Pin(stoi(datos[0]), datos[1], datos[2], stoi(datos[3]), stoi(datos[4]), stoi(datos[5]), datos[6]));
                }
            }

            cout << "[OK] Datos cargados correctamente.\n\n";
            cout << "Categorias cargadas: " << listaCategorias.getCantidad() << "\n";
            cout << "Pines cargados: " << listaPines.size() << "\n";

            cout << "\n--- CATEGORIAS ---\n";
            listaCategorias.recorrer([](Categoria categoria) { categoria.mostrarInfo(); });

            cout << "\n--- PINES ---\n";
            for (const Pin& pin : listaPines) { pin.mostrarInfo(); }

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

// Integrante 3: Recomendaciones y Métricas
float calcularSimilitudRecursiva(int difCategoria, int difPopularidad, int paso = 0) {
    if (paso == 0) {
        float scoreCat = (difCategoria == 0) ? 50.0f : 10.0f;
        return scoreCat + calcularSimilitudRecursiva(difCategoria, difPopularidad, 1);
    } 
    if (paso == 1) {
        float scorePop = 50.0f - (difPopularidad * 2.0f);
        if (scorePop < 0) scorePop = 0;
        return scorePop;
    }
    return 0.0f;
}

void menuModuloRecomendaciones() {
    static Cola<Recomendacion> colaRecomendaciones;
    int opcion = -1;

    do {
        Utils::limpiarPantalla();
        cout << "========================================\n";
        cout << "   MODULO 3: RECOMENDACIONES Y METRICAS\n";
        cout << "========================================\n";
        cout << "1. Encolar recomendacion (Cola)\n";
        cout << "2. Procesar siguiente recomendacion\n";
        cout << "3. Calcular similitud entre Pines (Recursividad)\n";
        cout << "4. Generar reporte / metricas de recomendaciones\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";

        if (!(cin >> opcion)) {
            Utils::limpiarEntrada();
            continue;
        }

        switch (opcion) {
        case 1: {
            Utils::limpiarPantalla();
            int id, idUsuario, idPin;
            float puntuacion;
            cout << "--- ENCOLAR RECOMENDACION ---\n";
            cout << "ID Recomendacion: "; cin >> id;
            cout << "ID Usuario: "; cin >> idUsuario;
            cout << "ID Pin: "; cin >> idPin;
            cout << "Puntuacion / Score (0.0 a 10.0): "; cin >> puntuacion;

            Recomendacion rec(id, idUsuario, idPin, puntuacion);
            colaRecomendaciones.encolar(rec);

            string lineaCSV = to_string(id) + "," + to_string(idUsuario) + "," + to_string(idPin) + "," + to_string(puntuacion);
            GestorArchivos::guardarLinea("data/recomendaciones.csv", lineaCSV);

            cout << "\n[OK] Recomendacion encolada correctamente y guardada en CSV.\n";
            Utils::pausar();
            break;
        }
        case 2: {
            Utils::limpiarPantalla();
            cout << "--- PROCESAR SIGUIENTE RECOMENDACION ---\n";
            if (colaRecomendaciones.esVacia()) {
                cout << "No hay recomendaciones pendientes en la cola.\n";
            } else {
                Recomendacion recAtendida;
                if (colaRecomendaciones.desencolar(recAtendida)) {
                    cout << "Procesando recomendacion:\n";
                    recAtendida.mostrarInfo();
                    cout << "\n[OK] Recomendacion procesada con exito.\n";
                }
            }
            Utils::pausar();
            break;
        }
        case 3: {
            Utils::limpiarPantalla();
            int cat1, cat2, pop1, pop2;
            cout << "--- CALCULADOR DE SIMILITUD (RECURSIVO) ---\n";
            cout << "ID Categoria Pin A: "; cin >> cat1;
            cout << "Popularidad Pin A (0-100): "; cin >> pop1;
            cout << "ID Categoria Pin B: "; cin >> cat2;
            cout << "Popularidad Pin B (0-100): "; cin >> pop2;

            int difCat = abs(cat1 - cat2);
            int difPop = abs(pop1 - pop2);

            float similitud = calcularSimilitudRecursiva(difCat, difPop);
            cout << "\n[Resultado] La similitud calculada de forma recursiva es: " << similitud << "%\n";
            Utils::pausar();
            break;
        }
        case 4: {
            Utils::limpiarPantalla();
            cout << "--- REPORTE / METRICAS DE COLA DE RECOMENDACIONES ---\n";
            cout << "Cantidad de recomendaciones en espera: " << colaRecomendaciones.getCantidad() << "\n";
            float promedioScore = colaRecomendaciones.promedio([](Recomendacion r) { return r.getPuntuacion(); });
            cout << "Promedio de puntuaciones en cola: " << promedioScore << "\n\n";

            if (colaRecomendaciones.esVacia()) {
                cout << "La cola se encuentra vacia.\n";
            } else {
                cout << "Listado de elementos en cola:\n";
                colaRecomendaciones.recorrer([](Recomendacion rec) { rec.mostrarInfo(); });
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
