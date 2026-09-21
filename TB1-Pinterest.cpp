#include <iostream>
#include <limits>
#include <string>

using namespace std;

void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mostrarEncabezado() {
    cout << "========================================\n";
    cout << "   TB1 Pinterest - AED 2026-2\n";
    cout << "========================================\n";
}

void mostrarMenu() {
    cout << "\nMenu principal\n";
    cout << "1. Usuarios y tableros\n";
    cout << "2. Pines y categorias\n";
    cout << "3. Recomendaciones\n";
    cout << "4. Ver requisitos del proyecto\n";
    cout << "0. Salir\n";
    cout << "Opcion: ";
}

void mostrarRequisitos() {
    cout << "\nRequisitos base para el grupo Pinterest:\n";
    cout << "- Lista simple: tableros.\n";
    cout << "- Lista doble: categorias.\n";
    cout << "- Cola: recomendaciones.\n";
    cout << "- MergeSort: ordenar por popularidad.\n";
    cout << "- Recursividad: similitud entre pines.\n";
    cout << "- Archivos: colecciones y datos del sistema.\n";
}

void moduloPendiente(const string& nombreModulo) {
    cout << "\n[Pendiente] Modulo: " << nombreModulo << "\n";
    cout << "Cada integrante puede implementar aqui sus entidades, estructuras y metodos.\n";
}

int main() {
    int opcion = -1;

    mostrarEncabezado();

    do {
        mostrarMenu();

        if (!(cin >> opcion)) {
            limpiarEntrada();
            cout << "Ingresa una opcion valida.\n";
            continue;
        }

        switch (opcion) {
        case 1:
            moduloPendiente("Usuarios y tableros");
            break;
        case 2:
            moduloPendiente("Pines y categorias");
            break;
        case 3:
            moduloPendiente("Recomendaciones");
            break;
        case 4:
            mostrarRequisitos();
            break;
        case 0:
            cout << "\nSaliendo del sistema.\n";
            break;
        default:
            cout << "Opcion no reconocida.\n";
            break;
        }
    } while (opcion != 0);

    return 0;
}
