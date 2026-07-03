
#include <iostream>
#include <string>  

using namespace std;

struct Nodo {
    int dato;       
    Nodo* siguiente; 

    Nodo(int valor) {
        dato = valor;
        siguiente = NULL;
    }
};

class ListaEnlazada {
public:
    Nodo* cabeza; 

    ListaEnlazada() {
        cabeza = NULL;
    }

    ~ListaEnlazada() {
        Nodo* actual = cabeza;
        while (actual != NULL) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    void insertarAlInicio(int valor) {
        Nodo* nuevoNodo = new Nodo(valor);
        nuevoNodo->siguiente = cabeza;
        cabeza = nuevoNodo;
    }

    void imprimir() {
        Nodo* actual = cabeza;
        while (actual != NULL) {
            cout << actual->dato;
            if (actual->siguiente != NULL) {
                cout << " -> ";
            }
            actual = actual->siguiente;
        }
    }

    bool estaVacia() {
        return cabeza == NULL;
    }
};

class Grafo {
private:
    int numVertices;               
    ListaEnlazada* listaAdyacencia; 
    string* nombresUsuarios;       

public:
    Grafo(int vertices) {
        numVertices = vertices;

        listaAdyacencia = new ListaEnlazada[numVertices];

        nombresUsuarios = new string[numVertices];

        for (int i = 0; i < numVertices; i++) {
            nombresUsuarios[i] = "Usuario_" + to_string(i);
        }
    }

    ~Grafo() {
        delete[] listaAdyacencia;
        delete[] nombresUsuarios;
    }

    void asignarNombre(int vertice, string nombre) {
        if (vertice >= 0 && vertice < numVertices) {
            nombresUsuarios[vertice] = nombre;
        }
    }

    void agregarArista(int origen, int destino) {
        if (origen < 0 || origen >= numVertices || destino < 0 || destino >= numVertices) {
            cout << "Error: vertices fuera de rango." << endl;
            return;
        }

        listaAdyacencia[origen].insertarAlInicio(destino);
        listaAdyacencia[destino].insertarAlInicio(origen);
    }

    void mostrarListaAdyacencia() {
        cout << "LISTA DE ADYACENCIA (Conexiones de la Red)" << endl;

        for (int i = 0; i < numVertices; i++) {
            cout << "  [" << i << "] " << nombresUsuarios[i] << " : ";
            if (listaAdyacencia[i].estaVacia()) {
                cout << "(sin conexiones)";
            } else {
                Nodo* actual = listaAdyacencia[i].cabeza;
                while (actual != NULL) {
                    cout << nombresUsuarios[actual->dato];
                    if (actual->siguiente != NULL) {
                        cout << ", ";
                    }
                    actual = actual->siguiente;
                }
            }
            cout << endl;
        }
    }

    void dfs(int vertice, bool* visitado, int* comunidad, int &tamComunidad) {
        visitado[vertice] = true;

        comunidad[tamComunidad] = vertice;
        tamComunidad++;

        Nodo* vecino = listaAdyacencia[vertice].cabeza;
        while (vecino != NULL) {
            if (!visitado[vecino->dato]) {
                dfs(vecino->dato, visitado, comunidad, tamComunidad);
            }
            vecino = vecino->siguiente;
        }
    }

    void detectarComunidades() {
        bool* visitado = new bool[numVertices];
        for (int i = 0; i < numVertices; i++) {
            visitado[i] = false;
        }

        int* comunidad = new int[numVertices];

        int numComunidad = 0; \

        cout << "COMUNIDADES DETECTADAS MEDIANTE DFS" << endl;

        for (int i = 0; i < numVertices; i++) {
            if (!visitado[i]) {
                numComunidad++;
                int tamComunidad = 0;\
                
                dfs(i, visitado, comunidad, tamComunidad);

                cout << "\n  Comunidad #" << numComunidad << " (" 
                     << tamComunidad << " miembros):" << endl;
                cout << "  ---------------------------------" << endl;

                for (int j = 0; j < tamComunidad; j++) {
                    cout << "    -> [" << comunidad[j] << "] " 
                         << nombresUsuarios[comunidad[j]] << endl;
                }
            }
        }

        cout << "\n  ---------------------------------" << endl;
        cout << "  Total de comunidades encontradas: " << numComunidad << endl;

        delete[] visitado;
        delete[] comunidad;
    }


    void mostrarEstadisticas() {
        cout << "ESTADISTICAS DE LA RED SOCIAL" << endl;
        cout << "Numero total de usuarios: " << numVertices << endl;

        int totalAristas = 0;
        int gradoMaximo = 0;
        int gradoMinimo = numVertices;
        string usuarioMasConectado = "";

        for (int i = 0; i < numVertices; i++) {
            int grado = 0;
            Nodo* actual = listaAdyacencia[i].cabeza;
            while (actual != NULL) {
                grado++;
                actual = actual->siguiente;
            }

            totalAristas = totalAristas + grado;

            if (grado > gradoMaximo) {
                gradoMaximo = grado;
                usuarioMasConectado = nombresUsuarios[i];
            }
            if (grado < gradoMinimo) {
                gradoMinimo = grado;
            }

            cout << "  " << nombresUsuarios[i] << " tiene " 
                 << grado << " conexion(es)" << endl;
        }

        totalAristas = totalAristas / 2;

        cout << "\n  Total de conexiones (aristas): " << totalAristas << endl;
        cout << "  Usuario mas conectado: " << usuarioMasConectado 
             << " (" << gradoMaximo << " conexiones)" << endl;
        cout << "  Grado minimo: " << gradoMinimo << endl;
        cout << "  Grado maximo: " << gradoMaximo << endl;
    }
};

int main() {
    cout << "ANALISIS Y DETECCION DE COMUNIDADES EN REDES    " << endl;
    cout << "SOCIALES BASADO EN RECORRIDOS DFS               " << endl;
    cout << "Proyecto Final - Estructuras de Datos           " << endl;

    int totalUsuarios = 8;
    Grafo redSocial(totalUsuarios);

    redSocial.asignarNombre(0, "Ana");
    redSocial.asignarNombre(1, "Luis");
    redSocial.asignarNombre(2, "Carlos");
    redSocial.asignarNombre(3, "Maria");
    redSocial.asignarNombre(4, "Diana");
    redSocial.asignarNombre(5, "Pedro");
    redSocial.asignarNombre(6, "Elena");
    redSocial.asignarNombre(7, "Sofia");

    //Comunidad 1
    redSocial.agregarArista(0, 1);  // Ana --> Luis
    redSocial.agregarArista(0, 2);  // Ana --> Carlos
    redSocial.agregarArista(1, 2);  // Luis --> Carlos
    redSocial.agregarArista(1, 3);  // Luis --> Maria

    //Comunidad 2
    redSocial.agregarArista(4, 5);  // Diana --> Pedro
    redSocial.agregarArista(4, 6);  // Diana --> Elena

    //Comunidad 3 (Sofia) => Vacia, sin conexiones

    redSocial.mostrarListaAdyacencia();

    redSocial.mostrarEstadisticas();

    redSocial.detectarComunidades();

    cout << ">> Fin del analisis\n" << endl;

    return 0;
}
