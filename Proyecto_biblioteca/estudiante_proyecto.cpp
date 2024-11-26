#include "Header.h"

Estudiante::Estudiante(int id) : id_estudiante(id) {}

void Estudiante::prestarLibro(int indice_libro, const string& nombreArchivo) {
    for (const auto& libro : libros_prestados) {
        if (libro.first == indice_libro) {
            cout << "\nEl libro con el indice " << indice_libro << " ya fue prestado al estudiante " << id_estudiante << "." << endl;
            return;
        }
    }

    Libro libro;
    if (leerRegistroLibro(nombreArchivo, indice_libro, libro) && libro.cantidad_disponible > 0) {
        libros_prestados.insert({ indice_libro, libro.titulo });
        actualizarRegistroLibro(nombreArchivo, indice_libro, libro.cantidad_disponible - 1);
        cout << "\nEl libro '" << libro.titulo << "' ha sido prestado con exito." << endl;
    }
    else {
        cout << "\nEl libro con indice " << indice_libro << " no esta disponible para su prestamo." << endl;
    }
}


// Args: el indice del libro y el nombre del bin
void Estudiante::devolverLibro(int indice_libro, const string& nombreArchivo) {
    
    // Usamos un iterador "it" para recorrer el contenedor libros_prestados (un set de pares que tiene a indice y titulo)
    auto it = libros_prestados.begin();
    bool encontrado = false;


    //Va por cada uno de los elementos del contenedor libros_prestados utilizando el iterador it
    for (; it != libros_prestados.end(); ++it) {
        
        if (it->first == indice_libro) {
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        libros_prestados.erase(it);

        Libro libro;
        
        if (leerRegistroLibro(nombreArchivo, indice_libro, libro)) {
            
            actualizarRegistroLibro(nombreArchivo, indice_libro, libro.cantidad_disponible + 1);
            cout << "\nEl libro con indice " << indice_libro << " ha sido devuelto con exito." << endl;
        }
    }

    else {
        cout << "\nEl libro con indice " << indice_libro << " no ha sido prestado al estudiante " << id_estudiante << "." << endl;
    }
}

void Estudiante::listarLibrosPrestados() const {
    
    if (libros_prestados.empty()) {
        cout << "\nEl estudiante " << id_estudiante << " no tiene libros prestados." << endl;
    }
    else {
        cout << "\nEl estudiante " << id_estudiante << " tiene los siguientes libros prestados:" << endl;
        
        for (const auto& libro : libros_prestados) {
            cout << " - " << libro.second << " (indice: " << libro.first << ")" << endl;
        }
    }
}

int Estudiante::obtenerCantidadLibrosPrestados() const {
    return libros_prestados.size();
}

void reportarEstudiantesConMasLibros(const vector<Estudiante>& estudiantes) {
    int max_libros = 0;
    
    for (const auto& estudiante : estudiantes) {
        
        if (estudiante.obtenerCantidadLibrosPrestados() > max_libros) {
            max_libros = estudiante.obtenerCantidadLibrosPrestados();
        }
    }
    cout << "\nEstudiantes con mas libros prestados (" << max_libros << " libros):" << endl;
    
    for (const auto& estudiante : estudiantes) {
        
        if (estudiante.obtenerCantidadLibrosPrestados() == max_libros) {
            cout << " - ID del estudiante: " << estudiante.id_estudiante << endl;
        }
    }
}

void reportarEstudiantesSinLibros(const vector<Estudiante>& estudiantes) {
    cout << "\nEstudiantes sin libros prestados:" << endl;
    
    for (const auto& estudiante : estudiantes) {
        
        if (estudiante.obtenerCantidadLibrosPrestados() == 0) {
            cout << " - ID del estudiante: " << estudiante.id_estudiante << endl;
        }
    }
}

void reportarEstudiantesYLibrosPrestados(const vector<Estudiante>& estudiantes) {
    cout << "\nReporte: Estudiantes y los indices de sus libros prestados" << endl;
    
    for (const auto& estudiante : estudiantes) {
        cout << "ID del estudiante: " << estudiante.id_estudiante << " - Indices de libros prestados: ";
        
        if (estudiante.libros_prestados.empty()) {
            cout << "Ninguno";
        }
        else {
            
            for (const auto& libro : estudiante.libros_prestados) {
                cout << libro.first << " ";
            }
        }
        cout << endl;
    }
}