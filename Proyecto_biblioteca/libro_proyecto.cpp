#include "Header.h"

Libro::Libro() : indice(0), ventas(0), cantidad_disponible(5) { // inicializa 
    memset(titulo, 0, sizeof(titulo));
    memset(autores, 0, sizeof(autores));
    memset(idioma, 0, sizeof(idioma));
    memset(genero, 0, sizeof(genero));
}

void Libro::establecerTitulo(const string& nuevoTitulo) {
    size_t longitud = min(nuevoTitulo.size(), sizeof(titulo) - 1); // titulo del libro, maximo en memoria que puede usar
    nuevoTitulo.copy(titulo, longitud); // copia los primeros "longitud" caracteres al arreglo titulo
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

// filtro para comas
// "The lion, the witch and x", Rafa Campos, 1950, "Fantasy, Children"

vector<string> parsearLineaCSV(const string& linea) {
    vector<string> campos;
    string campo;
    bool dentro_de_comillas = false;

    for (size_t i = 0; i < linea.size(); ++i) {
        char c = linea[i];
        if (c == '"') {
            dentro_de_comillas = !dentro_de_comillas; // cambia el estado de las comillas a true o false
        }
        else if (c == ',' && !dentro_de_comillas) {
            // encontramos una coma fuera de las comillas, es un delimitador
            if (campo.empty()) {
                campo = "Null"; // Rellenar campo vacío
            }
            campos.push_back(campo);
            campo.clear();
        }
        else {
            campo += c; // agregar el carácter actual al campo
        }
    }

    // agregar el último campo
    if (campo.empty()) {
        campo = "Null"; // rellenar campo vacío
    }
    campos.push_back(campo);

    return campos;
}


vector<Libro> leerCSVSecuencial(const string& nombreArchivo) { //binario
    vector<Libro> libros;
    ifstream archivo(nombreArchivo); // leer el archivo, bin
    string linea;

    // filtro
    if (!archivo.is_open()) {
        cerr << "Error: No se puede abrir el archivo CSV" << endl;
        return libros;
    }

    getline(archivo, linea); // se salta la cabecera
    int indice = 1; // inicia los indices en 1
    while (getline(archivo, linea)) {
        vector<string> campos = parsearLineaCSV(linea); // lee por linea y nos regresa campos de cada linea (titulo, autor...)

        // filtro
        if (campos.size() < 6) {
            cerr << "Error al procesar la línea: " << linea << endl;
            continue; // reintentar con las siguientes líneas
        }

        Libro libro; // objeto tipo Libro llamado libro
        libro.indice = indice++;
        libro.establecerTitulo(campos[0]); // agarra el primer campo y lo settea en el titulo
        libro.establecerAutores(campos[1]);
        libro.establecerIdioma(campos[2]);

        // filtro para procesar la fecha
        try {
            // asumimos solo el año si no hay mes o día
            libro.fecha_publicacion = Fecha(stoi(campos[3]), 1, 1); // stoi = string to integer
        }
        catch (...) {
            cerr << "Error en la fecha: " << campos[3] << endl;
            libro.fecha_publicacion = Fecha(0, 0, 0); // fecha inválida
        }

        libro.ventas = (campos[4] != "Null") ? stof(campos[4]) : 0.0f; // ventas en 0 si es "Null", stof string to float
        libro.establecerGenero(campos[5]);
        libro.cantidad_disponible = 5;
        
        //cout << "Titulo: " << libro.titulo << " Autor: " << libro.autores << endl;

        libros.push_back(libro);
    }

    archivo.close();
    return libros;
}

void crearArchivoBinarioDesdeCSV(const string& nombreArchivo, const vector<Libro>& libros) {
    ofstream archivo(nombreArchivo, ios::binary); // manejar flujos de salida hacia un archivo en binario

    // filtro
    if (!archivo.is_open()) {
        cerr << "Error: No se puede crear el archivo binario." << endl;
        return;
    }
    
    // libros es un contenedor (en este caso, un vector) que almacena objetos tipo "Libro"
    // va de libro en libro 
    for (const auto& libro : libros) {
        
        // reinterpret_cast<const char*>(&libro) convierte la dirección del objeto "libro(&libro)" en un puntero de tipo const char*
        // esto se usa pq "archivo.write()" espera un puntero a un bloque de memoria representado como una secuencia de bytes(char*)
        // reinterpret_cast es un operador de conversion que interpreta un puntero de un tipo como si fuera de otro
        archivo.write(reinterpret_cast<const char*>(&libro), sizeof(Libro));
    }

    archivo.close();
    cout << "Archivo binario creado exitosamente con " << libros.size() << " libros." << endl;
}


bool leerRegistroLibro(const string& nombreArchivo, int indice_libro, Libro& libro) {
    ifstream archivo(nombreArchivo, ios::binary);
    
    // filtro
    if (!archivo.is_open()) {
        cerr << "Error: No se puede abrir el archivo binario para lectura." << endl;
        return false;
    }

    size_t posicion = (indice_libro - 1) * sizeof(Libro);
    archivo.seekg(posicion, ios::beg); // seekg: permite mover el puntero de lectura a una posición específica dentro de un archivo
    archivo.read(reinterpret_cast<char*>(&libro), sizeof(Libro));
    archivo.close();

    return archivo.good(); // verifica si el flujo está en un estado válido y listo para operar
}

void actualizarRegistroLibro(const string& nombreArchivo, int indice_libro, int nueva_cantidad) {
    fstream archivo(nombreArchivo, ios::in | ios::out | ios::binary);
    
    // filtro
    if (!archivo.is_open()) {
        cerr << "Error: No se puede abrir el archivo binario para ser actualizado." << endl;
        return;
    }

    size_t posicion = (indice_libro - 1) * sizeof(Libro);
    archivo.seekp(posicion, ios::beg); // seekp: permite mover el puntero de escritura a una posición específica dentro de un archivo
    Libro libro;
    archivo.read(reinterpret_cast<char*>(&libro), sizeof(Libro));
    libro.cantidad_disponible = nueva_cantidad;
    archivo.seekp(posicion, ios::beg);
    archivo.write(reinterpret_cast<const char*>(&libro), sizeof(Libro));
    archivo.close();
}

void reportarLibrosNoDisponibles(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo, ios::binary);
    // definimos el archivo de texto
    ofstream archivoTXT("comoUstedesQuieran.txt", ios::out);

    
    //filtro 
    if (!archivo.is_open()) {
        cerr << "Error: No se puede abrir el archivo binario para su lectura." << endl;
        return;
    }

    Libro libro;
    cout << "\nLibros que NO estan disponibles para prestamo:" << endl;
    while (archivo.read(reinterpret_cast<char*>(&libro), sizeof(Libro))) {
        if (libro.cantidad_disponible == 0) {
            cout << " - " << libro.titulo << " (Indice: " << libro.indice << ")" << endl;
            // funcion agregada en la presentacion para que mande el flujo de salida al archivo de texto
            archivoTXT << " - " << libro.titulo << " (Indice: " << libro.indice << ")" << endl;

        }
    }
    archivoTXT.close();
    archivo.close();
}
