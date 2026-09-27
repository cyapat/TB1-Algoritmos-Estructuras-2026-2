
#ifndef NODO_H
#define NODO_H

// Nodo para Lista Simple (Integrante 1) y Cola (Integrante 3)
template <typename T>
class NodoSimple {
private:
    T dato;
    NodoSimple<T>* siguiente;

public:
    NodoSimple() {
        siguiente = nullptr;
    }

    NodoSimple(T d) {
        dato = d;
        siguiente = nullptr;
    }

    ~NodoSimple() {}

    T getDato() { return dato; }
    void setDato(T d) { dato = d; }

    NodoSimple<T>* getSiguiente() { return siguiente; }
    void setSiguiente(NodoSimple<T>* sig) { siguiente = sig; }
};

// Nodo para Lista Doble (Integrante 2)
template <typename T>
class NodoDoble {
private:
    T dato;
    NodoDoble<T>* siguiente;
    NodoDoble<T>* anterior;

public:
    NodoDoble() {
        siguiente = nullptr;
        anterior = nullptr;
    }

    NodoDoble(T d) {
        dato = d;
        siguiente = nullptr;
        anterior = nullptr;
    }

    ~NodoDoble() {}

    T getDato() { return dato; }
    void setDato(T d) { dato = d; }

    NodoDoble<T>* getSiguiente() { return siguiente; }
    void setSiguiente(NodoDoble<T>* sig) { siguiente = sig; }

    NodoDoble<T>* getAnterior() { return anterior; }
    void setAnterior(NodoDoble<T>* ant) { anterior = ant; }
};

#endif // NODO_H