# Análisis y Detección de Comunidades en Redes Sociales (DFS)
**Universidad de Lima - Estructuras de Datos 2**

Este repositorio contiene la implementación en C++ del proyecto final enfocado en la segmentación de redes sociales utilizando Teoría de Grafos y el algoritmo de Búsqueda en Profundidad (DFS).

## 👥 Integrantes (Grupo 3)
* Alcarraz Marcoz, Andree Rodrigo
* Chancafe Medina, Geraldine Celeste
* Huaytani Avendaño, Mauricio Miguel

## ⚙️ Características Técnicas
* **Estructura base:** Lista de Adyacencia (implementada manualmente con punteros, sin STL).
* **Complejidad Asintótica:** $O(V + E)$ en tiempo y espacio.
* **Algoritmo de segmentación:** Búsqueda en Profundidad (DFS Recursivo).

## 🚀 ¿Cómo compilar y ejecutar?
El código no posee dependencias externas. Para compilarlo usando GCC (MinGW), ejecute el siguiente comando en la terminal:

```bash
g++ Proyecto_Final_Grupo_3.cpp -o programa
```

Luego, ejecute el archivo generado:

```bash
./programa.exe
```

## 📊 Pruebas
La captura de pantalla con la validación del funcionamiento (lista de adyacencia y segmentación de comunidades), así como el registro de salida en consola, se encuentran disponibles en la carpeta `/pruebas` de este repositorio.