#include <iostream>
#include <string>
//CunyasLanasca Geanpiero Andre
//Vilchez Aquino Andy Jeison
//TORRES PATILLA XIOMARA YAMILE 
using namespace std;

// ==========================================
// 1. ESTRUCTURA LISTA (Inventario)
// ==========================================
struct NodoMedicamento {
    int id;
    string nombre;
    NodoMedicamento* siguiente;
    
    // Constructor para compatibilidad con C++98
    NodoMedicamento(int _id, string _nombre, NodoMedicamento* _siguiente) {
        id = _id;
        nombre = _nombre;
        siguiente = _siguiente;
    }
};

class ListaInventario {
private:
    NodoMedicamento* cabeza;
public:
    ListaInventario() { cabeza = NULL; }

    bool estaVacia() { return cabeza == NULL; }

    void insertarPrincipio(int id, string nombre) {
        NodoMedicamento* nuevo = new NodoMedicamento(id, nombre, cabeza);
        cabeza = nuevo;
        cout << "Medicamento insertado al principio.\n";
    }

    void insertarFinal(int id, string nombre) {
        NodoMedicamento* nuevo = new NodoMedicamento(id, nombre, NULL);
        if (estaVacia()) {
            cabeza = nuevo;
        } else {
            NodoMedicamento* temp = cabeza;
            while (temp->siguiente != NULL) temp = temp->siguiente;
            temp->siguiente = nuevo;
        }
        cout << "Medicamento insertado al final.\n";
    }

    void eliminarPrimerNodo() {
        if (estaVacia()) { cout << "Lista vacia.\n"; return; }
        NodoMedicamento* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        cout << "Primer medicamento eliminado.\n";
    }

    void eliminarUltimoNodo() {
        if (estaVacia()) { cout << "Lista vacia.\n"; return; }
        if (cabeza->siguiente == NULL) {
            delete cabeza;
            cabeza = NULL;
        } else {
            NodoMedicamento* temp = cabeza;
            while (temp->siguiente->siguiente != NULL) temp = temp->siguiente;
            delete temp->siguiente;
            temp->siguiente = NULL;
        }
        cout << "Ultimo medicamento eliminado.\n";
    }

    void eliminarEspecifico(int id) {
        if (estaVacia()) return;
        if (cabeza->id == id) {
            eliminarPrimerNodo();
            return;
        }
        NodoMedicamento* temp = cabeza;
        while (temp->siguiente != NULL && temp->siguiente->id != id) {
            temp = temp->siguiente;
        }
        if (temp->siguiente != NULL) {
            NodoMedicamento* aBorrar = temp->siguiente;
            temp->siguiente = temp->siguiente->siguiente;
            delete aBorrar;
            cout << "Medicamento ID " << id << " eliminado.\n";
        } else {
            cout << "Medicamento no encontrado.\n";
        }
    }

    void buscarNodo(int id) {
        NodoMedicamento* temp = cabeza;
        while (temp != NULL) {
            if (temp->id == id) {
                cout << "Encontrado: ID " << temp->id << " - " << temp->nombre << "\n";
                return;
            }
            temp = temp->siguiente;
        }
        cout << "No se encontro el medicamento.\n";
    }

    void vaciarLista() {
        while (!estaVacia()) eliminarPrimerNodo();
        cout << "Todos los nodos eliminados.\n";
    }
    
    void mostrar() {
        if (estaVacia()) { cout << "Inventario vacio.\n"; return; }
        NodoMedicamento* temp = cabeza;
        while (temp != NULL) {
            cout << "[ID: " << temp->id << " - " << temp->nombre << "] -> ";
            temp = temp->siguiente;
        }
        cout << "NULL\n";
    }
};

// ==========================================
// 2. ESTRUCTURA PILA (Historial)
// ==========================================
struct NodoHistorial {
    string accion;
    NodoHistorial* siguiente;
    
    // Constructor
    NodoHistorial(string _accion, NodoHistorial* _siguiente) {
        accion = _accion;
        siguiente = _siguiente;
    }
};

class PilaHistorial {
private:
    NodoHistorial* tope;
    int tamano;
public:
    PilaHistorial() { tope = NULL; tamano = 0; }

    bool estaVacia() { return tope == NULL; }

    void insertarSuperior(string accion) {
        NodoHistorial* nuevo = new NodoHistorial(accion, tope);
        tope = nuevo;
        tamano++;
        cout << "Accion registrada en el historial.\n";
    }

    void eliminarSuperior() {
        if (estaVacia()) { cout << "Pila vacia.\n"; return; }
        NodoHistorial* temp = tope;
        tope = tope->siguiente;
        delete temp;
        tamano--;
        cout << "Ultima accion eliminada del historial.\n";
    }

    void verSuperior() {
        if (estaVacia()) { cout << "Pila vacia.\n"; return; }
        cout << "Ultima accion: " << tope->accion << "\n";
    }

    void mostrarTamano() {
        cout << "Tamano de la pila: " << tamano << "\n";
    }

    void mostrarTodos() {
        if (estaVacia()) { cout << "Historial vacio.\n"; return; }
        NodoHistorial* temp = tope;
        cout << "--- Historial de Acciones (Pila) ---\n";
        while (temp != NULL) {
            cout << temp->accion << "\n";
            temp = temp->siguiente;
        }
    }

    void vaciarPila() {
        while (!estaVacia()) eliminarSuperior();
        cout << "Historial borrado.\n";
    }
};

// ==========================================
// 3. ESTRUCTURA COLA (Atencion de Clientes)
// ==========================================
struct NodoCliente {
    string nombre;
    NodoCliente* siguiente;
    
    // Constructor
    NodoCliente(string _nombre, NodoCliente* _siguiente) {
        nombre = _nombre;
        siguiente = _siguiente;
    }
};

class ColaAtencion {
private:
    NodoCliente* frente;
    NodoCliente* finalCola;
    int tamano;
public:
    ColaAtencion() { frente = NULL; finalCola = NULL; tamano = 0; }

    bool estaVacia() { return frente == NULL; }

    void insertarFinal(string nombre) {
        NodoCliente* nuevo = new NodoCliente(nombre, NULL);
        if (estaVacia()) {
            frente = nuevo;
            finalCola = nuevo;
        } else {
            finalCola->siguiente = nuevo;
            finalCola = nuevo;
        }
        tamano++;
        cout << "Cliente " << nombre << " agregado a la cola.\n";
    }

    void eliminarPrimero() {
        if (estaVacia()) { cout << "Cola vacia.\n"; return; }
        NodoCliente* temp = frente;
        frente = frente->siguiente;
        if (frente == NULL) finalCola = NULL;
        delete temp;
        tamano--;
        cout << "Cliente atendido (eliminado de la cola).\n";
    }

    void mostrarPrimero() {
        if (estaVacia()) { cout << "Cola vacia.\n"; return; }
        cout << "Siguiente cliente a atender: " << frente->nombre << "\n";
    }

    void mostrarTamano() {
        cout << "Clientes en espera: " << tamano << "\n";
    }

    void imprimirElementos() {
        if (estaVacia()) { cout << "No hay clientes en espera.\n"; return; }
        NodoCliente* temp = frente;
        cout << "--- Fila de Espera ---\n";
        while (temp != NULL) {
            cout << temp->nombre << " -> ";
            temp = temp->siguiente;
        }
        cout << "FIN\n";
    }

    void vaciarCola() {
        while (!estaVacia()) eliminarPrimero();
        cout << "Todos los clientes fueron eliminados de la cola.\n";
    }
};

// ==========================================
// MENÚ PRINCIPAL
// ==========================================
void menu() {
    ListaInventario inventario;
    PilaHistorial historial;
    ColaAtencion atencion;
    int opcionPrincipal, subOpcion, id;
    string nombre;

    do {
        cout << "\n========== SISTEMA DE FARMACIA ==========\n";
        cout << "1. Gestionar Inventario (LISTAS)\n";
        cout << "2. Historial de Acciones (PILAS)\n";
        cout << "3. Atencion al Cliente (COLAS)\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcionPrincipal;

        switch (opcionPrincipal) {
            case 1: // MENU LISTAS
                do {
                    cout << "\n--- INVENTARIO (LISTAS) ---\n";
                    cout << "1. Insertar al principio\n2. Insertar al final\n3. Eliminar primer nodo\n";
                    cout << "4. Eliminar ultimo nodo\n5. Eliminar nodo en especifico\n6. Buscar nodo\n";
                    cout << "7. Verificar si esta vacia\n8. Eliminar todos los nodos\n9. Mostrar inventario\n0. Volver\n";
                    cout << "Opcion: ";
                    cin >> subOpcion;
                    switch (subOpcion) {
                        case 1: cout<<"ID: "; cin>>id; cout<<"Nombre: "; cin>>nombre; inventario.insertarPrincipio(id, nombre); break;
                        case 2: cout<<"ID: "; cin>>id; cout<<"Nombre: "; cin>>nombre; inventario.insertarFinal(id, nombre); break;
                        case 3: inventario.eliminarPrimerNodo(); break;
                        case 4: inventario.eliminarUltimoNodo(); break;
                        case 5: cout<<"ID a eliminar: "; cin>>id; inventario.eliminarEspecifico(id); break;
                        case 6: cout<<"ID a buscar: "; cin>>id; inventario.buscarNodo(id); break;
                        case 7: cout << (inventario.estaVacia() ? "La lista esta vacia.\n" : "La lista NO esta vacia.\n"); break;
                        case 8: inventario.vaciarLista(); break;
                        case 9: inventario.mostrar(); break;
                    }
                } while (subOpcion != 0);
                break;

            case 2: // MENU PILAS
                do {
                    cout << "\n--- HISTORIAL (PILAS) ---\n";
                    cout << "1. Insertar (Push)\n2. Eliminar (Pop)\n3. Ver superior (Peek)\n";
                    cout << "4. Verificar si esta vacia\n5. Mostrar tamano\n6. Mostrar todos\n";
                    cout << "7. Eliminar todos\n0. Volver\n";
                    cout << "Opcion: ";
                    cin >> subOpcion;
                    switch (subOpcion) {
                        case 1: cout<<"Accion: "; cin>>nombre; historial.insertarSuperior(nombre); break;
                        case 2: historial.eliminarSuperior(); break;
                        case 3: historial.verSuperior(); break;
                        case 4: cout << (historial.estaVacia() ? "La pila esta vacia.\n" : "La pila NO esta vacia.\n"); break;
                        case 5: historial.mostrarTamano(); break;
                        case 6: historial.mostrarTodos(); break;
                        case 7: historial.vaciarPila(); break;
                    }
                } while (subOpcion != 0);
                break;

            case 3: // MENU COLAS
                do {
                    cout << "\n--- ATENCION (COLAS) ---\n";
                    cout << "1. Insertar al final (Enqueue)\n2. Eliminar primero (Dequeue)\n3. Mostrar primero\n";
                    cout << "4. Verificar si esta vacia\n5. Imprimir elementos\n6. Mostrar tamano\n";
                    cout << "7. Eliminar todos\n0. Volver\n";
                    cout << "Opcion: ";
                    cin >> subOpcion;
                    switch (subOpcion) {
                        case 1: cout<<"Nombre del cliente: "; cin>>nombre; atencion.insertarFinal(nombre); break;
                        case 2: atencion.eliminarPrimero(); break;
                        case 3: atencion.mostrarPrimero(); break;
                        case 4: cout << (atencion.estaVacia() ? "La cola esta vacia.\n" : "La cola NO esta vacia.\n"); break;
                        case 5: atencion.imprimirElementos(); break;
                        case 6: atencion.mostrarTamano(); break;
                        case 7: atencion.vaciarCola(); break;
                    }
                } while (subOpcion != 0);
                break;
        }
    } while (opcionPrincipal != 4);
}

int main() {
    menu();
    return 0;
}
