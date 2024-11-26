#include "Header.h"

Libro::Libro() : indice(0), ventas(0), cantidad_disponible(5) {
    memset(titulo, 0, sizeof(titulo));
    memset(autores, 0, sizeof(autores));
    memset(idioma, 0, sizeof(idioma));
    memset(genero, 0, sizeof(genero));
}

void Libro::establecerTitulo(const string& nuevoTitulo) {
    size_t longitud = min(nuevoTitulo.size(), sizeof(titulo) - 1);
    nuevoTitulo.copy(titulo, longitud);
    titulo[longitud] = '\0';
}

void Libro::establecerAutores(const string& nuevosAutores) {
    size_t longitud = min(nuevosAutores.size(), sizeof(autores) - 1);
    nuevosAutores.copy(autores, longitud);
    autores[longitud] = '\0';
}

void Libro::establecerIdioma(const string& nuevoIdioma) {
    size_t longitud = min(nuevoIdioma.size(), sizeof(idioma) - 1);
    nuevoIdioma.copy(idioma, longitud);
    idioma[longitud] = '\0';
}

void Libro::establecerGenero(const string& nuevoGenero) {
    size_t longitud = min(nuevoGenero.size(), sizeof(genero) - 1);
    nuevoGenero.copy(genero, longitud);
    genero[longitud] = '\0';
}

vector<string> parsearLineaCSV(const string& linea) {
    vector<string> campos;
    string campo;
    bool dentro_de_comillas = false;

    for (size_t i = 0; i < linea.size(); ++i) {
        char c = linea[i];
        if (c == '"') {
            dentro_de_comillas = !dentro_de_comillas; // Cambiar el estado de comillas
        }
        else if (c == ',' && !dentro_de_comillas) {
            // Encontramos una coma fuera de las comillas, es un delimitador
            if (campo.empty()) {
                campo = "Null"; // Rellenar campo vac�o
            }
            campos.push_back(campo);
            campo.clear();
        }
        else {
            campo += c; // Agregar el car�cter actual al campo
        }
    }

    // Agregar el �ltimo campo
    if (campo.empty()) {
        campo = "Null"; // Rellenar campo vac�o
    }
    campos.push_back(campo);

    return campos;
}


vector<Libro> leerCSVSecuencial(const string& nombreArchivo) {
    vector<Libro> libros;
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error: No se puede abrir el archivo CSV" << endl;
        return libros;
    }

    getline(archivo, linea); // Saltar la cabecera
    int indice = 1; // Iniciar los �ndices en 1
    while (getline(archivo, linea)) {
        vector<string> campos = parsearLineaCSV(linea);

        if (campos.size() < 6) {
            cerr << "Error al procesar la l�nea: " << linea << endl;
            continue; // Reintentar con las siguientes l�neas
        }

        Libro libro;
        libro.indice = indice++;
        libro.establecerTitulo(campos[0]);
        libro.establecerAutores(campos[1]);
        libro.establecerIdioma(campos[2]);

        // Procesar la fecha
        try {
            libro.fecha_publicacion = Fecha(stoi(campos[3]), 1, 1); // Asumimos solo el a�o si no hay mes o d�a
        }
        catch (...) {
            cerr << "Error en la fecha: " << campos[3] << endl;
            libro.fecha_publicacion = Fecha(0, 0, 0); // Fecha inv�lida
        }

        libro.ventas = (campos[4] != "Null") ? stof(campos[4]) : 0.0f; // Ventas en 0 si es "Null"
        libro.establecerGenero(campos[5]);
        libro.cantidad_disponible = 5;
        
        //cout << "Titulo: " << libro.titulo << " Autor: " << libro.autores << endl;

        libros.push_back(libro);
    }

    archivo.close();
    return libros;
}

void crearArchivoBinarioDesdeCSV(const string& nombreArchivo, const vector<Libro>& libros) {
    ofstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se puede crear el archivo binario." << endl;
        return;
    }
    // libros es un contenedor (en este caso, un vector) que almacena objetos tipo "Libro"
    for (const auto& libro : libros) {
        
        // reinterpret_cast<const char*>(&libro) convierte la direcci�n del objeto "libro(&libro)" en un puntero de tipo const char*
        // esto se usa pq "archivo.write()" espera un puntero a un bloque de memoria representado como una secuencia de bytes(char*)
        // reinterpret_cast es un operador de conversion que interpreta un puntero de un tipo como si fuera de otro
        archivo.write(reinterpret_cast<const char*>(&libro), sizeof(Libro));
    }

    archivo.close();
    cout << "Archivo binario creado exitosamente con " << libros.size() << " libros." << endl;
}


bool leerRegistroLibro(const string& nombreArchivo, int indice_libro, Libro& libro) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se puede abrir el archivo binario para lectura." << endl;
        return false;
    }

    size_t posicion = (indice_libro - 1) * sizeof(Libro);
    archivo.seekg(posicion, ios::beg);
    archivo.read(reinterpret_cast<char*>(&libro), sizeof(Libro));
    archivo.close();

    return archivo.good();
}

void actualizarRegistroLibro(const string& nombreArchivo, int indice_libro, int nueva_cantidad) {
    fstream archivo(nombreArchivo, ios::in | ios::out | ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se puede abrir el archivo binario para ser actualizado." << endl;
        return;
    }

    size_t posicion = (indice_libro - 1) * sizeof(Libro);
    archivo.seekp(posicion, ios::beg);
    Libro libro;
    archivo.read(reinterpret_cast<char*>(&libro), sizeof(Libro));
    libro.cantidad_disponible = nueva_cantidad;
    archivo.seekp(posicion, ios::beg);
    archivo.write(reinterpret_cast<const char*>(&libro), sizeof(Libro));
    archivo.close();
}

void reportarLibrosNoDisponibles(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se puede abrir el archivo binario para su lectura." << endl;
        return;
    }

    Libro libro;
    cout << "\nLibros que NO estan disponibles para prestamo:" << endl;
    while (archivo.read(reinterpret_cast<char*>(&libro), sizeof(Libro))) {
        if (libro.cantidad_disponible == 0) {
            cout << " - " << libro.titulo << " (Indice: " << libro.indice << ")" << endl;
        }
    }

    archivo.close();
}