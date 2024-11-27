#include "Header.h"

int main() {
    // cout << sizeof(Libro) << endl;
    
    string archivoCSV = "best-selling-books.csv"; // definir nombres de los archivos
    string archivoBinario = "libros.bin";

    vector<Libro> libros = leerCSVSecuencial(archivoCSV); // vector tipo libro llamado libros
    crearArchivoBinarioDesdeCSV(archivoBinario, libros); // crea el binario 

    // vector de tipo Estudiante
    vector<Estudiante> estudiantes;
    for (int i = 1; i <= 10; ++i) {
        estudiantes.emplace_back(i); // emplace_back es más eficiente que push_back en este caso pq construye el objeto directamente dentro del vector y evita una copia temporal.
    }

    int opcion = 0;
    while (opcion != 7) {
        cout << "\n############### MENU ###############" << endl;
        cout << "1. Prestar un libro\n2. Devolver un libro\n3. Lista de libros prestados\n4. Reporte de libros no disponibles" << endl;
        cout << "5. Reporte de estudiantes con mas y menos libros\n6. Reporte de estudiantes y libros prestados\n7. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            int id_estudiante, indice_libro;
            cout << "Ingrese el ID del estudiante: ";
            cin >> id_estudiante;
            cout << "Ingrese el indice del libro que desea prestar: ";
            cin >> indice_libro;

            if (id_estudiante > 0 && id_estudiante <= 10) {
                estudiantes[id_estudiante - 1].prestarLibro(indice_libro, archivoBinario); // se resta 1 pq el vector inicia en 0
            }
            else {
                cout << "El ID del estudiante es invalido." << endl;
            }
            break;
        }
        case 2: {
            int id_estudiante, indice_libro;
            cout << "Ingrese el ID del estudiante: ";
            cin >> id_estudiante;
            cout << "Ingrese el indice del libro que va a regresar: ";
            cin >> indice_libro;

            if (id_estudiante > 0 && id_estudiante <= 10) {
                estudiantes[id_estudiante - 1].devolverLibro(indice_libro, archivoBinario);
            }
            else {
                cout << "El ID del estudiante es invalido." << endl;
            }
            break;
        }
        case 3: {
            int id_estudiante;
            cout << "Ingrese el ID del estudiante: ";
            cin >> id_estudiante;

            if (id_estudiante > 0 && id_estudiante <= 10) {
                estudiantes[id_estudiante - 1].listarLibrosPrestados(); // getter de libros que tiene el estudiante
            }
            else {
                cout << "El ID del estudiante es invalido." << endl;
            }
            break;
        }
        case 4:
            reportarLibrosNoDisponibles(archivoBinario);
            break;
        case 5:
            reportarEstudiantesConMasLibros(estudiantes);
            reportarEstudiantesSinLibros(estudiantes);
            break;
        case 6:
            reportarEstudiantesYLibrosPrestados(estudiantes);
            break;
        case 7:
            cout << "Saliendo del programa." << endl;
            break;
        default:
            cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
        }
    }

    return 0;
}
