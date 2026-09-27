#include <iostream>
#include <string>

// Cabeceras base de infraestructura del grupo
#include "Entidades.h"
#include "Nodo.h"
#include "GestorArchivos.h"
#include "Utils.h"

using namespace std;

// ==========================================
// SECCIÓN DE MÓDULOS POR INTEGRANTE
// ==========================================

// Integrante 1: Usuarios y Tableros
void menuModuloUsuariosYTableros() {
    int opcion = -1;
    do {
        Utils::limpiarPantalla();
        cout << "========================================\n";
        cout << "   MODULO 1: USUARIOS Y TABLEROS\n";
        cout << "========================================\n";
        cout << "1. Registrar usuario\n";
        cout << "2. Crear nuevo tablero (Lista Simple)\n";
        cout << "3. Listar tableros de un usuario\n";
        cout << "4. Cargar / Guardar datos desde CSV\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";

        if (!(cin >> opcion)) {
            Utils::limpiarEntrada();
            continue;
        }

        switch (opcion) {
        case 1:
            cout << "\n[En desarrollo por Integrante 1]\n";
            Utils::pausar();
            break;
        case 2:
            cout << "\n[En desarrollo por Integrante 1]\n";
            Utils::pausar();
            break;
        case 3:
            cout << "\n[En desarrollo por Integrante 1]\n";
            Utils::pausar();
            break;
        case 4:
            cout << "\n[En desarrollo por Integrante 1]\n";
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
