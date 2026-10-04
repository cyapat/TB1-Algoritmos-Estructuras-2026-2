#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

// Cabeceras base del proyecto
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

// Funcion para ordenar los tableros por su ID usando QuickSort
void quickSortTableros(vector<Tablero>& tableros, int izquierda, int derecha) {
    if (izquierda >= derecha) return;

    int i = izquierda;
    int j = derecha;
    // Tomamos el elemento central como pivote
    int pivote = tableros[izquierda + (derecha - izquierda) / 2].getIdTablero();

    while (i <= j) {
        while (tableros[i].getIdTablero() < pivote) i++;
        while (tableros[j].getIdTablero() > pivote) j--;

        if (i <= j) {
            swap(tableros[i], tableros[j]);
            i++;
            j--;
        }
    }

    // Llamadas recursivas para las dos sublistas
    if (izquierda < j) quickSortTableros(tableros, izquierda, j);
    if (i < derecha) quickSortTableros(tableros, i, derecha);
}

void menuModuloUsuariosYTableros() {
    ListaSimple<Tablero> listaTableros;
    int opcion = -1;

    // Cargar los tableros guardados en el CSV al iniciar
    vector<string> lineasTableros = GestorArchivos::leerLineas("data/tableros.csv");
    for (const string& linea : lineasTableros) {
        vector<string> datos = GestorArchivos::dividirLinea(linea, ',');
        // Validamos que la linea no sea la cabecera y tenga las columnas correctas
        if (datos.size() >= 4 && datos[0] != "idTablero") {
            int idTablero = stoi(datos[0]);
            string nombre = datos[1];
            int idUsuario = stoi(datos[2]);
            bool esPrivado = (datos[3] == "1");
            listaTableros.insertarFinal(Tablero(idTablero, idUsuario, nombre, esPrivado));
        }
    }

    do {
        Utils::limpiarPantalla();
        cout << "========================================\n";
        cout << "    MODULO 1: USUARIOS Y TABLEROS (Persona 1)\n";
        cout << "========================================\n";
        cout << "1. Registrar usuario\n";
        cout << "2. Crear nuevo tablero (Lista Simple)\n";
        cout << "3. Listar todos los tableros\n";
        cout << "4. Ordenar Tableros por ID (QuickSort - Persona 1)\n";
        cout << "5. Ver metricas de tableros (Lambdas Persona 1)\n";
        cout << "6. Ver usuarios registrados (CSV)\n";
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
            Utils::limpiarEntrada(); // Limpiamos el buffer para que no se salte el getline
            cout << "Nombre: "; getline(cin, nombre);
            cout << "Email: "; getline(cin, email);

            string lineaCSV = to_string(id) + "," + nombre + "," + email;
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

            bool privadoBool = (esPrivado == 1);
            listaTableros.insertarFinal(Tablero(idTablero, idUsuario, nombre, privadoBool));

            // Guardamos con el formato exacto del CSV: idTablero,nombre,idUsuario,esPrivado
            string lineaCSV = to_string(idTablero) + "," + nombre + "," + to_string(idUsuario) + "," + string(privadoBool ? "1" : "0");
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
            cout << "--- ORDENAMIENTO DE TABLEROS POR QUICKSORT ---\n";
            if (listaTableros.esVacia()) {
                cout << "No hay tableros para ordenar.\n";
            } else {
                // Pasamos los elementos de la ListaSimple a un vector temporal para pasarlo al QuickSort
                vector<Tablero> vecTableros;
                listaTableros.recorrer([&vecTableros](Tablero t) {
                    vecTableros.push_back(t);
                });

                quickSortTableros(vecTableros, 0, static_cast<int>(vecTableros.size()) - 1);

                cout << "[OK] Tableros ordenados por ID mediante QuickSort:\n\n";
                for (const auto& t : vecTableros) {
                    t.mostrarInfo();
                }
            }
            Utils::pausar();
            break;
        }
        case 5: {
            Utils::limpiarPantalla();
            cout << "--- METRICAS DE TABLEROS (USO DE LAMBDAS - PERSONA 1) ---\n";
            
            // Usamos funciones lambda para filtrar los tableros
            int privados = listaTableros.contarSi([](Tablero t) {
                return t.getEsPrivado();
            });

            int publicos = listaTableros.contarSi([](Tablero t) {
                return !t.getEsPrivado();
            });

            cout << "Total de tableros registrados: " << listaTableros.getCantidad() << "\n";
            cout << "Tableros Privados: " << privados << "\n";
            cout << "Tableros Publicos: " << publicos << "\n";
            
            Utils::pausar();
            break;
        }
        case 6: {
            Utils::limpiarPantalla();
            cout << "--- USUARIOS EN USUARIOS.CSV ---\n";
            vector<string> lineasUsuarios = GestorArchivos::leerLineas("data/usuarios.csv");
            for (const string& linea : lineasUsuarios) {
                vector<string> usuario = GestorArchivos::dividirLinea(linea, ',');
                if (usuario.size() >= 3 && usuario[0] != "idUsuario") {
                    Usuario usuarioActual(stoi(usuario[0]), usuario[1], usuario[2]);
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

// Funcion auxiliar para juntar las mitades en MergeSort de mayor a menor
void mezclarPines(vector<Pin>& pines, int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    vector<Pin> izq(n1);
    vector<Pin> der(n2);

    for (int i = 0; i < n1; i++) izq[i] = pines[izquierda + i];
    for (int j = 0; j < n2; j++) der[j] = pines[medio + 1 + j];

    int i = 0, j = 0, k = izquierda;

    // Ordenamos de mayor popularidad a menor
    while (i < n1 && j < n2) {
        if (izq[i].getPopularidad() >= der[j].getPopularidad()) {
            pines[k] = izq[i];
            i++;
        } else {
            pines[k] = der[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        pines[k] = izq[i];
        i++;
        k++;
    }

    while (j < n2) {
        pines[k] = der[j];
        j++;
        k++;
    }
}

// Algoritmo MergeSort para ordenar pines por su nivel de popularidad
void mergeSortPines(vector<Pin>& pines, int izquierda, int derecha) {
    if (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        mergeSortPines(pines, izquierda, medio);
        mergeSortPines(pines, medio + 1, derecha);

        mezclarPines(pines, izquierda, medio, derecha);
    }
}

void menuModuloPinesYCategorias() {
    ListaDoble<Categoria> listaCategorias;
    vector<Pin> listaPines;

    // Cargar las categorias registradas al iniciar el modulo
    vector<string> lineasCategorias = GestorArchivos::leerLineas("data/categorias.csv");
    for (const string& linea : lineasCategorias) {
        vector<string> datos = GestorArchivos::dividirLinea(linea, ',');
        if (datos.size() >= 4 && datos[0] != "idCategoria") {
            listaCategorias.insertarFinal(Categoria(stoi(datos[0]), datos[1], datos[2], stoi(datos[3])));
        }
    }

    // Cargar los pines guardados al iniciar
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
        cout << "    MODULO 2: PINES Y CATEGORIAS\n";
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

            // Verificamos que no se repitan los ID de las categorias
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

            // Validacion de ID de Pin unico
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

            // Comprobar que la categoria a asignar exista realmente
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
        case 3: {
            Utils::limpiarPantalla();
            cout << "--- ORDENAR PINES POR POPULARIDAD (MERGESORT - PERSONA 2) ---\n\n";
            
            if (listaPines.empty()) {
                cout << "No hay pines registrados para ordenar.\n";
            } else {
                // Pasamos el rango valido para evitar desbordamientos de memoria
                mergeSortPines(listaPines, 0, static_cast<int>(listaPines.size()) - 1);

                cout << "[OK] Pines ordenados exitosamente de MAYOR a MENOR popularidad:\n\n";
                for (const auto& pin : listaPines) {
                    pin.mostrarInfo();
                }
            }
            Utils::pausar();
            break;
        }
        case 4: {
            Utils::limpiarPantalla();
            cout << "--- CARGAR DATOS DESDE CSV ---\n\n";

            // Limpiamos los contenedores antes de recargar
            listaCategorias.limpiar();
            listaPines.clear();

            vector<string> lineasCat = GestorArchivos::leerLineas("data/categorias.csv");
            for (const string& linea : lineasCat) {
                vector<string> datos = GestorArchivos::dividirLinea(linea, ',');
                if (datos.size() >= 4 && datos[0] != "idCategoria") {
                    listaCategorias.insertarFinal(Categoria(stoi(datos[0]), datos[1], datos[2], stoi(datos[3])));
                }
            }

            vector<string> lineasPin = GestorArchivos::leerLineas("data/pines.csv");
            for (const string& linea : lineasPin) {
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

// Funcion recursiva para calcular la similitud segun la categoria y popularidad
float calcularSimilitudRecursiva(int difCategoria, int difPopularidad, int paso = 0) {
    // Caso base / Primer paso: Evaluamos coincidencia de categoria
    if (paso == 0) {
        float scoreCat = (difCategoria == 0) ? 50.0f : 10.0f;
        return scoreCat + calcularSimilitudRecursiva(difCategoria, difPopularidad, 1);
    } 
    // Segundo paso: Restamos puntos por la diferencia de popularidad
    if (paso == 1) {
        float scorePop = 50.0f - (difPopularidad * 2.0f);
        if (scorePop < 0) scorePop = 0;
        return scorePop;
    }
    return 0.0f;
}

void menuModuloRecomendaciones() {
    // 'static' para mantener el estado de la cola mientras la aplicacion este abierta
    static Cola<Recomendacion> colaRecomendaciones;
    int opcion = -1;

    do {
        Utils::limpiarPantalla();
        cout << "========================================\n";
        cout << "    MODULO 3: RECOMENDACIONES Y METRICAS\n";
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
    cout << "    TB1 Pinterest - AED 2026-2\n";
    cout << "========================================\n";
}

void mostrarRequisitos() {
    Utils::limpiarPantalla();
    cout << "========================================\n";
    cout << "    REQUISITOS DEL PROYECTO PINTEREST\n";
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
