#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
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

    Libro();
    void establecerTitulo(const string& nuevoTitulo);
    void establecerAutores(const string& nuevosAutores);
    void establecerIdioma(const string& nuevoIdioma);
    void establecerGenero(const string& nuevoGenero);
};

// dividido para que lo veamos mejor
// operaciones secuenciales
vector<Libro> leerCSVSecuencial(const string& nombreArchivo);
void crearArchivoBinarioDesdeCSV(const string& nombreArchivo, const vector<Libro>& libros);

// operaciones no secuenciales
bool leerRegistroLibro(const string& nombreArchivo, int indice_libro, Libro& libro);
void actualizarRegistroLibro(const string& nombreArchivo, int indice_libro, int nueva_cantidad);
void reportarLibrosNoDisponibles(const string& nombreArchivo);

class Estudiante {
public:
    int id_estudiante;
    set<pair<int, string>> libros_prestados;

    Estudiante(int id);
    void prestarLibro(int indice_libro, const string& nombreArchivo);
    void devolverLibro(int indice_libro, const string& nombreArchivo);
    void listarLibrosPrestados() const;
    int obtenerCantidadLibrosPrestados() const;
};

// reportes de estudiantes
void reportarEstudiantesConMasLibros(const vector<Estudiante>& estudiantes);
void reportarEstudiantesSinLibros(const vector<Estudiante>& estudiantes);
void reportarEstudiantesYLibrosPrestados(const vector<Estudiante>& estudiantes);

#endif
