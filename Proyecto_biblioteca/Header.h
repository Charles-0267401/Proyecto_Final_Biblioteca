#ifndef HEADER_H
#define HEADER_H


// predeterminada cout
#include <iostream>
// operaciones con archivos
#include <fstream>
// manipular cadenas de texto
#include <string>
// para usar memset
#include <cstring>
//  leer datos en cadenas de textos y modificarlos
#include <sstream>
// manejar vectores (contenedores)
#include <vector>
// usar sets
#include <set>

using namespace std;

class Fecha {
public:
    int año, mes, dia;
    Fecha(int a = 0, int m = 0, int d = 0) : año(a), mes(m), dia(d) {}
};

class Libro {
public:
    int indice;
    char titulo[150];
    char autores[150];
    char idioma[50];
    Fecha fecha_publicacion;
    float ventas;
    char genero[50];
    int cantidad_disponible;

    // Constructor de la clase
    Libro();
    // agrega los parametros que queremos
    void establecerTitulo(const string& nuevoTitulo);
    void establecerAutores(const string& nuevosAutores);
    void establecerIdioma(const string& nuevoIdioma);
    void establecerGenero(const string& nuevoGenero);
};

// dividido para que lo veamos mejor
// operaciones secuenciales
vector<Libro> leerCSVSecuencial(const string& nombreArchivo); // apunta al CSV
void crearArchivoBinarioDesdeCSV(const string& nombreArchivo, const vector<Libro>& libros); // nombre del bin y agrega los libros (vector) al binario

// operaciones no secuenciales
bool leerRegistroLibro(const string& nombreArchivo, int indice_libro, Libro& libro); // archivo binario, accede al indice por medio de la dirección del objeto Libro
void actualizarRegistroLibro(const string& nombreArchivo, int indice_libro, int nueva_cantidad); // archivo binario, indice del libro y agrega o quita libros de la db
void reportarLibrosNoDisponibles(const string& nombreArchivo); // *****

class Estudiante {
public:
    int id_estudiante; // solo tiene id del 1-10
    set<pair<int, string>> libros_prestados; // tiene los pares de datos para rastrear los libros prestados por el estudiante.

    Estudiante(int id); // se crea con id
    void prestarLibro(int indice_libro, const string& nombreArchivo); // indice y archivo bin
    void devolverLibro(int indice_libro, const string& nombreArchivo); // indice y archivo bin
    void listarLibrosPrestados() const; //getter
    int obtenerCantidadLibrosPrestados() const; //getter
};

// reportes de estudiantes
void reportarEstudiantesConMasLibros(const vector<Estudiante>& estudiantes);
void reportarEstudiantesSinLibros(const vector<Estudiante>& estudiantes);
void reportarEstudiantesYLibrosPrestados(const vector<Estudiante>& estudiantes);

#endif
