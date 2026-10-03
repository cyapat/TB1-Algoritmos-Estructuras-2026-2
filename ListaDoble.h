#pragma once

#include <functional>
#include "Nodo.h"

using namespace std;

template <typename T>
class ListaDoble {
private:
    NodoDoble<T>* cabeza;
    NodoDoble<T>* cola;
    int cantidad;

public:

    class Iterador {
    private:
        NodoDoble<T>* actual;

    public:
        Iterador(NodoDoble<T>* nodo) {
            actual = nodo;
        }

        bool esValido() const {
            return actual != nullptr;
        }

        T getDato() {
            return actual->getDato();
        }

        void avanzar() {
            if (actual != nullptr) {
                actual = actual->getSiguiente();
            }
        }

        void retroceder() {
            if (actual != nullptr) {
                actual = actual->getAnterior();
            }
        }
    };


    ListaDoble() {
        cabeza = nullptr;
        cola = nullptr;
        cantidad = 0;
    }

    ~ListaDoble() {
        limpiar();
    }


    int getCantidad() const {
        return cantidad;
    }

    bool esVacia() const {
        return cabeza == nullptr;
    }


    void insertarInicio(T dato) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(dato);

        if (esVacia()) {
            cabeza = nuevo;
            cola = nuevo;
        }
        else {
            nuevo->setSiguiente(cabeza);
            cabeza->setAnterior(nuevo);
            cabeza = nuevo;
        }

        cantidad++;
    }


    void insertarFinal(T dato) {
        NodoDoble<T>* nuevo = new NodoDoble<T>(dato);

        if (esVacia()) {
            cabeza = nuevo;
            cola = nuevo;
        }
        else {
            cola->setSiguiente(nuevo);
            nuevo->setAnterior(cola);
            cola = nuevo;
        }

        cantidad++;
    }


    void recorrer(function<void(T)> accion) const {
        NodoDoble<T>* aux = cabeza;

        while (aux != nullptr) {
            accion(aux->getDato());
            aux = aux->getSiguiente();
        }
    }


    void recorrerInverso(function<void(T)> accion) const {
        NodoDoble<T>* aux = cola;

        while (aux != nullptr) {
            accion(aux->getDato());
            aux = aux->getAnterior();
        }
    }


    bool buscar(function<bool(T)> criterio, T& resultado) const {
        NodoDoble<T>* aux = cabeza;

        while (aux != nullptr) {
            if (criterio(aux->getDato())) {
                resultado = aux->getDato();
                return true;
            }

            aux = aux->getSiguiente();
        }

        return false;
    }


    void filtrar(function<bool(T)> criterio,
        function<void(T)> accion) const {

        NodoDoble<T>* aux = cabeza;

        while (aux != nullptr) {
            T dato = aux->getDato();

            if (criterio(dato)) {
                accion(dato);
            }

            aux = aux->getSiguiente();
        }
    }


    Iterador obtenerIteradorInicio() {
        return Iterador(cabeza);
    }

    Iterador obtenerIteradorFinal() {
        return Iterador(cola);
    }


    void limpiar() {
        while (cabeza != nullptr) {
            NodoDoble<T>* aux = cabeza;
            cabeza = cabeza->getSiguiente();

            delete aux;
        }

        cola = nullptr;
        cantidad = 0;
    }
};