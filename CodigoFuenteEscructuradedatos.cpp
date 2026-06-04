/*
 * ============================================================
 *  SISTEMA DE GESTION DE PROCESOS
 *  Simulador de administracion de recursos en un Sistema Operativo
 *
 *  Universidad Continental | Estructura de Datos | 2026
 *  Integrantes:
 *    - Cunyas Lanasca, Geanpiero Andre
 *    - Vilchez Aquino, Andy Jeison
 *    - Torres Patilla, Xiomara Yamile
 *    - Aguado Garay, Frank Joseph
 *
 *  Restricciones:
 *    - Lenguaje: C++ (DEV C++)
 *    - Prohibido usar STL
 *    - Toda gestion de datos: nodos y punteros nativos
 *    - Uso obligatorio de delete para liberar memoria
 * ============================================================
 */

#include <iostream>
#include <cstring>
using namespace std;

const int TAM_STR = 50;

// ============================================================
//  FUNCIONES DE LECTURA SEGURA
//  Evitan que el programa se rompa con entradas invalidas
// ============================================================

// Leer un entero positivo. Si el usuario mete letras o negativo
// lo rechaza y vuelve a pedir hasta recibir un numero valido.
int leerEnteroPositivo(const char* mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail() || valor <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida. Ingrese un numero entero positivo." << endl;
        } else {
            cin.ignore(1000, '\n');
            return valor;
        }
    }
}

// Leer un entero >= 0 (acepta cero, util para IDs o menus)
int leerEntero(const char* mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida. Ingrese un numero entero." << endl;
        } else {
            cin.ignore(1000, '\n');
            return valor;
        }
    }
}

// Leer una cadena de texto sin espacios (una palabra)
// Rechaza entrada vacia o demasiado larga
void leerCadena(const char* mensaje, char* destino, int maxLen) {
    while (true) {
        cout << mensaje;
        cin >> destino;
        if (cin.fail() || strlen(destino) == 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada invalida. Intente de nuevo." << endl;
        } else {
            // Truncar si por alguna razon supera el limite
            destino[maxLen - 1] = '\0';
            cin.ignore(1000, '\n');
            return;
        }
    }
}

// ============================================================
//  ESTRUCTURA COMPARTIDA: Proceso
// ============================================================
struct Proceso {
    int  id;
    char nombre[TAM_STR];
    int  prioridad;
    char estado[TAM_STR];
};

// ============================================================
//  MODULO 1: GESTOR DE PROCESOS - Lista Enlazada Simple
//  REQ-F01, REQ-F02, REQ-F03, REQ-F08
// ============================================================

struct NodoProceso {
    Proceso      dato;
    NodoProceso* siguiente;
};

struct ListaProcesos {
    NodoProceso* inicio;
    int          total;

    ListaProcesos() : inicio(NULL), total(0) {}
};

// REQ-F01: Agregar proceso al final de la lista
void agregarProceso(ListaProcesos& lista, int id, const char* nombre, int prioridad) {
    // Verificar que el ID no exista
    NodoProceso* aux = lista.inicio;
    while (aux != NULL) {
        if (aux->dato.id == id) {
            cout << "ERROR: Ya existe un proceso con ID " << id << endl;
            return;
        }
        aux = aux->siguiente;
    }

    // Crear nuevo nodo
    NodoProceso* nuevo = new NodoProceso();
    nuevo->dato.id = id;
    strncpy(nuevo->dato.nombre, nombre, TAM_STR - 1);
    strncpy(nuevo->dato.estado, "Listo", TAM_STR - 1);
    nuevo->dato.prioridad = prioridad;
    nuevo->siguiente = NULL;

    // Insertar al final
    if (lista.inicio == NULL) {
        lista.inicio = nuevo;
    } else {
        NodoProceso* temp = lista.inicio;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }

    lista.total++;
    cout << "Proceso '" << nombre << "' (ID=" << id << ") registrado correctamente." << endl;
}

// REQ-F02: Buscar proceso por ID
NodoProceso* buscarProceso(ListaProcesos& lista, int idBuscado) {
    NodoProceso* aux = lista.inicio;
    while (aux != NULL) {
        if (aux->dato.id == idBuscado) {
            return aux;
        }
        aux = aux->siguiente;
    }
    return NULL;
}

// REQ-F03: Modificar prioridad y estado
void modificarProceso(ListaProcesos& lista, int id, int nuevaPrioridad, const char* nuevoEstado) {
    NodoProceso* encontrado = buscarProceso(lista, id);
    if (encontrado == NULL) {
        cout << "ERROR: No existe un proceso con ID " << id << endl;
        return;
    }
    encontrado->dato.prioridad = nuevaPrioridad;
    strncpy(encontrado->dato.estado, nuevoEstado, TAM_STR - 1);
    cout << "Proceso ID=" << id << " actualizado. Prioridad=" << nuevaPrioridad
         << " | Estado=" << nuevoEstado << endl;
}

// REQ-F03: Eliminar proceso
void eliminarProceso(ListaProcesos& lista, int id) {
    if (lista.inicio == NULL) {
        cout << "ERROR: La lista de procesos esta vacia." << endl;
        return;
    }

    NodoProceso* actual   = lista.inicio;
    NodoProceso* anterior = NULL;

    while (actual != NULL && actual->dato.id != id) {
        anterior = actual;
        actual   = actual->siguiente;
    }

    if (actual == NULL) {
        cout << "ERROR: No existe un proceso con ID " << id << endl;
        return;
    }

    // Reasignar punteros para desconectar el nodo
    if (anterior == NULL) {
        lista.inicio = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    cout << "Proceso '" << actual->dato.nombre << "' (ID=" << id << ") eliminado." << endl;

    delete actual;
    actual = NULL;
    lista.total--;
}

// REQ-F08: Mostrar todos los procesos
void mostrarProcesos(const ListaProcesos& lista) {
    if (lista.inicio == NULL) {
        cout << "No hay procesos registrados." << endl;
        return;
    }

    cout << "--------------------------------------------------" << endl;
    cout << "ID    | Nombre             | Prioridad | Estado" << endl;
    cout << "--------------------------------------------------" << endl;

    NodoProceso* aux = lista.inicio;
    while (aux != NULL) {
        printf("%-5d | %-18s | %-9d | %s\n",
               aux->dato.id,
               aux->dato.nombre,
               aux->dato.prioridad,
               aux->dato.estado);
        aux = aux->siguiente;
    }

    cout << "--------------------------------------------------" << endl;
    cout << "Total de procesos: " << lista.total << endl;
}

// ============================================================
//  MODULO 2: PLANIFICADOR DE CPU - Cola de Prioridad
//  REQ-F04, REQ-F05, REQ-F08
// ============================================================

struct NodoCola {
    Proceso   dato;
    NodoCola* siguiente;
};

struct ColaPrioridad {
    NodoCola* frente;
    NodoCola* final;
    int       total;

    ColaPrioridad() : frente(NULL), final(NULL), total(0) {}
};

// REQ-F04: Encolar proceso segun prioridad (menor numero = mayor prioridad)
void encolarProceso(ColaPrioridad& cola, const Proceso& proc) {
    NodoCola* nuevo = new NodoCola();
    nuevo->dato      = proc;
    nuevo->siguiente = NULL;

    if (cola.frente == NULL) {
        cola.frente = nuevo;
        cola.final  = nuevo;
    } else if (nuevo->dato.prioridad < cola.frente->dato.prioridad) {
        // Es el mas urgente, va al frente
        nuevo->siguiente = cola.frente;
        cola.frente = nuevo;
    } else {
        // Buscar posicion correcta
        NodoCola* aux = cola.frente;
        while (aux->siguiente != NULL &&
               aux->siguiente->dato.prioridad <= nuevo->dato.prioridad) {
            aux = aux->siguiente;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente   = nuevo;
        if (nuevo->siguiente == NULL) {
            cola.final = nuevo;
        }
    }

    cola.total++;
    cout << "Proceso '" << proc.nombre << "' encolado con prioridad " << proc.prioridad << endl;
}

// REQ-F05: Desencolar y simular ejecucion
void desencolarProceso(ColaPrioridad& cola) {
    if (cola.frente == NULL) {
        cout << "La cola de ejecucion esta vacia." << endl;
        return;
    }

    NodoCola* temp = cola.frente;
    cout << "[CPU] Ejecutando: '" << temp->dato.nombre
         << "' (ID=" << temp->dato.id << " | Prioridad=" << temp->dato.prioridad << ")" << endl;

    cola.frente = cola.frente->siguiente;
    if (cola.frente == NULL) {
        cola.final = NULL;
    }

    delete temp;
    temp = NULL;
    cola.total--;
    cout << "Proceso finalizado y removido de la cola." << endl;
}

// REQ-F08: Mostrar cola
void mostrarCola(const ColaPrioridad& cola) {
    if (cola.frente == NULL) {
        cout << "La cola de ejecucion esta vacia." << endl;
        return;
    }

    cout << "Orden de ejecucion (frente -> final):" << endl;
    cout << "------------------------------------------" << endl;
    cout << "ID    | Nombre             | Prioridad" << endl;
    cout << "------------------------------------------" << endl;

    NodoCola* aux = cola.frente;
    while (aux != NULL) {
        printf("%-5d | %-18s | %d\n",
               aux->dato.id,
               aux->dato.nombre,
               aux->dato.prioridad);
        aux = aux->siguiente;
    }

    cout << "------------------------------------------" << endl;
    cout << "Procesos en cola: " << cola.total << endl;
}

//  MODULO 3: GESTOR DE MEMORIA - Pila Dinamica
//  REQ-F06, REQ-F07, REQ-F08

struct NodoPila {
    int       idProceso;
    int       tamBloque;
    NodoPila* anterior;
};

struct PilaMemoria {
    NodoPila* tope;
    int       totalBloques;
    int       memoriaUsada;

    PilaMemoria() : tope(NULL), totalBloques(0), memoriaUsada(0) {}
};

// REQ-F06: Asignar bloque de memoria (push)
void asignarMemoria(PilaMemoria& pila, int idProceso, int tamBloque) {
    NodoPila* nuevo  = new NodoPila();
    nuevo->idProceso = idProceso;
    nuevo->tamBloque = tamBloque;
    nuevo->anterior  = pila.tope;

    pila.tope = nuevo;
    pila.totalBloques++;
    pila.memoriaUsada += tamBloque;

    cout << "[PUSH] Bloque de " << tamBloque << " KB asignado al proceso ID=" << idProceso
         << ". Memoria en uso: " << pila.memoriaUsada << " KB" << endl;
}

// REQ-F07: Liberar bloque de memoria (pop)
void liberarMemoria(PilaMemoria& pila) {
    if (pila.tope == NULL) {
        cout << "La pila de memoria esta vacia." << endl;
        return;
    }

    NodoPila* temp = pila.tope;
    cout << "[POP] Liberando bloque de " << temp->tamBloque << " KB "
         << "(Proceso ID=" << temp->idProceso << ")" << endl;

    pila.tope = pila.tope->anterior;
    pila.memoriaUsada -= temp->tamBloque;
    pila.totalBloques--;

    delete temp;
    temp = NULL;

    cout << "Bloque liberado. Memoria en uso: " << pila.memoriaUsada << " KB" << endl;
}

// REQ-F08: Mostrar estado de la pila
void mostrarPila(const PilaMemoria& pila) {
    if (pila.tope == NULL) {
        cout << "La pila de memoria esta vacia." << endl;
        return;
    }

    cout << "Estado de la Pila (tope -> base):" << endl;
    cout << "------------------------------" << endl;
    cout << "ID Proceso  | Tamano (KB)" << endl;
    cout << "------------------------------" << endl;

    NodoPila* aux = pila.tope;
    while (aux != NULL) {
        printf("%-11d | %d KB\n", aux->idProceso, aux->tamBloque);
        aux = aux->anterior;
    }

    cout << "------------------------------" << endl;
    cout << "Bloques activos : " << pila.totalBloques << endl;
    cout << "Memoria en uso  : " << pila.memoriaUsada << " KB" << endl;
}

// ============================================================
//  FUNCIONES AUXILIARES
// ============================================================

void limpiarPantalla() {
    system("cls");
}

void pausar() {
    cout << "\nPresione ENTER para continuar...";
    cin.ignore();
    cin.get();
}

// ============================================================
//  SUBMENU - MODULO 1: GESTOR DE PROCESOS
// ============================================================
void menuGestorProcesos(ListaProcesos& lista, ColaPrioridad& cola, PilaMemoria& pila) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "=== GESTOR DE PROCESOS (Lista Enlazada Simple) ===" << endl;
        cout << "1. Registrar nuevo proceso" << endl;
        cout << "2. Buscar proceso por ID" << endl;
        cout << "3. Modificar prioridad / estado" << endl;
        cout << "4. Eliminar proceso" << endl;
        cout << "5. Ver todos los procesos" << endl;
        cout << "0. Volver al menu principal" << endl;
        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            int  id, prioridad, tamBloque;
            char nombre[TAM_STR];
            cout << "\n-- REGISTRAR PROCESO --" << endl;
            id        = leerEnteroPositivo("ID (entero unico): ");
            leerCadena("Nombre: ", nombre, TAM_STR);
            prioridad = leerEnteroPositivo("Prioridad (1=alta): ");
            agregarProceso(lista, id, nombre, prioridad);

            // REQ-F06: Asignar bloque de memoria al crearlo
            tamBloque = leerEnteroPositivo("Tamano de bloque de memoria a asignar (KB): ");
            asignarMemoria(pila, id, tamBloque);

        } else if (opcion == 2) {
            int id;
            cout << "\n-- BUSCAR PROCESO --" << endl;
            id = leerEnteroPositivo("ID a buscar: ");
            NodoProceso* resultado = buscarProceso(lista, id);
            if (resultado != NULL) {
                cout << "Encontrado -> ID=" << resultado->dato.id
                     << " | Nombre: "    << resultado->dato.nombre
                     << " | Prioridad: " << resultado->dato.prioridad
                     << " | Estado: "    << resultado->dato.estado << endl;
            } else {
                cout << "No se encontro el proceso con ID=" << id << endl;
            }

        } else if (opcion == 3) {
            int  id, nuevaPrioridad;
            char nuevoEstado[TAM_STR];
            cout << "\n-- MODIFICAR PROCESO --" << endl;
            id             = leerEnteroPositivo("ID a modificar: ");
            nuevaPrioridad = leerEnteroPositivo("Nueva prioridad: ");
            leerCadena("Nuevo estado (Listo/Espera/Ejecutando): ", nuevoEstado, TAM_STR);
            modificarProceso(lista, id, nuevaPrioridad, nuevoEstado);

        } else if (opcion == 4) {
            int id;
            cout << "\n-- ELIMINAR PROCESO --" << endl;
            id = leerEnteroPositivo("ID a eliminar: ");
            eliminarProceso(lista, id);

        } else if (opcion == 5) {
            cout << "\n-- LISTA DE PROCESOS --" << endl;
            mostrarProcesos(lista);
        }

        if (opcion != 0) pausar();

    } while (opcion != 0);
}

// ============================================================
//  SUBMENU - MODULO 2: PLANIFICADOR DE CPU
// ============================================================
void menuPlanificadorCPU(ListaProcesos& lista, ColaPrioridad& cola) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "=== PLANIFICADOR DE CPU (Cola de Prioridad) ===" << endl;
        cout << "1. Encolar proceso para CPU" << endl;
        cout << "2. Ejecutar (desencolar) proceso" << endl;
        cout << "3. Ver cola de ejecucion" << endl;
        cout << "0. Volver al menu principal" << endl;
        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            int id;
            cout << "\n-- ENCOLAR PROCESO --" << endl;
            id = leerEnteroPositivo("ID del proceso a encolar: ");
            NodoProceso* resultado = buscarProceso(lista, id);
            if (resultado != NULL) {
                encolarProceso(cola, resultado->dato);
            } else {
                cout << "Proceso con ID=" << id << " no encontrado en el registro." << endl;
            }

        } else if (opcion == 2) {
            cout << "\n-- EJECUTAR PROCESO (CPU) --" << endl;
            desencolarProceso(cola);

        } else if (opcion == 3) {
            cout << "\n-- COLA DE EJECUCION --" << endl;
            mostrarCola(cola);
        }

        if (opcion != 0) pausar();

    } while (opcion != 0);
}

// ============================================================
//  SUBMENU - MODULO 3: GESTOR DE MEMORIA
// ============================================================
void menuGestorMemoria(PilaMemoria& pila) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "=== GESTOR DE MEMORIA (Pila Dinamica) ===" << endl;
        cout << "1. Asignar bloque de memoria (push)" << endl;
        cout << "2. Liberar bloque de memoria (pop)" << endl;
        cout << "3. Ver estado de la memoria" << endl;
        cout << "0. Volver al menu principal" << endl;
        opcion = leerEntero("Opcion: ");

        if (opcion == 1) {
            int id, tamBloque;
            cout << "\n-- ASIGNAR BLOQUE (PUSH) --" << endl;
            id        = leerEnteroPositivo("ID del proceso: ");
            tamBloque = leerEnteroPositivo("Tamano del bloque (KB): ");
            asignarMemoria(pila, id, tamBloque);

        } else if (opcion == 2) {
            cout << "\n-- LIBERAR BLOQUE (POP) --" << endl;
            liberarMemoria(pila);

        } else if (opcion == 3) {
            cout << "\n-- ESTADO DE LA MEMORIA --" << endl;
            mostrarPila(pila);
        }

        if (opcion != 0) pausar();

    } while (opcion != 0);
}

// ============================================================
//  MENU PRINCIPAL - REQ-F09
// ============================================================
int main() {
    ListaProcesos lista;
    ColaPrioridad cola;
    PilaMemoria   pila;

    int opcion;
    do {
        limpiarPantalla();
        cout << "========================================" << endl;
        cout << "   SISTEMA DE GESTION DE PROCESOS" << endl;
        cout << "   Simulador de SO | Estructura de Datos" << endl;
        cout << "   Universidad Continental  |  2026" << endl;
        cout << "========================================" << endl;
        cout << "1. Gestor de Procesos  (Lista Enlazada)" << endl;
        cout << "2. Planificador de CPU (Cola Prioridad)" << endl;
        cout << "3. Gestor de Memoria   (Pila Dinamica)" << endl;
        cout << "4. Ver resumen del sistema" << endl;
        cout << "0. Salir" << endl;
        cout << "========================================" << endl;
        opcion = leerEntero("Opcion: ");

        switch (opcion) {
            case 1:
                menuGestorProcesos(lista, cola, pila);
                break;
            case 2:
                menuPlanificadorCPU(lista, cola);
                break;
            case 3:
                menuGestorMemoria(pila);
                break;
            case 4:
                limpiarPantalla();
                cout << "\n=== RESUMEN DEL SISTEMA ===" << endl;
                cout << "\n> PROCESOS REGISTRADOS:" << endl;
                mostrarProcesos(lista);
                cout << "\n> COLA DE EJECUCION (CPU):" << endl;
                mostrarCola(cola);
                cout << "\n> MEMORIA RAM SIMULADA:" << endl;
                mostrarPila(pila);
                pausar();
                break;
            case 0:
                cout << "Cerrando el simulador..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
                pausar();
        }

    } while (opcion != 0);

    // Liberar toda la memoria dinamica al cerrar (REQ-NF03)

    // Liberar lista enlazada
    NodoProceso* pAux = lista.inicio;
    while (pAux != NULL) {
        NodoProceso* temp = pAux;
        pAux = pAux->siguiente;
        delete temp;
    }

    // Liberar cola de prioridad
    NodoCola* cAux = cola.frente;
    while (cAux != NULL) {
        NodoCola* temp = cAux;
        cAux = cAux->siguiente;
        delete temp;
    }

    // Liberar pila de memoria
    NodoPila* mAux = pila.tope;
    while (mAux != NULL) {
        NodoPila* temp = mAux;
        mAux = mAux->anterior;
        delete temp;
    }

    return 0;
}
