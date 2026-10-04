#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// ============================================================
// Utilidades para guardar entidades en CSV
// ============================================================

// Reemplaza las comas (separador del CSV) y los saltos de linea del texto
inline string limpiarCampo(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == ',') s[i] = ';';
        else if (s[i] == '\r' || s[i] == '\n') s[i] = ' ';
    }
    return s;
}

// Convierte un float a texto con 1 decimal (9.2 en vez de 9.200000)
inline string floatATexto(float v) {
    ostringstream o;
    o << fixed << setprecision(1) << v;
    return o.str();
}

// ############################################################
// PERSONA 1: Usuarios y tableros
// Entidades: Usuario, Tablero, Perfil, Seguidor, Notificacion
// ############################################################

// ==========================================
// 1. ENTIDAD: Usuario
// CSV: idUsuario,nombre,username,correo,fechaRegistro
// ==========================================
class Usuario {
private:
    int idUsuario;
    string nombre;
    string username;
    string correo;
    string fechaRegistro;

public:
    Usuario() {
        idUsuario = 0;
        nombre = "";
        username = "";
        correo = "";
        fechaRegistro = "";
    }

    Usuario(int id, string nom, string user, string mail, string fecha) {
        idUsuario = id;
        nombre = nom;
        username = user;
        correo = mail;
        fechaRegistro = fecha;
    }

    int getIdUsuario() const { return idUsuario; }
    string getNombre() const { return nombre; }
    string getUsername() const { return username; }
    string getCorreo() const { return correo; }
    string getFechaRegistro() const { return fechaRegistro; }

    void setIdUsuario(int id) { idUsuario = id; }
    void setNombre(string nom) { nombre = nom; }
    void setUsername(string user) { username = user; }
    void setCorreo(string mail) { correo = mail; }
    void setFechaRegistro(string fecha) { fechaRegistro = fecha; }

    string toCSV() const {
        return to_string(idUsuario) + "," + limpiarCampo(nombre) + "," +
            limpiarCampo(username) + "," + limpiarCampo(correo) + "," +
            limpiarCampo(fechaRegistro);
    }

    void mostrarInfo() const {
        cout << "[Usuario #" << idUsuario << "] " << nombre
             << " (@" << username << ") | " << correo
             << " | Registro: " << fechaRegistro << "\n";
    }
};


// ==========================================
// 2. ENTIDAD: Tablero
// CSV: idTablero,nombre,idUsuario,descripcion,esPublico,cantidadPines,fechaCreacion
// ==========================================
class Tablero {
private:
    int idTablero;
    string nombre;
    int idUsuario;
    string descripcion;
    bool esPublico;
    int cantidadPines;
    string fechaCreacion;

public:
    Tablero() {
        idTablero = 0;
        nombre = "";
        idUsuario = 0;
        descripcion = "";
        esPublico = true;
        cantidadPines = 0;
        fechaCreacion = "";
    }

    Tablero(int id, string nom, int idUser, string desc, bool publico, int cantidad, string fecha) {
        idTablero = id;
        nombre = nom;
        idUsuario = idUser;
        descripcion = desc;
        esPublico = publico;
        cantidadPines = cantidad;
        fechaCreacion = fecha;
    }

    int getIdTablero() const { return idTablero; }
    string getNombre() const { return nombre; }
    int getIdUsuario() const { return idUsuario; }
    string getDescripcion() const { return descripcion; }
    bool getEsPublico() const { return esPublico; }
    bool getEsPrivado() const { return !esPublico; }
    int getCantidadPines() const { return cantidadPines; }
    string getFechaCreacion() const { return fechaCreacion; }

    void setIdTablero(int id) { idTablero = id; }
    void setNombre(string nom) { nombre = nom; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setDescripcion(string desc) { descripcion = desc; }
    void setEsPublico(bool publico) { esPublico = publico; }
    void setCantidadPines(int cantidad) { cantidadPines = cantidad; }
    void setFechaCreacion(string fecha) { fechaCreacion = fecha; }

    string toCSV() const {
        return to_string(idTablero) + "," + limpiarCampo(nombre) + "," +
            to_string(idUsuario) + "," + limpiarCampo(descripcion) + "," +
            string(esPublico ? "1" : "0") + "," + to_string(cantidadPines) + "," +
            limpiarCampo(fechaCreacion);
    }

    void mostrarInfo() const {
        cout << "[Tablero #" << idTablero << "] " << nombre
             << " | Usuario: " << idUsuario
             << " | " << (esPublico ? "Publico" : "Privado")
             << " | Pines: " << cantidadPines << "\n"
             << "      " << descripcion << " (creado " << fechaCreacion << ")\n";
    }
};


// ==========================================
// 3. ENTIDAD: Perfil
// CSV: idPerfil,idUsuario,biografia,fotoPerfil,cantidadSeguidores
// ==========================================
class Perfil {
private:
    int idPerfil;
    int idUsuario;
    string biografia;
    string fotoPerfil;
    int cantidadSeguidores;

public:
    Perfil() {
        idPerfil = 0;
        idUsuario = 0;
        biografia = "";
        fotoPerfil = "";
        cantidadSeguidores = 0;
    }

    Perfil(int id, int idUser, string bio, string foto, int seguidores) {
        idPerfil = id;
        idUsuario = idUser;
        biografia = bio;
        fotoPerfil = foto;
        cantidadSeguidores = seguidores;
    }

    int getIdPerfil() const { return idPerfil; }
    int getIdUsuario() const { return idUsuario; }
    string getBiografia() const { return biografia; }
    string getFotoPerfil() const { return fotoPerfil; }
    int getCantidadSeguidores() const { return cantidadSeguidores; }

    void setIdPerfil(int id) { idPerfil = id; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setBiografia(string bio) { biografia = bio; }
    void setFotoPerfil(string foto) { fotoPerfil = foto; }
    void setCantidadSeguidores(int seguidores) { cantidadSeguidores = seguidores; }

    string toCSV() const {
        return to_string(idPerfil) + "," + to_string(idUsuario) + "," +
            limpiarCampo(biografia) + "," + limpiarCampo(fotoPerfil) + "," +
            to_string(cantidadSeguidores);
    }

    void mostrarInfo() const {
        cout << "[Perfil #" << idPerfil << "] Usuario: " << idUsuario
             << " | Bio: " << biografia
             << " | Foto: " << fotoPerfil
             << " | Seguidores: " << cantidadSeguidores << "\n";
    }
};


// ==========================================
// 4. ENTIDAD: Seguidor
// CSV: idSeguidor,idUsuarioQueSigue,idUsuarioSeguido,fechaInicio
// ==========================================
class Seguidor {
private:
    int idSeguidor;
    int idUsuarioQueSigue;
    int idUsuarioSeguido;
    string fechaInicio;

public:
    Seguidor() {
        idSeguidor = 0;
        idUsuarioQueSigue = 0;
        idUsuarioSeguido = 0;
        fechaInicio = "";
    }

    Seguidor(int id, int quienSigue, int seguido, string fecha) {
        idSeguidor = id;
        idUsuarioQueSigue = quienSigue;
        idUsuarioSeguido = seguido;
        fechaInicio = fecha;
    }

    int getIdSeguidor() const { return idSeguidor; }
    int getIdUsuarioQueSigue() const { return idUsuarioQueSigue; }
    int getIdUsuarioSeguido() const { return idUsuarioSeguido; }
    string getFechaInicio() const { return fechaInicio; }

    void setIdSeguidor(int id) { idSeguidor = id; }
    void setIdUsuarioQueSigue(int quienSigue) { idUsuarioQueSigue = quienSigue; }
    void setIdUsuarioSeguido(int seguido) { idUsuarioSeguido = seguido; }
    void setFechaInicio(string fecha) { fechaInicio = fecha; }

    string toCSV() const {
        return to_string(idSeguidor) + "," + to_string(idUsuarioQueSigue) + "," +
            to_string(idUsuarioSeguido) + "," + limpiarCampo(fechaInicio);
    }

    void mostrarInfo() const {
        cout << "[Seguidor #" << idSeguidor << "] Usuario " << idUsuarioQueSigue
             << " sigue a " << idUsuarioSeguido << " desde " << fechaInicio << "\n";
    }
};


// ==========================================
// 5. ENTIDAD: Notificacion
// CSV: idNotificacion,idUsuario,mensaje,leida,fecha
// ==========================================
class Notificacion {
private:
    int idNotificacion;
    int idUsuario;
    string mensaje;
    bool leida;
    string fecha;

public:
    Notificacion() {
        idNotificacion = 0;
        idUsuario = 0;
        mensaje = "";
        leida = false;
        fecha = "";
    }

    Notificacion(int id, int idUser, string msg, bool vista, string fec) {
        idNotificacion = id;
        idUsuario = idUser;
        mensaje = msg;
        leida = vista;
        fecha = fec;
    }

    int getIdNotificacion() const { return idNotificacion; }
    int getIdUsuario() const { return idUsuario; }
    string getMensaje() const { return mensaje; }
    bool getLeida() const { return leida; }
    string getFecha() const { return fecha; }

    void setIdNotificacion(int id) { idNotificacion = id; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setMensaje(string msg) { mensaje = msg; }
    void setLeida(bool vista) { leida = vista; }
    void setFecha(string fec) { fecha = fec; }

    string toCSV() const {
        return to_string(idNotificacion) + "," + to_string(idUsuario) + "," +
            limpiarCampo(mensaje) + "," + string(leida ? "1" : "0") + "," +
            limpiarCampo(fecha);
    }

    void mostrarInfo() const {
        cout << (leida ? "  [leida] " : "  [NUEVA] ") << "#" << idNotificacion
             << " " << mensaje << " (" << fecha << ")\n";
    }
};


// ############################################################
// PERSONA 2: Pines y categorias
// Entidades: Pin, Categoria, Etiqueta, Comentario, Interaccion
// ############################################################

// ==========================================
// 6. ENTIDAD: Pin
// CSV: idPin,titulo,descripcion,idTablero,idCategoria,popularidad,fechaCreacion
// ==========================================
class Pin {
private:
    int idPin;
    string titulo;
    string descripcion;
    int idTablero;
    int idCategoria;
    int popularidad;
    string fechaCreacion;

public:
    Pin() {
        idPin = 0;
        titulo = "";
        descripcion = "";
        idTablero = 0;
        idCategoria = 0;
        popularidad = 0;
        fechaCreacion = "";
    }

    Pin(int id, string tit, string desc, int idTab, int idCat, int pop, string fecha) {
        idPin = id;
        titulo = tit;
        descripcion = desc;
        idTablero = idTab;
        idCategoria = idCat;
        popularidad = pop;
        fechaCreacion = fecha;
    }

    int getIdPin() const { return idPin; }
    string getTitulo() const { return titulo; }
    string getDescripcion() const { return descripcion; }
    int getIdTablero() const { return idTablero; }
    int getIdCategoria() const { return idCategoria; }
    int getPopularidad() const { return popularidad; }
    string getFechaCreacion() const { return fechaCreacion; }

    void setIdPin(int id) { idPin = id; }
    void setTitulo(string tit) { titulo = tit; }
    void setDescripcion(string desc) { descripcion = desc; }
    void setIdTablero(int idTab) { idTablero = idTab; }
    void setIdCategoria(int idCat) { idCategoria = idCat; }
    void setPopularidad(int pop) { popularidad = pop; }
    void setFechaCreacion(string fecha) { fechaCreacion = fecha; }

    string toCSV() const {
        return to_string(idPin) + "," + limpiarCampo(titulo) + "," +
            limpiarCampo(descripcion) + "," + to_string(idTablero) + "," +
            to_string(idCategoria) + "," + to_string(popularidad) + "," +
            limpiarCampo(fechaCreacion);
    }

    void mostrarInfo() const {
        cout << "[Pin #" << idPin << "] " << titulo
             << " | Popularidad: " << popularidad
             << " | Tablero: " << idTablero
             << " | Categoria: " << idCategoria << "\n";
    }
};

// ==========================================
// 7. ENTIDAD: Categoria
// CSV: idCategoria,nombre,descripcion,cantidadPines
// ==========================================
class Categoria {
private:
    int idCategoria;
    string nombre;
    string descripcion;
    int cantidadPines;

public:
    Categoria() {
        idCategoria = 0;
        nombre = "";
        descripcion = "";
        cantidadPines = 0;
    }

    Categoria(int id, string nom, string desc, int cantidad) {
        idCategoria = id;
        nombre = nom;
        descripcion = desc;
        cantidadPines = cantidad;
    }

    int getIdCategoria() const { return idCategoria; }
    string getNombre() const { return nombre; }
    string getDescripcion() const { return descripcion; }
    int getCantidadPines() const { return cantidadPines; }

    void setIdCategoria(int id) { idCategoria = id; }
    void setNombre(string nom) { nombre = nom; }
    void setDescripcion(string desc) { descripcion = desc; }
    void setCantidadPines(int cantidad) { cantidadPines = cantidad; }

    string toCSV() const {
        return to_string(idCategoria) + "," + limpiarCampo(nombre) + "," +
            limpiarCampo(descripcion) + "," + to_string(cantidadPines);
    }

    void mostrarInfo() const {
        cout << "[Categoria #" << idCategoria << "] "
             << nombre << " - " << descripcion
             << " | Pines: " << cantidadPines << "\n";
    }
};

// ==========================================
// 8. ENTIDAD: Etiqueta
// ==========================================
class Etiqueta {
private:
    int idEtiqueta;
    string nombre;
    int idPin;

public:
    Etiqueta() {
        idEtiqueta = 0;
        nombre = "";
        idPin = 0;
    }

    Etiqueta(int id, string nom, int idP) {
        idEtiqueta = id;
        nombre = nom;
        idPin = idP;
    }

    int getIdEtiqueta() const { return idEtiqueta; }
    string getNombre() const { return nombre; }
    int getIdPin() const { return idPin; }

    void setIdEtiqueta(int id) { idEtiqueta = id; }
    void setNombre(string nom) { nombre = nom; }
    void setIdPin(int idP) { idPin = idP; }

    string toCSV() const {
        return to_string(idEtiqueta) + "," + limpiarCampo(nombre) + "," + to_string(idPin);
    }

    void mostrarInfo() const {
        cout << "[Etiqueta #" << idEtiqueta << "] " << nombre
             << " | Pin ID: " << idPin << "\n";
    }
};

// ==========================================
// 9. ENTIDAD: Comentario
// ==========================================
class Comentario {
private:
    int idComentario;
    int idPin;
    int idUsuario;
    string texto;
    string fecha;

public:
    Comentario() {
        idComentario = 0;
        idPin = 0;
        idUsuario = 0;
        texto = "";
        fecha = "";
    }

    Comentario(int id, int idP, int idUser, string txt, string fec) {
        idComentario = id;
        idPin = idP;
        idUsuario = idUser;
        texto = txt;
        fecha = fec;
    }

    int getIdComentario() const { return idComentario; }
    int getIdPin() const { return idPin; }
    int getIdUsuario() const { return idUsuario; }
    string getTexto() const { return texto; }
    string getFecha() const { return fecha; }

    void setIdComentario(int id) { idComentario = id; }
    void setIdPin(int idP) { idPin = idP; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setTexto(string txt) { texto = txt; }
    void setFecha(string fec) { fecha = fec; }

    string toCSV() const {
        return to_string(idComentario) + "," + to_string(idPin) + "," +
            to_string(idUsuario) + "," + limpiarCampo(texto) + "," + limpiarCampo(fecha);
    }

    void mostrarInfo() const {
        cout << "[Comentario #" << idComentario << "] "
             << "Pin: " << idPin << " | Usuario: " << idUsuario
             << " | " << texto << " (" << fecha << ")\n";
    }
};

// ==========================================
// 10. ENTIDAD: Interaccion
// ==========================================
class Interaccion {
private:
    int idInteraccion;
    int idPin;
    int idUsuario;
    string tipo;
    string fecha;

public:
    Interaccion() {
        idInteraccion = 0;
        idPin = 0;
        idUsuario = 0;
        tipo = "";
        fecha = "";
    }

    Interaccion(int id, int idP, int idUser, string tip, string fec) {
        idInteraccion = id;
        idPin = idP;
        idUsuario = idUser;
        tipo = tip;
        fecha = fec;
    }

    int getIdInteraccion() const { return idInteraccion; }
    int getIdPin() const { return idPin; }
    int getIdUsuario() const { return idUsuario; }
    string getTipo() const { return tipo; }
    string getFecha() const { return fecha; }

    void setIdInteraccion(int id) { idInteraccion = id; }
    void setIdPin(int idP) { idPin = idP; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setTipo(string tip) { tipo = tip; }
    void setFecha(string fec) { fecha = fec; }

    string toCSV() const {
        return to_string(idInteraccion) + "," + to_string(idPin) + "," +
            to_string(idUsuario) + "," + limpiarCampo(tipo) + "," + limpiarCampo(fecha);
    }

    void mostrarInfo() const {
        cout << "[Interaccion #" << idInteraccion << "] "
             << "Pin: " << idPin << " | Usuario: " << idUsuario
             << " | Tipo: " << tipo << " | Fecha: " << fecha << "\n";
    }
};


// ############################################################
// PERSONA 3: Recomendaciones
// Entidades: Recomendacion, SimilitudPin, HistorialBusqueda,
//            PreferenciaUsuario, TendenciaDiaria
// ############################################################

// ==========================================
// 11. ENTIDAD: Recomendacion
// CSV: idRecomendacion,idUsuario,idPin,puntuacion
// ==========================================
class Recomendacion {
private:
    int idRecomendacion;
    int idUsuario;
    int idPin;
    float puntuacion;

public:
    Recomendacion() {
        idRecomendacion = 0;
        idUsuario = 0;
        idPin = 0;
        puntuacion = 0.0f;
    }

    Recomendacion(int id, int idUser, int idP, float punt) {
        idRecomendacion = id;
        idUsuario = idUser;
        idPin = idP;
        puntuacion = punt;
    }

    int getIdRecomendacion() const { return idRecomendacion; }
    int getIdUsuario() const { return idUsuario; }
    int getIdPin() const { return idPin; }
    float getPuntuacion() const { return puntuacion; }

    void setIdRecomendacion(int id) { idRecomendacion = id; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setIdPin(int idP) { idPin = idP; }
    void setPuntuacion(float punt) { puntuacion = punt; }

    string toCSV() const {
        return to_string(idRecomendacion) + "," + to_string(idUsuario) + "," +
            to_string(idPin) + "," + floatATexto(puntuacion);
    }

    void mostrarInfo() const {
        cout << "[Recomendacion #" << idRecomendacion << "] "
             << "Usuario: " << idUsuario
             << " | Pin: " << idPin
             << " | Score: " << floatATexto(puntuacion) << "\n";
    }
};

// ==========================================
// 12. ENTIDAD: SimilitudPin
// CSV: idSimilitud,idPinA,idPinB,porcentajeSimilitud
// ==========================================
class SimilitudPin {
private:
    int idSimilitud;
    int idPinA;
    int idPinB;
    float porcentajeSimilitud;

public:
    SimilitudPin() {
        idSimilitud = 0;
        idPinA = 0;
        idPinB = 0;
        porcentajeSimilitud = 0.0f;
    }

    SimilitudPin(int id, int pinA, int pinB, float porcentaje) {
        idSimilitud = id;
        idPinA = pinA;
        idPinB = pinB;
        porcentajeSimilitud = porcentaje;
    }

    int getIdSimilitud() const { return idSimilitud; }
    int getIdPinA() const { return idPinA; }
    int getIdPinB() const { return idPinB; }
    float getPorcentajeSimilitud() const { return porcentajeSimilitud; }

    void setIdSimilitud(int id) { idSimilitud = id; }
    void setIdPinA(int pinA) { idPinA = pinA; }
    void setIdPinB(int pinB) { idPinB = pinB; }
    void setPorcentajeSimilitud(float porcentaje) { porcentajeSimilitud = porcentaje; }

    string toCSV() const {
        return to_string(idSimilitud) + "," + to_string(idPinA) + "," +
            to_string(idPinB) + "," + floatATexto(porcentajeSimilitud);
    }

    void mostrarInfo() const {
        cout << "[Similitud #" << idSimilitud << "] "
             << "Pin A: " << idPinA << " | Pin B: " << idPinB
             << " | Similitud: " << floatATexto(porcentajeSimilitud) << "%\n";
    }
};

// ==========================================
// 13. ENTIDAD: HistorialBusqueda
// ==========================================
class HistorialBusqueda {
private:
    int idHistorial;
    int idUsuario;
    string terminoBuscado;
    string fecha;

public:
    HistorialBusqueda() {
        idHistorial = 0;
        idUsuario = 0;
        terminoBuscado = "";
        fecha = "";
    }

    HistorialBusqueda(int id, int idUser, string termino, string fec) {
        idHistorial = id;
        idUsuario = idUser;
        terminoBuscado = termino;
        fecha = fec;
    }

    int getIdHistorial() const { return idHistorial; }
    int getIdUsuario() const { return idUsuario; }
    string getTerminoBuscado() const { return terminoBuscado; }
    string getFecha() const { return fecha; }

    void setIdHistorial(int id) { idHistorial = id; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setTerminoBuscado(string termino) { terminoBuscado = termino; }
    void setFecha(string fec) { fecha = fec; }

    string toCSV() const {
        return to_string(idHistorial) + "," + to_string(idUsuario) + "," +
            limpiarCampo(terminoBuscado) + "," + limpiarCampo(fecha);
    }

    void mostrarInfo() const {
        cout << "[Historial #" << idHistorial << "] "
             << "Usuario: " << idUsuario
             << " | Busqueda: " << terminoBuscado
             << " | Fecha: " << fecha << "\n";
    }
};

// ==========================================
// 14. ENTIDAD: PreferenciaUsuario
// ==========================================
class PreferenciaUsuario {
private:
    int idPreferencia;
    int idUsuario;
    int idCategoria;
    int nivelInteres;

public:
    PreferenciaUsuario() {
        idPreferencia = 0;
        idUsuario = 0;
        idCategoria = 0;
        nivelInteres = 0;
    }

    PreferenciaUsuario(int id, int idUser, int idCat, int nivel) {
        idPreferencia = id;
        idUsuario = idUser;
        idCategoria = idCat;
        nivelInteres = nivel;
    }

    int getIdPreferencia() const { return idPreferencia; }
    int getIdUsuario() const { return idUsuario; }
    int getIdCategoria() const { return idCategoria; }
    int getNivelInteres() const { return nivelInteres; }

    void setIdPreferencia(int id) { idPreferencia = id; }
    void setIdUsuario(int idUser) { idUsuario = idUser; }
    void setIdCategoria(int idCat) { idCategoria = idCat; }
    void setNivelInteres(int nivel) { nivelInteres = nivel; }

    string toCSV() const {
        return to_string(idPreferencia) + "," + to_string(idUsuario) + "," +
            to_string(idCategoria) + "," + to_string(nivelInteres);
    }

    void mostrarInfo() const {
        cout << "[Preferencia #" << idPreferencia << "] "
             << "Usuario: " << idUsuario
             << " | Categoria: " << idCategoria
             << " | Interes: " << nivelInteres << "/10\n";
    }
};

// ==========================================
// 15. ENTIDAD: TendenciaDiaria
// ==========================================
class TendenciaDiaria {
private:
    int idTendencia;
    int idCategoria;
    int totalInteracciones;
    string fecha;

public:
    TendenciaDiaria() {
        idTendencia = 0;
        idCategoria = 0;
        totalInteracciones = 0;
        fecha = "";
    }

    TendenciaDiaria(int id, int idCat, int total, string fec) {
        idTendencia = id;
        idCategoria = idCat;
        totalInteracciones = total;
        fecha = fec;
    }

    int getIdTendencia() const { return idTendencia; }
    int getIdCategoria() const { return idCategoria; }
    int getTotalInteracciones() const { return totalInteracciones; }
    string getFecha() const { return fecha; }

    void setIdTendencia(int id) { idTendencia = id; }
    void setIdCategoria(int idCat) { idCategoria = idCat; }
    void setTotalInteracciones(int total) { totalInteracciones = total; }
    void setFecha(string fec) { fecha = fec; }

    string toCSV() const {
        return to_string(idTendencia) + "," + to_string(idCategoria) + "," +
            to_string(totalInteracciones) + "," + limpiarCampo(fecha);
    }

    void mostrarInfo() const {
        cout << "[Tendencia #" << idTendencia << "] "
             << "Categoria: " << idCategoria
             << " | Interacciones: " << totalInteracciones
             << " | Fecha: " << fecha << "\n";
    }
};
