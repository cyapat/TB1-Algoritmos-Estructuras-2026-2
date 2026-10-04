// ============================================================
// TB1 - Algoritmos y Estructuras de Datos 2026-2
// Grupo 9: Recomendacion visual (Pinterest)
//
// Estructuras: ListaSimple (tableros, usuarios, ...), ListaDoble (categorias),
//              Cola (recomendaciones)
// Ordenamientos: QuickSort (Persona 1), MergeSort (Persona 2), HeapSort (Persona 3)
// Recursividad: busqueda binaria (P1), suma de popularidad (P2), similitud (P3)
// Archivos: carpeta data/ (CSV con cabecera)
// ============================================================

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>

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
// DATOS COMPARTIDOS ENTRE LOS 3 MODULOS
// ==========================================

struct Datos {
    ListaSimple<Usuario> usuarios;            // Persona 1
    ListaSimple<Tablero> tableros;            // Persona 1 (lista simple del enunciado)
    ListaSimple<Seguidor> seguidores;         // Persona 1
    ListaSimple<Notificacion> notificaciones; // Persona 1
    ListaSimple<Perfil> perfiles;             // Persona 1
    ListaDoble<Categoria> categorias;         // Persona 2 (lista doble del enunciado)
    vector<Pin> pines;                        // Persona 2 (se ordena con MergeSort)
    Cola<Recomendacion> recomendaciones;      // Persona 3 (cola del enunciado)
    ListaSimple<SimilitudPin> similitudes;    // Persona 3
};

Datos bd;

// Rutas de los archivos (la carpeta data/ debe estar junto al ejecutable / directorio de trabajo)
const string R_USUARIOS = "data/usuarios.csv";
const string R_TABLEROS = "data/tableros.csv";
const string R_CATEGORIAS = "data/categorias.csv";
const string R_PINES = "data/pines.csv";
const string R_RECOMENDACIONES = "data/recomendaciones.csv";
const string R_SIMILITUDES = "data/similitudes.csv";
const string R_SEGUIDORES = "data/seguidores.csv";
const string R_NOTIFICACIONES = "data/notificaciones.csv";
const string R_PERFILES = "data/perfiles.csv";

// ==========================================
// UTILIDADES GENERALES
// ==========================================

bool archivoExiste(const string& ruta) {
    ifstream f(ruta.c_str());
    return f.good();
}

int aEntero(const string& s) {
    try { return stoi(s); }
    catch (...) { return 0; }
}

float aFloat(const string& s) {
    try { return stof(s); }
    catch (...) { return 0.0f; }
}

bool esNumero(const string& s) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.size(); i++) {
        if (!isdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    return true;
}

string fechaHoy() {
    time_t t = time(nullptr);
    tm* lt = localtime(&t);
    char buf[16];
    strftime(buf, sizeof(buf), "%Y-%m-%d", lt);
    return string(buf);
}

// Lee un CSV (sin lineas vacias y quitando el '\r' de archivos creados en Windows)
vector<string> leerCSV(const string& ruta) {
    vector<string> resultado;
    if (!archivoExiste(ruta)) return resultado;

    vector<string> lineas = GestorArchivos::leerLineas(ruta);
    for (size_t i = 0; i < lineas.size(); i++) {
        string s = lineas[i];
        if (!s.empty() && s[s.size() - 1] == '\r') s.erase(s.size() - 1);
        if (!s.empty()) resultado.push_back(s);
    }
    return resultado;
}

// Reescribe un CSV completo (cabecera + lineas)
void sobrescribir(const string& ruta, const string& cabecera, const vector<string>& lineas) {
    ofstream archivo(ruta.c_str(), ios::trunc);
    if (!archivo.is_open()) {
        cout << "[Error] No se pudo escribir en " << ruta
             << " (existe la carpeta data/?)\n";
        return;
    }
    archivo << cabecera << "\n";
    for (size_t i = 0; i < lineas.size(); i++) {
        archivo << lineas[i] << "\n";
    }
}

// ----- Entrada de datos (todo con getline para que pausar() funcione bien) -----

string leerTexto(const string& mensaje, bool permitirVacio = false) {
    string s;
    while (true) {
        cout << mensaje;
        if (!getline(cin, s)) {
            cout << "\n";
            exit(0);
        }
        if (!s.empty() && s[s.size() - 1] == '\r') s.erase(s.size() - 1);
        if (!s.empty() || permitirVacio) return limpiarCampo(s);
        cout << "[Error] El campo no puede estar vacio.\n";
    }
}

int leerEntero(const string& mensaje, int minimo, int maximo) {
    string s;
    while (true) {
        cout << mensaje;
        if (!getline(cin, s)) {
            cout << "\n";
            exit(0);
        }
        try {
            size_t pos = 0;
            int valor = stoi(s, &pos);
            bool soloEspacios = true;
            for (size_t i = pos; i < s.size(); i++) {
                if (!isspace(static_cast<unsigned char>(s[i]))) soloEspacios = false;
            }
            if (soloEspacios && valor >= minimo && valor <= maximo) return valor;
        }
        catch (...) {}
        cout << "[Error] Ingresa un numero entre " << minimo << " y " << maximo << ".\n";
    }
}

float leerFloat(const string& mensaje, float minimo, float maximo) {
    string s;
    while (true) {
        cout << mensaje;
        if (!getline(cin, s)) {
            cout << "\n";
            exit(0);
        }
        try {
            size_t pos = 0;
            float valor = stof(s, &pos);
            bool soloEspacios = true;
            for (size_t i = pos; i < s.size(); i++) {
                if (!isspace(static_cast<unsigned char>(s[i]))) soloEspacios = false;
            }
            if (soloEspacios && valor >= minimo && valor <= maximo) return valor;
        }
        catch (...) {}
        cout << "[Error] Ingresa un numero entre " << floatATexto(minimo)
             << " y " << floatATexto(maximo) << ".\n";
    }
}

void banner(const string& titulo) {
    Utils::limpiarPantalla();
    cout << "========================================\n";
    cout << "  " << titulo << "\n";
    cout << "========================================\n";
}

// Siguiente ID disponible (maximo + 1) para cualquier estructura con recorrer()
// Uso: siguienteId<Tablero>(bd.tableros, [](Tablero t) { return t.getIdTablero(); });
template <typename T, typename Contenedor>
int siguienteId(const Contenedor& contenedor, function<int(T)> selector) {
    int maximo = 0;
    contenedor.recorrer([&](T elemento) {
        int valor = selector(elemento);
        if (valor > maximo) maximo = valor;
    });
    return maximo + 1;
}

// ==========================================
// CARGA Y GUARDADO DE ARCHIVOS
// ==========================================

void cargarTodo() {
    vector<string> lineas;
    vector<string> c;

    bd.usuarios.limpiar();
    lineas = leerCSV(R_USUARIOS);
    for (size_t i = 0; i < lineas.size(); i++) {
        c = GestorArchivos::dividirLinea(lineas[i], ',');
        if (c.size() >= 5 && esNumero(c[0])) {
            bd.usuarios.insertarFinal(Usuario(aEntero(c[0]), c[1], c[2], c[3], c[4]));
        }
    }

    bd.tableros.limpiar();
    lineas = leerCSV(R_TABLEROS);
    for (size_t i = 0; i < lineas.size(); i++) {
        c = GestorArchivos::dividirLinea(lineas[i], ',');
        if (c.size() >= 7 && esNumero(c[0])) {
            bd.tableros.insertarFinal(Tablero(aEntero(c[0]), c[1], aEntero(c[2]), c[3],
                c[4] == "1", aEntero(c[5]), c[6]));
        }
    }

    bd.categorias.limpiar();
    lineas = leerCSV(R_CATEGORIAS);
    for (size_t i = 0; i < lineas.size(); i++) {
        c = GestorArchivos::dividirLinea(lineas[i], ',');
        if (c.size() >= 4 && esNumero(c[0])) {
            bd.categorias.insertarFinal(Categoria(aEntero(c[0]), c[1], c[2], aEntero(c[3])));
        }
    }

    bd.pines.clear();
    lineas = leerCSV(R_PINES);
    for (size_t i = 0; i < lineas.size(); i++) {
        c = GestorArchivos::dividirLinea(lineas[i], ',');
        if (c.size() >= 7 && esNumero(c[0])) {
            bd.pines.push_back(Pin(aEntero(c[0]), c[1], c[2], aEntero(c[3]),
                aEntero(c[4]), aEntero(c[5]), c[6]));
        }
    }

    bd.recomendaciones.limpiar();
    lineas = leerCSV(R_RECOMENDACIONES);
    for (size_t i = 0; i < lineas.size(); i++) {
        c = GestorArchivos::dividirLinea(lineas[i], ',');
        if (c.size() >= 4 && esNumero(c[0])) {
            bd.recomendaciones.encolar(Recomendacion(aEntero(c[0]), aEntero(c[1]),
                aEntero(c[2]), aFloat(c[3])));
        }
    }

    bd.similitudes.limpiar();
    lineas = leerCSV(R_SIMILITUDES);
    for (size_t i = 0; i < lineas.size(); i++) {
        c = GestorArchivos::dividirLinea(lineas[i], ',');
        if (c.size() >= 4 && esNumero(c[0])) {
            bd.similitudes.insertarFinal(SimilitudPin(aEntero(c[0]), aEntero(c[1]),
                aEntero(c[2]), aFloat(c[3])));
        }
    }

    // Archivos opcionales de la Persona 1 (se crean al usarlos por primera vez)
    bd.seguidores.limpiar();
    lineas = leerCSV(R_SEGUIDORES);
    for (size_t i = 0; i < lineas.size(); i++) {
        c = GestorArchivos::dividirLinea(lineas[i], ',');
        if (c.size() >= 4 && esNumero(c[0])) {
            bd.seguidores.insertarFinal(Seguidor(aEntero(c[0]), aEntero(c[1]),
                aEntero(c[2]), c[3]));
        }
    }

    bd.notificaciones.limpiar();
    lineas = leerCSV(R_NOTIFICACIONES);
    for (size_t i = 0; i < lineas.size(); i++) {
        c = GestorArchivos::dividirLinea(lineas[i], ',');
        if (c.size() >= 5 && esNumero(c[0])) {
            bd.notificaciones.insertarFinal(Notificacion(aEntero(c[0]), aEntero(c[1]),
                c[2], c[3] == "1", c[4]));
        }
    }

    bd.perfiles.limpiar();
    lineas = leerCSV(R_PERFILES);
    for (size_t i = 0; i < lineas.size(); i++) {
        c = GestorArchivos::dividirLinea(lineas[i], ',');
        if (c.size() >= 5 && esNumero(c[0])) {
            bd.perfiles.insertarFinal(Perfil(aEntero(c[0]), aEntero(c[1]), c[2], c[3],
                aEntero(c[4])));
        }
    }
}

void guardarUsuarios() {
    vector<string> l;
    bd.usuarios.recorrer([&l](Usuario u) { l.push_back(u.toCSV()); });
    sobrescribir(R_USUARIOS, "idUsuario,nombre,username,correo,fechaRegistro", l);
}

void guardarTableros() {
    vector<string> l;
    bd.tableros.recorrer([&l](Tablero t) { l.push_back(t.toCSV()); });
    sobrescribir(R_TABLEROS,
        "idTablero,nombre,idUsuario,descripcion,esPublico,cantidadPines,fechaCreacion", l);
}

void guardarCategorias() {
    vector<string> l;
    bd.categorias.recorrer([&l](Categoria c) { l.push_back(c.toCSV()); });
    sobrescribir(R_CATEGORIAS, "idCategoria,nombre,descripcion,cantidadPines", l);
}

void guardarPines() {
    vector<string> l;
    for (size_t i = 0; i < bd.pines.size(); i++) l.push_back(bd.pines[i].toCSV());
    sobrescribir(R_PINES,
        "idPin,titulo,descripcion,idTablero,idCategoria,popularidad,fechaCreacion", l);
}

void guardarRecomendaciones() {
    vector<string> l;
    bd.recomendaciones.recorrer([&l](Recomendacion r) { l.push_back(r.toCSV()); });
    sobrescribir(R_RECOMENDACIONES, "idRecomendacion,idUsuario,idPin,puntuacion", l);
}

void guardarSimilitudes() {
    vector<string> l;
    bd.similitudes.recorrer([&l](SimilitudPin s) { l.push_back(s.toCSV()); });
    sobrescribir(R_SIMILITUDES, "idSimilitud,idPinA,idPinB,porcentajeSimilitud", l);
}

void guardarSeguidores() {
    vector<string> l;
    bd.seguidores.recorrer([&l](Seguidor s) { l.push_back(s.toCSV()); });
    sobrescribir(R_SEGUIDORES, "idSeguidor,idUsuarioQueSigue,idUsuarioSeguido,fechaInicio", l);
}

void guardarNotificaciones() {
    vector<string> l;
    bd.notificaciones.recorrer([&l](Notificacion n) { l.push_back(n.toCSV()); });
    sobrescribir(R_NOTIFICACIONES, "idNotificacion,idUsuario,mensaje,leida,fecha", l);
}

void guardarPerfiles() {
    vector<string> l;
    bd.perfiles.recorrer([&l](Perfil p) { l.push_back(p.toCSV()); });
    sobrescribir(R_PERFILES, "idPerfil,idUsuario,biografia,fotoPerfil,cantidadSeguidores", l);
}

// ==========================================
// CONSULTAS COMUNES (validaciones entre modulos)
// ==========================================

bool obtenerUsuario(int id, Usuario& resultado) {
    Usuario* p = bd.usuarios.buscar([id](Usuario u) { return u.getIdUsuario() == id; });
    if (p == nullptr) return false;
    resultado = *p;
    delete p; // ListaSimple::buscar devuelve memoria dinamica
    return true;
}

bool existeUsuario(int id) {
    return bd.usuarios.contarSi([id](Usuario u) { return u.getIdUsuario() == id; }) > 0;
}

bool existeTablero(int id) {
    return bd.tableros.contarSi([id](Tablero t) { return t.getIdTablero() == id; }) > 0;
}

// Devuelve el id del usuario dueno del tablero, o -1 si el tablero no existe
int duenoDeTablero(int idTablero) {
    Tablero* p = bd.tableros.buscar([idTablero](Tablero t) { return t.getIdTablero() == idTablero; });
    if (p == nullptr) return -1;
    int dueno = p->getIdUsuario();
    delete p;
    return dueno;
}

bool existeCategoria(int id) {
    Categoria c;
    return bd.categorias.buscar([id](Categoria cat) { return cat.getIdCategoria() == id; }, c);
}

bool obtenerPin(int id, Pin& resultado) {
    for (size_t i = 0; i < bd.pines.size(); i++) {
        if (bd.pines[i].getIdPin() == id) {
            resultado = bd.pines[i];
            return true;
        }
    }
    return false;
}

// Recalcula cantidadPines de tableros y categorias a partir de los pines reales
void recalcularContadores() {
    vector<Tablero> tv;
    bd.tableros.recorrer([&tv](Tablero t) { tv.push_back(t); });
    bd.tableros.limpiar();
    for (size_t i = 0; i < tv.size(); i++) {
        int total = 0;
        for (size_t j = 0; j < bd.pines.size(); j++) {
            if (bd.pines[j].getIdTablero() == tv[i].getIdTablero()) total++;
        }
        tv[i].setCantidadPines(total);
        bd.tableros.insertarFinal(tv[i]);
    }

    vector<Categoria> cv;
    bd.categorias.recorrer([&cv](Categoria c) { cv.push_back(c); });
    bd.categorias.limpiar();
    for (size_t i = 0; i < cv.size(); i++) {
        int total = 0;
        for (size_t j = 0; j < bd.pines.size(); j++) {
            if (bd.pines[j].getIdCategoria() == cv[i].getIdCategoria()) total++;
        }
        cv[i].setCantidadPines(total);
        bd.categorias.insertarFinal(cv[i]);
    }
}

// ==========================================
// PERSONA 1: USUARIOS Y TABLEROS
// ==========================================

// QuickSort (recursivo) para ordenar los tableros por ID
void quickSortTableros(vector<Tablero>& tableros, int izquierda, int derecha) {
    if (izquierda >= derecha) return;

    int i = izquierda;
    int j = derecha;
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

    if (izquierda < j) quickSortTableros(tableros, izquierda, j);
    if (i < derecha) quickSortTableros(tableros, i, derecha);
}

// Busqueda binaria RECURSIVA sobre el vector ordenado (devuelve la posicion o -1)
int busquedaBinariaTableros(const vector<Tablero>& v, int id, int izquierda, int derecha) {
    if (izquierda > derecha) return -1; // caso base: no encontrado

    int medio = izquierda + (derecha - izquierda) / 2;
    if (v[medio].getIdTablero() == id) return medio; // caso base: encontrado

    if (v[medio].getIdTablero() > id) {
        return busquedaBinariaTableros(v, id, izquierda, medio - 1);
    }
    return busquedaBinariaTableros(v, id, medio + 1, derecha);
}

vector<Tablero> tablerosAVector() {
    vector<Tablero> v;
    bd.tableros.recorrer([&v](Tablero t) { v.push_back(t); });
    return v;
}

void mostrarPerfilYNotificaciones(int idUsuario) {
    Usuario u;
    if (!obtenerUsuario(idUsuario, u)) {
        cout << "[Error] El usuario no existe.\n";
        return;
    }

    // Perfil: si no existe se crea uno por defecto
    int tienePerfil = bd.perfiles.contarSi([idUsuario](Perfil p) { return p.getIdUsuario() == idUsuario; });
    if (tienePerfil == 0) {
        int idPerfil = siguienteId<Perfil>(bd.perfiles, [](Perfil p) { return p.getIdPerfil(); });
        bd.perfiles.insertarFinal(Perfil(idPerfil, idUsuario, "Sin biografia", "default.png", 0));
        guardarPerfiles();
    }

    int seguidores = bd.seguidores.contarSi([idUsuario](Seguidor s) { return s.getIdUsuarioSeguido() == idUsuario; });
    int siguiendo = bd.seguidores.contarSi([idUsuario](Seguidor s) { return s.getIdUsuarioQueSigue() == idUsuario; });

    Perfil* perfil = bd.perfiles.buscar([idUsuario](Perfil p) { return p.getIdUsuario() == idUsuario; });
    cout << "--- PERFIL ---\n";
    u.mostrarInfo();
    if (perfil != nullptr) {
        cout << "Biografia: " << perfil->getBiografia() << " | Foto: " << perfil->getFotoPerfil() << "\n";
        delete perfil;
    }
    cout << "Seguidores: " << seguidores << " | Siguiendo: " << siguiendo << "\n";

    cout << "\n--- TABLEROS DEL USUARIO ---\n";
    int cantidadTableros = 0;
    bd.tableros.recorrer([&](Tablero t) {
        if (t.getIdUsuario() == idUsuario) {
            t.mostrarInfo();
            cantidadTableros++;
        }
    });
    if (cantidadTableros == 0) cout << "(sin tableros)\n";

    cout << "\n--- NOTIFICACIONES ---\n";
    int cantidadNotif = 0;
    bd.notificaciones.recorrer([&](Notificacion n) {
        if (n.getIdUsuario() == idUsuario) {
            n.mostrarInfo();
            cantidadNotif++;
        }
    });
    if (cantidadNotif == 0) {
        cout << "(sin notificaciones)\n";
    }
    else {
        // Se marcan como leidas: se reconstruye la lista con las notificaciones actualizadas
        vector<Notificacion> todas;
        bd.notificaciones.recorrer([&todas](Notificacion n) { todas.push_back(n); });
        bd.notificaciones.limpiar();
        for (size_t i = 0; i < todas.size(); i++) {
            if (todas[i].getIdUsuario() == idUsuario) todas[i].setLeida(true);
            bd.notificaciones.insertarFinal(todas[i]);
        }
        guardarNotificaciones();
    }
}

void menuModuloUsuariosYTableros() {
    int opcion = -1;

    do {
        banner("MODULO 1: USUARIOS Y TABLEROS (Persona 1)");
        cout << " 1. Registrar usuario\n";
        cout << " 2. Ver usuarios\n";
        cout << " 3. Crear tablero (Lista Simple)\n";
        cout << " 4. Listar tableros\n";
        cout << " 5. Eliminar tablero\n";
        cout << " 6. Ordenar tableros por ID (QuickSort)\n";
        cout << " 7. Buscar tablero por ID (busqueda binaria recursiva)\n";
        cout << " 8. Invertir orden de la lista de tableros\n";
        cout << " 9. Metricas de tableros (lambdas)\n";
        cout << "10. Seguir a un usuario\n";
        cout << "11. Ver perfil, tableros y notificaciones de un usuario\n";
        cout << " 0. Volver al menu principal\n";
        opcion = leerEntero("Opcion: ", 0, 11);

        switch (opcion) {
        case 1: {
            banner("REGISTRAR USUARIO");
            string nombre = leerTexto("Nombre completo: ");

            string username;
            while (true) {
                username = leerTexto("Username: ");
                int repetidos = bd.usuarios.contarSi([&username](Usuario u) {
                    return u.getUsername() == username;
                });
                if (repetidos == 0) break;
                cout << "[Error] Ese username ya existe.\n";
            }

            string correo;
            while (true) {
                correo = leerTexto("Correo: ");
                if (correo.find('@') != string::npos) break;
                cout << "[Error] El correo debe contener '@'.\n";
            }

            int id = siguienteId<Usuario>(bd.usuarios, [](Usuario u) { return u.getIdUsuario(); });
            bd.usuarios.insertarFinal(Usuario(id, nombre, username, correo, fechaHoy()));
            guardarUsuarios();
            cout << "\n[OK] Usuario #" << id << " registrado y guardado en usuarios.csv\n";
            Utils::pausar();
            break;
        }
        case 2: {
            banner("USUARIOS REGISTRADOS");
            if (bd.usuarios.esVacia()) {
                cout << "No hay usuarios registrados.\n";
            }
            else {
                bd.usuarios.recorrer([](Usuario u) { u.mostrarInfo(); });
            }
            Utils::pausar();
            break;
        }
        case 3: {
            banner("CREAR TABLERO");
            int idUsuario = leerEntero("ID del usuario propietario: ", 1, 1000000);
            if (!existeUsuario(idUsuario)) {
                cout << "\n[Error] No existe un usuario con ese ID.\n";
                Utils::pausar();
                break;
            }
            string nombre = leerTexto("Nombre del tablero: ");
            string descripcion = leerTexto("Descripcion: ");
            int publico = leerEntero("Es publico? (1 = Si, 0 = No): ", 0, 1);

            int id = siguienteId<Tablero>(bd.tableros, [](Tablero t) { return t.getIdTablero(); });
            bd.tableros.insertarFinal(Tablero(id, nombre, idUsuario, descripcion, publico == 1, 0, fechaHoy()));
            guardarTableros();
            cout << "\n[OK] Tablero #" << id << " insertado en la lista simple y guardado en tableros.csv\n";
            Utils::pausar();
            break;
        }
        case 4: {
            banner("LISTA DE TABLEROS (" + to_string(bd.tableros.getCantidad()) + ")");
            if (bd.tableros.esVacia()) {
                cout << "No hay tableros registrados.\n";
            }
            else {
                bd.tableros.recorrer([](Tablero t) { t.mostrarInfo(); });
            }
            Utils::pausar();
            break;
        }
        case 5: {
            banner("ELIMINAR TABLERO");
            if (bd.tableros.esVacia()) {
                cout << "No hay tableros para eliminar.\n";
                Utils::pausar();
                break;
            }
            int id = leerEntero("ID del tablero a eliminar: ", 1, 1000000);
            if (!existeTablero(id)) {
                cout << "\n[Error] No existe un tablero con ese ID.\n";
                Utils::pausar();
                break;
            }
            int pinesAsociados = 0;
            for (size_t i = 0; i < bd.pines.size(); i++) {
                if (bd.pines[i].getIdTablero() == id) pinesAsociados++;
            }
            if (pinesAsociados > 0) {
                cout << "\n[Error] El tablero tiene " << pinesAsociados
                     << " pin(es); no se puede eliminar.\n";
            }
            else if (bd.tableros.eliminarSi([id](Tablero t) { return t.getIdTablero() == id; })) {
                guardarTableros();
                cout << "\n[OK] Tablero eliminado.\n";
            }
            Utils::pausar();
            break;
        }
        case 6: {
            banner("ORDENAR TABLEROS POR ID (QUICKSORT)");
            if (bd.tableros.esVacia()) {
                cout << "No hay tableros para ordenar.\n";
            }
            else {
                vector<Tablero> v = tablerosAVector();
                quickSortTableros(v, 0, static_cast<int>(v.size()) - 1);

                // La lista simple se reconstruye con el nuevo orden
                bd.tableros.limpiar();
                for (size_t i = 0; i < v.size(); i++) bd.tableros.insertarFinal(v[i]);
                guardarTableros();

                cout << "[OK] Tableros ordenados por ID:\n\n";
                bd.tableros.recorrer([](Tablero t) { t.mostrarInfo(); });
            }
            Utils::pausar();
            break;
        }
        case 7: {
            banner("BUSCAR TABLERO (BUSQUEDA BINARIA RECURSIVA)");
            if (bd.tableros.esVacia()) {
                cout << "No hay tableros registrados.\n";
                Utils::pausar();
                break;
            }
            vector<Tablero> v = tablerosAVector();
            quickSortTableros(v, 0, static_cast<int>(v.size()) - 1); // la busqueda binaria exige orden
            int id = leerEntero("ID a buscar: ", 1, 1000000);
            int pos = busquedaBinariaTableros(v, id, 0, static_cast<int>(v.size()) - 1);
            if (pos == -1) {
                cout << "\n[Resultado] No se encontro el tablero #" << id << ".\n";
            }
            else {
                cout << "\n[Resultado] Tablero encontrado (posicion " << pos << " del vector ordenado):\n";
                v[pos].mostrarInfo();
            }
            Utils::pausar();
            break;
        }
        case 8: {
            banner("INVERTIR LISTA DE TABLEROS");
            if (bd.tableros.esVacia()) {
                cout << "No hay tableros registrados.\n";
            }
            else {
                bd.tableros.invertir();
                guardarTableros();
                cout << "[OK] Lista invertida (nuevo orden):\n\n";
                bd.tableros.recorrer([](Tablero t) { t.mostrarInfo(); });
            }
            Utils::pausar();
            break;
        }
        case 9: {
            banner("METRICAS DE TABLEROS (LAMBDAS)");
            int privados = bd.tableros.contarSi([](Tablero t) { return t.getEsPrivado(); });
            int publicos = bd.tableros.contarSi([](Tablero t) { return t.getEsPublico(); });
            int vacios = bd.tableros.contarSi([](Tablero t) { return t.getCantidadPines() == 0; });

            cout << "Total de tableros:  " << bd.tableros.getCantidad() << "\n";
            cout << "Tableros publicos:  " << publicos << "\n";
            cout << "Tableros privados:  " << privados << "\n";
            cout << "Tableros sin pines: " << vacios << "\n";
            Utils::pausar();
            break;
        }
        case 10: {
            banner("SEGUIR A UN USUARIO");
            int quienSigue = leerEntero("Tu ID de usuario: ", 1, 1000000);
            Usuario origen;
            if (!obtenerUsuario(quienSigue, origen)) {
                cout << "\n[Error] No existe un usuario con ese ID.\n";
                Utils::pausar();
                break;
            }
            int seguido = leerEntero("ID del usuario a seguir: ", 1, 1000000);
            if (!existeUsuario(seguido)) {
                cout << "\n[Error] No existe un usuario con ese ID.\n";
            }
            else if (seguido == quienSigue) {
                cout << "\n[Error] No puedes seguirte a ti mismo.\n";
            }
            else if (bd.seguidores.contarSi([=](Seguidor s) {
                         return s.getIdUsuarioQueSigue() == quienSigue && s.getIdUsuarioSeguido() == seguido;
                     }) > 0) {
                cout << "\n[Aviso] Ya sigues a ese usuario.\n";
            }
            else {
                int idSeg = siguienteId<Seguidor>(bd.seguidores, [](Seguidor s) { return s.getIdSeguidor(); });
                bd.seguidores.insertarFinal(Seguidor(idSeg, quienSigue, seguido, fechaHoy()));

                int idNot = siguienteId<Notificacion>(bd.notificaciones, [](Notificacion n) { return n.getIdNotificacion(); });
                bd.notificaciones.insertarFinal(Notificacion(idNot, seguido,
                    origen.getNombre() + " comenzo a seguirte", false, fechaHoy()));

                guardarSeguidores();
                guardarNotificaciones();
                cout << "\n[OK] Ahora sigues al usuario #" << seguido << " (se le envio una notificacion).\n";
            }
            Utils::pausar();
            break;
        }
        case 11: {
            banner("PERFIL DE USUARIO");
            int id = leerEntero("ID de usuario: ", 1, 1000000);
            cout << "\n";
            mostrarPerfilYNotificaciones(id);
            Utils::pausar();
            break;
        }
        case 0:
            break;
        }
    } while (opcion != 0);
}

// ==========================================
// PERSONA 2: PINES Y CATEGORIAS
// ==========================================

// Juntar las mitades en MergeSort (de mayor a menor popularidad)
void mezclarPines(vector<Pin>& pines, int izquierda, int medio, int derecha) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    vector<Pin> izq(n1);
    vector<Pin> der(n2);

    for (int i = 0; i < n1; i++) izq[i] = pines[izquierda + i];
    for (int j = 0; j < n2; j++) der[j] = pines[medio + 1 + j];

    int i = 0, j = 0, k = izquierda;

    while (i < n1 && j < n2) {
        if (izq[i].getPopularidad() >= der[j].getPopularidad()) {
            pines[k] = izq[i];
            i++;
        }
        else {
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

// MergeSort (recursivo) para ordenar pines por popularidad
void mergeSortPines(vector<Pin>& pines, int izquierda, int derecha) {
    if (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        mergeSortPines(pines, izquierda, medio);
        mergeSortPines(pines, medio + 1, derecha);

        mezclarPines(pines, izquierda, medio, derecha);
    }
}

// Metodo recursivo de la Persona 2: suma la popularidad de los pines de una categoria
int sumarPopularidadRecursivo(const vector<Pin>& pines, int idCategoria, size_t indice) {
    if (indice >= pines.size()) return 0; // caso base
    int actual = (pines[indice].getIdCategoria() == idCategoria) ? pines[indice].getPopularidad() : 0;
    return actual + sumarPopularidadRecursivo(pines, idCategoria, indice + 1);
}

void menuModuloPinesYCategorias() {
    int opcion = -1;

    do {
        banner("MODULO 2: PINES Y CATEGORIAS (Persona 2)");
        cout << "1. Agregar categoria (Lista Doble)\n";
        cout << "2. Listar categorias (inicio a fin)\n";
        cout << "3. Listar categorias en orden inverso\n";
        cout << "4. Navegar categorias con iterador\n";
        cout << "5. Agregar pin\n";
        cout << "6. Listar pines\n";
        cout << "7. Ordenar pines por popularidad (MergeSort)\n";
        cout << "8. Reporte de popularidad por categoria (filtrar + recursividad)\n";
        cout << "9. Recargar datos desde CSV\n";
        cout << "0. Volver al menu principal\n";
        opcion = leerEntero("Opcion: ", 0, 9);

        switch (opcion) {
        case 1: {
            banner("AGREGAR CATEGORIA");
            string nombre;
            while (true) {
                nombre = leerTexto("Nombre: ");
                bool repetido = false;
                bd.categorias.recorrer([&](Categoria c) {
                    if (c.getNombre() == nombre) repetido = true;
                });
                if (!repetido) break;
                cout << "[Error] Ya existe una categoria con ese nombre.\n";
            }
            string descripcion = leerTexto("Descripcion: ");
            int id = siguienteId<Categoria>(bd.categorias, [](Categoria c) { return c.getIdCategoria(); });

            bd.categorias.insertarFinal(Categoria(id, nombre, descripcion, 0));
            guardarCategorias();
            cout << "\n[OK] Categoria #" << id << " insertada en la lista doble y guardada en categorias.csv\n";
            Utils::pausar();
            break;
        }
        case 2: {
            banner("CATEGORIAS (" + to_string(bd.categorias.getCantidad()) + ")");
            if (bd.categorias.esVacia()) cout << "No hay categorias registradas.\n";
            else bd.categorias.recorrer([](Categoria c) { c.mostrarInfo(); });
            Utils::pausar();
            break;
        }
        case 3: {
            banner("CATEGORIAS EN ORDEN INVERSO");
            if (bd.categorias.esVacia()) cout << "No hay categorias registradas.\n";
            else bd.categorias.recorrerInverso([](Categoria c) { c.mostrarInfo(); });
            Utils::pausar();
            break;
        }
        case 4: {
            banner("NAVEGAR CATEGORIAS (ITERADOR)");
            if (bd.categorias.esVacia()) {
                cout << "No hay categorias registradas.\n";
                Utils::pausar();
                break;
            }
            ListaDoble<Categoria>::Iterador it = bd.categorias.obtenerIteradorInicio();
            string comando = "";
            while (it.esValido() && comando != "s") {
                cout << "\n";
                it.getDato().mostrarInfo();
                comando = leerTexto("[n] siguiente  [p] anterior  [s] salir: ");
                if (comando == "n") it.avanzar();
                else if (comando == "p") it.retroceder();
            }
            if (!it.esValido()) cout << "\n(Se llego al extremo de la lista)\n";
            Utils::pausar();
            break;
        }
        case 5: {
            banner("AGREGAR PIN");
            if (bd.categorias.esVacia() || bd.tableros.esVacia()) {
                cout << "Necesitas al menos una categoria y un tablero para crear un pin.\n";
                Utils::pausar();
                break;
            }

            cout << "Categorias disponibles:\n";
            bd.categorias.recorrer([](Categoria c) { cout << "  " << c.getIdCategoria() << ". " << c.getNombre() << "\n"; });
            int idCategoria = leerEntero("ID de categoria: ", 1, 1000000);
            if (!existeCategoria(idCategoria)) {
                cout << "\n[Error] La categoria indicada no existe.\n";
                Utils::pausar();
                break;
            }

            cout << "\nTableros disponibles:\n";
            bd.tableros.recorrer([](Tablero t) { cout << "  " << t.getIdTablero() << ". " << t.getNombre() << "\n"; });
            int idTablero = leerEntero("ID de tablero: ", 1, 1000000);
            if (!existeTablero(idTablero)) {
                cout << "\n[Error] El tablero indicado no existe.\n";
                Utils::pausar();
                break;
            }

            string titulo = leerTexto("Titulo: ");
            string descripcion = leerTexto("Descripcion: ");
            int popularidad = leerEntero("Popularidad inicial (0 - 100000): ", 0, 100000);

            int id = 1;
            for (size_t i = 0; i < bd.pines.size(); i++) {
                if (bd.pines[i].getIdPin() >= id) id = bd.pines[i].getIdPin() + 1;
            }

            bd.pines.push_back(Pin(id, titulo, descripcion, idTablero, idCategoria, popularidad, fechaHoy()));
            recalcularContadores();
            guardarPines();
            guardarTableros();
            guardarCategorias();
            cout << "\n[OK] Pin #" << id << " guardado; se actualizaron los contadores del tablero y la categoria.\n";
            Utils::pausar();
            break;
        }
        case 6: {
            banner("PINES (" + to_string(bd.pines.size()) + ")");
            if (bd.pines.empty()) cout << "No hay pines registrados.\n";
            for (size_t i = 0; i < bd.pines.size(); i++) bd.pines[i].mostrarInfo();
            Utils::pausar();
            break;
        }
        case 7: {
            banner("PINES POR POPULARIDAD (MERGESORT)");
            if (bd.pines.empty()) {
                cout << "No hay pines registrados para ordenar.\n";
            }
            else {
                vector<Pin> copia = bd.pines; // se ordena una copia para no alterar el archivo
                mergeSortPines(copia, 0, static_cast<int>(copia.size()) - 1);
                cout << "[OK] Ordenados de MAYOR a MENOR popularidad:\n\n";
                for (size_t i = 0; i < copia.size(); i++) copia[i].mostrarInfo();
            }
            Utils::pausar();
            break;
        }
        case 8: {
            banner("POPULARIDAD TOTAL POR CATEGORIA");
            if (bd.categorias.esVacia()) {
                cout << "No hay categorias registradas.\n";
                Utils::pausar();
                break;
            }
            cout << "(solo categorias con al menos 1 pin)\n\n";
            bd.categorias.filtrar(
                [](Categoria c) { return c.getCantidadPines() > 0; },
                [](Categoria c) {
                    int total = sumarPopularidadRecursivo(bd.pines, c.getIdCategoria(), 0);
                    cout << c.getNombre() << ": " << c.getCantidadPines() << " pin(es), popularidad total "
                         << total << " (promedio " << (total / c.getCantidadPines()) << ")\n";
                });
            Utils::pausar();
            break;
        }
        case 9: {
            banner("RECARGAR DATOS DESDE CSV");
            cargarTodo();
            cout << "[OK] Datos recargados.\n";
            cout << "Categorias: " << bd.categorias.getCantidad() << "\n";
            cout << "Pines:      " << bd.pines.size() << "\n";
            Utils::pausar();
            break;
        }
        case 0:
            break;
        }
    } while (opcion != 0);
}

// ==========================================
// PERSONA 3: RECOMENDACIONES Y SIMILITUD
// ==========================================

// HeapSort: heapify recursivo con monticulo de MINIMOS -> el resultado queda de mayor a menor
void heapifyRecomendaciones(vector<Recomendacion>& v, int n, int i) {
    int menor = i;
    int izq = 2 * i + 1;
    int der = 2 * i + 2;

    if (izq < n && v[izq].getPuntuacion() < v[menor].getPuntuacion()) menor = izq;
    if (der < n && v[der].getPuntuacion() < v[menor].getPuntuacion()) menor = der;

    if (menor != i) {
        swap(v[i], v[menor]);
        heapifyRecomendaciones(v, n, menor); // llamada recursiva
    }
}

void heapSortRecomendaciones(vector<Recomendacion>& v) {
    int n = static_cast<int>(v.size());
    for (int i = n / 2 - 1; i >= 0; i--) heapifyRecomendaciones(v, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(v[0], v[i]);
        heapifyRecomendaciones(v, i, 0);
    }
}

// Separa un texto en palabras (minusculas, solo letras/numeros, mas de 3 letras, sin repetidas)
vector<string> tokenizar(const string& texto) {
    vector<string> palabras;
    string actual = "";
    for (size_t i = 0; i <= texto.size(); i++) {
        if (i < texto.size() && isalnum(static_cast<unsigned char>(texto[i]))) {
            actual += static_cast<char>(tolower(static_cast<unsigned char>(texto[i])));
        }
        else {
            if (actual.size() > 3) palabras.push_back(actual);
            actual = "";
        }
    }
    sort(palabras.begin(), palabras.end());
    palabras.erase(unique(palabras.begin(), palabras.end()), palabras.end());
    return palabras;
}

// Metodo recursivo de la Persona 3: cuenta cuantas palabras de 'a' aparecen tambien en 'b'
int coincidenciasRecursivo(const vector<string>& a, const vector<string>& b, size_t indice) {
    if (indice >= a.size()) return 0; // caso base
    int actual = (find(b.begin(), b.end(), a[indice]) != b.end()) ? 1 : 0;
    return actual + coincidenciasRecursivo(a, b, indice + 1);
}

// Similitud entre dos pines (0 a 100):
//   50 puntos si comparten categoria
//   30 puntos segun las palabras en comun del titulo/descripcion (recursivo)
//   20 puntos segun lo cercana que es la popularidad
float similitudRecursiva(const Pin& a, const Pin& b) {
    float puntaje = (a.getIdCategoria() == b.getIdCategoria()) ? 50.0f : 0.0f;

    vector<string> ta = tokenizar(a.getTitulo() + " " + a.getDescripcion());
    vector<string> tb = tokenizar(b.getTitulo() + " " + b.getDescripcion());
    size_t minimo = min(ta.size(), tb.size());
    if (minimo > 0) {
        int comunes = coincidenciasRecursivo(ta, tb, 0);
        puntaje += 30.0f * static_cast<float>(comunes) / static_cast<float>(minimo);
    }

    int mayorPop = max(max(a.getPopularidad(), b.getPopularidad()), 1);
    int diferencia = abs(a.getPopularidad() - b.getPopularidad());
    puntaje += 20.0f * (1.0f - static_cast<float>(diferencia) / static_cast<float>(mayorPop));

    if (puntaje > 100.0f) puntaje = 100.0f;
    if (puntaje < 0.0f) puntaje = 0.0f;
    return puntaje;
}

void menuModuloRecomendaciones() {
    int opcion = -1;

    do {
        banner("MODULO 3: RECOMENDACIONES (Persona 3)");
        cout << "1. Encolar recomendacion manual (Cola)\n";
        cout << "2. Generar recomendaciones para un usuario (similitud + HeapSort)\n";
        cout << "3. Procesar siguiente recomendacion\n";
        cout << "4. Calcular similitud entre dos pines (recursivo)\n";
        cout << "5. Ver cola y metricas (lambdas)\n";
        cout << "6. Ver cola ordenada por puntuacion (HeapSort)\n";
        cout << "7. Ver similitudes guardadas\n";
        cout << "0. Volver al menu principal\n";
        opcion = leerEntero("Opcion: ", 0, 7);

        switch (opcion) {
        case 1: {
            banner("ENCOLAR RECOMENDACION");
            int idUsuario = leerEntero("ID usuario destino: ", 1, 1000000);
            if (!existeUsuario(idUsuario)) {
                cout << "\n[Error] No existe un usuario con ese ID.\n";
                Utils::pausar();
                break;
            }
            int idPin = leerEntero("ID pin a recomendar: ", 1, 1000000);
            Pin pin;
            if (!obtenerPin(idPin, pin)) {
                cout << "\n[Error] No existe un pin con ese ID.\n";
                Utils::pausar();
                break;
            }
            bool repetida = bd.recomendaciones.existe([=](Recomendacion r) {
                return r.getIdUsuario() == idUsuario && r.getIdPin() == idPin;
            });
            if (repetida) {
                cout << "\n[Aviso] Ese pin ya esta en la cola para ese usuario.\n";
                Utils::pausar();
                break;
            }
            float puntuacion = leerFloat("Puntuacion (0.0 a 10.0): ", 0.0f, 10.0f);

            int id = siguienteId<Recomendacion>(bd.recomendaciones, [](Recomendacion r) { return r.getIdRecomendacion(); });
            bd.recomendaciones.encolar(Recomendacion(id, idUsuario, idPin, puntuacion));
            guardarRecomendaciones();
            cout << "\n[OK] Recomendacion #" << id << " encolada y guardada en recomendaciones.csv\n";
            Utils::pausar();
            break;
        }
        case 2: {
            banner("GENERAR RECOMENDACIONES");
            int idUsuario = leerEntero("ID usuario: ", 1, 1000000);
            if (!existeUsuario(idUsuario)) {
                cout << "\n[Error] No existe un usuario con ese ID.\n";
                Utils::pausar();
                break;
            }

            // Pines del usuario (en sus tableros) y pines candidatos (de otros usuarios)
            vector<Pin> propios, candidatos;
            for (size_t i = 0; i < bd.pines.size(); i++) {
                if (duenoDeTablero(bd.pines[i].getIdTablero()) == idUsuario) propios.push_back(bd.pines[i]);
                else candidatos.push_back(bd.pines[i]);
            }
            if (propios.empty()) {
                cout << "\nEl usuario no tiene pines en sus tableros; no hay base para recomendar.\n";
                Utils::pausar();
                break;
            }

            vector<Recomendacion> nuevas;
            for (size_t i = 0; i < candidatos.size(); i++) {
                int idPin = candidatos[i].getIdPin();
                bool yaEnCola = bd.recomendaciones.existe([=](Recomendacion r) {
                    return r.getIdUsuario() == idUsuario && r.getIdPin() == idPin;
                });
                if (yaEnCola) continue;

                float mejor = 0.0f;
                for (size_t j = 0; j < propios.size(); j++) {
                    mejor = max(mejor, similitudRecursiva(candidatos[i], propios[j]));
                }
                nuevas.push_back(Recomendacion(0, idUsuario, idPin, mejor / 10.0f));
            }

            if (nuevas.empty()) {
                cout << "\nNo hay pines nuevos para recomendar a este usuario.\n";
                Utils::pausar();
                break;
            }

            heapSortRecomendaciones(nuevas); // de mayor a menor puntuacion
            int limite = min(3, static_cast<int>(nuevas.size()));
            int idBase = siguienteId<Recomendacion>(bd.recomendaciones, [](Recomendacion r) { return r.getIdRecomendacion(); });

            cout << "\nSe encolaron las " << limite << " mejores recomendaciones:\n";
            for (int i = 0; i < limite; i++) {
                nuevas[i].setIdRecomendacion(idBase + i);
                bd.recomendaciones.encolar(nuevas[i]);
                nuevas[i].mostrarInfo();
            }
            guardarRecomendaciones();
            Utils::pausar();
            break;
        }
        case 3: {
            banner("PROCESAR SIGUIENTE RECOMENDACION");
            Recomendacion atendida;
            if (bd.recomendaciones.desencolar(atendida)) {
                cout << "Procesando recomendacion:\n";
                atendida.mostrarInfo();
                Pin pin;
                if (obtenerPin(atendida.getIdPin(), pin)) {
                    cout << "Pin recomendado: " << pin.getTitulo() << " - " << pin.getDescripcion() << "\n";
                }
                guardarRecomendaciones();
                cout << "\n[OK] Recomendacion procesada y retirada de la cola.\n";
            }
            else {
                cout << "No hay recomendaciones pendientes en la cola.\n";
            }
            Utils::pausar();
            break;
        }
        case 4: {
            banner("SIMILITUD ENTRE PINES (RECURSIVO)");
            if (bd.pines.size() < 2) {
                cout << "Se necesitan al menos 2 pines registrados.\n";
                Utils::pausar();
                break;
            }
            Pin a, b;
            int idA = leerEntero("ID del pin A: ", 1, 1000000);
            if (!obtenerPin(idA, a)) {
                cout << "\n[Error] No existe el pin A.\n";
                Utils::pausar();
                break;
            }
            int idB = leerEntero("ID del pin B: ", 1, 1000000);
            if (!obtenerPin(idB, b)) {
                cout << "\n[Error] No existe el pin B.\n";
                Utils::pausar();
                break;
            }
            if (idA == idB) {
                cout << "\n[Error] Elige dos pines distintos.\n";
                Utils::pausar();
                break;
            }

            float similitud = similitudRecursiva(a, b);
            cout << "\n" << a.getTitulo() << "  vs  " << b.getTitulo() << "\n";
            cout << "[Resultado] Similitud: " << floatATexto(similitud) << "%\n";

            int existente = bd.similitudes.contarSi([=](SimilitudPin s) {
                return (s.getIdPinA() == idA && s.getIdPinB() == idB) ||
                       (s.getIdPinA() == idB && s.getIdPinB() == idA);
            });
            if (existente == 0) {
                int id = siguienteId<SimilitudPin>(bd.similitudes, [](SimilitudPin s) { return s.getIdSimilitud(); });
                bd.similitudes.insertarFinal(SimilitudPin(id, idA, idB, similitud));
                guardarSimilitudes();
                cout << "[OK] Guardada en similitudes.csv\n";
            }
            else {
                cout << "(Este par ya estaba guardado en similitudes.csv)\n";
            }
            Utils::pausar();
            break;
        }
        case 5: {
            banner("COLA DE RECOMENDACIONES Y METRICAS");
            cout << "Recomendaciones en espera: " << bd.recomendaciones.getCantidad() << "\n";

            Recomendacion frente;
            if (bd.recomendaciones.verFrente(frente)) {
                cout << "Siguiente en salir: ";
                frente.mostrarInfo();
            }

            float promedio = bd.recomendaciones.promedio([](Recomendacion r) { return r.getPuntuacion(); });
            int altas = bd.recomendaciones.contarSi([](Recomendacion r) { return r.getPuntuacion() >= 8.0f; });
            bool hayExcelente = bd.recomendaciones.existe([](Recomendacion r) { return r.getPuntuacion() >= 9.5f; });

            cout << "Puntuacion promedio:        " << floatATexto(promedio) << "\n";
            cout << "Con puntuacion >= 8.0:      " << altas << "\n";
            cout << "Hay alguna >= 9.5:          " << (hayExcelente ? "Si" : "No") << "\n\n";

            if (bd.recomendaciones.esVacia()) {
                cout << "La cola esta vacia.\n";
            }
            else {
                cout << "Contenido de la cola (orden de llegada):\n";
                bd.recomendaciones.recorrer([](Recomendacion r) { r.mostrarInfo(); });
            }
            Utils::pausar();
            break;
        }
        case 6: {
            banner("COLA ORDENADA POR PUNTUACION (HEAPSORT)");
            if (bd.recomendaciones.esVacia()) {
                cout << "La cola esta vacia.\n";
            }
            else {
                vector<Recomendacion> v;
                bd.recomendaciones.recorrer([&v](Recomendacion r) { v.push_back(r); });
                heapSortRecomendaciones(v); // se ordena una copia, la cola no cambia
                cout << "[OK] De mayor a menor puntuacion (la cola original no se altera):\n\n";
                for (size_t i = 0; i < v.size(); i++) v[i].mostrarInfo();
            }
            Utils::pausar();
            break;
        }
        case 7: {
            banner("SIMILITUDES GUARDADAS");
            if (bd.similitudes.esVacia()) cout << "Aun no hay similitudes guardadas.\n";
            else bd.similitudes.recorrer([](SimilitudPin s) { s.mostrarInfo(); });
            Utils::pausar();
            break;
        }
        case 0:
            break;
        }
    } while (opcion != 0);
}

// ==========================================
// MENU PRINCIPAL
// ==========================================

void mostrarRequisitos() {
    banner("REQUISITOS DEL PROYECTO PINTEREST");
    cout << "- Lista simple: tableros, usuarios (Persona 1)\n";
    cout << "- Lista doble + iterador: categorias (Persona 2)\n";
    cout << "- Cola: recomendaciones (Persona 3)\n";
    cout << "- QuickSort (P1), MergeSort (P2), HeapSort (P3)\n";
    cout << "- Recursividad: busqueda binaria (P1), popularidad (P2), similitud (P3)\n";
    cout << "- Archivos: CSV en la carpeta data/\n";
    Utils::pausar();
}

int main() {
#ifdef _WIN32
    // Activa los codigos ANSI (limpiar pantalla) en la consola de Windows
    HANDLE salida = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo = 0;
    if (GetConsoleMode(salida, &modo)) SetConsoleMode(salida, modo | 0x0004);
#endif

    if (!archivoExiste(R_USUARIOS)) {
        cout << "[Aviso] No se encontro data/usuarios.csv.\n"
             << "        Copia la carpeta data/ junto al ejecutable (directorio de trabajo).\n\n";
    }
    cargarTodo();
    recalcularContadores(); // deja consistentes cantidadPines de tableros y categorias

    int opcion = -1;
    do {
        banner("TB1 Pinterest - AED 2026-2");
        cout << "Cargados: " << bd.usuarios.getCantidad() << " usuarios, "
             << bd.tableros.getCantidad() << " tableros, "
             << bd.categorias.getCantidad() << " categorias, "
             << bd.pines.size() << " pines, "
             << bd.recomendaciones.getCantidad() << " recomendaciones\n\n";
        cout << "1. Modulo: Usuarios y Tableros (Persona 1)\n";
        cout << "2. Modulo: Pines y Categorias (Persona 2)\n";
        cout << "3. Modulo: Recomendaciones (Persona 3)\n";
        cout << "4. Ver requisitos del sistema\n";
        cout << "0. Salir\n";
        opcion = leerEntero("Opcion: ", 0, 4);

        switch (opcion) {
        case 1: menuModuloUsuariosYTableros(); break;
        case 2: menuModuloPinesYCategorias(); break;
        case 3: menuModuloRecomendaciones(); break;
        case 4: mostrarRequisitos(); break;
        case 0:
            cout << "\nGracias por usar el sistema Pinterest.\n";
            break;
        }
    } while (opcion != 0);

    return 0;
}
