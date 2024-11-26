# Gestión de Biblioteca Universitaria 📚

Este proyecto implementa un sistema de gestión de una biblioteca universitaria, permitiendo registrar libros, gestionar préstamos y devoluciones, y generar reportes relacionados con los libros y los estudiantes.

## Tabla de Contenidos
1. [Descripción](#descripción)
2. [Características](#características)
3. [Estructura del Proyecto](#estructura-del-proyecto)
4. [Requisitos del Sistema](#requisitos-del-sistema)
5. [Instalación](#instalación)
6. [Uso](#uso)
7. [Autores](#autores)

---

## Descripción
El sistema automatiza la gestión de una biblioteca universitaria utilizando operaciones sobre archivos CSV y binarios. Este proyecto está diseñado para aplicar conceptos avanzados de manipulación de archivos en C++.

---

## Características
- Lectura de archivos CSV que contienen información sobre libros.
- Creación de un archivo binario para almacenar registros con tamaño fijo.
- Funcionalidades para:
  - Registrar préstamos y devoluciones de libros.
  - Generar reportes sobre libros no disponibles y estudiantes con más o menos libros prestados.
- Menú interactivo para gestionar todas las operaciones del sistema.

---

## Estructura del Proyecto
├── main_proyecto.cpp # Archivo principal con el menú interactivo ├── libro_proyecto.cpp # Implementación de la clase Libro y operaciones con archivos ├── estudiante_proyecto.cpp # Implementación de la clase Estudiante y gestión de préstamos ├── Header.h # Archivo de encabezado con las definiciones de clases y funciones ├── best-selling-books.csv # Archivo de entrada con datos de libros └── README.md # Este archivo


---

## Requisitos del Sistema
- Lenguaje: C++
- Compilador compatible con C++11 o superior (por ejemplo, GCC, Clang, MSVC)
- Editor de texto o IDE (por ejemplo, Visual Studio Code)

---

Sigue el menú interactivo para realizar las operaciones disponibles:
Registrar préstamos y devoluciones.
Consultar reportes sobre libros y estudiantes.


Autores
[Rafael Campos] - Contacto
[Emilio Espino] - Contacto
[Carlos Escamilla] - Contacto


Proyecto desarrollado como parte de la materia Programación Avanzada.


Licencia
Este proyecto está bajo la licencia MIT. Consulta el archivo LICENSE para más detalles.
